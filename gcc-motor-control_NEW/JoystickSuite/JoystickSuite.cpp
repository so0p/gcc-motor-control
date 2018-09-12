#include "Arduino.h"
#include "../JoystickSuite/JoystickSuite.h"
#include "../DangerSuite/DangerSuite.h"

// rx, tx needed because 4 serial ports already in use, SoftwareSerial object turns two pins into data pins
JoystickSuite::JoystickSuite(int rx,int tx):XBee(rx,tx){ 

  // *****************************
  // Software Serial Object (XBee)
  // *****************************

  // XBee's DOUT (TX) is connected to pin 2 (Arduino's Software RX)
  // XBee's DIN (RX) is connected to pin 3 (Arduino's Software TX)
  // on xbee shield, place jumper on XB_TX_11 and DIGITAL, and
  // XB_RX_10 and DIGITAL

  serialPtr = &XBee;
  
  // Set up both ports at 9600 baud. This value is most important
  // for the XBee. Make sure the baud rate matches the config
  // setting of your XBee.

  XBee.begin(9600);
  
  xbee_on = false;
  xbee_counter = 0;
  lastTimeJSMessageRecieved;

  // **********
  // DEBUG MODE
  // ********** 

  debugMode = false;                // Enabled/Disables debug messages
  
  // ************************
  // GLOBAL VARIABLES
  // ************************
  
  drive_mode = SLOW;    // indicates which driving profile is currently used
  hillMode = true;      // maintain velocity of 0 (ie: brake if not driving)
  
  
  last_loop_time = 0;

  joystick_command_count = 0;         // count of commands from joystick
  
  //COMMAND_FROM_THING_TO_MC CMDS_TO_MC;
  
  // current and goal speeds for each side
  rover_cur_spd_lt  = 0;               // current left motor speed for Rover
  rover_cur_spd_rt  = 0;               // current right motor speed for Rover
  rover_goal_spd_lt = 0;               // left motor goal speed for Rover
  rover_goal_spd_rt = 0;               // right motor goal speed for Rover 
  arm_cur_spd_m1  = 0;                 // current motor1 speed for Arm
  arm_cur_spd_m2  = 0;                 // current motor2 speed for Arm
  arm_cur_spd_m3  = 0;                 // current motor3 speed for Arm
  arm_cur_spd_m4  = 0;                 // current motor4 speed for Arm
  arm_cur_spd_m5  = 0;                 // current motor5 speed for Arm
  arm_cur_spd_m6  = 0;                 // current motor6 speed for Arm
  arm_goal_spd_m1 = 0;                 // motor1 goal speed for Arm
  arm_goal_spd_m2 = 0;                 // motor2 goal speed for Arm
  arm_goal_spd_m3 = 0;                 // motor3 goal speed for Arm
  arm_goal_spd_m4 = 0;                 // motor4 goal speed for Arm
  arm_goal_spd_m5 = 0;                 // motor5 goal speed for Arm
  arm_goal_spd_m6 = 0;                 // motor6 goal speed for Arm
  
  tm1638_keys  = 0;                    // push button inputs from TM1638
  
  eStop = false;                       // emergency stop flag
  
  // delete if not being used....
  // bool megaSpeed = 0;
  // int velocity = FAST_VELOCITY;

  // ***************************
  // Joystick Commmand Variables
  // ***************************

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
  //    Setup
  // ************************

  //get the time
  lastTimeJSMessageRecieved = millis();
  // lastTimeThingMessageRecieved = millis(); //moved to ThingSuite.h
};

// **************************************************************
//                        Joystick Functions
// **************************************************************

