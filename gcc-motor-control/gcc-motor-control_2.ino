void setup() {
  /* <--- JoystickSuite.h
  // Set up both ports at 9600 baud. This value is most important
  // for the XBee. Make sure the baud rate matches the config
  // setting of your XBee.
  XBee.begin(9600);*/

  // ***********
  // DEBUG MODES // Enable/disable debug messages for objects/main 
  // ***********

  debugMain = false; // Main loop debug messages
  Joystick_1.debugMode = true;
  Danger_1.debugMode = false;
  Motors_1.debugMode = false;

  Serial.begin(57600);
  if(debugMain == true)
    Serial.println(F("SETUP START"));
  //For Thing on Web Control
  //Serial1.begin(115200);
  Serial2.begin(115200);
  Serial3.begin(115200);
  
  //Open roboclaw serial ports
  roboclaw1.begin(38400);
  roboclaw2.begin(38400);

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
  Joystick_1.serialPtr->flush();

  //set the counter to 0
  Joystick_1.xbee_counter=0;

  if(debugMain == true)
    Serial.println(F("SETUP END")); //DEBUG MSG
} // setup()
