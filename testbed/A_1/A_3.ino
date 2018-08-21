void loop() {
  
  // get current time in millis
  unsigned long cur_time = millis();

  if( (cur_time - Joystick_1.last_loop_time) >  LOOP_PERIOD_MS) {
    Joystick_1.last_loop_time = cur_time;
        // Serial.println("loop time ");
        // Serial.println(cur_time, DEC);

    //may not need since included in get joystick
    // Check if joystick is on

    //Checking before loop
    //    Serial.print("Before the motors - ");
    //    Serial.print("    curL: ");
    //    Serial.print(rover_cur_spd_lt, DEC);
    //    Serial.print("   curR: ");
    //    Serial.println(rover_cur_spd_rt, DEC);
    
    // Get JoyStick Commands
    Joystick_1.getJoystick(Danger_1);
    Serial.println(F("getJoystick done"));
    //    Serial.print("After get joystick - ");
    //    Serial.print("    curL: ");
    //    Serial.print(rover_cur_spd_lt, DEC);
    //    Serial.print("   curR: ");
    //    Serial.println(rover_cur_spd_rt, DEC);
    // Delta Motor Controls Added
    // 12/14/2017

    //***********
    // Get Thing
    //***********
    // Processing packets from SparkFun Thing sent from Wilbur
    Thing_1.getThing(Joystick_1);

    //***********
    // Get Danger
    //***********
    // Detects Bumper Collisions and Checks Currents
    Serial.println(F("DANGER READ BEFORE"));
    Danger_1.buttonStateFront_R = digitalRead(Danger_1.BUTTON_PIN_FRONT_R);
    Serial.println(Danger_1.buttonStateFront_R);
    Danger_1.buttonStateBack_R = digitalRead(Danger_1.BUTTON_PIN_BACK_R);
    Danger_1.buttonStateFront_L = digitalRead(Danger_1.BUTTON_PIN_FRONT_L);
    Danger_1.buttonStateBack_L = digitalRead(Danger_1.BUTTON_PIN_BACK_L);
          
    Danger_1.getDanger(Joystick_1);

    // TODO: process commands from future serial input
    // TBD....

    // If data comes in from serial monitor, send it out to XBee  
    // this is our debug route
    //    if (Serial.available()) {
    //      Serial.println("sending something...");
    //      XBee.write(Serial.read());
    //    }
  
    // set new speed based on time and current parameters
    setSpeed(Joystick_1,Danger_1,Thing_1);

    Serial.print(F("goalL: "));
    Serial.println(Joystick_1.rover_goal_spd_lt, DEC);
    Serial.print(F("   goalR: "));
    Serial.println(Joystick_1.rover_goal_spd_rt, DEC);
    Serial.println(F("After set speed"));
    Serial.print("    curL: ");
    Serial.println(Joystick_1.rover_cur_spd_lt, DEC);
    Serial.print(F("   curR: "));
    Serial.println(Joystick_1.rover_cur_spd_rt, DEC);
    //    Serial.print("battL: ");
    //    Serial.print(mcL_batt, DEC);
    //    Serial.print("   battR: ");
    //    Serial.print(mcR_batt, DEC);
    //    Serial.print("   jscnt: ");
    //    Serial.println(jscmd_cnt, DEC);
  

    // drive the newly calculated speed
    Motors_1.driveMotors(roboclaw1,roboclaw2,Joystick_1);

    // update the display status
    //TEMP refresh_tm1638();

    // update values of motor controller
    //getStatus();

    // send information up to web client
    //sendTelemetry();

    // check if arduino is alive
    //ping();
  
    // TODO: get MC battery levels. If 0, MC is not responding (ie: error)
    //get_roboclaw_status();
    
    // TODO: get button states from TM1638
    //process_tm1638_keys();
    
  } // big if 50Hz loop
  else {
    delay(LOOP_PERIOD_MS / 10);
  }
  
} // loop()

