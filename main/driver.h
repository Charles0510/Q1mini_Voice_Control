#ifndef DRIVER_H
#define DRIVER_H

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// Function to map angle to PWM pulse width for PCA9685
uint16_t angleToPulse(int angle) {
    return map(angle, 0, 180, SERVO_MIN, SERVO_MAX);
}

// Function to set the servo angle on a specific PCA9685 channel
void setServoAngle(Adafruit_PWMServoDriver &pca9685, int channel, int angle) {
    uint16_t pulse = angleToPulse(angle);
    pca9685.setPWM(channel, 0, pulse); // Set PWM pulse for the servo
}

// Initialize the PCA9685 object (driver)
Adafruit_PWMServoDriver pca9685 = Adafruit_PWMServoDriver(0x7F); // Address of the PCA9685 board

// Servo parameters
#define SERVO_MIN 100     // Minimum pulse length count (for 0 degrees)
#define SERVO_MAX 500     // Maximum pulse length count (for 180 degrees)

// Define the channels for 8 servos
int servoChannels[] = {2, 3, 4, 5, 10, 11, 12, 13}; // Channels 0 to 7


#endif