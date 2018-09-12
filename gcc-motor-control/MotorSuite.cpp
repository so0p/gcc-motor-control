#include "Arduino.h"
#include "MotorSuite.h"

MotorSuite::MotorSuite(){

  // **********
  // DEBUG MODE
  // ********** 

  debugMode = false;                // Enabled/Disables debug messages
  
  mc1_batt = 250; //0;
  mc2_batt = 250; //0;
  mc3_batt = 250; //Checking battery for MC3, specifically needed for the arm
    
  batteryOK = true;               // battery status is OK flag

};

// **************************************************************
//     Drive Motors & get Roboclaw Status
// **************************************************************

// drive with velocity command
void MotorSuite::driveMotors(RoboClaw& roboclaw1,RoboClaw& roboclaw2,JoystickSuite& joystick){
    
    //Code By Avery

    //Identify if it is ROVER (0) or ARM (1)

  if (joystick.mode==MODE_ROVER) {
    if(debugMode == true)
        Serial.println(F("driveMotors() MODE ROVER"));
        
    if(batteryOK && mc1_batt>1 && mc2_batt>1) {  // IF ALL OK...
      if(debugMode == true)
        Serial.println(F("ALL OK"));
      if(joystick.rover_cur_spd_lt != 0 || joystick.rover_cur_spd_rt != 0) {
        roboclaw1.SpeedM1(address,joystick.rover_cur_spd_lt);  
        roboclaw1.SpeedM2(address,joystick.rover_cur_spd_lt);
        roboclaw2.SpeedM1(address,joystick.rover_cur_spd_rt);
        roboclaw2.SpeedM2(address,joystick.rover_cur_spd_rt); 
      }

      else if(joystick.hillMode) {
        if(debugMode == true)
          Serial.println(F("driveMotors HILLMODE TRUE"));
        roboclaw1.SpeedM1(address,0);
        roboclaw1.SpeedM2(address,0);
        roboclaw2.SpeedM1(address,0);
        roboclaw2.SpeedM2(address,0);      
        // drive to velocity 0
      }
      else if(!joystick.hillMode) {
        if(debugMode == true)
          Serial.println(F("driveMotors HILLMODE FALSE"));
        roboclaw1.BackwardM1(address,0); //Stop Motor1 
        roboclaw1.BackwardM2(address,0); //Stop Motor2 
        roboclaw2.BackwardM1(address,0); //Stop Motor1 
        roboclaw2.BackwardM2(address,0); //Stop Motor2      
        // don't drive the motors anymore... 
      }
    } // if everything is OK

    else if(!batteryOK) {
      if(debugMode == true)
        Serial.print(F("NOT OK"));
        Serial.println(batteryOK);
      roboclaw1.BackwardM1(address,0); //Stop Motor1 
      roboclaw1.BackwardM2(address,0); //Stop Motor2 
      roboclaw2.BackwardM1(address,0); //Stop Motor1 
      roboclaw2.BackwardM2(address,0); //Stop Motor2      
    }
  } // drive_motors(0)
//  else if (mode==MODE_ARM) {
//
//    if(batteryOK && mc1_batt>1 && mc2_batt>1 && mc3_batt>1) {  // IF ALL OK... 
//      if(arm_cur_spd_m1 != 0 || arm_cur_spd_m2 != 0 || arm_cur_spd_m3 != 0 || arm_cur_spd_m4 != 0 || arm_cur_spd_m5 != 0 || arm_cur_spd_m6 != 0) {
//        roboclaw1.SpeedM1(address,arm_cur_spd_m1);
//        roboclaw1.SpeedM2(address,arm_cur_spd_m2);
//        roboclaw2.SpeedM1(address,arm_cur_spd_m3);
//        roboclaw2.SpeedM2(address,arm_cur_spd_m4); 
//        roboclaw3.SpeedM1(address,arm_cur_spd_m5);
//        roboclaw3.SpeedM2(address,arm_cur_spd_m6);
//      }   // drive_motors (1)
//    } 
//  }
}

// get roboclaw's battery levels
// if roboclaw is not responsive, set voltage to 0. this will
// indicate that RC communication is dead
void MotorSuite::get_battery_status(RoboClaw& roboclaw1,RoboClaw& roboclaw2) {
  
  bool rc1_alive = false;
  bool rc2_alive = false;  

  mc1_batt = roboclaw1.ReadMainBatteryVoltage(address, &rc1_alive);
  mc2_batt = roboclaw2.ReadMainBatteryVoltage(address, &rc2_alive);  

  // if battery level gets low, completely stop driving
  if(mc1_batt<227 || mc2_batt<226) {
    batteryOK = false;
  }
 
  if(!rc1_alive) {
    mc1_batt = 0;
  }
  if(!rc2_alive) {
    mc2_batt = 0;
  }
    
} // get_roboclaw_status()