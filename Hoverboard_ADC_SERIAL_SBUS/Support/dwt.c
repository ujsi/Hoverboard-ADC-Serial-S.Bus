// Module..: DWT.C
// Version.: 1.0
// Compiler: GCC-ARM
// Chip....: STM32xx
// Date....: January 2025
// Author..: Udo Juerss
//-----------------------------------------------------------------------------

static u32 dwt_us_divisor;
//-----------------------------------------------------------------------------

void dwt_init(void) // Enable the DTW Counter (Data Watchpoint and Trace)
{
  dwt_us_divisor = (HAL_RCC_GetSysClockFreq() / 1000000); // Setup divisor to speed-up later calculation

  CoreDebug->DEMCR &= ~0x01000000;
  CoreDebug->DEMCR |= 0x01000000;

  DWT->CTRL &= ~0x00000001;
  DWT->CTRL |= 0x00000001;
}
//-----------------------------------------------------------------------------

void dwt_delay_us(u32 us)
{
  DWT_RESET();

  while (DWT->CYCCNT < (us * dwt_us_divisor))
  {
  }
}
//-----------------------------------------------------------------------------

void dwt_delay_ms(u32 ms)
{
  dwt_delay_us(ms * 1000);
}
