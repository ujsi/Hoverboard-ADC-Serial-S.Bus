This hoverboard firmware can change between three control modes without programming.
  1. ADC control by two analog inputs like potentiometers.
  2. Serial Command Interpreter for extended control.
  3. Radio Controlled S.Bus controls up to 8 Boards with 16 motors, servos and other devices.

All three modes can be selected on the fly just by holding the button for a certain time.
//-----------------------------------------------------------------------------

Mode 1 (Analog Control) usually done with potentiometers. In this mode a terminal can be used to
receive debug data from USART3.
//-----------------------------------------------------------------------------

Mode 2 (Serial Command Interpreter) you can set the motor speed and steering, setup
the Control Mode, configure the S.Bus address for speed and steering motors and many more.
Here is a short overview of the Serial Commands:

const tCI_ITEM CI_TABLE[] = // Command Interpreter Table
{
  {CI_HASH2("sr"),   1, ci_software_reset,  "sr   Software Reset"},
  {CI_HASH1("x"),    1, ci_emergency,       "x    Emergency Power Off"},
  {CI_HASH4("EEE*"), 1, ci_ee_erase,        "EEE* EEPROM Erase"},
  {CI_HASH3("ees"),  1, ci_ee_save,         "ees  EEPROM Save Parameters"},
  {CI_HASH2("cm"),   1, ci_set_ctrl_mode,   "cm   Set Control Mode (1..3)"},
  {CI_HASH2("ss"),   1, ci_set_speed_steer, "ss   Set Speed and Steer Values (Speed Value, Steer Value)"},
  {CI_HASH2("sp"),   1, ci_set_speed,       "sp   Set Speed Value (-1000..1000)"},
  {CI_HASH2("st"),   1, ci_set_steer,       "st   Set Steer Value (-1000..1000)"},
  {CI_HASH4("sbsp"), 1, ci_set_sbus_speed,  "sbsp Set S.Bus Speed Address (1..16)"},
  {CI_HASH4("sbst"), 1, ci_set_sbus_steer,  "sbst Set S.Bus Steering Address (1..16)"},
  {CI_HASH3("sbh"),  1, ci_set_sbus_hold,   "sbh  Set S.Bus Hold last values on Error (0..1)"},
  {CI_HASH3("ee?"),  1, ci_ee_get_params,   "ee?  Get EEPROM Parameters"},
  {CI_HASH1("?"),    1, ci_get_help,        "?    Get Help"},
  {0,                0, NULL,               NULL} // End of table
};
//-----------------------------------------------------------------------------

Mode 3 (S.Bus) is widely used and is the de facto standard in model making industry. 
It´s a very versatile bus system, developed by Futaba / Robbe around 2010. With up to 16
channels with just one wire! you can control different devices like servos, motors (bushed or 
brushless) by ESC and some more. In this mode a terminal can be used to receive debug data from USART3.
To receive valid S.Bus protocols the output signal must be inverted by a simple electronic patch.
//-----------------------------------------------------------------------------

How to change the Control Mode
After flashing this firmware connect the board and turn it on. You will not hear the normal
sound melody, but instead you hear beeps accordingly to the selected control mode (2 is default). 
One beep for ADC control mode, two beeps for Serial Command Interpreter control mode
and three beeps for RC-S.Bus control mode. To change the control mode turn on the board and 
keep the button pressed. After 3 seconds you will hear beeps of the next command mode. 
If you keep the button pressed, then the next mode is selected - and so on. After mode 3 
(RC-S.Bus) the next mode will be 1 (ADC) again. Simply release the button after the desired 
mode is selected. The board will directly start in the new mode.
//-----------------------------------------------------------------------------

Programming Connector SWD
  +3.3V // Can be used as supply for analog inputs (max. 30mA)
  SWCLK  
  GND
  SWDIO
//-----------------------------------------------------------------------------

Sideboard Right 
  Blue  = PB10, USART3 Tx, 100kBit
  Green = PB11, S.Bus USART3 Rx, 100kBit
  Black = GND
  Red   = +15V, Do Not Connect!

Sideboard Left 
  Blue  = PA2, ADC Speed, USART2 Tx 
  Green = PA3, ADC Steering, USART2 Rx 
  Black = GND
  Red   = +15V, Do Not Connect!

6-Pin Connector                               Sideboards
                                      Right                Left
                                   gr        bl        bl        gr
                                   |         |         |         |
Female Connector     GND +3V3     PB11_Rx   PB10_Tx   PB10      PB11
ADC                  GND +3V3                         PA2_Spd   PA3_Steer 
Male S.Bus Receiver  GND +3V3     PB11_Rx
Male Serial Debug    GND +3V3               PB10_Tx
Male Serial Control  GND +3V3                         PA2_Tx    PA3_Rx
