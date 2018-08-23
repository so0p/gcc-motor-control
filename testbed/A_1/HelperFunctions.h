#ifndef HelperFunctions_h
#define HelperFunctions_h
#include "ThingSuite.h"
#include "DangerSuite.h"
#include "MotorSuite.h"
#include "TM1638.h"

void setSpeed(JoystickSuite& joystick,DangerSuite& danger,ThingSuite& thing);
void process_tm1638_keys(TM1638& tm1,JoystickSuite& joystick);
void refresh_tm1638(TM1638& tm1,JoystickSuite& joystick, MotorSuite& motors);
    
#endif // HELPERFUNCTIONS_H
