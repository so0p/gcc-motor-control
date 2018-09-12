#include "Arduino.h"
#include "HelperFunctions.h"

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

//  if(drive_mode == LUDICROUS) {
//    led = led | 0x4;
//  }

  tm1.setLEDs(led);

} // refresh_tm1638()
