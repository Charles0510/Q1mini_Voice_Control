#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// Initialize the PCA9685 object
Adafruit_PWMServoDriver pca9685 = Adafruit_PWMServoDriver(0x7F); // Address of the PCA9685 board

// Servo parameters
#define SERVO_MIN 100     // Minimum pulse length count (for 0 degrees)
#define SERVO_MAX 500     // Maximum pulse length count (for 180 degrees)

// Define the channels for 8 servos
int servoChannels[] = {2, 3, 12, 13, 10, 11, 4, 5}; // Channels 0 to 7

int l0h= servoChannels[0];
int l0v= servoChannels[1];
int l1h= servoChannels[2];
int l1v= servoChannels[3];
int l2h= servoChannels[4];
int l2v= servoChannels[5];
int l3h= servoChannels[6];
int l3v= servoChannels[7];

// Function to map angle to PWM pulse width for PCA9685
uint16_t angleToPulse(int angle) {
    return map(angle, 0, 180, SERVO_MIN, SERVO_MAX);
}

// Function to set the servo angle on a specific PCA9685 channel
void setServoAngle(Adafruit_PWMServoDriver &pca9685, int channel, int angle) {
    uint16_t pulse = angleToPulse(angle);
    pca9685.setPWM(channel, 0, pulse); // Set PWM pulse for the servo
}

void setup() {
    Serial.begin('COM6', 9600);
    Serial.println("PCA9685 Servo Test with 8 Servos");

    // Configure I2C pins explicitly for Nano BLE (A6=SCL, A7=SDA)
    Wire.begin(A6);
    Wire.begin(A7);

    // Initialize the PCA9685 board
    pca9685.begin();
    pca9685.setPWMFreq(50); // Servos run at ~50 Hz



    
}

void loop() {
    // Loop through all 8 servos and move them sequentially
  setServoAngle(pca9685, l0h, 90);
  delay(1000);

  setServoAngle(pca9685, l1h, 90);
  delay(1000);

  setServoAngle(pca9685, l2h, 60);
  delay(1000);

  setServoAngle(pca9685, l3h, 30);
  delay(1000);


}
