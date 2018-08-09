// **************************************************************
//     Drive Motors & get Roboclaw Status
// **************************************************************

// drive with velocity command
void driveMotors() {
    
    //Code By Avery

    //Identify if it is ROVER (0) or ARM (1)

  if (mode==MODE_ROVER) {
    
    if(batteryOK && mc1_batt>1 && mc2_batt>1) {  // IF ALL OK... 
      if(rover_cur_spd_lt != 0 || rover_cur_spd_rt != 0) {
        roboclaw1.SpeedM1(address,rover_cur_spd_lt);  
        roboclaw1.SpeedM2(address,rover_cur_spd_lt);
        //roboclaw2.SpeedM1(address,rover_cur_spd_rt);
        //roboclaw2.SpeedM2(address,rover_cur_spd_rt); 
      }

      else if(hillMode) {
        roboclaw1.SpeedM1(address,0);
        roboclaw1.SpeedM2(address,0);
        //roboclaw2.SpeedM1(address,0);
        //roboclaw2.SpeedM2(address,0);      
        // drive to velocity 0
      }
      else if(!hillMode) {
        roboclaw1.BackwardM1(address,0); //Stop Motor1 
        roboclaw1.BackwardM2(address,0); //Stop Motor2 
        //roboclaw2.BackwardM1(address,0); //Stop Motor1 
        //roboclaw2.BackwardM2(address,0); //Stop Motor2      
        // don't drive the motors anymore... 
      }
    } // if everything is OK

    else if(!batteryOK) {
      roboclaw1.BackwardM1(address,0); //Stop Motor1 
      roboclaw1.BackwardM2(address,0); //Stop Motor2 
      //roboclaw2.BackwardM1(address,0); //Stop Motor1 
      //roboclaw2.BackwardM2(address,0); //Stop Motor2      
    }
  } // drive_motors(0)
//  else if (mode==MODE_ARM) {
//
//    if(batteryOK && mc1_batt>1 && mc2_batt>1 && mc3_batt>1) {  // IF ALL OK... 
//      if(arm_cur_spd_m1 != 0 || arm_cur_spd_m2 != 0 || arm_cur_spd_m3 != 0 || arm_cur_spd_m4 != 0 || arm_cur_spd_m5 != 0 || arm_cur_spd_m6 != 0) {
//        roboclaw1.SpeedM1(address,arm_cur_spd_m1);
//        roboclaw1.SpeedM2(address,arm_cur_spd_m2);
//        roboclaw2.SpeedM1(address,arm_cur_spd_m3);
//        roboclaw2.SpeedM2(address,arm_cur_spd_m4); 
//        roboclaw3.SpeedM1(address,arm_cur_spd_m5);
//        roboclaw3.SpeedM2(address,arm_cur_spd_m6);
//      }   // drive_motors (1)
//    } 
//  }
}

// get roboclaw's battery levels
// if roboclaw is not responsive, set voltage to 0. this will
// indicate that RC communication is dead
void get_roboclaw_status() {
  
  bool rc1_alive = false;
  bool rc2_alive = false;  

  mc1_batt = roboclaw1.ReadMainBatteryVoltage(address, &rc1_alive);
  //mc2_batt = roboclaw2.ReadMainBatteryVoltage(address, &rc2_alive);  

  // if battery level gets low, completely stop driving
  if(mc1_batt<227 || mc2_batt<226) {
    batteryOK = false;
  }
 
  if(!rc1_alive) {
    mc1_batt = 0;
  }
  if(!rc2_alive) {
    mc2_batt = 0;
  }
    
} // get_roboclaw_status()


// **************************************************************
//     Danger Function
// **************************************************************

