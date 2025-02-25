// Module..: DEBUG.C
// Version.: 1.0
// Compiler: GCC-ARM
// Chip....: STM32F103xx
// Date....: January 2025
// Author..: Udo Juerss
//-----------------------------------------------------------------------------

#ifdef DEBUG_SERIAL_USART3
  #define UART_DMA_CHANNEL DMA1_Channel2
#endif

static u8 uart_buf[100];
static s16 ch_buf[8];
//-----------------------------------------------------------------------------

void debug_set_chn(u8 ch, s16 val)
{
  ch_buf[ch] = val;
}
//-----------------------------------------------------------------------------

void debug_scope(void)
{
#if defined DEBUG_SERIAL_SERVOTERM && (defined DEBUG_SERIAL_USART2 || defined DEBUG_SERIAL_USART3)
  uart_buf[0] = 0xff;
  uart_buf[1] = CLAMP(ch_buf[0] + 127, 0, 255);
  uart_buf[2] = CLAMP(ch_buf[1] + 127, 0, 255);
  uart_buf[3] = CLAMP(ch_buf[2] + 127, 0, 255);
  uart_buf[4] = CLAMP(ch_buf[3] + 127, 0, 255);
  uart_buf[5] = CLAMP(ch_buf[4] + 127, 0, 255);
  uart_buf[6] = CLAMP(ch_buf[5] + 127, 0, 255);
  uart_buf[7] = CLAMP(ch_buf[6] + 127, 0, 255);
  uart_buf[8] = CLAMP(ch_buf[7] + 127, 0, 255);
  uart_buf[9] = '\n';

  if (UART_DMA_CHANNEL->CNDTR == 0)
  {
    UART_DMA_CHANNEL->CCR &= ~DMA_CCR_EN;
    UART_DMA_CHANNEL->CNDTR = 10;
    UART_DMA_CHANNEL->CMAR  = (uint32_t)uart_buf;
    UART_DMA_CHANNEL->CCR |= DMA_CCR_EN;
  }
#endif

#if defined DEBUG_SERIAL_ASCII && (defined DEBUG_SERIAL_USART2 || defined DEBUG_SERIAL_USART3)
  memset(uart_buf, 0, sizeof(uart_buf));
  sprintf((char*)&uart_buf, "1:%i 2:%i 3:%i 4:%i 5:%i 6:%i 7:%i 8:%i\r\n", ch_buf[0], ch_buf[1],
           ch_buf[2], ch_buf[3], ch_buf[4], ch_buf[5], ch_buf[6], ch_buf[7]);

  if (UART_DMA_CHANNEL->CNDTR == 0)
  {
    UART_DMA_CHANNEL->CCR &= ~DMA_CCR_EN;
    UART_DMA_CHANNEL->CNDTR = strlen((char*)&uart_buf);
    UART_DMA_CHANNEL->CMAR  = (uint32_t)uart_buf;
    UART_DMA_CHANNEL->CCR |= DMA_CCR_EN;
  }
#endif
}
