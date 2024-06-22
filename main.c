
// Problem 3: Software Implementation

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>

// Constants
#define SAMPLE_RATE 200
#define OUTER_SAMPLE_RATE 20

// Global variables
double theta, phi;
double u1, u2;
double prev_u1[3] = {0, 0, 0}, prev_y1[3] = {0, 0, 0};
double prev_u2[3] = {0, 0, 0}, prev_y2[3] = {0, 0, 0};

// Complementary filter for angle estimate theta
void complementary_filter(double gyro, double accel, double dt) {
    const double alpha = 0.98;
    theta = alpha * (theta + gyro * dt) + (1 - alpha) * accel;
}

// Difference equation for D1(z)
double controller_D1(double error) {
    double a1 = 1.0, a2 = -0.5; // Example coefficients
    double b0 = 0.1, b1 = 0.2, b2 = 0.1;
    double output = b0 * error + b1 * prev_u1[1] + b2 * prev_u1[2] - a1 * prev_y1[1] - a2 * prev_y1[2];
    prev_u1[2] = prev_u1[1];
    prev_u1[1] = error;
    prev_y1[2] = prev_y1[1];
    prev_y1[1] = output;
    return output;
}

// Difference equation for D2(z)
double controller_D2(double error) {
    double a1 = 1.0, a2 = -0.5; // Example coefficients
    double b0 = 0.1, b1 = 0.2, b2 = 0.1;
    double output = b0 * error + b1 * prev_u2[1] + b2 * prev_u2[2] - a1 * prev_y2[1] - a2 * prev_y2[2];
    prev_u2[2] = prev_u2[1];
    prev_u2[1] = error;
    prev_y2[2] = prev_y2[1];
    prev_y2[1] = output;
    return output;
}

// IMU interrupt function at 200Hz
void *imu_interrupt(void *arg) {
    while (1) {
        double gyro = 0.0; // Read gyro value
        double accel = 0.0; // Read accel value
        double dt = 1.0 / SAMPLE_RATE;

        complementary_filter(gyro, accel, dt);
        double error1 = -theta; // Assuming reference angle theta is 0
        u1 = controller_D1(error1);

        // Drive motors with u1 (to be implemented)
        usleep(1000000 / SAMPLE_RATE);
    }
    return NULL;
}

// Outer loop thread at 20Hz
void *outer_loop(void *arg) {
    while (1) {
        double error2 = -phi; // Assuming reference angle phi is 0
        u2 = controller_D2(error2);

        // Update inner loop reference angle theta
        double new_theta = u2;
        // To be implemented: adjust theta for inner loop

        usleep(1000000 / OUTER_SAMPLE_RATE);
    }
    return NULL;
}

int main() {
    pthread_t imu_thread, outer_thread;

    // Create threads
    pthread_create(&imu_thread, NULL, imu_interrupt, NULL);
    pthread_create(&outer_thread, NULL, outer_loop, NULL);

    // Wait for threads to finish
    pthread_join(imu_thread, NULL);
    pthread_join(outer_thread, NULL);

    return 0;
}
