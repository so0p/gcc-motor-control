Glendale Community College Robotics: Motor Controller Software
=====

Motor Controller built on Arduino

## Hardware Contained on Life of the Party Rover
* [RoboClaw Motor Controller](https://www.amazon.com/Orion-Robotics-R0413-RoboClaw-Controller/dp/B00R1LFTZ2?ie=UTF8&*Version*=1&*entries*=0) 
* [tm1638 LED display module](https://www.amazon.com/tm1638-display-module-digital-arduino/dp/b00w4j5tpg)
* [Arduino Mega 2560](https://www.arduino.cc/en/Main/arduinoBoardMega2560/)
* [XBee ZigBee](https://www.amazon.com/XBee-2mW-Wire-Antenna-ZigBee/dp/B007R9U1QA/ref=sr_1_4?ie=UTF8&qid=1506119916&sr=8-4&keywords=xbee+zigbee)
* [Wireless GamePad V2.0 for Arduino (XBee Socket)](https://www.dfrobot.com/product-858.html)


## Software: Table of Contents
1. Arduino Libraries : RoboClaw and LED Display Module Factory Drivers
2. MC_GamePad : Controls for the Wireless Gamepad
3. MC_MegaController : Software for the main arduino on the Life of the Party Rover. Contains gamepad decoding for motor controls, hill mode, robocla status updates, speed controls, display programming for LED display, and ludicrious mode.

### 1. [Arduino Libaries](https://github.com/khanoyan/gcc_motor_controller/tree/master/Arduino%20Libraries)
Contains Libraries for RoboClaw and tm1638 LED Display:

* RoboClaw
* tm1638

### 2. [MC_GamePad](https://github.com/khanoyan/gcc_motor_controller/tree/master/MC_GamePad)
Contains:
* MC_GamePad.ino


### 3. [MC_MegaController](https://github.com/khanoyan/gcc_motor_controller/tree/master/MC_MegaController)
Contains:
* MC_MegaController.ino
* drive_motors.ino
* process_joystick_inputs.ino
* set_new_speed.ino
* setup.ino
* tm1638.ino

###### Documentation Written by [Charlson So](github.com/so0p)
