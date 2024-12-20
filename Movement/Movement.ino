#include "driver.h"
#include "kinematics.h"
#include "Arduino.h"


int D2_value;
int D3_value;
int D2_value_old;
int D3_value_old;

volatile bool leanForwardFlag = false; // Flags for state changes
volatile bool layDownFlag = false;

bool currentStateLean = false;  // Current state of Lean action
bool currentStateLay = false;   // Current state of Lay action


void setup() {
  Serial.begin('COM6', 9600);
  Serial.println("PCA9685 Servo Test with 8 Servos");

  // Configure I2C pins explicitly for Nano BLE (A6=SCL, A7=SDA)
  Wire.begin(A6);
  Wire.begin(A7);

  // Initialize the PCA9685 board
  pca9685.begin();
  pca9685.setPWMFreq(50); // Servos run at ~50 Hz

  pinMode(D2, INPUT_PULLUP);
  pinMode(D3, INPUT_PULLUP);
  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);


    // Attach interrupts
  attachInterrupt(digitalPinToInterrupt(D2), setLeanForwardFlag, RISING);
  attachInterrupt(digitalPinToInterrupt(D3), setLayDownFlag, RISING);

}

void loop() {
  // Perform Lean Forward action if flag is set and it's not already active
  if (leanForwardFlag && !currentStateLean) {
    leanForwardFlag = false;  // Reset the flag
    currentStateLean = true; // Set the Lean action as active
    currentStateLay = false; // Ensure Lay action is inactive
    performLeanForwardAction();
  }

  // Perform Lay Down action if flag is set and it's not already active
  if (layDownFlag && !currentStateLay) {
    layDownFlag = false;  // Reset the flag
    currentStateLay = true; // Set the Lay action as active
    currentStateLean = false; // Ensure Lean action is inactive
    performLayDownAction();
  }
}

// Interrupt Service Routines (ISR)
void setLeanForwardFlag() {
  leanForwardFlag = true; // Set flag for Lean Forward action
}

void setLayDownFlag() {
  layDownFlag = true; // Set flag for Lay Down action
}

// Perform Lean Forward action
void performLeanForwardAction() {
  digitalWrite(LEDG, LOW);  
  digitalWrite(LEDR, HIGH); 
  lean_forward();           // Perform the action
  delay(2000);              // Optional delay to allow the action to complete

}

// Perform Lay Down action
void performLayDownAction() {
  digitalWrite(LEDR, LOW);  
  digitalWrite(LEDG, HIGH); 
  lay_down();               // Perform the action
  delay(2000);              // Optional delay to allow the action to complete

}
