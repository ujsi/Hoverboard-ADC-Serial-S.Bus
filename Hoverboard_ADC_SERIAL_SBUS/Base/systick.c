// Module..: SYSTICK.C
// Version.: 1.0
// Compiler: GCC-ARM
// Date....: January 2025
// Author..: Udo Juerss
//-----------------------------------------------------------------------------

volatile u32 systick_count_up;
volatile u32 systick_main_loop_counter;
volatile u32 systick_debug_counter;
volatile u32 systick_button_counter;
volatile u32 systick_led_counter;
//-----------------------------------------------------------------------------

void systick_init(void)
{
  SysTick_Config(HAL_RCC_GetSysClockFreq() / 1000);
  systick_count_up = 0;
}
//-----------------------------------------------------------------------------

void systick_delay(u32 ticks)
{
  u32 stop_ticks;

  stop_ticks = systick_count_up + ticks;

  while (systick_count_up <= stop_ticks) ;
}
//-----------------------------------------------------------------------------

void SysTick_Handler(void)
{
  systick_count_up++;
  systick_main_loop_counter++;
  systick_debug_counter++;
  systick_button_counter++;
  systick_led_counter++;
}
