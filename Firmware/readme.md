# Firmware

## Hardware

- Arduino Pro Micro
- 2 micro servos
- FlySky receiver

## Motion Modes

The firmware currently supports:

1. Sine-wave wing motion
2. Triangular-wave wing motion (to be added)

## Uploading

1. Open `bionic_butterfly.ino` in Arduino IDE.
2. Select Arduino pro micro.
3. Select the appropriate processor/bootloader.
4. Select the correct COM/serial port.
5. Upload.

## Configuration

Motion parameters can be adjusted in the source code.

These include parameters such as:

- Servo center
- Servo amplitude
- Motion frequency
- Receiver input range
- Servo limits
