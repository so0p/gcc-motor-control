// read and parse full packet from XBee interface and 
// populate the jscmd struct
//


void process_joystick_inputs() {
//****Rover Mode**************************************************
if (robotID=0){
//rover if robotID=0 

  static bool last_b4 = false;  // last state of B4 button


 // read from XBee stream. parse and update jscmd struct
  byte bytes_to_read = XBee.available();
  //********************************************dear figure out the XBEE stuff please**********************
  if(bytes_to_read >= 2) {

   
    for(byte i = 0; i< bytes_to_read; i++) {
      parse_xbee_byte();
      jscmd_cnt++;
    }


//check if danger override button is pushed or not
   if(jscmd.b2) {
  danger_override = true;    //from Mariam: can we make a bool not an if else statment eg. bool dangerOverride = false; (false means button isnt pressed) 
  {
    else {
      danger_override = false;
    }
    }
  }


//set the drive mode slow of fast
if(jscmd.r2) {
  drive_mode = FAST; }
  else {
    drive_mode = SLOW;
  }

    // check if button 4 state has changed...
    // b4 tells us to toggle the hold mode
    bool cur_b4 = jscmd.b4;
    if(!last_b4 && cur_b4) {
      hillMode = !hillMode;
    }
    last_b4 = cur_b4; // set lastmode and current mode equal

//*****for arm ***************************************************
if (robotID=1){
  //if robotID=1 then arm mode

   drive_mode = ARM;

   hillMode= !hillMode
    // update the goal speeds
    set_goal_speed();
    show_joystick_inputs();
   }
  }
  
  // also check if this link is alive... if TBD millis have gone
  // since last msg, notify main program

  // every TBD cycles, send a HB message to joystick
  
} // process_joystick_inputs()


//*****Start of setting goal speeds******************************
// set our goal speeds based on the joystick inputs
void set_goal_speed() { 

  //****Rover Mode**************************************************
  
if (robotID=0){
//rover if robotID=0

  if(jscmd.up && jscmd.lt) {
    goal_spd_lt = param[drive_mode].vel - param[drive_mode].diag;
    goal_spd_rt = param[drive_mode].vel + param[drive_mode].diag;    
  }
  else if(jscmd.up && jscmd.rt) {
    goal_spd_lt = param[drive_mode].vel + param[drive_mode].diag;
    goal_spd_rt = param[drive_mode].vel - param[drive_mode].diag;    
  }
  else if(jscmd.dn && jscmd.lt) {
    goal_spd_lt = -param[drive_mode].vel + param[drive_mode].diag;
    goal_spd_rt = -param[drive_mode].vel - param[drive_mode].diag;    
  }
  else if(jscmd.dn && jscmd.rt) {
    goal_spd_lt = -param[drive_mode].vel - param[drive_mode].diag;
    goal_spd_rt = -param[drive_mode].vel + param[drive_mode].diag;    
  }  
  else if(jscmd.up) {
    goal_spd_lt = param[drive_mode].vel;
    goal_spd_rt = param[drive_mode].vel;
  }
  else if(jscmd.dn) {
    goal_spd_lt = -param[drive_mode].vel;
    goal_spd_rt = -param[drive_mode].vel;
  }
  else if(jscmd.lt) {
    goal_spd_lt = -param[drive_mode].vel;
    goal_spd_rt = param[drive_mode].vel;    
  }
  else if(jscmd.rt) {
    goal_spd_lt = param[drive_mode].vel;
    goal_spd_rt = -param[drive_mode].vel;    
  }
  else {
    goal_spd_lt = 0;
    goal_spd_rt = 0;     
  }
  
}

//*****for arm ***************************************************
if (robotID=1){
  //if robotID=1 then arm mode

//GRIP:!!!!!!!!!!!!!!!!!!
// Grip open 
if(jscmd.b1) {
goal_spd_M6 = param[drive_mode].vel;
}

// Grip close
if(jscmd.b3) {
goal_spd_M6 = -param[drive_mode].vel;
}
//WRIST:
// Wrist right
if(jscmd.rt) {
goal_spd_M4 = param[drive_mode].vel;
goal_spd_M5 = param[drive_mode].vel;
}
// Wrist left
if(jscmd.lt) {
goal_spd_M4 = -param[drive_mode].vel;
goal_spd_M5 = -param[drive_mode].vel;
}
//Wrist up
if(jscmd.up) {
goal_spd_M4 = -param[drive_mode].vel;
goal_spd_M5 = param[drive_mode].vel;
}
//Wrist down
if(jscmd.dn) {
goal_spd_M4 = param[drive_mode].vel;
goal_spd_M5 = -param[drive_mode].vel;
}

//ELBOW:
//Elbow up
if(jscmd.L1) {
goal_spd_M3 = -param[drive_mode].vel;
}
//Elbow down
if(jscmd.L2) {
goal_spd_M3 = param[drive_mode].vel;
}

//SHOULDER:
//Shoulder up
if(jscmd.R1) {
goal_spd_M2 = param[drive_mode].vel;
}
//Shoulder down
if(jscmd.R2) {
goal_spd_M2 = -param[drive_mode].vel;
}

//BASE:
//Base left
if(jscmd.b2) {
goal_spd_M1 = -param[drive_mode].vel;
}
//Base right
if(jscmd.b4) {
goal_spd_M1 = param[drive_mode].vel;
  }
 }
} // set_goal_speed()

//*****end of setting goal speeds******************************
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
