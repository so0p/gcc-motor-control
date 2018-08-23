/*****************************************************************
MC_MegaConotroller.ino

NOTE: This code only compiles on Arduino Mega 2560 as it requires
the 4 hardware serial ports.

Set up a software serial port to pass data between an XBee Shield
and the serial monitor.

Hardware Hookup:
  The XBee Shield makes all of the connections you'll need
  between Arduino and XBee. If you have the shield make
  sure the SWITCH IS IN THE "DLINE" POSITION. That will connect
  the XBee's DOUT and DIN pins to Arduino pins 2 and 3.

*****************************************************************/

// **************************************************************
//     LIBRARIES
// **************************************************************

//Includes required to use Roboclaw library
#include "RoboClaw.h"

// We'll use SoftwareSerial to communicate with the XBee:
#include <SoftwareSerial.h> // <--- not needed, already included in headers for RoboClaw.h and GlobalData.h

//OBSOLETE #include "GlobalData.h" // used to generate instances of global variables
#include "JoystickSuite.h" // incorporates several functions into a single structure
#include "DangerSuite.h"
#include "ThingSuite.h"
#include "MotorSuite.h"
#include "HelperFunctions.h"

// for TM1638 display unit
#include "TM1638.h"

//#define cmdDelay 150 // WHAT IS THIS USED FOR?

// Digital output for visual indication of Ludicrous mode
#define BIGLIGHT_PIN 31

// *****************************
// Global Objects Initialization
// *****************************

JoystickSuite Joystick_1(11,10); // (RX, TX) <- data pins
DangerSuite Danger_1;
ThingSuite Thing_1;
MotorSuite Motors_1;

// ************************
//        ROBOCLAW
// ************************

//Setup communcaitions with roboclaw. Use pins 10 and 11 with 10ms timeout
//For Rover, claw1 is L, claw2 is right
//For Arm,

// .. and Hardware Serial (on the Arduino MEGA) for RoboClaw control
#include <HardwareSerial.h>

RoboClaw roboclaw1(&Serial2,10000);
RoboClaw roboclaw2(&Serial3,10000); // 2
//RoboClaw roboclaw3(&Serial1, 10000);

// *******************
// setup TM1638 module
// *******************

// pin 48: data    pin 50: clock    pin 52: strobe
TM1638 tm1638(48, 50, 52);
