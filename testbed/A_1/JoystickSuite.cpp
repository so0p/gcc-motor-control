#include "Arduino.h"
#include "JoystickSuite.h"


JoystickSuite::JoystickSuite(int rx,int tx):XBee(rx,tx){

  // ***********************
  //       XBEE
  // ***********************

  // XBee's DOUT (TX) is connected to pin 2 (Arduino's Software RX)
  // XBee's DIN (RX) is connected to pin 3 (Arduino's Software TX)
  // on xbee shield, place jumper on XB_TX_11 and DIGITAL, and
  // XB_RX_10 and DIGITAL

  serialPtr = &XBee;
  
  // Set up both ports at 9600 baud. This value is most important
  // for the XBee. Make sure the baud rate matches the config
  // setting of your XBee.

  XBee.begin(9600);
  
  bool xbee_on = false;
  int xbee_counter = 0;
  long lastTimeJSMessageRecieved;

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
  //       Joystick Commmand Variables
  // ***********************

  linkActive = true; // override this value until we check for it
  up = false;
  dn = false;
  lt = false;
  rt = false;
  b1 = false;
  b2 = false;
  b3 = false;
  b4 = false;
  r1 = false;
  r2 = false;
  l1 = false;
  l2 = false;
  st = false;
  se = false;

  // populate the elements of the DRIVE_PARAM struct array 
  drive_parameters[SLOW].vel       = ROVER_VEL_SLOW;
  drive_parameters[SLOW].ramp      = ROVER_RAMP_RATE_SLOW;
  drive_parameters[SLOW].thr       = ROVER_THR_SLOW;
  drive_parameters[SLOW].diag      = DIAG_OFFSET_SLOW;
  drive_parameters[FAST].vel       = ROVER_VEL_FAST;
  drive_parameters[FAST].ramp      = ROVER_RAMP_RATE_FAST;
  drive_parameters[FAST].thr       = ROVER_THR_FAST;
  drive_parameters[FAST].diag      = DIAG_OFFSET_FAST;  
  drive_parameters[ARM].vel        = ARM_VEL;
  drive_parameters[ARM].ramp       = ARM_RAMP_RATE;
  drive_parameters[ARM].thr        = ARM_THR;
  
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

  // ************************
  //    Setup
  // ************************
  
  //Initalizing Bumper Pins
  pinMode(BUTTON_PIN_FRONT_R, INPUT_PULLUP);
  pinMode(BUTTON_PIN_FRONT_L, INPUT_PULLUP);
  pinMode(BUTTON_PIN_BACK_R, INPUT_PULLUP);
  pinMode(BUTTON_PIN_BACK_L, INPUT_PULLUP);

  //get the time
  lastTimeJSMessageRecieved = millis();
  lastTimeThingMessageRecieved = millis();
};

// **************************************************************
//     Joystick functions
// **************************************************************

void JoystickSuite::getJoystick() {

  //if xbee is not avaiable and less than 100
  //increase count
  //if xbee is avaiable, set count to 0
  //if xbee count is greater than 100
  //xbee is off
  //Serial.println("No Pointer"); //DEBUG
  
  if (serialPtr->available()>0){ // softwareSerial object
    Serial.println("XBEE ON");
    lastTimeJSMessageRecieved = millis();
    xbee_on = true;
    xbee_counter =0;
    static bool last_b4 = false;  // last state of B4 button
    //****Rover Mode******
    // RoverID is 0, ArmID is 1
    if (mode==MODE_ROVER){
      Serial.println("MODE ROVER "); // Debug statement
      // read from XBee stream. parse and update joystick command variables
      byte bytes_to_read = serialPtr->available();
      
      if(bytes_to_read >= 2) {
        for(byte i = 0; i< bytes_to_read; i++) {
          parse_xbee_byte();
          joystick_command_count++;          
        }

        //check if danger override button is pushed or not!
        if(b2) {
          dangerOverride = true;
          Serial.println("b2 "); // Debug statement
        }
        else{
          dangerOverride = false;
        }
      }
      //set the drive mode slow of fast.
      //While you hold down r2 FAST mode is engaged
      if(r2) {
        drive_mode = FAST;
        Serial.println("r2 FAST "); // Debug statement 
      }
      else {
        drive_mode = SLOW;
        Serial.println("r2 SLOW "); // Debug statement
      }

      set_goal_speed();
    }
    // check if button 4 state has changed...
    // b4 tells us to toggle the hold mode
    bool cur_b4 = b4;
    if(!last_b4 && cur_b4) {
      Serial.println("B4 PRESSED dahksjdaksjdahskdashjdahkjsdhasjdkahsjdajkshdkashh"); // Debug statement
      hillMode = !hillMode;
    }
    last_b4 = cur_b4; // set lastmode and current mode equal

    //Arm Mode
    if (mode==MODE_ARM){
      Serial.println("MODE ARM "); // Debug statement
      //if robotID=1 then arm mode
      drive_mode = ARM;
      hillMode= true;
      
      // update the goal speeds
      set_goal_speed();
      show_joystick_inputs();
    }
  }
  else{
    Serial.println("XBEE OFF");
    xbee_on=false;
    if(millis() - lastTimeJSMessageRecieved > 1000){
      rover_goal_spd_lt = 0;
      rover_goal_spd_rt = 0;  
    }
    
  }
}    
      // also check if this link is alive... if TBD millis have gone
      // since last msg, notify main program
      // every TBD cycles, send a HB message to joystick
      // process_joystick_inputs()

