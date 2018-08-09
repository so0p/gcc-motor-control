#ifndef JoystickSuite_h
#define JoystickSuite_h
#include <SoftwareSerial.h>

class JoystickSuite{
  public:

  //********************************
  //     Constructors and Function Prototypes
  //********************************
  
  JoystickSuite(int rx,int tx);
  
  void getJoystick();
  void show_joystick_inputs();
  void set_goal_speed();
  void parse_xbee_byte();
    
  // *******************************
  //    Constant Parameter Definitions
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
  
  byte drive_mode ; //= SLOW;    // indicates which driving profile is currently used
  bool hillMode ; //= true;      // maintain velocity of 0 (ie: brake if not driving)
  
  //DRIVE_PARAMS param[ROVER_SPEED_SETTINGS];  // LUT for driving parameters <--- OBSOLETE
  
  unsigned long last_loop_time ; //= 0;
  //JOYSTICK_CMD jscmd;                  // current joystick command <--- OBSOLETE
  unsigned long joystick_command_count ; //= 0;         // count of commands from joystick
  
  //COMMAND_FROM_THING_TO_MC CMDS_TO_MC; <--- OBSOLETE
  
  // current and goal speeds for each side
  
  
  int rover_cur_spd_lt  ; //= 0;                 // current left motor speed for Rover
  int rover_cur_spd_rt  ; //= 0;                 // current right motor speed for Rover
  int rover_goal_spd_lt ; //= 0;                 // left motor goal speed for Rover
  int rover_goal_spd_rt ; //= 0;                 // right motor goal speed for Rover 
  int arm_cur_spd_m1  ; //= 0;                 // current motor1 speed for Arm
  int arm_cur_spd_m2  ; //= 0;                 // current motor2 speed for Arm
  int arm_cur_spd_m3  ; //= 0;                 // current motor3 speed for Arm
  int arm_cur_spd_m4  ; //= 0;                 // current motor4 speed for Arm
  int arm_cur_spd_m5  ; //= 0;                 // current motor5 speed for Arm
  int arm_cur_spd_m6  ; //= 0;                 // current motor6 speed for Arm
  int arm_goal_spd_m1 ; //= 0;                 // motor1 goal speed for Arm
  int arm_goal_spd_m2 ; //= 0;                 // motor2 goal speed for Arm
  int arm_goal_spd_m3 ; //= 0;                 // motor3 goal speed for Arm
  int arm_goal_spd_m4 ; //= 0;                 // motor4 goal speed for Arm
  int arm_goal_spd_m5 ; //= 0;                 // motor5 goal speed for Arm
  int arm_goal_spd_m6 ; //= 0;                 // motor6 goal speed for Arm
  
  byte tm1638_keys  ; //= 0;               // push button inputs from TM1638
  
  bool eStop ; //= false;                  // emergency stop flag
  
  unsigned int mc1_batt ; //= 250; //0;
  unsigned int mc2_batt ; //= 250; //0;
  unsigned int mc3_batt ; //= 250; //Checking battery for MC3, specifically needed for the arm
  
  bool batteryOK ; //= true;               // battery status is OK flag
  
  // delete if not being used....
  //bool megaSpeed ; //= 0;
  //int velocity ; //= FAST_VELOCITY;
  
  // ***********************
  //       XBEE Variables
  // ***********************
  
  SoftwareSerial *serialPtr; // Ptr for acccessing members of the SoftwareSerial object
  
  bool xbee_on ; //= false;
  int xbee_counter ; //= 0;
  long lastTimeJSMessageRecieved;

  // ***********************
  //       Joystick Command Variables
  // ***********************

  bool linkActive;      // is the JS link active?
  bool up, dn, lt, rt;  // Up, Down, Left, Right
  bool r1, r2, l1, l2;  // Right1, Right2, Left1, Left2
  bool b1, b2, b3, b4;  // Button1, Button2, Button3, Button4
  bool st, se;          // Start, Select
  // TODO: add analogs

  // ***********************
  //       Thing Variables
  // ***********************
  
  bool thing_on =false;
  int direction;
  int motorNum;
  int duration;
  long lastTimeThingMessageRecieved;
  
  // ************************
  //        Drive Parameters
  // ************************
  
  typedef struct {
    int vel;
    int ramp;
    int thr;
    int diag;
  }DRIVE_PARAMS;

  DRIVE_PARAMS drive_parameters[ROVER_SPEED_SETTINGS];  // LUT for driving parameters, this is an array containing instances of the struct
  
  // ************************
  //    DANGER
  // ************************
  
  bool dangerOverride ; //= false;                        // Danger Override
  int dangerCounter ; //= 0;
  bool dangerFront ; //= false;                           // Rover Danger Variables
  bool dangerBack ; //= false;                            // Rover Danger Variables
  bool FrontRight ; //= false;
  bool FrontLeft ; //= false;
  bool BackRight ; //= false;
  bool BackLeft ; //= false;
  
  int buttonStateFront_R ; //= 0;
  int buttonStateFront_L ; //= 0;
  int buttonStateBack_R ; //= 0;
  int buttonStateBack_L ; //= 0;
  
  // Arm Danger Variables
  
  bool dangerM1 ; //= false;
  bool dangerM2 ; //= false;
  bool dangerM3 ; //= false;
  bool dangerM4 ; //= false;
  bool dangerM5 ; //= false;
  bool dangerM6 ; //= false;   
  
  // Arm Motor Current Theshold
  
  int M1_thresh ; //= 1;
  int M2_thresh ; //= 2;
  int M3_thresh ; //= 3;
  int M4_thresh ; //= 4;
  int M5_thresh ; //= 5;
  int M6_thresh ; //= 6;              // undertermined values; requires testing
  
  // Pin Locations for Rover
  int BUTTON_PIN_FRONT_R ; //= 43;  
  int BUTTON_PIN_FRONT_L ; //= 41;
  int BUTTON_PIN_BACK_R ; //= 47;
  int BUTTON_PIN_BACK_L ; //= 45;

  private:

  SoftwareSerial XBee; // RX, TX (this is confusing and wrong, probably!)
};
#endif // JoystickSuite_h

