#include <driver.h>
#include <kinematics.h>



void setup() {
  Serial.begin(9600);
  Serial.println("PCA9685 Servo Test with 8 Servos");

  // Configure I2C pins explicitly for Nano BLE (A6=SCL, A7=SDA)
  // Wire.begin(A6, A7);

  // Initialize the PCA9685 board
  pca9685.begin();
  pca9685.setPWMFreq(50); // Servos run at ~50 Hz

  



}

void loop() {
  // put your main code here, to run repeatedly:

}
