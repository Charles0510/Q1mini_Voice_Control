This is a project for MF2025 Project Work in Mechatronics

Materials:
 - Two Arduino BLE 33  
 - two VTC5A rechargeable batteries   
 - 3D printer - 3D printed body  
 - 8 Servomotors  
 - Motor driver  
 - TinyML Arduino shield  
 - Other cables and screws to make the connections possible   
  
The Q1 mini quadruped robot is controlled by voice command  

Arduino project explain: 
 - micro_speech_final: run on the voice detection Arduino board, which detect the voice input, send result to kinematics Arduion board
 - Movement: run on the kinematics Arduino board, receive the result from voice detection board, and control the robot to perform some moving patterns
 - test_pca9685_Q1: test the pca9685 shield, and use to fine tune the servo motors
 - Adafruit_BusIO-master.zip and Adafruit-PWM-Servo-Driver-Library-master.zip: necessary Arduino libraries, include to your Arduino IDE
 - train_micro_speech_model_final.ipynb: training the voice detection model


Author: Mingcheng Kou, Kritarth Mishra, Daniel Heydari
