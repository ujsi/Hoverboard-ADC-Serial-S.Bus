#pragma once
//-----------------------------------------------------------------------------

#define DWT_RESET() (DWT->CYCCNT = 0) // Reset the DWT cycle counter
#define DWT_GET() (DWT->CYCCNT) // Get the DWT cycle counter
//-----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif
//-----------------------------------------------------------------------------

void dwt_init(void);
void dwt_delay_us(u32 us);
void dwt_delay_ms(u32 ms);
//-----------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif
