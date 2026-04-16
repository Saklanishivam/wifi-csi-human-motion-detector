# Detection Tuning Guide

The detector uses variance of recent CSI amplitude values.

## Main Setting

In RX firmware:

```cpp
static constexpr float DETECTION_THRESHOLD = 18.0f;
```

## If It Always Says NO_HUMAN

Lower the threshold:

```cpp
static constexpr float DETECTION_THRESHOLD = 10.0f;
```

If still weak, try:

```cpp
static constexpr float DETECTION_THRESHOLD = 6.0f;
```

## If It Always Says HUMAN

Raise the threshold:

```cpp
static constexpr float DETECTION_THRESHOLD = 25.0f;
```

If still noisy, try:

```cpp
static constexpr float DETECTION_THRESHOLD = 35.0f;
```

## Moving Average Window

Current value:

```cpp
static constexpr size_t MOVING_WINDOW = 20;
```

Recommended changes:

- use `10` for faster response
- use `20` for balanced detection
- use `30` for smoother output

## Sample Interval

Current value:

```cpp
static constexpr uint32_t SAMPLE_INTERVAL_MS = 25;
```

Recommended changes:

- use `25` for fast updates
- use `40` for smoother serial output
- use `60` for lower-noise detection

## Good Calibration Method

1. Keep room empty and still for 20 seconds.
2. Watch the `var` value in Serial Monitor.
3. Walk between TX and RX.
4. Watch the new `var` value.
5. Set threshold between the empty-room variance and movement variance.

Example:

```text
empty room variance: 4 to 8
human motion variance: 20 to 40
good threshold: 14 to 18
```