// XBee packet definition from joystick
// =====================================
// pack buttonState[] into xbeeMsg
// xbeeMsg[0] : { 0 , DN , L , R , R1 , R2 , L1 , L2 }
// xbeeMsg[1] : { 1 , UP , B1 , B2 , B3 , B4 , ST , SE } 
//

// read one byte from XBee stream and parse its content
void JoystickSuite::parse_xbee_byte() {
  byte xb = serialPtr->read();
  if(xb > 0x7f) {  // we're reading Msg 1
    se = (xb & B00000001);
    st = (xb & B00000010);
    b4 = (xb & B00000100);
    b3 = (xb & B00001000);
    b2 = (xb & B00010000);
    b1 = (xb & B00100000);
    up = (xb & B01000000);
  }
  else {           // we're reading Msg 0
    l2 = (xb & B00000001);
    l1 = (xb & B00000010);
    r2 = (xb & B00000100);
    r1 = (xb & B00001000);
    rt = (xb & B00010000);
    lt = (xb & B00100000);
    dn = (xb & B01000000);    
  }
} // parse_xbee_byte()

//*****Start of setting goal speeds******************************
// set our goal speeds based on the joystick inputs
void JoystickSuite::set_goal_speed() { 

//****Rover Mode**************************************************
      
    if (mode==MODE_ROVER){
      //rover if robotID=0
      if(up && lt) {
        Serial.println("UP LT "); // Debug statement
        rover_goal_spd_lt = drive_parameters[drive_mode].vel - drive_parameters[drive_mode].diag;
        rover_goal_spd_rt = drive_parameters[drive_mode].vel + drive_parameters[drive_mode].diag;    
      }
      else if(up && rt) {
        Serial.println("UP RT "); // Debug statement
        rover_goal_spd_lt = drive_parameters[drive_mode].vel + drive_parameters[drive_mode].diag;
        rover_goal_spd_rt = drive_parameters[drive_mode].vel - drive_parameters[drive_mode].diag;    
      }
      else if(dn && lt) {
        Serial.println("DN LT "); // Debug statement
        rover_goal_spd_lt = -drive_parameters[drive_mode].vel + drive_parameters[drive_mode].diag;
        rover_goal_spd_rt = -drive_parameters[drive_mode].vel - drive_parameters[drive_mode].diag;    
      }
      else if(dn && rt) {
        Serial.println("DN RT "); // Debug statement
        rover_goal_spd_lt = -drive_parameters[drive_mode].vel - drive_parameters[drive_mode].diag;
        rover_goal_spd_rt = -drive_parameters[drive_mode].vel + drive_parameters[drive_mode].diag;    
      }  
      else if(up) {
        Serial.println("UP "); // Debug statement
        rover_goal_spd_lt = drive_parameters[drive_mode].vel;
        rover_goal_spd_rt = drive_parameters[drive_mode].vel;
      }
      else if(dn) {
        Serial.println("DN "); // Debug statement
        rover_goal_spd_lt = -drive_parameters[drive_mode].vel;
        rover_goal_spd_rt = -drive_parameters[drive_mode].vel;
      }
      else if(lt) {
        Serial.println("LT "); // Debug statement
        rover_goal_spd_lt = -drive_parameters[drive_mode].vel;
        rover_goal_spd_rt = drive_parameters[drive_mode].vel;    
      }
      else if(rt) {
        Serial.println("RT "); // Debug statement
        rover_goal_spd_lt = drive_parameters[drive_mode].vel;
        rover_goal_spd_rt = -drive_parameters[drive_mode].vel;    
      }
      else {
        rover_goal_spd_lt = 0;
        rover_goal_spd_rt = 0;     
      }
      
    }

    //*****for arm ***************************************************
    if (mode==MODE_ARM){
      //if robotID=1 then arm mode

      //GRIP:!!!!!!!!!!!!!!!!!!
      // Grip open 
      if(b1) {
        Serial.println("bL "); // Debug statement
        arm_goal_spd_m6 = drive_parameters[drive_mode].vel;
      }

      // Grip close
      if(b3) {
        Serial.println("b3 "); // Debug statement
        arm_goal_spd_m6 = -drive_parameters[drive_mode].vel;
      }
      //WRIST:
      // Wrist right
      if(rt) {
        Serial.println("RT "); // Debug statement
        arm_goal_spd_m4 = drive_parameters[drive_mode].vel;
        arm_goal_spd_m5 = drive_parameters[drive_mode].vel;
      }
      // Wrist left
      if(lt) {
        Serial.println("LT "); // Debug statement
        arm_goal_spd_m4 = -drive_parameters[drive_mode].vel;
        arm_goal_spd_m5 = -drive_parameters[drive_mode].vel;
      }
      //Wrist up
      if(up) {
        Serial.println("UP "); // Debug statement
        arm_goal_spd_m4 = -drive_parameters[drive_mode].vel;
        arm_goal_spd_m5 = drive_parameters[drive_mode].vel;
      }
      //Wrist down
      if(dn) {
        Serial.println("DN "); // Debug statement
        arm_goal_spd_m4 = drive_parameters[drive_mode].vel;
        arm_goal_spd_m5 = -drive_parameters[drive_mode].vel;
      }

      //ELBOW:
      //Elbow up
      if(l1) {
        Serial.println("L1 "); // Debug statement
        arm_goal_spd_m3 = -drive_parameters[drive_mode].vel;
      }
      //Elbow down
      if(l2) {
        Serial.println("L2 "); // Debug statement
        arm_goal_spd_m3 = drive_parameters[drive_mode].vel;
      }

      //SHOULDER:
      //Shoulder up
      if(r1) {
        Serial.println("R1 "); // Debug statement
        arm_goal_spd_m2 = drive_parameters[drive_mode].vel;
      }
      //Shoulder down
      if(r2) {
        Serial.println("R2 "); // Debug statement
        arm_goal_spd_m2 = -drive_parameters[drive_mode].vel;
      }

      //BASE:
      //Base left
      if(b2) {
        Serial.println("B2 "); // Debug statement
        arm_goal_spd_m1 = -drive_parameters[drive_mode].vel;
      }
      //Base right
      if(b4) {
        Serial.println("B4 "); // Debug statement
        arm_goal_spd_m1 = drive_parameters[drive_mode].vel;
      }
    }
    if(serialPtr->available()==0 && xbee_counter<100){
      xbee_counter++;
    }
    else if(serialPtr->available()==0 && xbee_counter>100){
      xbee_on=false;
    }
} // end set_goal_speed()

// debug code for showing joystick inputs
void JoystickSuite::show_joystick_inputs() {
  Serial.println("SHOW JOYSTICK "); // Debug statement
  
  if(up) Serial.print("UP ");
  if(dn) Serial.print("DN ");
  if(lt) Serial.print("LT ");
  if(rt) Serial.print("RT ");
  if(r1) Serial.print("R1 ");
  if(r2) Serial.print("R2 ");
  if(l1) Serial.print("L1 ");
  if(l2) Serial.print("L2 ");
  if(b1) Serial.print("B1 ");
  if(b2) Serial.print("B2 ");
  if(b3) Serial.print("B3 ");
  if(b4) Serial.print("B4 ");
  if(st) Serial.print("ST ");
  if(se) Serial.print("SE ");
  //  Serial.print(jscmd_cnt, DEC);
  Serial.println();   
} // show_joystick_inputs()

