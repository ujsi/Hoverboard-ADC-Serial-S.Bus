// Module..: CI_FUNC.C (Command Interpreter Functions)
// Version.: 1.2
// Compiler: GCC-ARM
// Date....: January 2025
// Author..: Udo Juerss
//-----------------------------------------------------------------------------

void ci_disp_mode(void)
{
  switch (ee.ctrl_mode)
  {
    case 1:
      serial_puts("ADC");
    break;
    case 2:
      serial_puts("SERIAL");
    break;
    case 3:
      serial_puts("RC-S.BUS");
    break;
    default:
    break;
  }
}
//-----------------------------------------------------------------------------

u32 ci_software_reset(void) // Do software reset
{
  NVIC_SystemReset();

  return (CI_NO_UART_ACK);
}
//-----------------------------------------------------------------------------

u32 ci_emergency(void) // Do Stop
{
  enable = 0;
  GPIOA_5_CLR(); // Turn off the supply signal

  return (CI_OK);
}
//-----------------------------------------------------------------------------

u32 ci_ee_erase(void) // Erase EEPROM parameters
{
  if (ee_erase())
  {
    return (CI_OK);
  }

  return (CI_MEMORY_ERROR);
}
//-----------------------------------------------------------------------------

u32 ci_ee_save(void) // Save EEPROM parameters
{
  if (ee_save())
  {
    return (CI_OK);
  }

  return (CI_MEMORY_ERROR);
}
//-----------------------------------------------------------------------------

u32 ci_set_ctrl_mode(void) // Set a new Control Mode
{
  if (ci_get_param_count() != 1) // Must have one parameter
  {
    return (CI_PARAMETER_ERROR);
  }

  u8 cm = ci_get_param_int(0); // Assign parameter

  if ((cm < 1) || (cm > 3)) // Check valid range
  {
    return (CI_PARAMETER_ERROR);
  }

  ee.ctrl_mode = cm; // Assign the parameter value to the EEPROM
  ci_ee_save(); // Save the new mode in EEPROM
  serial_puts("Switched to ");
  ci_disp_mode(); // Display the selected mode
  serial_puts(" Mode, select the right interface...\r\n");
  dwt_delay_ms(50); // Wait until all character are sent
  NVIC_SystemReset(); // Reset to start the new mode

  return (CI_OK);
}
//-----------------------------------------------------------------------------

u32 ci_set_sbus_speed(void) // Set the S.Bus Speed Address
{
  if (ci_get_param_count() != 1) // Must have one parameter
  {
    return (CI_PARAMETER_ERROR);
  }

  u8 sa = ci_get_param_int(0); // Assign parameter

  if ((sa < 1) || (sa > 16)) // Check valid range
  {
    return (CI_PARAMETER_ERROR);
  }

  ee.sbus_speed_addr = sa; // Assign the parameter value to the EEPROM
  serial_puts("Save the S.Bus Speed Addresswith <ees> if required.\r\n");

  return (CI_OK);
}
//-----------------------------------------------------------------------------

u32 ci_set_sbus_steer(void) // Set the S.Bus Steer Address
{
  if (ci_get_param_count() != 1) // Must have one parameter
  {
    return (CI_PARAMETER_ERROR);
  }

  u8 sa = ci_get_param_int(0); // Assign parameter

  if ((sa < 1) || (sa > 16)) // Check valid range
  {
    return (CI_PARAMETER_ERROR);
  }

  ee.sbus_steer_addr = sa; // Assign the parameter value to the EEPROM
  serial_puts("Save the new S.Bus Steering Address with <ees> if required.\r\n");

  return (CI_OK);
}
//-----------------------------------------------------------------------------

u32 ci_set_sbus_hold(void) // Set the S.Bus Hold on Error
{
  if (ci_get_param_count() != 1) // Must have one parameter
  {
    return (CI_PARAMETER_ERROR);
  }

  u8 hold = ci_get_param_int(0); // Assign parameter

  if ((hold < 0) || (hold > 1)) // Check valid range
  {
    return (CI_PARAMETER_ERROR);
  }

  ee.sbus_hold = hold; // Assign the parameter value to the EEPROM
  serial_puts("Save the new Mode with <ees> if required.\r\n");

  return (CI_OK);
}
//-----------------------------------------------------------------------------

