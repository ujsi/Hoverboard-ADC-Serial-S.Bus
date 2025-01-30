#pragma once
//-----------------------------------------------------------------------------

extern volatile u32 systick_count_up;
extern volatile u32 systick_main_loop_counter;
extern volatile u32 systick_debug_counter;
extern volatile u32 systick_button_counter;
extern volatile u32 systick_led_counter;
//-----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif
//-----------------------------------------------------------------------------

void systick_init(void);
void systick_delay(u32 ticks);
void SysTick_Handler(void);
//-----------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif
