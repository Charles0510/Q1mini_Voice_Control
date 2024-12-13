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
      : driverInstance(driver),
        verticalServoChannel(legVerticalServo), 
        horizontalServoChannel(legHorizontalServo), 
        driverInstance(driver) {
    }

    // lift the leg up
    void lift(){ 
      setServoAngle(driverInstance, legVerticalServo, 180);
    }

    // lower the leg down
    void lower(){ 
      setServoAngle(driverInstance, legVerticalServo, 120);
    }

    // lower the leg to lowest position, used to sit
    void lowest(){ 

    }

    // move the leg to specific angle horizontally
    void move(int angle){ 
      setServoAngle(driver, legHorizontalServo, angle);
    }

    // lift the leg up and move, then put down
    void lift_move(int angle){
      setServoAngle(driverInstance, legVerticalServo, 180);
      setServoAngle(driver, legHorizontalServo, angle);
      etServoAngle(driverInstance, legVerticalServo, 120);
    }
}

// below maybe defind in driver.h
// Adafruit_PWMServoDriver pca9685 = Adafruit_PWMServoDriver(0x7F); // Address of the PCA9685 board

Leg leg0(0, servoChannels[0], servoChannels[1], &pca9685); // initial legs
Leg leg1(1, servoChannels[2], servoChannels[3], &pca9685);
Leg leg2(2, servoChannels[4], servoChannels[5], &pca9685);
Leg leg3(3, servoChannels[6], servoChannels[7], &pca9685);

// leg0    leg1
//     body   
// leg3    leg2

void step_forward(){
  // Phase A
  leg1.lift_move(120);
  leg2.lift_move(120);

  // Phase B
  leg0.move(120);
  leg1.move(90);
  leg2.move(90);
  leg3.move(120);

  // Phase C
  leg0.lift_move(60);
  leg3.lift_move(60);

  // Phase D
  leg0.move(90);
  leg1.move(60);
  leg2.move(60);
  leg3.move(90);

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
  leg0.lift_move(90);
  leg1.lift_move(90);
  leg2.lift_move(90);
  leg3.lift_move(90);

  leg0.lowest();
  leg1.lowest();
  leg2.lowest();
  leg3.lowest();

}

void reset(){
  leg0.lift_move(90);
  leg1.lift_move(90);
  leg2.lift_move(90);
  leg3.lift_move(90);
}

#endif