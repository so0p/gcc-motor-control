#include "Arduino.h"
#include "./HelperFunctions.h"

// **************************************************************
//     Set Speed
// **************************************************************

void setSpeed(JoystickSuite& joystick,DangerSuite& danger,ThingSuite& thing){
  int goal_thr = joystick.drive_parameters[joystick.drive_mode].thr;
  int goal_ramp = joystick.drive_parameters[joystick.drive_mode].ramp;

  if(danger.dangerFront || danger.dangerBack) {
    //joystick.rover_goal_spd_lt = 0;
    //joystick.rover_goal_spd_rt = 0;
    joystick.rover_cur_spd_lt = 0;
    joystick.rover_cur_spd_rt = 0;

    /*TEMP if (danger.dangerBack){
      if(  (joystick.rover_goal_spd_lt > 0 )) {  
          if(joystick.rover_cur_spd_lt < joystick.rover_goal_spd_lt) {
            joystick.rover_cur_spd_lt += goal_ramp;
            Serial.println("SetSpeed BACK LEFT +");
          }
          else {
            joystick.rover_cur_spd_lt -= goal_ramp;
            Serial.println("SetSpeed BACK LEFT -");
          }
        }

        if(  (joystick.rover_goal_spd_rt > 0 )) { 
          if(joystick.rover_cur_spd_rt < joystick.rover_goal_spd_rt) {
            joystick.rover_cur_spd_rt += goal_ramp;
            Serial.println("SetSpeed BACK RIGHT +");
          }
          else {
            joystick.rover_cur_spd_rt -= goal_ramp;
            Serial.println("SetSpeed BACK RIGHT -");
          }      
        }
    }

    if (danger.dangerFront){
      if( (joystick.rover_goal_spd_lt < 0 )) {  
          if(joystick.rover_cur_spd_lt < joystick.rover_goal_spd_lt) {
            joystick.rover_cur_spd_lt += goal_ramp;
            Serial.println("SetSpeed FRONT LEFT +");
          }
          else {
            joystick.rover_cur_spd_lt -= goal_ramp;
            Serial.println("SetSpeed FRONT LEFT -");
          }
        }

        if(  (joystick.rover_goal_spd_rt < 0 )) { 
          if(joystick.rover_cur_spd_rt < joystick.rover_goal_spd_rt) {
            joystick.rover_cur_spd_rt += goal_ramp;
            Serial.println("SetSpeed FRONT RIGHT +");
          }
          else {
            joystick.rover_cur_spd_rt -= goal_ramp;
            Serial.println("SetSpeed FRONT RIGHT -");
          }      
        }
    }*/

//    joystick.arm_goal_spd_m1 = 0;
//    joystick.arm_goal_spd_m2 = 0;
//    joystick.arm_goal_spd_m3 = 0;
//    joystick.arm_goal_spd_m4 = 0; 
//    joystick.arm_goal_spd_m5 = 0;
//    joystick.arm_goal_spd_m6 = 0;

//    joystick.arm_cur_spd_m1 = 0;
//    joystick.arm_cur_spd_m2 = 0;
//    joystick.arm_cur_spd_m3 = 0;
//    joystick.arm_cur_spd_m4 = 0;
//    joystick.arm_cur_spd_m5 = 0;
//    joystick.arm_cur_spd_m6 = 0;
  }
  
  

  else {
    //************************Joystick *******************************
    if(joystick.xbee_on){
      Serial.println("SetSpeed XBEE ON +");
      //*********************Rover Joystick ***************************
      if (joystick.mode == MODE_ROVER){
        //are we checking which joystick commands are triggered
        if( !( (joystick.rover_goal_spd_lt-goal_thr < joystick.rover_cur_spd_lt) && (joystick.rover_goal_spd_lt+goal_ramp > joystick.rover_cur_spd_lt) ) ) {  
          if(joystick.rover_cur_spd_lt < joystick.rover_goal_spd_lt) {
            joystick.rover_cur_spd_lt += goal_ramp;
          }
          else {
            joystick.rover_cur_spd_lt -= goal_ramp;
          }
        }

        if( !( (joystick.rover_goal_spd_rt-goal_thr < joystick.rover_cur_spd_rt) && (joystick.rover_goal_spd_rt+goal_ramp > joystick.rover_cur_spd_rt) ) ) { 
          if(joystick.rover_cur_spd_rt < joystick.rover_goal_spd_rt) {
            joystick.rover_cur_spd_rt += goal_ramp;
          }
          else {
            joystick.rover_cur_spd_rt -= goal_ramp;
          }      
        }
      }
      // ********************* Arm Mode Joystick**********************
      else if (joystick.mode == MODE_ARM){
        if ( ! ( (joystick.arm_goal_spd_m1-goal_thr < joystick.arm_cur_spd_m1)  &&  (joystick.arm_goal_spd_m1+goal_thr > joystick.arm_cur_spd_m1) )  )       // if speed is not within range 
        {  
          if (joystick.arm_cur_spd_m1 < joystick.arm_goal_spd_m1){
            joystick.arm_cur_spd_m1 += goal_ramp;      // increase speed
          }
          else 
          {  
            joystick.arm_cur_spd_m1 -= goal_ramp;     //decrease speed
          }
        }
        if ( ! ( (joystick.arm_goal_spd_m2-goal_thr < joystick.arm_cur_spd_m2)  && (joystick.arm_goal_spd_m2 + goal_thr > joystick.arm_cur_spd_m2) ) )       // Motor 2
        {  
          if (joystick.arm_cur_spd_m2 < joystick.arm_goal_spd_m2)
          {
              joystick.arm_cur_spd_m2 += goal_ramp;
          }
          else
          {  
            joystick.arm_cur_spd_m2 -= goal_ramp;
          }
        }
    
        if ( ! ( (joystick.arm_goal_spd_m3-goal_thr < joystick.arm_cur_spd_m3)  && (joystick.arm_goal_spd_m3 + goal_thr > joystick.arm_cur_spd_m3) ) )       // Motor 3
        {  
          if (joystick.arm_cur_spd_m3 < joystick.arm_goal_spd_m3)
          {
            joystick.arm_cur_spd_m3 += goal_ramp;
          }
          else 
          {  
            joystick.arm_cur_spd_m3 -= goal_ramp;
          }
        }

        if ( ! ( (joystick.arm_goal_spd_m4 - goal_thr < joystick.arm_cur_spd_m4)  && (joystick.arm_goal_spd_m4 + goal_thr > joystick.arm_cur_spd_m4) ) )       // Motor 4 
        {  
          if (joystick.arm_cur_spd_m4 < joystick.arm_goal_spd_m4)
          {
           joystick.arm_cur_spd_m4 += goal_ramp;
          }
          else
          {  
           joystick.arm_cur_spd_m4 -= goal_ramp;
          }
        }

        if ( ! ( (joystick.arm_goal_spd_m5 - goal_thr < joystick.arm_cur_spd_m5)  && (joystick.arm_goal_spd_m5 + goal_thr > joystick.arm_cur_spd_m5) ) )       // Motor 5 
        {  
          if (joystick.arm_cur_spd_m5 < joystick.arm_goal_spd_m5)
          {
            joystick.arm_cur_spd_m5 += goal_ramp;
          }
          else {  
            joystick.arm_cur_spd_m5 -= goal_ramp;
           }
        }
        if ( ! ( (joystick.arm_goal_spd_m6 - goal_thr < joystick.arm_cur_spd_m6)  && (joystick.arm_goal_spd_m6 + goal_thr > joystick.arm_cur_spd_m6) ) )       // Motor 6 
        {  
          if (joystick.arm_cur_spd_m6 < joystick.arm_goal_spd_m6)
          {
             joystick.arm_cur_spd_m6 += goal_ramp;
          }
          else {  
            joystick.arm_cur_spd_m6 -= goal_ramp;
          }
        }
      }
    }
  //************************End of Arm Mode****************************

  //************************Rover Mode with THING************************  
    else if(!joystick.xbee_on && thing.thing_on)     // if thing is not alive and THING comes in
    { 
      Serial.println("SetSpeed XBEE ON THING ON +");
      joystick.drive_mode = SLOW;   // drive mode for arm and rover should be slow 
      if (joystick.mode == MODE_ROVER){
        if( !( (joystick.rover_goal_spd_lt-goal_thr < joystick.rover_cur_spd_lt) && (joystick.rover_goal_spd_lt+goal_thr > joystick.rover_cur_spd_lt) ) ) {  
          if(joystick.rover_cur_spd_lt < joystick.rover_goal_spd_lt) {
             joystick.rover_cur_spd_lt += goal_ramp;
          }
         else {
          joystick.rover_cur_spd_lt -= goal_ramp;
         }
        }

        if( !( (joystick.rover_goal_spd_rt-goal_thr < joystick.rover_cur_spd_rt) && (joystick.rover_goal_spd_rt+goal_thr > joystick.rover_cur_spd_rt) ) ) { 
          if(joystick.rover_cur_spd_rt < joystick.rover_goal_spd_rt) {
            joystick.rover_cur_spd_rt += goal_ramp;
          }
          else {
            joystick.rover_cur_spd_rt -= goal_ramp;
          }      
        }
      }
      // ********************* Arm Mode with THING**********************
      else if (joystick.mode == MODE_ARM)
      {       
        if ( ! ( (joystick.arm_goal_spd_m1-goal_thr < joystick.arm_cur_spd_m1)  && (joystick.arm_goal_spd_m1+goal_thr > joystick.arm_cur_spd_m1) )  )       // if speed is not within range 
        {  
            if (joystick.arm_cur_spd_m1 < joystick.arm_goal_spd_m1){
             joystick.arm_cur_spd_m1 += goal_ramp;      // increase speed
            }
            else {  
              joystick.arm_cur_spd_m1 -= goal_ramp;     //decrease speed
            }
        }
        if ( ! ( (joystick.arm_goal_spd_m2-goal_thr < joystick.arm_cur_spd_m2)  && (joystick.arm_goal_spd_m2 + goal_thr > joystick.arm_cur_spd_m2) ) )       // Motor 2
        {  
          if (joystick.arm_cur_spd_m2 < joystick.arm_goal_spd_m2)
          {
              joystick.arm_cur_spd_m2 += goal_ramp;
          }
          else
          {  
            joystick.arm_cur_spd_m2 -= goal_ramp;
          }
        }
    
        if ( ! ( (joystick.arm_goal_spd_m3-goal_thr < joystick.arm_cur_spd_m3)  && (joystick.arm_goal_spd_m3 + goal_thr > joystick.arm_cur_spd_m3) ) )       // Motor 3
        {  
          if (joystick.arm_cur_spd_m3 < joystick.arm_goal_spd_m3)
          {
              joystick.arm_cur_spd_m3 += goal_ramp;
          }
          else 
          {  
            joystick.arm_cur_spd_m3 -= goal_ramp;
          }
        }

        if ( ! ( (joystick.arm_goal_spd_m4 - goal_thr < joystick.arm_cur_spd_m4)  && (joystick.arm_goal_spd_m4 + goal_thr > joystick.arm_cur_spd_m4) ) )       // Motor 4 
        {  
          if (joystick.arm_cur_spd_m4 < joystick.arm_goal_spd_m4)
          {
              joystick.arm_cur_spd_m4 += goal_ramp;
          }
          else
          {  
            joystick.arm_cur_spd_m4 -= goal_ramp;
          }
        }
    
        if ( ! ( (joystick.arm_goal_spd_m5 - goal_thr < joystick.arm_cur_spd_m5)  && (joystick.arm_goal_spd_m5 + goal_thr > joystick.arm_cur_spd_m5) ) )       // Motor 5 
        {  
          if (joystick.arm_cur_spd_m5 < joystick.arm_goal_spd_m5)
          {
            joystick.arm_cur_spd_m5 += goal_ramp;
          }
          else {  
            joystick.arm_cur_spd_m5 -= goal_ramp;
          }
        }
     
        if ( ! ( (joystick.arm_goal_spd_m6 - goal_thr < joystick.arm_cur_spd_m6)  && (joystick.arm_goal_spd_m6 + goal_thr > joystick.arm_cur_spd_m6) ) )       // Motor 6 
        {  
          if (joystick.arm_cur_spd_m6 < joystick.arm_goal_spd_m6){
            joystick.arm_cur_spd_m6 += goal_ramp;
          }
          else {  
            joystick.arm_cur_spd_m6 -= goal_ramp;
          }
        }
      } 
    }
  }
} 
// ********************* END OF ARM MODE **********************

// read the TM1638 keys 
void process_tm1638_keys(TM1638& tm1,JoystickSuite& joystick) {
  joystick.tm1638_keys = tm1.getButtons();
  // do some validations of it and set any appropriate states
} //process_tm1638_keys()


// update the TM1638 display
void refresh_tm1638(TM1638& tm1,JoystickSuite& joystick, MotorSuite& motors) {
  tm1.clearDisplay();  

  char s[8];
//  if(drive_mode == LUDICROUS) {
//    snprintf(s,8, "LUDIC %02d", joystick_command_count%99);
//  }
//  else 
  if(joystick.hillMode) {
    snprintf(s,8, "BRAKE %02d", joystick.joystick_command_count%99);
  }
  else {
    snprintf(s,8, "OPEN  %02d", joystick.joystick_command_count%99);
  }
  tm1.setDisplayToString(s);

  byte led = 0;
  if(!motors.batteryOK) {
    led = led | 0x1;
  }

  if(motors.mc1_batt == 0) {
    led = led | 0x80;
  }
  if(motors.mc2_batt == 0) {
    led = led | 0x40;
  }
//
//  if(drive_mode == LUDICROUS) {
//    led = led | 0x4;
//  }

  tm1.setLEDs(led);

} // refresh_tm1638()
