#ifndef JOYSTICK_H
#define JOYSTICK_H
// Parse full packet from XBee interface and populate the joystick_command struct

// Reference to JoyStick
class JoyStick{
    struct JoystickCommands {
        bool linkActive;      // JS to Xbee Link is active
        bool up, dn, lt, rt;  // Up, Down, Left, Right
        bool r1, r2, l1, l2;  // Right1, Right2, Left1, Left2
        bool b1, b2, b3, b4;  // Button1, Button2, Button3, Button4
        bool st, se;          // Start, Select
        // TODO: add analogs
    };

    private:
        int pin_rx;
        int pin_tx;
        SoftwareSerial xbee;
        unsigned long count;
        JoystickCommands joystick_commands;
        unsigned long last_joystick_message_received_millis;
        bool xbee_on;

        void parse_xbee_byte();

    public:
        JoyStick();
        JoystickCommands get_joystick_data();
        void show_joystick_input();
        bool is_xbee_alive();



}
#endif
