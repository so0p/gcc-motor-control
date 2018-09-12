#ifndef DangerSuite_h
#define DangerSuite_h
#include "JoystickSuite.h"

class DangerSuite{
  public:

  DangerSuite();
  void getDanger(JoystickSuite& joystick);

  // **********
  // DEBUG MODE
  // ********** 

  bool debugMode = false;                // Enabled/Disables debug messages
  
  // ************************
  // DANGER
  // ************************

  bool dangerOverride ;                        // Danger Override

  int dangerCounter ;
  bool dangerFront ;                           // Rover Danger Variables
  bool dangerBack ;                           // Rover Danger Variables
  bool FrontRight ;
  bool FrontLeft ;
  bool BackRight ;
  bool BackLeft ;
  
  int buttonStateFront_R ;
  int buttonStateFront_L ;
  int buttonStateBack_R ;
  int buttonStateBack_L ;
  
  // Arm Danger Variables
  
  bool dangerM1 ;
  bool dangerM2 ;
  bool dangerM3 ;
  bool dangerM4 ;
  bool dangerM5 ;
  bool dangerM6 ;   
  
  // Arm Motor Current Theshold
  
  int M1_thresh ;
  int M2_thresh ;
  int M3_thresh ;
  int M4_thresh ;
  int M5_thresh ;
  int M6_thresh ;              // undertermined values; requires testing
  
  // Pin Locations for Rover
  const byte BUTTON_PIN_FRONT_R = 47;  
  const byte BUTTON_PIN_FRONT_L = 45;
  const byte BUTTON_PIN_BACK_R = 43; 
  const byte BUTTON_PIN_BACK_L = 41; 

  // ************************
  //       TELEMETRY
  // ************************
  
  uint8_t currentM1 ;
  uint8_t currentM2 ;
  uint8_t currentM3 ;
  uint8_t currentM4 ;
  uint8_t currentM5 ;
  uint8_t currentM6 ;
};
#endif // DANGERSUITE_H
