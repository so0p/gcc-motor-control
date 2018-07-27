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

  jscmd.linkActive = true; // override this value until we check for it
  jscmd.up = false;
  jscmd.dn = false;
  jscmd.lt = false;
  jscmd.rt = false;
  jscmd.b1 = false;
  jscmd.b2 = false;
  jscmd.b3 = false;
  jscmd.b4 = false;
  jscmd.r1 = false;
  jscmd.r2 = false;
  jscmd.l1 = false;
  jscmd.l2 = false;
  jscmd.st = false;
  jscmd.se = false;

  // populate drive param 
  param[SLOW].vel       = ROVER_VEL_SLOW;
  param[SLOW].ramp      = ROVER_RAMP_RATE_SLOW;
  param[SLOW].thr       = ROVER_THR_SLOW;
  param[SLOW].diag      = DIAG_OFFSET_SLOW;
  param[FAST].vel       = ROVER_VEL_FAST;
  param[FAST].ramp      = ROVER_RAMP_RATE_FAST;
  param[FAST].thr       = ROVER_THR_FAST;
  param[FAST].diag      = DIAG_OFFSET_FAST;  
  param[ARM].vel        = ARM_VEL;
  param[ARM].ramp       = ARM_RAMP_RATE;
  param[ARM].thr        = ARM_THR;
   

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
  xbee_counter=0;

  //Initalizing Bumper Pins
  pinMode(BUTTON_PIN_FRONT_R, INPUT_PULLUP);
  pinMode(BUTTON_PIN_FRONT_L, INPUT_PULLUP);
  pinMode(BUTTON_PIN_BACK_R, INPUT_PULLUP);
  pinMode(BUTTON_PIN_BACK_L, INPUT_PULLUP);

  //get the time
  lastTimeJSMessageRecieved = millis();
  lastTimeThingMessageRecieved = millis();
} // setup()
