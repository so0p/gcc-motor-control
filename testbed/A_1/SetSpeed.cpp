#include "Arduino.h"
#include "SetSpeed.h"

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

    if (danger.dangerBack){
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
    }

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
