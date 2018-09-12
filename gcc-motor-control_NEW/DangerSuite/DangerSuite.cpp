#include "Arduino.h"
#include "./DangerSuite.h"

DangerSuite::DangerSuite(){

  // **********
  // DEBUG MODE
  // ********** 

  debugMode = false;                             // Enabled/Disables debug messages
  
  // ****************
  // Global Variables
  // ****************
  
  dangerOverride = false;                        // Danger Override
  
  dangerCounter = 0;
  dangerFront = false;                           // Rover Danger Variables
  dangerBack = false;                            // Rover Danger Variables
  FrontRight = false;
  FrontLeft = false;
  BackRight = false;
  BackLeft = false;
  
  buttonStateFront_R = 0;
  buttonStateFront_L = 0;
  buttonStateBack_R = 0;
  buttonStateBack_L = 0;
  
  // Arm Danger Variables
  
  dangerM1 = false;
  dangerM2 = false;
  dangerM3 = false;
  dangerM4 = false;
  dangerM5 = false;
  dangerM6 = false;   
  
  // Arm Motor Current Theshold
  
  M1_thresh = 1;
  M2_thresh = 2;
  M3_thresh = 3;
  M4_thresh = 4;
  M5_thresh = 5;
  M6_thresh = 6;              // undertermined values; requires testing
  
  // *****
  // Setup
  // *****
  
  //Initalizing Bumper Pins
  pinMode(BUTTON_PIN_FRONT_R, INPUT_PULLUP);
  pinMode(BUTTON_PIN_FRONT_L, INPUT_PULLUP);
  pinMode(BUTTON_PIN_BACK_R, INPUT_PULLUP);
  pinMode(BUTTON_PIN_BACK_L, INPUT_PULLUP);
};

// **************************************************************
// Danger Function
// **************************************************************

void DangerSuite::getDanger(JoystickSuite &joystick){
  if( dangerOverride == true){
    if(debugMode == true)
      Serial.println(F("getDanger() OVERRIDE TRUE"));
    dangerM1 = false;
    dangerM2 = false;
    dangerM3 = false;
    dangerM4 = false;
    dangerM5 = false;
    dangerM6 = false;   

    dangerFront = false;
    dangerBack = false;
  }

  else {
    if(debugMode == true)
      Serial.println(F("getDanger() OVERRIDE FALSE"));
    if(joystick.mode == MODE_ROVER){
          if(debugMode == true)
            Serial.println(F("getDanger() MODE_ROVER"));
          buttonStateFront_R = digitalRead(BUTTON_PIN_FRONT_R);
          buttonStateBack_R = digitalRead(BUTTON_PIN_BACK_R);
          buttonStateFront_L = digitalRead(BUTTON_PIN_FRONT_L);
          buttonStateBack_L = digitalRead(BUTTON_PIN_BACK_L);

          if (buttonStateFront_R == LOW || buttonStateFront_L == LOW){
            dangerFront = true;
            if(debugMode == true)
              Serial.println(F("DF: T DB:  "));
          }
          else {
            dangerFront = false;
            if(debugMode == true)
              Serial.println(F("DF: F DB:  "));
          }
          if (buttonStateBack_R == LOW  || buttonStateBack_L == LOW){
            dangerBack = true;
            if(debugMode == true)
              Serial.println(F("DF:   DB:  T"));
          }
          else{
            dangerBack = false;
            if(debugMode == true)
              Serial.println(F("DF:   DB:  F"));
          }
    }
    else if(joystick.mode == MODE_ARM){
      if(debugMode == true)
        Serial.println(F("getDanger() MODE_ARM"));
      if(dangerCounter == 50){
        
//        roboclaw1.ReadCurrents(address, currentM1, currentM2);
//        roboclaw2.ReadCurrents(address, currentM3, currentM4);
//        roboclaw3.ReadCurrents(address, currentM5, currentM6);
        
        if(currentM1 > M1_thresh){
          dangerM1 = true;
        }
        else if(currentM2 > M2_thresh){
          dangerM2 = true;
        }
        else if(currentM3 > M3_thresh){
          dangerM3 = true;
        }
        else if(currentM4 > M4_thresh){
          dangerM4 = true;
        }
        else if(currentM5 > M5_thresh){
          dangerM5 = true;
        }
        else if(currentM6 > M6_thresh){
          dangerM6 = true;
        }
        dangerCounter=0;
      }
      dangerCounter++;         
      }
  }
}