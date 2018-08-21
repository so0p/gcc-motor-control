#include "Arduino.h"
#include "ThingSuite.h"
//#include "JoystickSuite.h"

ThingSuite::ThingSuite(){ 
  
// *******************************
// Global Variables       
// *******************************
  
thing_on =false; // getThing checks this value
lastTimeThingMessageRecieved = millis(); 
};

// **************************************************************
//     Serial Comm Functions
// **************************************************************

void ThingSuite::getThing(JoystickSuite &joystick){
  if(Serial1.available()>4){
    thing_on = true;
    joystick.lastTimeJSMessageRecieved = millis();
    Serial.println(F("thing is on"));
  }
  else{
    Serial.println(F("thing is off"));
    thing_on=false;
  }
  if(!joystick.xbee_on && thing_on){

    byte command_array[5];
    
    if (Serial1.available() > 4){            // if there are 4 or more than 4 bytes in the buffer go in the loop
      delay(100);
      Serial.print(F("getting packets"));
      Serial1.readBytes(command_array, 5);           // read the bytes
      joystick.drive_mode = SLOW;   // drive mode for arm and rover should be slow 
      if (command_array[0] == 183){                  // check for header to be 183
        if (joystick.mode == MODE_ROVER){              // if rover
          for(int j=0; j<5;j++){
            Serial.println(command_array[j]);
          }
          if (command_array[4] == 237){        // check that ending byte is 234
            Serial.print(F("setting direction"));                                  // if the ending byte is 234 then save data into the struct
            commands_to_mc.direction = command_array[1];
          }
          
          setThingSpeed(joystick);
          
          
        }
        
        else if (joystick.mode == MODE_ARM){

          Serial1.readBytes(command_array, 4);

          if (command_array[3] == 237){          // check for ending byte, if true then save bytes into struct

            commands_to_mc.direction = command_array[1];
            commands_to_mc.duration = command_array[2];
            commands_to_mc.motorNum = command_array[3];

          }
        }
      }
    }
    else {
      
      if(millis() - lastTimeThingMessageRecieved > 1000){
        joystick.rover_goal_spd_lt = 0;
        joystick.rover_goal_spd_rt = 0;  
      }     
    }
  }
}

void ThingSuite::setThingSpeed(JoystickSuite &joystick){
  if (joystick.mode==MODE_ROVER && !joystick.xbee_on && thing_on){
        //rover if robotID=0
        if(commands_to_mc.direction==1 && commands_to_mc.direction==3) {
          joystick.rover_goal_spd_lt = joystick.drive_parameters[joystick.drive_mode].vel - joystick.drive_parameters[joystick.drive_mode].diag;
          joystick.rover_goal_spd_rt = joystick.drive_parameters[joystick.drive_mode].vel + joystick.drive_parameters[joystick.drive_mode].diag;
          Serial.print(F("1"));    
        }
        else if(commands_to_mc.direction==1 && commands_to_mc.direction==4) {
          joystick.rover_goal_spd_lt = joystick.drive_parameters[joystick.drive_mode].vel + joystick.drive_parameters[joystick.drive_mode].diag;
          joystick.rover_goal_spd_rt = joystick.drive_parameters[joystick.drive_mode].vel - joystick.drive_parameters[joystick.drive_mode].diag;
          Serial.print(F("2"));    
        }
        else if(commands_to_mc.direction==2 && commands_to_mc.direction==3) {
          joystick.rover_goal_spd_lt = -joystick.drive_parameters[joystick.drive_mode].vel + joystick.drive_parameters[joystick.drive_mode].diag;
          joystick.rover_goal_spd_rt = -joystick.drive_parameters[joystick.drive_mode].vel - joystick.drive_parameters[joystick.drive_mode].diag;
          Serial.print(F("3"));    
        }
        else if(commands_to_mc.direction==2 && commands_to_mc.direction==4) {
          joystick.rover_goal_spd_lt = -joystick.drive_parameters[joystick.drive_mode].vel - joystick.drive_parameters[joystick.drive_mode].diag;
          joystick.rover_goal_spd_rt = -joystick.drive_parameters[joystick.drive_mode].vel + joystick.drive_parameters[joystick.drive_mode].diag;
          Serial.print(F("4"));    
        }  
        else if(commands_to_mc.direction==1) {
          joystick.rover_goal_spd_lt = joystick.drive_parameters[joystick.drive_mode].vel;
          joystick.rover_goal_spd_rt = joystick.drive_parameters[joystick.drive_mode].vel;
          Serial.print(F("5"));
        }
        else if(commands_to_mc.direction==2) {
          joystick.rover_goal_spd_lt = -joystick.drive_parameters[joystick.drive_mode].vel;
          joystick.rover_goal_spd_rt = -joystick.drive_parameters[joystick.drive_mode].vel;
          Serial.print(F("6"));
        }
        else if(commands_to_mc.direction==3) {
          joystick.rover_goal_spd_lt = -joystick.drive_parameters[joystick.drive_mode].vel;
          joystick.rover_goal_spd_rt = joystick.drive_parameters[joystick.drive_mode].vel;
          Serial.print(F("7"));    
        }
        else if(commands_to_mc.direction==4) {
          joystick.rover_goal_spd_lt = joystick.drive_parameters[joystick.drive_mode].vel;
          joystick.rover_goal_spd_rt = -joystick.drive_parameters[joystick.drive_mode].vel;
          Serial.print(F("8"));
        }
        else if(commands_to_mc.direction ==0){
          joystick.rover_goal_spd_lt = 0;
          joystick.rover_goal_spd_rt = 0;
        }  
  }
}
