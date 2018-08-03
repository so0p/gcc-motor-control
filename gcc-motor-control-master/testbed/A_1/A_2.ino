void setup() {
  // Set up both ports at 9600 baud. This value is most important
  // for the XBee. Make sure the baud rate matches the config
  // setting of your XBee.
  XBee.begin(9600);
  Serial.begin(57600);

  //For Thing on Web Control
  Serial1.begin(115200);
  Serial2.begin(115200);
  Serial3.begin(115200);


  //Open roboclaw serial ports
  roboclaw1.begin(38400);
  //roboclaw2.begin(38400);

  global_vars.linkActive = true; // override this value until we check for it
  global_vars.up = false;
  global_vars.dn = false;
  global_vars.lt = false;
  global_vars.rt = false;
  global_vars.b1 = false;
  global_vars.b2 = false;
  global_vars.b3 = false;
  global_vars.b4 = false;
  global_vars.r1 = false;
  global_vars.r2 = false;
  global_vars.l1 = false;
  global_vars.l2 = false;
  global_vars.st = false;
  global_vars.se = false;

  // populate the elements of the DRIVE_PARAM struct array 
  global_vars.drive_parameters[SLOW].vel       = ROVER_VEL_SLOW;
  global_vars.drive_parameters[SLOW].ramp      = ROVER_RAMP_RATE_SLOW;
  global_vars.drive_parameters[SLOW].thr       = ROVER_THR_SLOW;
  global_vars.drive_parameters[SLOW].diag      = DIAG_OFFSET_SLOW;
  global_vars.drive_parameters[FAST].vel       = ROVER_VEL_FAST;
  global_vars.drive_parameters[FAST].ramp      = ROVER_RAMP_RATE_FAST;
  global_vars.drive_parameters[FAST].thr       = ROVER_THR_FAST;
  global_vars.drive_parameters[FAST].diag      = DIAG_OFFSET_FAST;  
  global_vars.drive_parameters[ARM].vel        = ARM_VEL;
  global_vars.drive_parameters[ARM].ramp       = ARM_RAMP_RATE;
  global_vars.drive_parameters[ARM].thr        = ARM_THR;
   

  // connect to TM1638 module
  // display a hexadecimal number and set the left 4 dots
  //tm1638.setDisplayToHexNumber(0x6CC, 0xF0);
  char s[8];
  sprintf(s, " HELLO ");
  tm1638.setDisplayToString(s);
  tm1638.setLEDs(0x0);
  delay(500);

  pinMode(BIGLIGHT_PIN, OUTPUT);
  // flush XBee serial stream before we get into loop()
  XBee.flush();

  //set the counter to 0
  global_vars.xbee_counter=0;

  //Initalizing Bumper Pins
  pinMode(global_vars.BUTTON_PIN_FRONT_R, INPUT_PULLUP);
  pinMode(global_vars.BUTTON_PIN_FRONT_L, INPUT_PULLUP);
  pinMode(global_vars.BUTTON_PIN_BACK_R, INPUT_PULLUP);
  pinMode(global_vars.BUTTON_PIN_BACK_L, INPUT_PULLUP);

  //get the time
  global_vars.lastTimeJSMessageRecieved = millis();
  global_vars.lastTimeThingMessageRecieved = millis();
} // setup()