void getDanger(){
  if( dangerOverride == true){
    dangerM1 = false;
    dangerM2 = false;
    dangerM3 = false;
    dangerM4 = false;
    dangerM5 = false;
    dangerM6 = false;   

    dangerFront = false;
    dangerBack = false;

  }

  else {

    if(mode == MODE_ROVER){

          buttonStateFront_R = digitalRead(BUTTON_PIN_FRONT_R);
          buttonStateBack_R = digitalRead(BUTTON_PIN_BACK_R);
          buttonStateFront_L = digitalRead(BUTTON_PIN_FRONT_L);
          buttonStateBack_L = digitalRead(BUTTON_PIN_BACK_L);         

          if (buttonStateFront_R == LOW || buttonStateFront_L == LOW){
            dangerFront = true;
          }
          else {
            dangerFront = false;
          }
    
          if (buttonStateBack_R == LOW  || buttonStateBack_L == LOW){
            dangerBack = true;
          }

          else{
            dangerBack = false;
          }
    }
    else if( mode == MODE_ARM){
      if(dangerCounter == 50){
        
//        roboclaw1.ReadCurrents(address, currentM1, currentM2);
//        roboclaw2.ReadCurrents(address, currentM3, currentM4);
//        roboclaw3.ReadCurrents(address, currentM5, currentM6);
        
        if(currentM1 > M1_thresh){
          dangerM1 = true;
        }

        else if(currentM2 > M2_thresh){
          dangerM2 = true;
        }

        else if(currentM3 > M3_thresh){
          dangerM3 = true;
        }

        else if(currentM4 > M4_thresh){
          dangerM4 = true;
        }

        else if(currentM5 > M5_thresh){
          dangerM5 = true;
        }

        else if(currentM6 > M6_thresh){
          dangerM6 = true;
        }

        dangerCounter=0;

      }
   
      dangerCounter++;        
          
        
    }
  }
}

// read and parse full packet from XBee interface and 
// populate the jscmd struct

// **************************************************************
//     Joystick functions
// **************************************************************

