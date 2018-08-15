#include "Arduino.h"
#include "DangerSuite.h"
#include "JoystickSuite.h"

DangerSuite::DangerSuite(){
  
  // ************************
  // Global Variables
  // ************************
  
  bool dangerOverride = false;                        // Danger Override
  int dangerCounter = 0;
  bool dangerFront = false;                           // Rover Danger Variables
  bool dangerBack = false;                            // Rover Danger Variables
  bool FrontRight = false;
  bool FrontLeft = false;
  bool BackRight = false;
  bool BackLeft = false;
  
  int buttonStateFront_R = 0;
  int buttonStateFront_L = 0;
  int buttonStateBack_R = 0;
  int buttonStateBack_L = 0;
  
  // Arm Danger Variables
  
  bool dangerM1 = false;
  bool dangerM2 = false;
  bool dangerM3 = false;
  bool dangerM4 = false;
  bool dangerM5 = false;
  bool dangerM6 = false;   
  
  // Arm Motor Current Theshold
  
  int M1_thresh = 1;
  int M2_thresh = 2;
  int M3_thresh = 3;
  int M4_thresh = 4;
  int M5_thresh = 5;
  int M6_thresh = 6;              // undertermined values; requires testing
  
  // Pin Locations for Rover
  int BUTTON_PIN_FRONT_R = 43;  
  int BUTTON_PIN_FRONT_L = 41;
  int BUTTON_PIN_BACK_R = 47;
  int BUTTON_PIN_BACK_L = 45;
  
  // ************************
  // Setup
  // ************************
  
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
  Serial.println("getDANGER");
  
  if( dangerOverride == true){
    Serial.println("DANGER OVERRIDE TRUE");
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

    if(joystick.mode == MODE_ROVER){
          Serial.println("DANGER MODE_ROVER");
          buttonStateFront_R = digitalRead(BUTTON_PIN_FRONT_R);
          buttonStateBack_R = digitalRead(BUTTON_PIN_BACK_R);
          buttonStateFront_L = digitalRead(BUTTON_PIN_FRONT_L);
          buttonStateBack_L = digitalRead(BUTTON_PIN_BACK_L);         

          if (buttonStateFront_R == LOW || buttonStateFront_L == LOW){
            Serial.println("DANGER FRONT TRUE");
            dangerFront = true;
          }
          else {
            Serial.println("DANGER FRONT FALSE");
            dangerFront = false;
          }
          if (buttonStateBack_R == LOW  || buttonStateBack_L == LOW){
            Serial.println("DANGER BACK TRUE");
            dangerBack = true;
          }
          else{
            Serial.println("DANGER BACK FALSE");
            dangerBack = false;
          }
    }
    else if(joystick.mode == MODE_ARM){
      Serial.println("DANGER MODE_ARM");
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
