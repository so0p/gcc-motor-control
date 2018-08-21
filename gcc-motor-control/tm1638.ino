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

