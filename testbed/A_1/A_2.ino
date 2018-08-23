void setup() {
  /* <--- JoystickSuite.h
  // Set up both ports at 9600 baud. This value is most important
  // for the XBee. Make sure the baud rate matches the config
  // setting of your XBee.
  XBee.begin(9600);*/
  
  Serial.begin(57600);
  Serial.println(F("SETUP START")); //DEBUG MSG

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
  Serial.println(F("PRE FLUSH")); //DEBUG MSG
  Joystick_1.serialPtr->flush();
  Serial.println(F("PAST FLUSH")); //DEBUG MSG

  //set the counter to 0
  Joystick_1.xbee_counter=0;
  
  Serial.println(F("SETUP END")); //DEBUG MSG
} // setup()

