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

//*****Start of setting goal speeds******************************
// set our goal speeds based on the joystick inputs
void set_goal_speed() { 

      //****Rover Mode**************************************************
      
    if (mode==MODE_ROVER){
      //rover if robotID=0
      if(jscmd.up && jscmd.lt) {
        rover_goal_spd_lt = param[drive_mode].vel - param[drive_mode].diag;
        rover_goal_spd_rt = param[drive_mode].vel + param[drive_mode].diag;    
      }
      else if(jscmd.up && jscmd.rt) {
        rover_goal_spd_lt = param[drive_mode].vel + param[drive_mode].diag;
        rover_goal_spd_rt = param[drive_mode].vel - param[drive_mode].diag;    
      }
      else if(jscmd.dn && jscmd.lt) {
        rover_goal_spd_lt = -param[drive_mode].vel + param[drive_mode].diag;
        rover_goal_spd_rt = -param[drive_mode].vel - param[drive_mode].diag;    
      }
      else if(jscmd.dn && jscmd.rt) {
        rover_goal_spd_lt = -param[drive_mode].vel - param[drive_mode].diag;
        rover_goal_spd_rt = -param[drive_mode].vel + param[drive_mode].diag;    
      }  
      else if(jscmd.up) {
        rover_goal_spd_lt = param[drive_mode].vel;
        rover_goal_spd_rt = param[drive_mode].vel;
      }
      else if(jscmd.dn) {
        rover_goal_spd_lt = -param[drive_mode].vel;
        rover_goal_spd_rt = -param[drive_mode].vel;
      }
      else if(jscmd.lt) {
        rover_goal_spd_lt = -param[drive_mode].vel;
        rover_goal_spd_rt = param[drive_mode].vel;    
      }
      else if(jscmd.rt) {
        rover_goal_spd_lt = param[drive_mode].vel;
        rover_goal_spd_rt = -param[drive_mode].vel;    
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
      if(jscmd.b1) {
        arm_goal_spd_m6 = param[drive_mode].vel;
      }

      // Grip close
      if(jscmd.b3) {
        arm_goal_spd_m6 = -param[drive_mode].vel;
      }
      //WRIST:
      // Wrist right
      if(jscmd.rt) {
        arm_goal_spd_m4 = param[drive_mode].vel;
        arm_goal_spd_m5 = param[drive_mode].vel;
      }
      // Wrist left
      if(jscmd.lt) {
        arm_goal_spd_m4 = -param[drive_mode].vel;
        arm_goal_spd_m5 = -param[drive_mode].vel;
      }
      //Wrist up
      if(jscmd.up) {
        arm_goal_spd_m4 = -param[drive_mode].vel;
        arm_goal_spd_m5 = param[drive_mode].vel;
      }
      //Wrist down
      if(jscmd.dn) {
        arm_goal_spd_m4 = param[drive_mode].vel;
        arm_goal_spd_m5 = -param[drive_mode].vel;
      }

      //ELBOW:
      //Elbow up
      if(jscmd.l1) {
        arm_goal_spd_m3 = -param[drive_mode].vel;
      }
      //Elbow down
      if(jscmd.l2) {
        arm_goal_spd_m3 = param[drive_mode].vel;
      }

      //SHOULDER:
      //Shoulder up
      if(jscmd.r1) {
        arm_goal_spd_m2 = param[drive_mode].vel;
      }
      //Shoulder down
      if(jscmd.r2) {
        arm_goal_spd_m2 = -param[drive_mode].vel;
      }

      //BASE:
      //Base left
      if(jscmd.b2) {
        arm_goal_spd_m1 = -param[drive_mode].vel;
      }
      //Base right
      if(jscmd.b4) {
        arm_goal_spd_m1 = param[drive_mode].vel;
      }
    }
    if(XBee.available()==0 && xbee_counter<100){
      xbee_counter++;
    }
    else if(XBee.available()==0 && xbee_counter>100){
      xbee_on=false;
    }
} // end set_goal_speed()

 
 
void setSpeed(){
  int goal_thr = param[drive_mode].thr;
  int goal_ramp = param[drive_mode].ramp;

  if(dangerFront || dangerBack) { 
    //rover_goal_spd_lt = 0;
    //rover_goal_spd_rt = 0;
    rover_cur_spd_lt = 0;
    rover_cur_spd_rt = 0;

    if (dangerBack){
      if(  (rover_goal_spd_lt > 0 )) {  
          if(rover_cur_spd_lt < rover_goal_spd_lt) {
            rover_cur_spd_lt += goal_ramp;
          }
          else {
            rover_cur_spd_lt -= goal_ramp;
          }
        }

        if(  (rover_goal_spd_rt > 0 )) { 
          if(rover_cur_spd_rt < rover_goal_spd_rt) {
            rover_cur_spd_rt += goal_ramp;
          }
          else {
            rover_cur_spd_rt -= goal_ramp;
          }      
        }
    }

    if (dangerFront){
      if( (rover_goal_spd_lt < 0 )) {  
          if(rover_cur_spd_lt < rover_goal_spd_lt) {
            rover_cur_spd_lt += goal_ramp;
          }
          else {
            rover_cur_spd_lt -= goal_ramp;
          }
        }

        if(  (rover_goal_spd_rt < 0 )) { 
          if(rover_cur_spd_rt < rover_goal_spd_rt) {
            rover_cur_spd_rt += goal_ramp;
          }
          else {
            rover_cur_spd_rt -= goal_ramp;
          }      
        }
    }

//    arm_goal_spd_m1 = 0;
//    arm_goal_spd_m2 = 0;
//    arm_goal_spd_m3 = 0;
//    arm_goal_spd_m4 = 0; 
//    arm_goal_spd_m5 = 0;
//    arm_goal_spd_m6 = 0;

//    arm_cur_spd_m1 = 0;
//    arm_cur_spd_m2 = 0;
//    arm_cur_spd_m3 = 0;
//    arm_cur_spd_m4 = 0;
//    arm_cur_spd_m5 = 0;
//    arm_cur_spd_m6 = 0;
  }
  
  

  else {
    //************************Joystick *******************************
    if(xbee_on){

      //*********************Rover Joystick ***************************
      if (mode == MODE_ROVER){
        //are we checking which joystick commands are triggered
        if( !( (rover_goal_spd_lt-goal_thr < rover_cur_spd_lt) && (rover_goal_spd_lt+goal_ramp > rover_cur_spd_lt) ) ) {  
          if(rover_cur_spd_lt < rover_goal_spd_lt) {
            rover_cur_spd_lt += goal_ramp;
          }
          else {
            rover_cur_spd_lt -= goal_ramp;
          }
        }

        if( !( (rover_goal_spd_rt-goal_thr < rover_cur_spd_rt) && (rover_goal_spd_rt+goal_ramp > rover_cur_spd_rt) ) ) { 
          if(rover_cur_spd_rt < rover_goal_spd_rt) {
            rover_cur_spd_rt += goal_ramp;
          }
          else {
            rover_cur_spd_rt -= goal_ramp;
          }      
        }
      }
      // ********************* Arm Mode Joystick**********************
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
    else if(!xbee_on && thing_on)     // if thing is not alive and THING comes in
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
