#ifndef JoystickSuite_h
#define joystickSuite_h
#include <SoftwareSerial.h>
#include "GlobalData.h"

void getJoystick(GlobalData& data, SoftwareSerial& xbeeData);
void show_joystick_inputs(GlobalData& data);
void set_goal_speed(GlobalData& data, SoftwareSerial& xbeeData);
void parse_xbee_byte(GlobalData& data, SoftwareSerial& xbeeData);

#endif
