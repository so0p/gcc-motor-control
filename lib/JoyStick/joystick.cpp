#include "joystick.h"
//#include <SoftwareSerial.h>
#ifndef JOYSTICK
#define JOYSTICK

JoyStick::JoyStick(){
    xbee = SoftwareSerial(pin_rx, pin_tx);
    xbee_on = false;
    joystick_commands.linkActive = true; // override this value until we check for it
    joystick_commands.up = false;
    joystick_commands.dn = false;
    joystick_commands.lt = false;
    joystick_commands.rt = false;
    joystick_commands.b1 = false;
    joystick_commands.b2 = false;
    joystick_commands.b3 = false;
    joystick_commands.b4 = false;
    joystick_commands.r1 = false;
    joystick_commands.r2 = false;
    joystick_commands.l1 = false;
    joystick_commands.l2 = false;
    joystick_commands.st = false;
    joystick_commands.se = false;

    //Counter for number of XBee Messages
    count = 0;

    //initalize pins
    pin_rx = 11;
    pin_tx = 10;
};

bool JoyStick::is_xbee_alive(){
    if (xbee.available() > 0){
        xbee_on = true;
    }

    return xbee_on;
}

void JoyStick::get_joystick_data() {

  //if xbee is not avaiable and less than 100
  //increase count
  //if xbee is avaiable, set count to 0
  //if xbee count is greater than 100
  //xbee is off

  if (xbee_on){
    last_joystick_message_received_millis = millis();
    xbee_counter = 0;
    static bool last_b4 = false;  // last state of B4 button
    byte bytes_to_read = XBee.available();
      
        if(bytes_to_read >= 2) {
            for(byte i = 0; i< bytes_to_read; i++) {
                parse_xbee_byte();
                jscmd_cnt++;          
                }

            
      }
      //set the drive mode slow of fast
      if(jscmd.r2) {
        drive_mode = FAST; 
      }
      else {
        drive_mode = SLOW;
      }

      set_goal_speed();
    }
    // check if button 4 state has changed...
    // b4 tells us to toggle the hold mode
    bool cur_b4 = jscmd.b4;
    if(!last_b4 && cur_b4) {
      hillMode = !hillMode;
    }
    last_b4 = cur_b4; // set lastmode and current mode equal

    //place into different class or inherit from Joystick
    //Arm Mode
//    if (mode==MODE_ARM){
//      //if robotID=1 then arm mode
//      drive_mode = ARM;
//      hillMode= true;
//      
//      // update the goal speeds
//      set_goal_speed();
//      show_joystick_inputs();
//    }
  }
  else{
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


 
// debug code for showing joystick inputs
void JoyStick::show_joystick_inputs() {
  if(jscmd.up) Serial.print("UP ");
  if(jscmd.dn) Serial.print("DN ");
  if(jscmd.lt) Serial.print("LT ");
  if(jscmd.rt) Serial.print("RT ");
  if(jscmd.r1) Serial.print("R1 ");
  if(jscmd.r2) Serial.print("R2 ");
  if(jscmd.l1) Serial.print("L1 ");
  if(jscmd.l2) Serial.print("L2 ");
  if(jscmd.b1) Serial.print("B1 ");
  if(jscmd.b2) Serial.print("B2 ");
  if(jscmd.b3) Serial.print("B3 ");
  if(jscmd.b4) Serial.print("B4 ");
  if(jscmd.st) Serial.print("ST ");
  if(jscmd.se) Serial.print("SE ");
  //  Serial.print(jscmd_cnt, DEC);
  Serial.println();   
} // show_joystick_inputs()


// XBee packet definition from joystick
// =====================================
// pack buttonState[] into xbeeMsg
// xbeeMsg[0] : { 0 , DN , L , R , R1 , R2 , L1 , L2 }
// xbeeMsg[1] : { 1 , UP , B1 , B2 , B3 , B4 , ST , SE } 
//

// read one byte from XBee stream and parse its content
void JoyStick::parse_xbee_byte(){
  byte xb = XBee.read();
  if(xb > 0x7f) {  // we're reading Msg 1
    jscmd.se = (xb & B00000001);
    jscmd.st = (xb & B00000010);
    jscmd.b4 = (xb & B00000100);
    jscmd.b3 = (xb & B00001000);
    jscmd.b2 = (xb & B00010000);
    jscmd.b1 = (xb & B00100000);
    jscmd.up = (xb & B01000000);
  }
  else {           // we're reading Msg 0
    jscmd.l2 = (xb & B00000001);
    jscmd.l1 = (xb & B00000010);
    jscmd.r2 = (xb & B00000100);
    jscmd.r1 = (xb & B00001000);
    jscmd.rt = (xb & B00010000);
    jscmd.lt = (xb & B00100000);
    jscmd.dn = (xb & B01000000);    
  }
} // parse_xbee_byte()

#endif
