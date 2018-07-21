/*************************

  Get Thing

  Parses Commands from Web Client. Header value of packet should be 183 and Footer is 237

**************************/

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



