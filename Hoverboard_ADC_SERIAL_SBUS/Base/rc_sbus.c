// Module..: RC_SBUS.C
// Version.: 1.0
// Compiler: GCC-ARM
// Chip....: STM32F103xx
// Date....: January 2025
// Author..: Udo Juerss
//-----------------------------------------------------------------------------

#define RC_CHANNELS (8)
#define RC_CONV (200)
//-----------------------------------------------------------------------------

#define RC_USART (USART3)
#define RC_BAUDRATE (100000)
#define RC_LENGTH (25)
#define RC_START_CHAR (0x0F)
#define RC_END_CHAR (0x00)
#define RC_RX_BUFFER_SIZE (32)
#define RC_NORM_MIN_CHN_VALUE (192) // 172
#define RC_NORM_MAX_CHN_VALUE (1792) // 1811
#define RC_ABS_MIN_CHN_VALUE (RC_NORM_MIN_CHN_VALUE - 50)
#define RC_ABS_MAX_CHN_VALUE (RC_NORM_MAX_CHN_VALUE + 50)
#define RC_DIV ((RC_NORM_MAX_CHN_VALUE - RC_NORM_MIN_CHN_VALUE) / (RC_CONV * 2))
//-----------------------------------------------------------------------------

static u8 rc_buffer[RC_RX_BUFFER_SIZE];
static u8 rc_buffer_index;
volatile bool rc_ready;
volatile bool rc_valid;
volatile bool rc_failsafe;
volatile s16 rc_chn[RC_CHANNELS];
volatile s16 rc_raw[RC_CHANNELS];
//-----------------------------------------------------------------------------

void rc_init(void)
{
  // The S-Bus protocol has inverted receive level, 100 kBit baudrate,
  // 1 start bit, 8 data bits, 1 parity even and 2 stop bits
  GPIOB_11_IN_PU(); // Configure PB11 as Rx pin
  rc_buffer_index = 0;

  NVIC_SetPriority(USART3_IRQn, 1); // Enable the USART3 Interrupt
  NVIC_EnableIRQ(USART3_IRQn);
}
//-----------------------------------------------------------------------------

void rc_update(void) // Takes ~35µs @32MHz
{
  rc_ready = false; // Reset flags
  rc_valid = true;

  // Calculate the channel raw values
  rc_raw[0] = ((rc_buffer[1] | rc_buffer[2] << 8) & 0x07FF);
  rc_raw[1] = ((rc_buffer[2] >> 3 | rc_buffer[3] << 5) & 0x07FF);
  rc_raw[2] = ((rc_buffer[3] >> 6 | rc_buffer[4] << 2 | rc_buffer[5] << 10) & 0x07FF);
  rc_raw[3] = ((rc_buffer[5] >> 1 | rc_buffer[6] << 7) & 0x07FF);
  rc_raw[4] = ((rc_buffer[6] >> 4 | rc_buffer[7] << 4) & 0x07FF);
  rc_raw[5] = ((rc_buffer[7] >> 7 | rc_buffer[8] << 1 | rc_buffer[9] << 9) & 0x07FF);
  rc_raw[6] = ((rc_buffer[9] >> 2 | rc_buffer[10] << 6) & 0x07FF);
  rc_raw[7] = ((rc_buffer[10] >> 5 | rc_buffer[11] << 3) & 0x07FF);
//  rc_raw[8] = ((rc_buffer[12] | rc_buffer[13] << 8) & 0x07FF);
//  rc_raw[9] = ((rc_buffer[13] >> 3 | rc_buffer[14] << 5) & 0x07FF);
//  rc_raw[10] = ((rc_buffer[14] >> 6 | rc_buffer[15] << 2 | rc_buffer[16] << 10) & 0x07FF);
//  rc_raw[11] = ((rc_buffer[16] >> 1 | rc_buffer[17] << 7) & 0x07FF);
//  rc_raw[12] = ((rc_buffer[17] >> 4 | rc_buffer[18] << 4) & 0x07FF);
//  rc_raw[13] = ((rc_buffer[18] >> 7 | rc_buffer[19] << 1 | rc_buffer[20] << 9) & 0x07FF);
//  rc_raw[14] = ((rc_buffer[20] >> 2 | rc_buffer[21] << 6) & 0x07FF);
//  rc_raw[15] = ((rc_buffer[21] >> 5 | rc_buffer[22] << 3) & 0x07FF);
//  rc_raw[16] = ((rc_buffer[23]) & 0x0001) ? 2047 : 0;
//  rc_raw[17] = ((rc_buffer[23] >> 1) & 0x0001) ? 2047 : 0;
  rc_failsafe = ((rc_buffer[23] >> 3) & 0x0001) ? 1 : 0;

  for (u32 n = 0; n < RC_CHANNELS; n++) // Check the raw channel times for absolute limits
  {
    if ((rc_raw[n] < RC_ABS_MIN_CHN_VALUE) || (rc_raw[n] > RC_ABS_MAX_CHN_VALUE))
    {
      rc_valid = false;
    }
  }

  if (rc_valid) // Convert channel raw values to +-1000
  {
    for (u32 n = 0; n < RC_CHANNELS; n++)
    {
      s16 chn = ((rc_raw[n] - RC_NORM_MIN_CHN_VALUE) / RC_DIV) - RC_CONV;
      chn = mf_limit_s16(chn, RC_CONV);
      rc_chn[n] = chn * 5;
    }
  }
}
//-----------------------------------------------------------------------------

void USART3_IRQHandler(void) // Takes between 1µs and 3µs @32MHz
{
  char rc_char = RC_USART->DR; // Read received byte

  if ((rc_buffer_index == 0) && (rc_char == RC_START_CHAR))
  {
    rc_buffer[rc_buffer_index++] = rc_char; // Store first byte
    rc_buffer[RC_LENGTH - 1] = 0xFA; // Store invalid end byte (0xFA = FAlse)
  }
  else
  {
    rc_buffer[rc_buffer_index++] = rc_char;

    if (rc_buffer_index == RC_LENGTH)
    {
      rc_buffer_index = 0;

      if (rc_buffer[RC_LENGTH - 1] == RC_END_CHAR)
      {
        rc_ready = true;
      }
    }
  }
}
