#pragma once
//-----------------------------------------------------------------

#define PWM_FREQ (16000) // PWM frequency in Hz
#define DEAD_TIME (32) // PWM deadtime
#define DELAY_IN_MAIN_LOOP (5) // ms, default 5. it is independent of all the timing critical stuff. do not touch if you do not know what you are doing.
#define TIMEOUT (5) // Number of wrong / missing input commands before emergency off
#define START_FRAME (0xAAAA) // Serial command start-of-frame magic word
#define INP_NORM_VALUE (1000.0f) // Normalize value for inputs
// How to calibrate: connect GND and RX of a 3.3v uart-usb adapter to the right sensor
// board cable (be careful not to use the red wire of the cable. 15v will destroy everything
// if you are using nunchuck, disable it temporarily. Enable USART3 and
// DEBUG_SERIAL_ASCII use serial terminal.
// Battery voltage calibration: connect power source. see <How to calibrate>.
// Write value nr 5 to BAT_CALIB_ADC. make and flash firmware. then you can verify
// voltage on value 6 (devide it by 100.0 to get calibrated voltage).
#define BAT_CALIB_REAL_VOLTAGE (43.0f) // Input voltage measured by multimeter
#define BAT_CALIB_ADC (1704) // ADC-value measured by mainboard (value nr 5 on UART debug output)

#define BAT_NUMBER_OF_CELLS (10) // Normal Hoverboard battery: 10s
#define BAT_LOW_LVL1_ENABLE (0) // Beep or not to beep, 1 or 0
#define BAT_LOW_LVL1 (3.6f) // Gently beeps at this voltage level. [V/cell]
#define BAT_LOW_LVL2_ENABLE (1) // Beep or not to beep, 1 or 0
#define BAT_LOW_LVL2 (3.5f) // Battery is almost empty. Charge now! [V/cell]
#define BAT_LOW_DEAD (3.37f) // Undervoltage poweroff. (while not driving) [V/cell]

#define DC_CUR_LIMIT (15) // DC current limit in amps per motor. so 15 means it will draw 30A out of your battery. it does not disable motors, it is a soft current limit.

// Board overheat detection: the sensor is inside the STM/GD chip. it is very inaccurate without calibration (up to 45°C). so only enable this funcion after calibration! let your board cool down. see <How to calibrate>. get the real temp of the chip by thermo cam or another temp-sensor taped on top of the chip and write it to TEMP_CAL_LOW_DEG_C. write debug value 8 to TEMP_CAL_LOW_ADC. drive around to warm up the board. it should be at least 20°C warmer. repeat it for the HIGH-values. enable warning and/or poweroff and make and flash firmware.
#define TEMP_CAL_LOW_ADC (1655) // Temperature 1: ADC value
#define TEMP_CAL_LOW_DEG_C (35.8f) // Temperature 1: measured temperature [°C]
#define TEMP_CAL_HIGH_ADC (1588) // Temperature 2: ADC value
#define TEMP_CAL_HIGH_DEG_C (48.9f) // Temperature 2: measured temperature [°C]
#define TEMP_WARNING_ENABLE (0) // Beep or not to beep, 1 or 0, DO NOT ACTIVITE WITHOUT CALIBRATION!
#define TEMP_WARNING (60) // Annoying fast beeps [°C]
#define TEMP_POWEROFF_ENABLE (0) // Poweroff or not to poweroff, 1 or 0, DO NOT ACTIVITE WITHOUT CALIBRATION!
#define TEMP_POWEROFF (65) // Overheat poweroff. (while not driving) [°C]

#define INACTIVITY_TIMEOUT (8) // Minutes of not driving until poweroff. It is not very precise

#define DEBUG_SERIAL_USART3 // Right sensor board cable, disable if I2C (nunchuck or lcd) is used!
#define DEBUG_BAUD (100000) // 100kBit USART3 baud rate because of receive RC-SBus
#define DEBUG_SERIAL_ASCII // "1:345 2:1337 3:0 4:0 5:0 6:0 7:0 8:0\r\n"

// ADC-calibration to cover the full poti-range: connect potis to left sensor
// board cable (0 to 3.3V) (do NOT use the red 15V wire in the cable!).
// See <How to calibrate>. turn the potis to minimum position, write value 1 to
// ADC1_MIN and value 2 to ADC2_MIN. turn to maximum position and repeat it for
// ADC2_MAX. make, flash and test it
#define ADC_MAX (4095)
#define ADC_CENTER (ADC_MAX / 2)
#define ADC1_MIN (0) // Min ADC1-value while poti at minimum-position (0 - 4095)
#define ADC1_MAX (4095) // Max ADC1-value while poti at maximum-position (0 - 4095)
#define ADC2_MIN (0) // Min ADC2-value while poti at minimum-position (0 - 4095)
#define ADC2_MAX (4095) // Max ADC2-value while poti at maximum-position (0 - 4095)

#define FILTER (0.5f) // Lower value == softer filter. Do not use values < 0.01, you will get float precision issues
#define SPEED_COEFFICIENT (0.5f) // Higher value == stronger. 0.0 to ~2.0?
#define STEER_COEFFICIENT (0.5f) // Higher value == stronger. if you do not want any steering, set it to 0.0; 0.0 to 1.0
#define INVERT_R_DIRECTION
#define INVERT_L_DIRECTION
#define BEEPS_BACKWARD (1)
