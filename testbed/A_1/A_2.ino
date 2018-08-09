void setup() {
  /* <--- JoystickSuite.h
  // Set up both ports at 9600 baud. This value is most important
  // for the XBee. Make sure the baud rate matches the config
  // setting of your XBee.
  XBee.begin(9600);*/
  Serial.begin(57600);
  Serial.println("SETUP START"); //DEBUG MSG

  //For Thing on Web Control
  //Serial1.begin(115200);
  Serial2.begin(115200);
  Serial3.begin(115200);
  
  //Open roboclaw serial ports
  roboclaw1.begin(38400);
  roboclaw2.begin(38400);

  /* <--- JoyStick.h
  Joystick_1.linkActive = true; // override this value until we check for it
  Joystick_1.up = false;
  Joystick_1.dn = false;
  Joystick_1.lt = false;
  Joystick_1.rt = false;
  Joystick_1.b1 = false;
  Joystick_1.b2 = false;
  Joystick_1.b3 = false;
  Joystick_1.b4 = false;
  Joystick_1.r1 = false;
  Joystick_1.r2 = false;
  Joystick_1.l1 = false;
  Joystick_1.l2 = false;
  Joystick_1.st = false;
  Joystick_1.se = false;

  // populate the elements of the DRIVE_PARAM struct array 
  Joystick_1.drive_parameters[SLOW].vel       = ROVER_VEL_SLOW;
  Joystick_1.drive_parameters[SLOW].ramp      = ROVER_RAMP_RATE_SLOW;
  Joystick_1.drive_parameters[SLOW].thr       = ROVER_THR_SLOW;
  Joystick_1.drive_parameters[SLOW].diag      = DIAG_OFFSET_SLOW;
  Joystick_1.drive_parameters[FAST].vel       = ROVER_VEL_FAST;
  Joystick_1.drive_parameters[FAST].ramp      = ROVER_RAMP_RATE_FAST;
  Joystick_1.drive_parameters[FAST].thr       = ROVER_THR_FAST;
  Joystick_1.drive_parameters[FAST].diag      = DIAG_OFFSET_FAST;  
  Joystick_1.drive_parameters[ARM].vel        = ARM_VEL;
  Joystick_1.drive_parameters[ARM].ramp       = ARM_RAMP_RATE;
  Joystick_1.drive_parameters[ARM].thr        = ARM_THR;*/
   

  // connect to TM1638 module
  // display a hexadecimal number and set the left 4 dots
  //tm1638.setDisplayToHexNumber(0x6CC, 0xF0);
  char s[8];
  sprintf(s, " HELLO ");
  tm1638.setDisplayToString(s);
  tm1638.setLEDs(0x0);
  delay(500);

  pinMode(BIGLIGHT_PIN, OUTPUT);
  
  /* <--- JoystickSuite.h
  // flush XBee serial stream before we get into loop()
  XBee.flush();*/
  Joystick_1.serialPtr->flush();

  /* <--- JoystickSuite.h
  //set the counter to 0
  Joystick_1.xbee_counter=0;*/

  /* <--- JoystickSuite.h
  ///Initalizing Bumper Pins
  pinMode(Joystick_1.BUTTON_PIN_FRONT_R, INPUT_PULLUP);
  pinMode(Joystick_1.BUTTON_PIN_FRONT_L, INPUT_PULLUP);
  pinMode(Joystick_1.BUTTON_PIN_BACK_R, INPUT_PULLUP);
  pinMode(Joystick_1.BUTTON_PIN_BACK_L, INPUT_PULLUP);

  //get the time
  Joystick_1.lastTimeJSMessageRecieved = millis();
  Joystick_1.lastTimeThingMessageRecieved = millis();*/
  Serial.println("SETUP END"); //DEBUG MSG
} // setup()

