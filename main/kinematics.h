#ifndef KINEMATICS_H
#define KINEMATICS_H

#include "driver.h"

float delay_time = 0.15; // delay time after move one servo

class Leg {
  private: 
    int num;
    int verticalServoChannel;
    int horizontalServoChannel;
    Adafruit_PWMServoDriver* driverInstance; // pointer to driver board instance

  public: 
    // Constructor
    Leg(int legNum, int legVerticalServo, int legHorizontalServo, Adafruit_PWMServoDriver* driver)
      : num(legNum),
        driverInstance(driver),
        verticalServoChannel(legVerticalServo), 
        horizontalServoChannel(legHorizontalServo) {
    }

    // lift the leg up
    void lift(){ 
      if (num == 0 || num == 3){
        setServoAngle(*driverInstance, verticalServoChannel, 120);
      } else {
        setServoAngle(*driverInstance, verticalServoChannel,  60);
      }
    }

    // lower the leg down
    void lower(){ 
      if (num == 0 || num == 3){
        setServoAngle(*driverInstance, verticalServoChannel, 150);
        Serial.print(num);
      } else {
        setServoAngle(*driverInstance, verticalServoChannel, 30);
        Serial.print(num);
      }
      Serial.print(num);
      
    }
 
    // lower the leg to lowest position, used to sit
    void lowest(){ 
      if (num == 0 || num == 3){
        setServoAngle(*driverInstance, verticalServoChannel, 180);
      } else {
        setServoAngle(*driverInstance, verticalServoChannel, 0);
      }
    }

    // move the leg to specific angle horizontally
    void move(int angle){ 
      setServoAngle(*driverInstance, horizontalServoChannel, angle);
    }

    // lift the leg up and move, then put down
    void lift_move(int angle){
      lift();
      delay(100);
      setServoAngle(*driverInstance, horizontalServoChannel, angle);
      delay(100);
      lower();
      delay(100);
    }

    void lift_high(){
      if (num == 0 || num == 3){
        setServoAngle(*driverInstance, verticalServoChannel, 180);
      } else {
        setServoAngle(*driverInstance, verticalServoChannel,  0);
      }
    }
};

// below maybe defind in driver.h
// Adafruit_PWMServoDriver pca9685 = Adafruit_PWMServoDriver(0x7F); // Address of the PCA9685 board

Leg leg0(0, servoChannels[1], servoChannels[0], &pca9685); // initial legs
Leg leg1(1, servoChannels[3], servoChannels[2], &pca9685);
Leg leg2(2, servoChannels[5], servoChannels[4], &pca9685);
Leg leg3(3, servoChannels[7], servoChannels[6], &pca9685);

// leg0    leg1
//     body   
// leg3    leg2

void step_forward(){
  // Phase A
  leg1.lift_move(135);
  delay(100);
  leg2.lift_move(75);
  delay(100);

  // Phase B
  leg0.move(75);
  leg1.move(135);
  leg2.move(60);
  leg3.move(120);

  // Phase C
  leg0.lift_move(75);
  delay(100);
  leg3.lift_move(135);
  delay(100);

  // Phase D
  leg0.move(60);
  leg1.move(105);
  leg2.move(45);
  leg3.move(120);


}

void turn_left(){
  // Phase 0
  leg0.lift_move(80);
  leg1.lift_move(60);
  leg2.lift_move(120);
  leg3.lift_move(100);

  // Phase A
  leg1.lift();

  leg1.move(120);
  leg0.move(60);
  leg3.move(80);
  leg2.move(100);

  leg1.lower();

  // Phase B
  leg0.lift();

  leg0.move(120);
  leg3.move(60);
  leg2.move(80);
  leg1.move(100);

  leg0.lower();

  // Phase C
  leg3.lift();

  leg3.move(120);
  leg2.move(60);
  leg1.move(80);
  leg0.move(100);

  leg3.lower();

  // Phase D
  leg2.lift();

  leg2.move(120);
  leg1.move(60);
  leg0.move(80);
  leg3.move(100);

  leg2.lower();

}

void turn_right(){
  // Phase 0
  leg0.lift_move(120);
  leg1.lift_move(100);
  leg2.lift_move(80);
  leg3.lift_move(60);

  // Phase A
  leg0.lift();

  leg0.move(60);
  leg1.move(120);
  leg2.move(100);
  leg3.move(80);

  leg0.lower();

  // Phase B
  leg1.lift();

  leg1.move(60);
  leg2.move(120);
  leg3.move(100);
  leg0.move(80);

  leg1.lower();

  // Phase C
  leg2.lift();

  leg2.move(60);
  leg3.move(120);
  leg0.move(100);
  leg1.move(80);

  leg2.lower();

  // Phase D
  leg3.lift();

  leg3.move(60);
  leg0.move(120);
  leg1.move(100);
  leg2.move(80);

  leg3.lower();
}

void sit_down(){
  leg0.lift_move(60);
  delay(100);
  leg1.lift_move(120);
  delay(100);
  leg2.lift_move(60);
  delay(100);
  leg3.lift_move(120);
  delay(100);

  leg0.lowest();
  leg1.lowest();
  leg2.lowest();
  leg3.lowest();

}

void reset(){
  leg0.lift_move(60);
  //delay(100);
  leg1.lift_move(120);
  //delay(100);
  leg2.lift_move(60);
  //delay(100);
  leg3.lift_move(120);
  //delay(100);
}

#endif