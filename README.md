
# Self-Stabilizing Mobile Inverted Pendulum (MiP)

This BeagleBone Blue project contains the code and documentation for the Self-Stabilizing Mobile Inverted Pendulum.  This was created for UCSD MAE 144: Embedded Controls and Robotics.

## Problem 1: Stabilizing Body Angle

The goal of this problem is to develop a model `G1(s)` as a transfer function from the normalized duty cycle `u` of the motors to the angle `θ` of the MiP body in radians. A stabilizing controller `D1(s)` is designed to keep the MiP upright.

### Files
- `Stabilizing_Body_Angle.m`: MATLAB code to develop the transfer function, plot the angle of the body, design a stabilizing controller, and create a Bode plot.

## Problem 2: Stabilizing Wheel Position

This problem involves designing a second controller, `D2`, to stabilize the wheel position `φ`. The controller is designed using the successive loop closure method.

### Files
- `Stabilizing_Wheel_Position.m`: MATLAB code to model `G2(s)`, design `D2(s)`, and plot the step responses.

## Problem 3: Software Implementation

The software implementation involves modifying the complementary filter code to estimate the angle `φ` and implementing the difference equations for the controllers `D1(z)` and `D2(z)`.

### Files
- `main.c`: C code to implement the complementary filter, IMU interrupt function, and outer loop thread.

## How to Run

1. Run `Stabilizing_Body_Angle.m` and `Stabilizing_Wheel_Position.m` in MATLAB to generate the required plots and transfer functions.
2. Compile and run `main.c` on your BeagleBone or similar hardware to implement the balancing controllers.

## Hardware Used

- BeagleBone Blue.