u32 ci_set_speed_steer(void) // Set Speed and Steer value
{
  if (ci_get_param_count() != 2)
  {
    return (CI_PARAMETER_ERROR);
  }

  speed_input = mf_limit_s16(ci_get_param_int(0), INP_NORM_VALUE);
  steer_input = mf_limit_s16(ci_get_param_int(1), INP_NORM_VALUE);
  timeout = 0;

  return (CI_OK);
}
//-----------------------------------------------------------------------------

u32 ci_set_speed(void) // Set Speed value
{
  speed_input = mf_limit_s16(ci_get_param_int(0), INP_NORM_VALUE);
  timeout = 0;

  return (CI_OK);
}
//-----------------------------------------------------------------------------

u32 ci_set_steer(void) // Set Steer value
{
  steer_input = mf_limit_s16(ci_get_param_int(0), INP_NORM_VALUE);
  timeout = 0;

  return (CI_OK);
}
//-----------------------------------------------------------------------------

u32 ci_ee_get_params(void)
{
  serial_puts("Control Mode............: "); // Write the EEPROM parameters
  nc_u8s(serial_putc, ee.ctrl_mode, 1, 0);
  serial_puts(" = ");
  ci_disp_mode();
  serial_puts("\r\n");

  serial_puts("S.Bus Speed Address.....: ");
  nc_u8s(serial_putc, ee.sbus_speed_addr, 1, 1);
  serial_puts("S.Bus Steer Address.....: ");
  nc_u8s(serial_putc, ee.sbus_steer_addr, 1, 1);
  serial_puts("S.Bus Hold Data on Error: ");
  nc_u8s(serial_putc, ee.sbus_hold, 1, 1);

  return (CI_NO_UART_ACK);
}
//-----------------------------------------------------------------------------

u32 ci_get_help(void) // Get help
{
  u8 cmd_index = 0;

  while ((cmd_table)[cmd_index].hash_code > 0) // Write all visible table entry help texts
  {
    serial_puts((char*)(cmd_table)[cmd_index++].help_text);
    serial_puts("\r\n");
  }

  return (CI_NO_UART_ACK);
}
//-----------------------------------------------------------------------------

const tCI_ITEM CI_TABLE[] = // Command Interpreter Table
{
  {CI_HASH2("sr"),   1, ci_software_reset,  "sr   Do Software Reset"},
  {CI_HASH1("x"),    1, ci_emergency,       "x    Do Emergency Power Off"},
  {CI_HASH4("EEE*"), 1, ci_ee_erase,        "EEE* Do EEPROM Erase"},
  {CI_HASH3("ees"),  1, ci_ee_save,         "ees  Do EEPROM Save Parameters"},
  {CI_HASH2("cm"),   1, ci_set_ctrl_mode,   "cm   Set Control Mode (1..3)"},
  {CI_HASH2("ss"),   1, ci_set_speed_steer, "ss   Set Speed Steer Values (Speed Value, Steer Value)"},
  {CI_HASH2("sp"),   1, ci_set_speed,       "sp   Set Speed Value (-1000..1000)"},
  {CI_HASH2("st"),   1, ci_set_steer,       "st   Set Steer Value (-1000..1000)"},
  {CI_HASH4("sbsp"), 1, ci_set_sbus_speed,  "sbsp Set S.Bus Speed Address (0..15)"},
  {CI_HASH4("sbst"), 1, ci_set_sbus_steer,  "sbst Set S.Bus Steering Address (0..15)"},
  {CI_HASH3("sbh"),  1, ci_set_sbus_hold,   "sbh  Set S.Bus Hold on Error (0..1)"},
  {CI_HASH3("ee?"),  1, ci_ee_get_params,   "ee?  Get EEPROM Parameters"},
  {CI_HASH1("?"),    1, ci_get_help,        "?    Get Help"},
  {0,                0, NULL,               NULL} // End of table
};
