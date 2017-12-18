/*  
 *   Inputs: 
 *    1) goal speed 
 *    2) drive mode 
 *    3) current speed
 *   Output:
 *    1)Current Speed
 *  
 *  
 *  check if getting xbee is on, if not then automatically slow mode
 *  Mariam Grigorian Fall 2017
 */

 
void set_new_speed(){
  int goal_thr = param[drive_mode].thr;
  int goal_ramp = param[drive_mode].ramp;

  if(eStop) { 
    rover_goal_spd_lt = 0;
    rover_goal_spd_rt = 0;
    rover_cur_spd_lt = 0;
    rover_cur_spd_rt = 0;
    
    arm_goal_spd_m1 = 0;
    arm_goal_spd_m2 = 0;
    arm_goal_spd_m3 = 0;
    arm_goal_spd_m4 = 0; 
    arm_goal_spd_m5 = 0;
    arm_goal_spd_m6 = 0;

    arm_cur_spd_m1 = 0;
    arm_cur_spd_m2 = 0;
    arm_cur_spd_m3 = 0;
    arm_cur_spd_m4 = 0;
    arm_cur_spd_m5 = 0;
    arm_cur_spd_m6 = 0;
  }

  else {
  //************************Rover Mode with joystick *******************************
    if(XBEE_ON == 0){
    
      if (mode == MODE_ROVER){
        if( !( (rover_goal_spd_lt-goal_thr < rover_cur_spd_lt) && (rover_goal_spd_lt+goal_thr > rover_cur_spd_lt) ) ) {  
          if(rover_cur_spd_lt < rover_goal_spd_lt) {
            rover_cur_spd_lt += goal_ramp;
          }
          else {
            rover_cur_spd_lt -= goal_ramp;
          }
        }

        if( !( (rover_goal_spd_rt-goal_thr < rover_cur_spd_rt) && (rover_goal_spd_rt+goal_thr > rover_cur_spd_rt) ) ) { 
          if(rover_cur_spd_rt < rover_goal_spd_rt) {
            rover_cur_spd_rt += goal_ramp;
          }
          else {
            rover_cur_spd_rt -= goal_ramp;
          }      
        }
      }
      // ********************* Arm Mode with joystick**********************
      else if (mode == MODE_ARM){
        if ( ! ( (arm_goal_spd_m1-goal_thr < arm_cur_spd_m1)  &&  (arm_goal_spd_m1+goal_thr > arm_cur_spd_m1) )  )       // if speed is not within range 
        {  
          if (arm_cur_spd_m1 < arm_goal_spd_m1){
            arm_cur_spd_m1 += goal_ramp;      // increase speed
          }
          else 
          {  
            arm_cur_spd_m1 -= goal_ramp;     //decrease speed
          }
        }
        if ( ! ( (arm_goal_spd_m2-goal_thr < arm_cur_spd_m2)  && (arm_goal_spd_m2 + goal_thr > arm_cur_spd_m2) ) )       // Motor 2
        {  
          if (arm_cur_spd_m2 < arm_goal_spd_m2)
          {
              arm_cur_spd_m2 += goal_ramp;
          }
          else
          {  
            arm_cur_spd_m2 -= goal_ramp;
          }
        }
    
        if ( ! ( (arm_goal_spd_m3-goal_thr < arm_cur_spd_m3)  && (arm_goal_spd_m3 + goal_thr > arm_cur_spd_m3) ) )       // Motor 3
        {  
          if (arm_cur_spd_m3 < arm_goal_spd_m3)
          {
            arm_cur_spd_m3 += goal_ramp;
          }
          else 
          {  
            arm_cur_spd_m3 -= goal_ramp;
          }
        }

        if ( ! ( (arm_goal_spd_m4 - goal_thr < arm_cur_spd_m4)  && (arm_goal_spd_m4 + goal_thr > arm_cur_spd_m4) ) )       // Motor 4 
        {  
          if (arm_cur_spd_m4 < arm_goal_spd_m4)
          {
           arm_cur_spd_m4 += goal_ramp;
          }
          else
          {  
           arm_cur_spd_m4 -= goal_ramp;
          }
        }

        if ( ! ( (arm_goal_spd_m5 - goal_thr < arm_cur_spd_m5)  && (arm_goal_spd_m5 + goal_thr > arm_cur_spd_m5) ) )       // Motor 5 
        {  
          if (arm_cur_spd_m5 < arm_goal_spd_m5)
          {
            arm_cur_spd_m5 += goal_ramp;
          }
          else {  
            arm_cur_spd_m5 -= goal_ramp;
           }
        }
        if ( ! ( (arm_goal_spd_m6 - goal_thr < arm_cur_spd_m6)  && (arm_goal_spd_m6 + goal_thr > arm_cur_spd_m6) ) )       // Motor 6 
        {  
          if (arm_cur_spd_m6 < arm_goal_spd_m6)
          {
             arm_cur_spd_m6 += goal_ramp;
          }
          else {  
            arm_cur_spd_m6 -= goal_ramp;
          }
        }
      }
    }
  //************************End of Arm Mode****************************

  //************************Rover Mode with THING************************  
    else if(XBEE_ON == 1)     // if thing is not alive and THING comes in
    { 
      drive_mode = SLOW;   // drive mode for arm and rover should be slow 
      if (mode == MODE_ROVER){
        if( !( (rover_goal_spd_lt-goal_thr < rover_cur_spd_lt) && (rover_goal_spd_lt+goal_thr > rover_cur_spd_lt) ) ) {  
          if(rover_cur_spd_lt < rover_goal_spd_lt) {
             rover_cur_spd_lt += goal_ramp;
          }
         else {
          rover_cur_spd_lt -= goal_ramp;
         }
        }

        if( !( (rover_goal_spd_rt-goal_thr < rover_cur_spd_rt) && (rover_goal_spd_rt+goal_thr > rover_cur_spd_rt) ) ) { 
          if(rover_cur_spd_rt < rover_goal_spd_rt) {
            rover_cur_spd_rt += goal_ramp;
          }
          else {
            rover_cur_spd_rt -= goal_ramp;
          }      
        }
      }
      // ********************* Arm Mode with THING**********************
      else if (mode == MODE_ARM)
      {       
        if ( ! ( (arm_goal_spd_m1-goal_thr < arm_cur_spd_m1)  && (arm_goal_spd_m1+goal_thr > arm_cur_spd_m1) )  )       // if speed is not within range 
        {  
            if (arm_cur_spd_m1 < arm_goal_spd_m1){
             arm_cur_spd_m1 += goal_ramp;      // increase speed
            }
            else {  
              arm_cur_spd_m1 -= goal_ramp;     //decrease speed
            }
        }
        if ( ! ( (arm_goal_spd_m2-goal_thr < arm_cur_spd_m2)  && (arm_goal_spd_m2 + goal_thr > arm_cur_spd_m2) ) )       // Motor 2
        {  
          if (arm_cur_spd_m2 < arm_goal_spd_m2)
          {
              arm_cur_spd_m2 += goal_ramp;
          }
          else
          {  
            arm_cur_spd_m2 -= goal_ramp;
          }
        }
    
        if ( ! ( (arm_goal_spd_m3-goal_thr < arm_cur_spd_m3)  && (arm_goal_spd_m3 + goal_thr > arm_cur_spd_m3) ) )       // Motor 3
        {  
          if (arm_cur_spd_m3 < arm_goal_spd_m3)
          {
              arm_cur_spd_m3 += goal_ramp;
          }
          else 
          {  
            arm_cur_spd_m3 -= goal_ramp;
          }
        }

        if ( ! ( (arm_goal_spd_m4 - goal_thr < arm_cur_spd_m4)  && (arm_goal_spd_m4 + goal_thr > arm_cur_spd_m4) ) )       // Motor 4 
        {  
          if (arm_cur_spd_m4 < arm_goal_spd_m4)
          {
              arm_cur_spd_m4 += goal_ramp;
          }
          else
          {  
            arm_cur_spd_m4 -= goal_ramp;
          }
        }
    
        if ( ! ( (arm_goal_spd_m5 - goal_thr < arm_cur_spd_m5)  && (arm_goal_spd_m5 + goal_thr > arm_cur_spd_m5) ) )       // Motor 5 
        {  
          if (arm_cur_spd_m5 < arm_goal_spd_m5)
          {
            arm_cur_spd_m5 += goal_ramp;
          }
          else {  
            arm_cur_spd_m5 -= goal_ramp;
          }
        }
     
        if ( ! ( (arm_goal_spd_m6 - goal_thr < arm_cur_spd_m6)  && (arm_goal_spd_m6 + goal_thr > arm_cur_spd_m6) ) )       // Motor 6 
        {  
          if (arm_cur_spd_m6 < arm_goal_spd_m6){
            arm_cur_spd_m6 += goal_ramp;
          }
          else {  
            arm_cur_spd_m6 -= goal_ramp;
          }
        }
      } 
    }
  }
} 
// ********************* END OF ARM MODE **********************