void getJoystick() {

  //if xbee is not avaiable and less than 100
  //increase count
  //if xbee is avaiable, set count to 0
  //if xbee count is greater than 100
  //xbee is off

  if (XBee.available()>0){ // softwareSerial object
    lastTimeJSMessageRecieved = millis();
    xbee_on = true;
    xbee_counter =0;
    static bool last_b4 = false;  // last state of B4 button
    //****Rover Mode******
    // RoverID is 0, ArmID is 1
    if (mode==MODE_ROVER){
      // read from XBee stream. parse and update jscmd struct
      byte bytes_to_read = XBee.available();
      
      if(bytes_to_read >= 2) {
        for(byte i = 0; i< bytes_to_read; i++) {
          parse_xbee_byte();
          jscmd_cnt++;          
        }

        //check if danger override button is pushed or not!
        if(jscmd.b2) {
          dangerOverride = true;    
        }
        else{
          dangerOverride = false;
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

    //Arm Mode
    if (mode==MODE_ARM){
      //if robotID=1 then arm mode
      drive_mode = ARM;
      hillMode= true;
      
      // update the goal speeds
      set_goal_speed();
      show_joystick_inputs();
    }
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

  
// debug code for showing joystick inputs
void show_joystick_inputs() {
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
void parse_xbee_byte() {
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

/*************************

  Get Thing

  Parses Commands from Web Client. Header value of packet should be 183 and Footer is 237

**************************/

// **************************************************************
//     Serial Comm Functions
// **************************************************************

void getThing(){
  if(Serial1.available()>4){
    thing_on = true;
    lastTimeJSMessageRecieved = millis();
    Serial.println("thing is on");
  }
  else{
    Serial.println("thing is off");
    thing_on=false;
  }
  if(!xbee_on && thing_on){

    byte cmdArr[5];
    
    if (Serial1.available() > 4){            // if there are 4 or more than 4 bytes in the buffer go in the loop
      delay(100);
      Serial.print("getting packets");
      Serial1.readBytes(cmdArr, 5);           // read the bytes
      drive_mode = SLOW;   // drive mode for arm and rover should be slow 
      if (cmdArr[0] == 183){                  // check for header to be 183
        if (mode == MODE_ROVER){              // if rover
          for(int j=0; j<5;j++){
            Serial.println(cmdArr[j]);
          }
          if (cmdArr[4] == 237){        // check that ending byte is 234
            Serial.print("setting direction");                                  // if the ending byte is 234 then save data into the struct
            CMDS_TO_MC.direction = cmdArr[1];
          }
          
          setThingSpeed();
          
          
        }
        
        else if (mode == MODE_ARM){

          Serial1.readBytes(cmdArr, 4);

          if (cmdArr[3] == 237){          // check for ending byte, if true then save bytes into struct

            CMDS_TO_MC.direction = cmdArr[1];
            CMDS_TO_MC.duration = cmdArr[2];
            CMDS_TO_MC.motorNum = cmdArr[3];

          }
        }
      }
    }
    else {
      
      if(millis() - lastTimeThingMessageRecieved > 1000){
        rover_goal_spd_lt = 0;
        rover_goal_spd_rt = 0;  
      }     
    }
  }
}

void setThingSpeed(){
  if (mode==MODE_ROVER && !xbee_on && thing_on){
        //rover if robotID=0
        if(CMDS_TO_MC.direction==1 && CMDS_TO_MC.direction==3) {
          rover_goal_spd_lt = param[drive_mode].vel - param[drive_mode].diag;
          rover_goal_spd_rt = param[drive_mode].vel + param[drive_mode].diag;
          Serial.print("1");    
        }
        else if(CMDS_TO_MC.direction==1 && CMDS_TO_MC.direction==4) {
          rover_goal_spd_lt = param[drive_mode].vel + param[drive_mode].diag;
          rover_goal_spd_rt = param[drive_mode].vel - param[drive_mode].diag;
          Serial.print("2");    
        }
        else if(CMDS_TO_MC.direction==2 && CMDS_TO_MC.direction==3) {
          rover_goal_spd_lt = -param[drive_mode].vel + param[drive_mode].diag;
          rover_goal_spd_rt = -param[drive_mode].vel - param[drive_mode].diag;
          Serial.print("3");    
        }
        else if(CMDS_TO_MC.direction==2 && CMDS_TO_MC.direction==4) {
          rover_goal_spd_lt = -param[drive_mode].vel - param[drive_mode].diag;
          rover_goal_spd_rt = -param[drive_mode].vel + param[drive_mode].diag;
          Serial.print("4");    
        }  
        else if(CMDS_TO_MC.direction==1) {
          rover_goal_spd_lt = param[drive_mode].vel;
          rover_goal_spd_rt = param[drive_mode].vel;
          Serial.print("5");
        }
        else if(CMDS_TO_MC.direction==2) {
          rover_goal_spd_lt = -param[drive_mode].vel;
          rover_goal_spd_rt = -param[drive_mode].vel;
          Serial.print("6");
        }
        else if(CMDS_TO_MC.direction==3) {
          rover_goal_spd_lt = -param[drive_mode].vel;
          rover_goal_spd_rt = param[drive_mode].vel;
          Serial.print("7");    
        }
        else if(CMDS_TO_MC.direction==4) {
          rover_goal_spd_lt = param[drive_mode].vel;
          rover_goal_spd_rt = -param[drive_mode].vel;
          Serial.print("8");
        }
        else if(CMDS_TO_MC.direction ==0){
          rover_goal_spd_lt = 0;
          rover_goal_spd_rt = 0;
        }
        
        
  }
}

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

// **************************************************************
//     Set Speed
// **************************************************************

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

// **************************************************************
//     TM1638 functions
// **************************************************************

// read the TM1638 keys 
void process_tm1638_keys() {
  tm1638_keys = tm1638.getButtons();
  // do some validations of it and set any appropriate states
} //process_tm1638_keys()


// update the TM1638 display
void refresh_tm1638() {
  tm1638.clearDisplay();  

  char s[8];
//  if(drive_mode == LUDICROUS) {
//    snprintf(s,8, "LUDIC %02d", jscmd_cnt%99);
//  }
//  else 
  if(hillMode) {
    snprintf(s,8, "BRAKE %02d", jscmd_cnt%99);
  }
  else {
    snprintf(s,8, "OPEN  %02d", jscmd_cnt%99);
  }
  tm1638.setDisplayToString(s);

  byte led = 0;
  if(!batteryOK) {
    led = led | 0x1;
  }

  if(mc1_batt == 0) {
    led = led | 0x80;
  }
  if(mc2_batt == 0) {
    led = led | 0x40;
  }
//
//  if(drive_mode == LUDICROUS) {
//    led = led | 0x4;
//  }

  tm1638.setLEDs(led);

} // refresh_tm1638()