void JoystickSuite::getJoystick(DangerSuite &danger) {

  //if xbee is not avaiable and less than 100
  //increase count
  //if xbee is avaiable, set count to 0
  //if xbee count is greater than 100
  //xbee is off
  //Serial.println("No Pointer"); //DEBUG
  
  if (serialPtr->available()>0){ // softwareSerial object
    if(debugMode == true)
      Serial.println(F("getJoystick() XBEE ON"));
    lastTimeJSMessageRecieved = millis();
    xbee_on = true;
    xbee_counter =0;
    static bool last_b4 = false;  // last state of B4 button
    //*****Rover Mode******
    // RoverID is 0, ArmID is 1
    if (mode==MODE_ROVER){
      if(debugMode == true)
        Serial.println(F("MODE ROVER")); // Debug statement
      // read from XBee stream. parse and update joystick command variables
      byte bytes_to_read = serialPtr->available();
      
      if(bytes_to_read >= 2) {
        for(byte i = 0; i< bytes_to_read; i++) {
          parse_xbee_byte();
          joystick_command_count++;          
        }

        //check if danger override button is pushed or not!
        if(b2) {
          danger.dangerOverride = true;
          if(debugMode == true)
            Serial.println(F("b2 OVERRIDE TRUE")); // Debug statement
        }
        else{
          danger.dangerOverride = false;
          if(debugMode == true)
            Serial.println(F("b2 OVERRIDE FALSE")); // Debug statement
        }
      }
      //set the drive mode slow of fast.
      //While you hold down r2 FAST mode is engaged
      if(r2) {
        drive_mode = FAST;
        if(debugMode == true)
          Serial.println(F("r2 FAST")); // Debug statement 
      }
      else {
        drive_mode = SLOW;
        if(debugMode == true)
          Serial.println(F("r2 SLOW")); // Debug statement
      }

      set_goal_speed();
    }
    // check if button 4 state has changed...
    // b4 tells us to toggle the hold mode
    bool cur_b4 = b4;
    if(!last_b4 && cur_b4) {
      if(debugMode == true)
        Serial.println(F("B4 HILLMODE TOGGLE")); // Debug statement
      hillMode = !hillMode;
    }
    last_b4 = cur_b4; // set lastmode and current mode equal

    //Arm Mode
    if (mode==MODE_ARM){
      if(debugMode == true)
        Serial.println(F("MODE ARM")); // Debug statement
      //if robotID=1 then arm mode
      drive_mode = ARM;
      hillMode= true;
      
      // update the goal speeds
      set_goal_speed();
      show_joystick_inputs();
    }
  }
  else{
    if(debugMode == true)
      Serial.println(F("getJoystick() XBEE OFF"));
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
        if(debugMode == true)
          Serial.println(F("UP LT")); // Debug statement
        rover_goal_spd_lt = drive_parameters[drive_mode].vel - drive_parameters[drive_mode].diag;
        rover_goal_spd_rt = drive_parameters[drive_mode].vel + drive_parameters[drive_mode].diag;    
      }
      else if(up && rt) {
        if(debugMode == true)
          Serial.println(F("UP RT")); // Debug statement
        rover_goal_spd_lt = drive_parameters[drive_mode].vel + drive_parameters[drive_mode].diag;
        rover_goal_spd_rt = drive_parameters[drive_mode].vel - drive_parameters[drive_mode].diag;    
      }
      else if(dn && lt) {
        if(debugMode == true)
          Serial.println(F("DN LT")); // Debug statement
        rover_goal_spd_lt = -drive_parameters[drive_mode].vel + drive_parameters[drive_mode].diag;
        rover_goal_spd_rt = -drive_parameters[drive_mode].vel - drive_parameters[drive_mode].diag;    
      }
      else if(dn && rt) {
        if(debugMode == true)
          Serial.println(F("DN RT")); // Debug statement
        rover_goal_spd_lt = -drive_parameters[drive_mode].vel - drive_parameters[drive_mode].diag;
        rover_goal_spd_rt = -drive_parameters[drive_mode].vel + drive_parameters[drive_mode].diag;    
      }  
      else if(up) {
        if(debugMode == true)
          Serial.println(F("UP")); // Debug statement
        rover_goal_spd_lt = drive_parameters[drive_mode].vel;
        rover_goal_spd_rt = drive_parameters[drive_mode].vel;
      }
      else if(dn) {
        if(debugMode == true)
          Serial.println(F("DN")); // Debug statement
        rover_goal_spd_lt = -drive_parameters[drive_mode].vel;
        rover_goal_spd_rt = -drive_parameters[drive_mode].vel;
      }
      else if(lt) {
        if(debugMode == true)
          Serial.println(F("LT ")); // Debug statement
        rover_goal_spd_lt = -drive_parameters[drive_mode].vel;
        rover_goal_spd_rt = drive_parameters[drive_mode].vel;    
      }
      else if(rt) {
        if(debugMode == true)
          Serial.println(F("RT")); // Debug statement
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
        if(debugMode == true)
          Serial.println(F("bL")); // Debug statement
        arm_goal_spd_m6 = drive_parameters[drive_mode].vel;
      }

      // Grip close
      if(b3) {
        if(debugMode == true)
          Serial.println(F("b3")); // Debug statement
        arm_goal_spd_m6 = -drive_parameters[drive_mode].vel;
      }
      //WRIST:
      // Wrist right
      if(rt) {
        if(debugMode == true)
          Serial.println(F("RT")); // Debug statement
        arm_goal_spd_m4 = drive_parameters[drive_mode].vel;
        arm_goal_spd_m5 = drive_parameters[drive_mode].vel;
      }
      // Wrist left
      if(lt) {
        if(debugMode == true)
          Serial.println(F("LT")); // Debug statement
        arm_goal_spd_m4 = -drive_parameters[drive_mode].vel;
        arm_goal_spd_m5 = -drive_parameters[drive_mode].vel;
      }
      //Wrist up
      if(up) {
        if(debugMode == true)
          Serial.println(F("UP")); // Debug statement
        arm_goal_spd_m4 = -drive_parameters[drive_mode].vel;
        arm_goal_spd_m5 = drive_parameters[drive_mode].vel;
      }
      //Wrist down
      if(dn) {
        if(debugMode == true)
          Serial.println(F("DN")); // Debug statement
        arm_goal_spd_m4 = drive_parameters[drive_mode].vel;
        arm_goal_spd_m5 = -drive_parameters[drive_mode].vel;
      }

      //ELBOW:
      //Elbow up
      if(l1) {
        if(debugMode == true)
          Serial.println(F("L1")); // Debug statement
        arm_goal_spd_m3 = -drive_parameters[drive_mode].vel;
      }
      //Elbow down
      if(l2) {
        if(debugMode == true)
          Serial.println(F("L2")); // Debug statement
        arm_goal_spd_m3 = drive_parameters[drive_mode].vel;
      }

      //SHOULDER:
      //Shoulder up
      if(r1) {
        if(debugMode == true)
          Serial.println(F("R1")); // Debug statement
        arm_goal_spd_m2 = drive_parameters[drive_mode].vel;
      }
      //Shoulder down
      if(r2) {
        if(debugMode == true)
          Serial.println(F("R2")); // Debug statement
        arm_goal_spd_m2 = -drive_parameters[drive_mode].vel;
      }

      //BASE:
      //Base left
      if(b2) {
        if(debugMode == true)
          Serial.println(F("B2")); // Debug statement
        arm_goal_spd_m1 = -drive_parameters[drive_mode].vel;
      }
      //Base right
      if(b4) {
        if(debugMode == true)
          Serial.println(F("B4")); // Debug statement
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
  if(debugMode == true)
    Serial.println(F("SHOW JOYSTICK ")); // Debug statement
  
  if(up) Serial.print(F("UP"));
  if(dn) Serial.print(F("DN"));
  if(lt) Serial.print(F("LT"));
  if(rt) Serial.print(F("RT"));
  if(r1) Serial.print(F("R1"));
  if(r2) Serial.print(F("R2"));
  if(l1) Serial.print(F("L1"));
  if(l2) Serial.print(F("L2"));
  if(b1) Serial.print(F("B1"));
  if(b2) Serial.print(F("B2"));
  if(b3) Serial.print(F("B3"));
  if(b4) Serial.print(F("B4"));
  if(st) Serial.print(F("ST"));
  if(se) Serial.print(F("SE"));
  //  Serial.print(jscmd_cnt, DEC);
  Serial.println();   
} // show_joystick_inputs()

