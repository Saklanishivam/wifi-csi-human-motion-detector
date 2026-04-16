import argparse
import collections
import threading

import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import serial


def parse_args():
    parser = argparse.ArgumentParser(description="Plot ESP32 CSI amplitude in real time.")
    parser.add_argument("--port", required=True, help="Serial port, for example COM6")
    parser.add_argument("--baud", type=int, default=115200, help="Serial baud rate")
    parser.add_argument("--points", type=int, default=200, help="Visible samples")
    return parser.parse_args()


def main():
    args = parse_args()
    ser = serial.Serial(args.port, args.baud, timeout=1)

    raw_vals = collections.deque(maxlen=args.points)
    avg_vals = collections.deque(maxlen=args.points)
    var_vals = collections.deque(maxlen=args.points)
    state_vals = collections.deque(maxlen=args.points)
    lock = threading.Lock()

    def reader():
        while True:
            line = ser.readline().decode("utf-8", errors="ignore").strip()
            if not line.startswith("CSI,"):
                continue

            parts = line.split(",")
            if len(parts) != 5:
                continue

            try:
                raw_amp = float(parts[1])
                avg_amp = float(parts[2])
                variance = float(parts[3])
                state = 1.0 if parts[4] == "HUMAN" else 0.0
            except ValueError:
                continue

            with lock:
                raw_vals.append(raw_amp)
                avg_vals.append(avg_amp)
                var_vals.append(variance)
                state_vals.append(state)

    thread = threading.Thread(target=reader, daemon=True)
    thread.start()

    fig, (ax1, ax2) = plt.subplots(2, 1, figsize=(10, 7), sharex=True)
    raw_line, = ax1.plot([], [], label="raw amp")
    avg_line, = ax1.plot([], [], label="moving avg")
    var_line, = ax2.plot([], [], label="variance")
    state_line, = ax2.plot([], [], label="human state")

    ax1.set_title("ESP32 CSI amplitude")
    ax1.set_ylabel("Amplitude")
    ax1.grid(True)
    ax1.legend(loc="upper right")

    ax2.set_ylabel("Variance / State")
    ax2.set_xlabel("Sample")
    ax2.grid(True)
    ax2.legend(loc="upper right")

    def update(_frame):
        with lock:
            raw = list(raw_vals)
            avg = list(avg_vals)
            var = list(var_vals)
            state = list(state_vals)

        x = list(range(len(raw)))
        raw_line.set_data(x, raw)
        avg_line.set_data(x, avg)
        var_line.set_data(x, var)
        state_line.set_data(x, state)

        ax1.relim()
        ax1.autoscale_view()
        ax2.relim()
        ax2.autoscale_view()
        return raw_line, avg_line, var_line, state_line

    anim = FuncAnimation(fig, update, interval=100, cache_frame_data=False)
    _ = anim
    plt.tight_layout()
    plt.show()


if __name__ == "__main__":
    main()
