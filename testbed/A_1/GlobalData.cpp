/*#include "Arduino.h"
#include "GlobalData.h"

GlobalData::GlobalData (){
  
  // ************************
  //      GLOBAL VARIABLES
  // ************************
  
  //HardCode the Mode of Rover
  mode = MODE_ROVER;
  
  byte drive_mode = SLOW;    // indicates which driving profile is currently used
  bool hillMode = true;      // maintain velocity of 0 (ie: brake if not driving)
  
  //DRIVE_PARAMS param[ROVER_SPEED_SETTINGS];  // LUT for driving parameters
  
  unsigned long last_loop_time = 0;
  //JOYSTICK_CMD jscmd;                  // current joystick command
  unsigned long joystick_command_count = 0;         // count of commands from joystick
  
  //COMMAND_FROM_THING_TO_MC CMDS_TO_MC;
  
  // current and goal speeds for each side
  
  
  int rover_cur_spd_lt  = 0;               // current left motor speed for Rover
  int rover_cur_spd_rt  = 0;               // current right motor speed for Rover
  int rover_goal_spd_lt = 0;               // left motor goal speed for Rover
  int rover_goal_spd_rt = 0;               // right motor goal speed for Rover 
  int arm_cur_spd_m1  = 0;                 // current motor1 speed for Arm
  int arm_cur_spd_m2  = 0;                 // current motor2 speed for Arm
  int arm_cur_spd_m3  = 0;                 // current motor3 speed for Arm
  int arm_cur_spd_m4  = 0;                 // current motor4 speed for Arm
  int arm_cur_spd_m5  = 0;                 // current motor5 speed for Arm
  int arm_cur_spd_m6  = 0;                 // current motor6 speed for Arm
  int arm_goal_spd_m1 = 0;                 // motor1 goal speed for Arm
  int arm_goal_spd_m2 = 0;                 // motor2 goal speed for Arm
  int arm_goal_spd_m3 = 0;                 // motor3 goal speed for Arm
  int arm_goal_spd_m4 = 0;                 // motor4 goal speed for Arm
  int arm_goal_spd_m5 = 0;                 // motor5 goal speed for Arm
  int arm_goal_spd_m6 = 0;                 // motor6 goal speed for Arm
  
  byte tm1638_keys  = 0;               // push button inputs from TM1638
  
  bool eStop = false;                  // emergency stop flag
  
  unsigned int mc1_batt = 250; //0;
  unsigned int mc2_batt = 250; //0;
  unsigned int mc3_batt = 250; //Checking battery for MC3, specifically needed for the arm
  
  bool batteryOK = true;               // battery status is OK flag
  
  // delete if not being used....
  //bool megaSpeed = 0;
  //int velocity = FAST_VELOCITY;

  // ***********************
  //       XBEE
  // ***********************
  
  // XBee's DOUT (TX) is connected to pin 2 (Arduino's Software RX)
  // XBee's DIN (RX) is connected to pin 3 (Arduino's Software TX)
  // on xbee shield, place jumper on XB_TX_11 and DIGITAL, and
  // XB_RX_10 and DIGITAL
  
  bool xbee_on = false;
  int xbee_counter = 0;
  long lastTimeJSMessageRecieved;
  
  // ************************
  //    DANGER
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
}*/


