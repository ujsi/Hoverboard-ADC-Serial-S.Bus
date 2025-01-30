// Module..: MAIN.C
// Version.: 1.0
// Compiler: GCC-ARM
// Chip....: STM32F103xx
// Date....: January 2025
//-----------------------------------------------------------------------------

static s32 speed; // Global variable for speed (-1000 to 1000)
static s32 steer; // Global variable for steering (-1000 to 1000)
static u32 inactivity_timeout_counter;
s32 speed_input; // Normalized speed input value (-1000 to 1000)
s32 steer_input; // Normalized steer input value (-1000 to 1000)
int speedL;
int speedR;
u32 timeout;
bool btn_long_pressed;
bool ee_valid;
u8 no_init __attribute__ ((section (".noinit")));
//-----------------------------------------------------------------------------

int main(void)
{
  float board_temp_adc_filtered = (float)adc_buffer.temp;
  float board_temp_deg_c;
  int lastSpeedL = 0, lastSpeedR = 0;

  __HAL_RCC_AFIO_CLK_ENABLE();
  HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);
  HAL_NVIC_SetPriority(MemoryManagement_IRQn, 0, 0);
  HAL_NVIC_SetPriority(BusFault_IRQn, 0, 0);
  HAL_NVIC_SetPriority(UsageFault_IRQn, 0, 0);
  HAL_NVIC_SetPriority(SVCall_IRQn, 0, 0);
  HAL_NVIC_SetPriority(DebugMonitor_IRQn, 0, 0);
  HAL_NVIC_SetPriority(PendSV_IRQn, 0, 0);
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);

  systemclock_config();
  __HAL_RCC_DMA1_CLK_DISABLE();
  gpio_init();
  tim_init();
  adc1_init();
  adc2_init();
  systick_init(); // Initialize the system timer
  dwt_init(); // Initialize the Data Watchpoint and Trace unit
  ee_init(); // Initialize the Pseudo EEPROM
  ee_valid = ee_validate(); // Check the EEPROM data

  switch (ee.ctrl_mode) // Initialize the modules for all three Control Modes
  {
    case eCM_ADC: // Mode ADC
      usart3_debug_init(); // Send Debug data (100kBit, parity even, 2 Stopbits)
    break;
    case eCM_SERIAL: // Mode Serial
      nc_init(); // Initialize the Numeric Converter
      ci_init(); // Initialize the Command Interpreter
      serial_init(); // Initialize the Serial Command Terminal USART2 (PA2 Tx, PA3 Rx)
    break;
    case eCM_RC_SBUS: // Mode RC-S.BUS
      rc_init(); // Initialize the RC-SBUS Interface, receive RC-SBus protocol
      usart3_debug_init(); // Send Debug data (100kBit, parity even, 2 Stopbits)
    break;
    default:
      usart3_debug_init(); // Send Debug data (100kBit, parity even, 2 Stopbits)
    break;
  }

  GPIOA_5_SET(); // Set the OFF_PORT pin PA5

  HAL_ADC_Start(&hadc1);
  HAL_ADC_Start(&hadc2);

  if (no_init != 0xDA) // Don´t process the session if warm start is active
  {
    beep_control_mode(); // Control modes: 1 = ADC, 2 = Serial, 3 = RC-S.BUS
    systick_button_counter = 0; // Clear Button pressed counter
    bool btn_long_pressed = false;
    u32 button_compare = 3000;

    while (GPIOA_1_GET())
    {
      GPIOB_2_SET(); // Blink the LED fast until the button is released
      dwt_delay_ms(50);
      GPIOB_2_CLR();
      dwt_delay_ms(50);

      if (systick_button_counter > button_compare) // After 3s of holding the Button down
      {
        btn_long_pressed = true; // Set the flag to save a new Control Mode in EEPROM

        while (GPIOA_1_GET()) // Repeat as long as the Button is pressed
        {
          if (systick_button_counter > button_compare) // Do this loop every 3s
          {
            button_compare += 3000; // 3s more for a next loop

            if (++ee.ctrl_mode > eCM_RC_SBUS) // Increase the Control Mode
            {
              ee.ctrl_mode = eCM_ADC; // Reset to first Control Mode
            }

            beep_control_mode(); // Control modes: 1 = ADC, 2 = Serial, 3 = RC-S.BUS
          }
        }
      }
    }

    if (btn_long_pressed) // Check if a new Control Mode is selected
    {
      if (!ee_save()) // Save the actual Control Mode in EEPROM
      {
        for (int n = 0; n < 8; n++) // Beep out EEPROM Error
        {
          buzzer_freq = 8;
          dwt_delay_ms(250);
          buzzer_freq = 0;
          dwt_delay_ms(250);
        }
      }

      no_init = 0xDA; // Set the flag for warm start
      NVIC_SystemReset(); // Perform a warm start
    }
  }

  no_init = 0;
  enable = 1; // Enable motors

  while (1) // Main program loop
  {
    while (systick_main_loop_counter < DELAY_IN_MAIN_LOOP - 1) // Delay loop with some tasks
    {
      if (ee.ctrl_mode == eCM_SERIAL) // Check for Control Mode Serial
      {
        serial_check(); // Check if any Serial Command line is present
      }

      if (systick_led_counter >= 500) // Toggle the LED twice a second
      {
        systick_led_counter = 0; // Reset LED counter
        GPIOB_2_TGL(); // Toggle LED
      }
    }

    systick_main_loop_counter = 0; // Reset main loop counter

    if (ee.ctrl_mode == eCM_RC_SBUS) // Check for Control Mode RC-S.BUS
    {
      if (rc_ready) // Check for a complete RC-SBus protocol
      {
        rc_update(); // Decode RC channel data

        if ((rc_valid == true) && (rc_failsafe == false)) // Check if the RC-S.BUS data is valid
        {
          speed_input = rc_chn[ee.sbus_speed_addr]; // Assign speed value
          steer_input = rc_chn[ee.sbus_steer_addr]; // Assign steering value
        }
        else if (!ee.sbus_hold) // Invalid RC-S.BUS protocol
        {
          speed_input = 0;
          steer_input = 0;
        }
      }
    }
    else if (ee.ctrl_mode == eCM_ADC) // Check for Control Mode ADC, values range: 0 to 4095
    {
      speed_input = mf_limit_s16(adc_buffer.l_tx2 - ADC_CENTER, INP_NORM_VALUE);
      steer_input = mf_limit_s16(adc_buffer.l_rx2 - ADC_CENTER, INP_NORM_VALUE);
    }

    timeout = 0;
    steer = steer * (1.0f - FILTER) + speed_input * FILTER; // Low pass filter
    speed = speed * (1.0f - FILTER) + steer_input * FILTER;
    speedR = LIMIT(speed * SPEED_COEFFICIENT - steer * STEER_COEFFICIENT, -INP_NORM_VALUE, INP_NORM_VALUE); // Mixer
    speedL = LIMIT(speed * SPEED_COEFFICIENT + steer * STEER_COEFFICIENT, -INP_NORM_VALUE, INP_NORM_VALUE);

#define MAX_CHANGE_SPEED (200)
    if (((speedL < lastSpeedL + MAX_CHANGE_SPEED) && (speedL > lastSpeedL - MAX_CHANGE_SPEED)) && // Set outputs
        ((speedR < lastSpeedR + MAX_CHANGE_SPEED) && (speedR > lastSpeedR - MAX_CHANGE_SPEED)) && (timeout < TIMEOUT))
    {
#ifdef INVERT_R_DIRECTION
      pwmr = speedR;
#else
      pwmr = -speedR;
#endif

#ifdef INVERT_L_DIRECTION
      pwml = -speedL;
#else
      pwml = speedL;
#endif
    }

    lastSpeedL = speedL;
    lastSpeedR = speedR;

    if (systick_debug_counter >= 200) // Set debug values
    {
      systick_debug_counter = 0;
      board_temp_adc_filtered = board_temp_adc_filtered * 0.99f + (float)adc_buffer.temp * 0.01f;
      board_temp_deg_c = ((float)TEMP_CAL_HIGH_DEG_C - (float)TEMP_CAL_LOW_DEG_C) / ((float)TEMP_CAL_HIGH_ADC - (float)TEMP_CAL_LOW_ADC) * (board_temp_adc_filtered - (float)TEMP_CAL_LOW_ADC) + (float)TEMP_CAL_LOW_DEG_C;
      debug_set_chn(0, (int)speed_input); // 1: Speed_input
      debug_set_chn(1, (int)steer_input); // 2: Steering_input
      debug_set_chn(2, (int)speedR); // 3: Output speed: -1000..1000
      debug_set_chn(3, (int)speedL); // 4: Output speed: -1000..1000
      debug_set_chn(4, (int)pwmr);  // 5: PWM right motor
      debug_set_chn(5, (int)pwml); // 6: PWM left motor
      debug_set_chn(6, (int)board_temp_adc_filtered); // 7: For board temperature calibration
      debug_set_chn(7, (int)board_temp_deg_c); // 8: For verifying board temperature calibration
      debug_scope();
    }

    if (GPIOA_1_GET() && (weakr == 0) && (weakl == 0)) // Check the power button
    {
      enable = 0;

      while (GPIOA_1_GET()) // Blink LED fast until button released
      {
        buzzer_freq = 5;
        GPIOB_2_SET();
        dwt_delay_ms(50);
        GPIOB_2_CLR();
        dwt_delay_ms(50);
      }

      buzzer_freq = 0;
      power_off(); // Turn off the supply
    }

    if ((TEMP_POWEROFF_ENABLE && board_temp_deg_c >= TEMP_POWEROFF && abs(speed) < 20) ||
        (batteryVoltage < ((float)BAT_LOW_DEAD * (float)BAT_NUMBER_OF_CELLS) && abs(speed) < 20))
    { // Poweroff before mainboard burns OR low bat 3
      power_off();
    }
    else if (TEMP_WARNING_ENABLE && board_temp_deg_c >= TEMP_WARNING)
    { // Beep if mainboard gets hot
      buzzer_freq = 4;
      buzzer_pattern = 1;
    }
    else if (batteryVoltage < ((float)BAT_LOW_LVL1 * (float)BAT_NUMBER_OF_CELLS) && batteryVoltage > ((float)BAT_LOW_LVL2 * (float)BAT_NUMBER_OF_CELLS) && BAT_LOW_LVL1_ENABLE)
    { // Low bat 1: slow beep
      buzzer_freq = 5;
      buzzer_pattern = 42;
    }
    else if (batteryVoltage < ((float)BAT_LOW_LVL2 * (float)BAT_NUMBER_OF_CELLS) &&
      batteryVoltage > ((float)BAT_LOW_DEAD * (float)BAT_NUMBER_OF_CELLS) && BAT_LOW_LVL2_ENABLE)
    { // Low bat 2: fast beep
      buzzer_freq = 5;
      buzzer_pattern = 6;
    }
    else if (BEEPS_BACKWARD && speed < -50) // Backward beep
    {
      buzzer_freq = 5;
      buzzer_pattern = 1;
    }
    else // Do not beep
    {
      buzzer_freq = 0;
      buzzer_pattern = 0;
    }

    if (abs(speedL) > 200 || abs(speedR) > 200) // Check for inactivity timeout
    {
      inactivity_timeout_counter = 0;
    }
    else
    {
      inactivity_timeout_counter++;
    }

    if (inactivity_timeout_counter > (INACTIVITY_TIMEOUT * 60 * 1000) / (DELAY_IN_MAIN_LOOP + 1))
    {
      power_off();
    }

    timeout++;
  }
}
//-----------------------------------------------------------------------------

void beep_bye(void)
{
  for (int i = 0; i < 8; i++) // Play shutdown sound
  {
    buzzer_freq = i;
    dwt_delay_ms(50);
  }
}
//-----------------------------------------------------------------------------

void beep_control_mode(void) // Control modes: 1 = ADC, 2 = Serial, 3 = RC-S.BUS
{
  for (int i = 1; i <= ee.ctrl_mode; i++) // Beep out the actual Control mode
  {
    buzzer_freq = 8;
    dwt_delay_ms(250);
    buzzer_freq = 0;
    dwt_delay_ms(250);
  }
}
//-----------------------------------------------------------------------------

void power_off(void)
{
  buzzer_pattern = 0;
  beep_bye();
  enable = 0;
  GPIOA_5_CLR(); // Turn off the supply

  while (1);
}
