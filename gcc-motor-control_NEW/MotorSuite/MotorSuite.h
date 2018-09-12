#ifndef MotorSuite_h
#define MotorSuite_h
#include "../RoboClaw/RoboClaw.h"
#include "../JoystickSuite/JoystickSuite.h"
#include <SoftwareSerial.h>

class MotorSuite{
  public:

  MotorSuite();
  void driveMotors(RoboClaw& roboclaw1,RoboClaw& roboclaw2,JoystickSuite& joystick);
  void get_battery_status(RoboClaw& roboclaw1,RoboClaw& roboclaw2);

  //Roboclaw Address
  #define address 0x80

  // **********
  // DEBUG MODE
  // **********  

  bool debugMode = false;
  
  unsigned int mc1_batt ;
  unsigned int mc2_batt ;
  unsigned int mc3_batt ;     //Checking battery for MC3, specifically needed for the arm
  
  volatile bool batteryOK ;            // battery status is OK flag
  
};
#endif // MOTORSUITE_H
