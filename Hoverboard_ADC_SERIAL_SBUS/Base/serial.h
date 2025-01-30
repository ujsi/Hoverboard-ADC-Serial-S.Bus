#pragma once
//-----------------------------------------------------------------------------

#define SERIAL_RX_BUF_SIZE (256) // Receive buffer size
#define SERIAL_TX_BUF_SIZE (512) // Transmit buffer size
#define SERIAL_BAUDRATE (115200) // USART baudrate
#define SERIAL_IDN_STR "Hoverboard Command Interpreter *** 25020UJ" // Identity string
#define SERIAL_HLP_STR "\r\n>>> Type '?'<CR> for Help\r\n" // Help string
//-----------------------------------------------------------------------------

#ifdef __cplusplus
  extern "C" {
#endif
//-----------------------------------------------------------------------------

void serial_init(void);
void serial_putc(char data);
void serial_puts(const char* str);
void serial_check(void);
void USART3_IRQHandler(void);
//-----------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif
