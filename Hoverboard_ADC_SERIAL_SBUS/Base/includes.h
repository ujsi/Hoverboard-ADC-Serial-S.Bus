#pragma once
//-----------------------------------------------------------------

// Standard Includes
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <errno.h>

// System Includes
#include "stm32f1xx.h"
#include "stm32f103xe.h"
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_conf.h"
#include "system_stm32f1xx.h"
#include "stm32f1_gpio_common.h"
#include "stm32f1_gpioa.h"
#include "stm32f1_gpiob.h"
#include "stm32f1_gpioc.h"

// Board Includes
#include "config.h"
#include "defines.h"

// Base Includes
#include "typedefs.h"
#include "systick.h"
#include "eeprom_base.h"
#include "eeprom.h"
#include "dwt.h"
#include "str_util.h"
#include "math_functions.h"
#include "num_con.h"
#include "cmd_interp.h"
#include "rc_sbus.h"
#include "serial.h"
//-----------------------------------------------------------------

typedef struct
{
  u16 rr1;
  u16 rr2;
  u16 rl1;
  u16 rl2;
  u16 dcr;
  u16 dcl;
  u16 batt1;
  u16 l_tx2;
  u16 temp;
  u16 l_rx2;
} tADC_BUF;
//-----------------------------------------------------------------

extern TIM_HandleTypeDef htim_left;
extern TIM_HandleTypeDef htim_right;
extern ADC_HandleTypeDef hadc1;
extern ADC_HandleTypeDef hadc2;
extern UART_HandleTypeDef huart2;

extern volatile tADC_BUF adc_buffer;
extern volatile int pwml; // Global variable for pwm left. -1000 to 1000
extern volatile int pwmr; // Global variable for pwm right. -1000 to 1000
extern volatile int weakl; // Global variable for field weakening left. -1000 to 1000
extern volatile int weakr; // Global variable for field weakening right. -1000 to 1000
extern u32 buzzer_freq; // Global variable for the buzzer pitch. can be 1, 2, 3, 4, 5, 6, 7...
extern u32 buzzer_pattern; // Global variable for the buzzer pattern. can be 1, 2, 3, 4, 5, 6, 7...
extern u32 timeout; // Global variable for motor enable
extern u8 enable; // Global variable for motor enable
extern float batteryVoltage; // Global variable for battery voltage
extern s32 speed_input; // Normalized input value (-1000 to 1000)
extern s32 steer_input; // Normalized input value (-1000 to 1000)
extern int speedL;
extern int speedR;
extern bool ee_valid; // Flag if the EEPROM data is valid
//-----------------------------------------------------------------

#ifdef __cplusplus
 extern "C" {
#endif
//-----------------------------------------------------------------

void systemclock_config(void);
void gpio_init(void);
void tim_init(void);
void adc1_init(void);
void adc2_init(void);
void usart2_control_init(void);
void usart3_debug_init(void);
void debug_set_chn(u8 ch, s16 val);
void debug_scope(void);
void serial_putc(char data);
void power_off(void);
void beep_control_mode(void);
void beep_bye(void);
void block_pwm(int pwm, int pos, int *u, int *v, int *w);
void block_phase_current(int pos, int u, int v, int *q);
void DMA1_Channel1_IRQHandler(void);
//-----------------------------------------------------------------

#ifdef __cplusplus
}
#endif
