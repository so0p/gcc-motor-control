#ifndef JoystickSuite_h
#define JoystickSuite_h
#include <SoftwareSerial.h>
#include <avr/pgmspace.h>
class DangerSuite; // Forward Declaration to prevent cyclical dependencies

class JoystickSuite{
  public:

  // ********************************
  // Constructors and Member Function
  // ********************************
  
  JoystickSuite(int rx,int tx); // User provides desired data-pins for SoftwareSerial object to use
  
  void getJoystick(DangerSuite& danger);
  void show_joystick_inputs();
  void set_goal_speed();
  void parse_xbee_byte();
    
  // *******************************
  // Constant Parameter Definitions
  // *******************************
  
  // MODE SECTION
  
  #define MODE_ARM 1
  #define MODE_ROVER 2
  
  // SPEED SECTION
  
  #define ROVER_VEL_SLOW             400   // velocity preset
  #define ROVER_VEL_FAST            1200   // velocity preset
  #define ROVER_RAMP_RATE_SLOW        30   // the ramp rate for motor speed enveloping
  #define ROVER_RAMP_RATE_FAST       120   // the ramp rate for motor speed enveloping
  #define ROVER_THR_SLOW              20   // goal threshold
  #define ROVER_THR_FAST              60   // goal threshold
  
  #define ARM_SPEED_SETTINGS           1    // number of speed settings
  #define ARM_VEL                    100   // velocity preset FOR ARM
  #define ARM_RAMP_RATE               10   // the ramp rate for motor speed enveloping
  #define ARM_THR                     10   // goal threshold
  
  #define ROVER_SPEED_SETTINGS         2   // number of speed settings
  
  #define DIAG_OFFSET_RATE       2   // ????
  #define DIAG_OFFSET_SLOW          (ROVER_VEL_SLOW/DIAG_OFFSET_RATE)
  #define DIAG_OFFSET_FAST          (ROVER_VEL_FAST/DIAG_OFFSET_RATE)
  
  // define the name for the drive modes
  #define SLOW      0
  #define FAST      1
  #define ARM       2
  
  #define LOOP_PERIOD_MS 20   // 50Hz Loop

  // ************************
  //      GLOBAL VARIABLES
  // ************************
  
  
  //HardCode the Mode of Rover
  int mode ; //= MODE_ROVER;
  
  byte drive_mode ; // indicates which driving profile is currently used
  bool hillMode ; // maintain velocity of 0 (ie: brake if not driving)
  
  unsigned long last_loop_time ;
  
  unsigned long joystick_command_count ;         // count of commands from joystick
  
  // current and goal speeds for each side
  
  
  int rover_cur_spd_lt  ;                 // current left motor speed for Rover
  int rover_cur_spd_rt  ;                 // current right motor speed for Rover
  int rover_goal_spd_lt ;                 // left motor goal speed for Rover
  int rover_goal_spd_rt ;                 // right motor goal speed for Rover 
  int arm_cur_spd_m1  ;                 // current motor1 speed for Arm
  int arm_cur_spd_m2  ;                 // current motor2 speed for Arm
  int arm_cur_spd_m3  ;                 // current motor3 speed for Arm
  int arm_cur_spd_m4  ;                 // current motor4 speed for Arm
  int arm_cur_spd_m5  ;                 // current motor5 speed for Arm
  int arm_cur_spd_m6  ;                 // current motor6 speed for Arm
  int arm_goal_spd_m1 ;                 // motor1 goal speed for Arm
  int arm_goal_spd_m2 ;                 // motor2 goal speed for Arm
  int arm_goal_spd_m3 ;                 // motor3 goal speed for Arm
  int arm_goal_spd_m4 ;                 // motor4 goal speed for Arm
  int arm_goal_spd_m5 ;                 // motor5 goal speed for Arm
  int arm_goal_spd_m6 ;                 // motor6 goal speed for Arm
  
  byte tm1638_keys  ;               // push button inputs from TM1638
  
  bool eStop ;                  // emergency stop flag
  
  /*unsigned int mc1_batt ; //= 250; //0; <-- Moved to MotorSuite.h
  unsigned int mc2_batt ; //= 250; //0;
  unsigned int mc3_batt ; //= 250; //Checking battery for MC3, specifically needed for the arm
  
  bool batteryOK ; //= true;               // battery status is OK flag*/
  
  // delete if not being used....
  //bool megaSpeed ; //= 0;
  //int velocity ; //= FAST_VELOCITY;
  
  // **************
  // XBEE Variables
  // **************

  SoftwareSerial XBee;
  // used for the the xbee controller, data pins are submitted by the user using joystickSuite constructor
  SoftwareSerial *serialPtr; // Ptr for acccessing members of the SoftwareSerial object
  
  bool xbee_on ; // getJoystick checks this value, it should be passed to getThing which checks it too
  int xbee_counter ; //
  long lastTimeJSMessageRecieved;

  // **************************
  // Joystick Command Variables //Formerly a struct
  // **************************

  bool linkActive;      // is the JS link active?
  bool up, dn, lt, rt;  // Up, Down, Left, Right
  bool r1, r2, l1, l2;  // Right1, Right2, Left1, Left2
  bool b1, b2, b3, b4;  // Button1, Button2, Button3, Button4
  bool st, se;          // Start, Select
  // TODO: add analogs

  /*// *********************
  // Thing Struct           <--- ThingSuite.h
  // ***********************
  
  bool thing_on =false; // getThing checks this value
  int direction; //  accessed by setThingSpeed & checked by getThing
  int motorNum; // accessed by getThing
  int duration;*/ 
  
  // ***************
  // Thing Variables        
  // ***************
  
  //long lastTimeThingMessageRecieved; // used in getJoystick()
  
  // **********************
  // Drive Parameter Struct
  // **********************
  
  typedef struct {
    int vel;
    int ramp;
    int thr;
    int diag;
  }DRIVE_PARAMS;

  DRIVE_PARAMS drive_parameters[ROVER_SPEED_SETTINGS];  // LUT for driving parameters, this is an array containing instances of the struct
  
  /*// ************************
  // DANGER                    <-- Moved to DangerSuite.h
  // ************************
  
  bool dangerOverride ; //                        // Danger Override
  int dangerCounter ; //
  bool dangerFront ; //                           // Rover Danger Variables
  bool dangerBack ; //                            // Rover Danger Variables
  bool FrontRight ; //
  bool FrontLeft ; //
  bool BackRight ; //
  bool BackLeft ; //
  
  int buttonStateFront_R ; //
  int buttonStateFront_L ; //
  int buttonStateBack_R ; //
  int buttonStateBack_L ; //
  
  // Arm Danger Variables
  
  bool dangerM1 ; //
  bool dangerM2 ; //
  bool dangerM3 ; //
  bool dangerM4 ; //
  bool dangerM5 ; //
  bool dangerM6 ; //   
  
  // Arm Motor Current Theshold
  
  int M1_thresh ; //
  int M2_thresh ; //
  int M3_thresh ; //
  int M4_thresh ; //
  int M5_thresh ; //
  int M6_thresh ; //              undertermined values; requires testing
  
  // Pin Locations for Rover <-- Moved to DangerSuite.h
  int BUTTON_PIN_FRONT_R ; // 
  int BUTTON_PIN_FRONT_L ; //
  int BUTTON_PIN_BACK_R ; //
  int BUTTON_PIN_BACK_L ; //*/
};
#endif // JOYSTICKSUITE_H

