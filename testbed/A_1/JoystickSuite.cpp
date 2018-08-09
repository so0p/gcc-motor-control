#include "Arduino.h"
#include "JoystickSuite.h"
#include "GlobalData.h"

// **************************************************************
//     Joystick functions
// **************************************************************

void getJoystick(GlobalData& data, SoftwareSerial& xbeeData) {

  //if xbee is not avaiable and less than 100
  //increase count
  //if xbee is avaiable, set count to 0
  //if xbee count is greater than 100
  //xbee is off

  if (xbeeData.available()>0){ // softwareSerial object
    data.lastTimeJSMessageRecieved = millis();
    data.xbee_on = true;
    data.xbee_counter =0;
    static bool last_b4 = false;  // last state of B4 button
    //****Rover Mode******
    // RoverID is 0, ArmID is 1
    if (data.mode==MODE_ROVER){
      // read from XBee stream. parse and update jscmd struct
      byte bytes_to_read = xbeeData.available();
      
      if(bytes_to_read >= 2) {
        for(byte i = 0; i< bytes_to_read; i++) {
          parse_xbee_byte(data, xbeeData);
          data.jscmd_cnt++;          
        }

        //check if danger override button is pushed or not!
        if(data.b2) {
          data.dangerOverride = true;    
        }
        else{
          data.dangerOverride = false;
        }
      }
      //set the drive mode slow of fast
      if(data.r2) {
        data.drive_mode = FAST; 
      }
      else {
        data.drive_mode = SLOW;
      }

      set_goal_speed(data, xbeeData);
    }
    // check if button 4 state has changed...
    // b4 tells us to toggle the hold mode
    bool cur_b4 = data.b4;
    if(!last_b4 && cur_b4) {
      data.hillMode = !data.hillMode;
    }
    last_b4 = cur_b4; // set lastmode and current mode equal

    //Arm Mode
    if (data.mode==MODE_ARM){
      //if robotID=1 then arm mode
      data.drive_mode = ARM;
      data.hillMode= true;
      
      // update the goal speeds
      set_goal_speed(data, xbeeData);
      show_joystick_inputs(data);
    }
  }
  else{
    data.xbee_on=false;
    if(millis() - data.lastTimeJSMessageRecieved > 1000){
      data.rover_goal_spd_lt = 0;
      data.rover_goal_spd_rt = 0;  
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
void parse_xbee_byte(GlobalData& data, SoftwareSerial& xbeeData) {
  byte xb = xbeeData.read();
  if(xb > 0x7f) {  // we're reading Msg 1
    data.se = (xb & B00000001);
    data.st = (xb & B00000010);
    data.b4 = (xb & B00000100);
    data.b3 = (xb & B00001000);
    data.b2 = (xb & B00010000);
    data.b1 = (xb & B00100000);
    data.up = (xb & B01000000);
  }
  else {           // we're reading Msg 0
    data.l2 = (xb & B00000001);
    data.l1 = (xb & B00000010);
    data.r2 = (xb & B00000100);
    data.r1 = (xb & B00001000);
    data.rt = (xb & B00010000);
    data.lt = (xb & B00100000);
    data.dn = (xb & B01000000);    
  }
} // parse_xbee_byte()

//*****Start of setting goal speeds******************************
// set our goal speeds based on the joystick inputs
void set_goal_speed(GlobalData& data, SoftwareSerial& xbeeData) { 

      //****Rover Mode**************************************************
      
    if (data.mode==MODE_ROVER){
      //rover if robotID=0
      if(data.up && data.lt) {
        data.rover_goal_spd_lt = data.drive_parameters[data.drive_mode].vel - data.drive_parameters[data.drive_mode].diag;
        data.rover_goal_spd_rt = data.drive_parameters[data.drive_mode].vel + data.drive_parameters[data.drive_mode].diag;    
      }
      else if(data.up && data.rt) {
        data.rover_goal_spd_lt = data.drive_parameters[data.drive_mode].vel + data.drive_parameters[data.drive_mode].diag;
        data.rover_goal_spd_rt = data.drive_parameters[data.drive_mode].vel - data.drive_parameters[data.drive_mode].diag;    
      }
      else if(data.dn && data.lt) {
        data.rover_goal_spd_lt = -data.drive_parameters[data.drive_mode].vel + data.drive_parameters[data.drive_mode].diag;
        data.rover_goal_spd_rt = -data.drive_parameters[data.drive_mode].vel - data.drive_parameters[data.drive_mode].diag;    
      }
      else if(data.dn && data.rt) {
        data.rover_goal_spd_lt = -data.drive_parameters[data.drive_mode].vel - data.drive_parameters[data.drive_mode].diag;
        data.rover_goal_spd_rt = -data.drive_parameters[data.drive_mode].vel + data.drive_parameters[data.drive_mode].diag;    
      }  
      else if(data.up) {
        data.rover_goal_spd_lt = data.drive_parameters[data.drive_mode].vel;
        data.rover_goal_spd_rt = data.drive_parameters[data.drive_mode].vel;
      }
      else if(data.dn) {
        data.rover_goal_spd_lt = -data.drive_parameters[data.drive_mode].vel;
        data.rover_goal_spd_rt = -data.drive_parameters[data.drive_mode].vel;
      }
      else if(data.lt) {
        data.rover_goal_spd_lt = -data.drive_parameters[data.drive_mode].vel;
        data.rover_goal_spd_rt = data.drive_parameters[data.drive_mode].vel;    
      }
      else if(data.rt) {
        data.rover_goal_spd_lt = data.drive_parameters[data.drive_mode].vel;
        data.rover_goal_spd_rt = -data.drive_parameters[data.drive_mode].vel;    
      }
      else {
        data.rover_goal_spd_lt = 0;
        data.rover_goal_spd_rt = 0;     
      }
      
    }

    //*****for arm ***************************************************
    if (data.mode==MODE_ARM){
      //if robotID=1 then arm mode

      //GRIP:!!!!!!!!!!!!!!!!!!
      // Grip open 
      if(data.b1) {
        data.arm_goal_spd_m6 = data.drive_parameters[data.drive_mode].vel;
      }

      // Grip close
      if(data.b3) {
        data.arm_goal_spd_m6 = -data.drive_parameters[data.drive_mode].vel;
      }
      //WRIST:
      // Wrist right
      if(data.rt) {
        data.arm_goal_spd_m4 = data.drive_parameters[data.drive_mode].vel;
        data.arm_goal_spd_m5 = data.drive_parameters[data.drive_mode].vel;
      }
      // Wrist left
      if(data.lt) {
        data.arm_goal_spd_m4 = -data.drive_parameters[data.drive_mode].vel;
        data.arm_goal_spd_m5 = -data.drive_parameters[data.drive_mode].vel;
      }
      //Wrist up
      if(data.up) {
        data.arm_goal_spd_m4 = -data.drive_parameters[data.drive_mode].vel;
        data.arm_goal_spd_m5 = data.drive_parameters[data.drive_mode].vel;
      }
      //Wrist down
      if(data.dn) {
        data.arm_goal_spd_m4 = data.drive_parameters[data.drive_mode].vel;
        data.arm_goal_spd_m5 = -data.drive_parameters[data.drive_mode].vel;
      }

      //ELBOW:
      //Elbow up
      if(data.l1) {
        data.arm_goal_spd_m3 = -data.drive_parameters[data.drive_mode].vel;
      }
      //Elbow down
      if(data.l2) {
        data.arm_goal_spd_m3 = data.drive_parameters[data.drive_mode].vel;
      }

      //SHOULDER:
      //Shoulder up
      if(data.r1) {
        data.arm_goal_spd_m2 = data.drive_parameters[data.drive_mode].vel;
      }
      //Shoulder down
      if(data.r2) {
        data.arm_goal_spd_m2 = -data.drive_parameters[data.drive_mode].vel;
      }

      //BASE:
      //Base left
      if(data.b2) {
        data.arm_goal_spd_m1 = -data.drive_parameters[data.drive_mode].vel;
      }
      //Base right
      if(data.b4) {
        data.arm_goal_spd_m1 = data.drive_parameters[data.drive_mode].vel;
      }
    }
    if(xbeeData.available()==0 && data.xbee_counter<100){
      data.xbee_counter++;
    }
    else if(xbeeData.available()==0 && data.xbee_counter>100){
      data.xbee_on=false;
    }
} // end set_goal_speed()

// debug code for showing joystick inputs
void show_joystick_inputs(GlobalData& data) {
  if(data.up) Serial.print("UP ");
  if(data.dn) Serial.print("DN ");
  if(data.lt) Serial.print("LT ");
  if(data.rt) Serial.print("RT ");
  if(data.r1) Serial.print("R1 ");
  if(data.r2) Serial.print("R2 ");
  if(data.l1) Serial.print("L1 ");
  if(data.l2) Serial.print("L2 ");
  if(data.b1) Serial.print("B1 ");
  if(data.b2) Serial.print("B2 ");
  if(data.b3) Serial.print("B3 ");
  if(data.b4) Serial.print("B4 ");
  if(data.st) Serial.print("ST ");
  if(data.se) Serial.print("SE ");
  //  Serial.print(jscmd_cnt, DEC);
  Serial.println();   
} // show_joystick_inputs()
