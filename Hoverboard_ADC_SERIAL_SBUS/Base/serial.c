// Module..: SERIAL.C
// Version.: 1.0
// Compiler: GCC-ARM
// Chip....: STM32F103xx
// Date....: January 2025
// Author..: Udo Juerss
//-----------------------------------------------------------------------------

#define USART (USART2) // Select USART2
//-----------------------------------------------------------------------------

static char rx_buf[SERIAL_RX_BUF_SIZE];
static char tx_buf[SERIAL_TX_BUF_SIZE];
static u16 tx_buf_in;
static u16 tx_buf_out;
static volatile u8 rx_buf_index;
static volatile u16 tx_buf_free;
volatile bool rx_ready;
//-----------------------------------------------------------------------------

void serial_init(void)
{
  __HAL_RCC_GPIOA_CLK_ENABLE(); // Enable GPIOA and USART clocks
  __HAL_RCC_USART2_CLK_ENABLE();

  GPIOA_2_OUT_AFPP_2M(); // Configure PA2 as Tx pin
  GPIOA_3_IN_PU(); // Configure PA3 Rx as input pull-up

  USART->BRR = HAL_RCC_GetSysClockFreq() / SERIAL_BAUDRATE / 2; // Set Baudrate
  USART->CR1 = BIT6 | BIT5 | BIT3 | BIT2 | BIT0; // Enable USART, Tx and Rx with interrupts
  USART->CR1 = USART_CR1_RE | USART_CR1_TE | USART_CR1_UE | USART_CR1_RXNEIE; // Enable Tx and Rx with interrupts

  tx_buf_free = SERIAL_TX_BUF_SIZE; // Preset free buffer items

  NVIC_SetPriority(USART2_IRQn, 0); // Enable the USART Interrupt
  NVIC_EnableIRQ(USART2_IRQn);

  serial_puts("\r\nApplication.: ");
  serial_puts((char*)SERIAL_IDN_STR); // Display Identity string
  serial_puts("\r\nSystem clock: ");
  nc_u32s(serial_putc, HAL_RCC_GetSysClockFreq(), 8, 1);
  serial_puts("HCLK........: ");
  nc_u32s(serial_putc, HAL_RCC_GetHCLKFreq(), 8, 1);
  serial_puts("PCLK1.......: ");
  nc_u32s(serial_putc, HAL_RCC_GetPCLK1Freq(), 8, 1);
  serial_puts("\r\nEEPROM Data.: "); // Validate EEPROM data
  ee_valid ? serial_puts("Ok\r\n") : serial_puts("Invalid - new initialized!\r\n");
  serial_puts(SERIAL_HLP_STR); // Display Help string
}
//-----------------------------------------------------------------------------

void serial_check(void)
{
  if (rx_ready) // Check if a serial input line is present
  {
    if (rx_buf_index > 0)
    {
      serial_puts("\r\n");
      u32 n = ci_parse_line((char*)rx_buf); // Call the command interpreter

      if (n < CI_NO_UART_ACK) // Write the result of the command execution
      {
        serial_putc(n + 48);
        serial_puts("\r\n");
      }
    }
    else
    {
      serial_puts("\r\n>");
    }

    rx_ready = false; // Clear input buffer
    rx_buf_index = 0;
    rx_buf[0] = 0;
  }
}
//-----------------------------------------------------------------------------

void serial_putc(char data)
{
  while (tx_buf_free == 0); // Wait until the buffer has at least 1 byte free
  USART->CR1 &= ~BIT6; // Disable TX interrupt before updating Tx buffer
  tx_buf[tx_buf_in++] = data; // Add new character to the transmit buffer
  tx_buf_free--;

  if (tx_buf_in > SERIAL_TX_BUF_SIZE - 1) // Check in buffer for overrun
  {
    tx_buf_in = 0;
  }

  USART->CR1 |= BIT6; // Reenable Tx interrupt after updating Tx buffer
}
//-----------------------------------------------------------------------------

void serial_puts(const char* str)
{
  while (*str)
  {
    serial_putc(*str++);
  }
}
//-----------------------------------------------------------------------------

void USART2_IRQHandler(void)
{
  if (USART->SR & BIT5) // Byte received
  {
    char rx_char = USART->DR; // Read received byte

    if (rx_char != 13) // Store received character if it is not CR
    {
      if (rx_buf_index < SERIAL_RX_BUF_SIZE) // Store character if no buffer overrun
      {
        rx_buf[rx_buf_index++] = rx_char;
      }
    }
    else
    {
      rx_buf[rx_buf_index] = 0; // Terminate input string
      rx_ready = true; // Set ready flag
    }
  }
  else // Byte to send
  {
    if (tx_buf_free < SERIAL_TX_BUF_SIZE) // Send next byte from buffer
    {
      USART->DR = tx_buf[tx_buf_out++];
      tx_buf_free++;

      if (tx_buf_out > SERIAL_TX_BUF_SIZE - 1) // Check buffer out position for overrun
      {
        tx_buf_out = 0;
      }
    }
    else // No more bytes to send
    {
      USART->CR1 &= ~BIT6; // Disable Tx interrupt
    }
  }
}
