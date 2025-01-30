// Module..: NUM_CON.C
// Version.: 1.0
// Compiler: GCC-ARM
// Date....: January 2025
// Author..: Udo Juerss
//-----------------------------------------------------------------------------

static const char NC_HEX_ARRAY[] = "0123456789ABCDEF";
static char nc_buffer[NC_BUFFER_LENGTH];
char nc_fill_char;
//-----------------------------------------------------------------------------

void nc_init(void)
{
  nc_fill_char = NC_STD_FILL_CHAR;
}
//-----------------------------------------------------------------------------

void nc_u8s(NC_PUTC nc_putc, u8 value, u8 digits, bool crlf) // Convert u8 value to string
{
  char* pstr = nc_buffer;

  if (value >= 100) *pstr++ = ('0' + (value % 1000 / 100));
  if (value >= 10) *pstr++ = ('0' + (value % 100 / 10));

  *pstr++ = ('0' + (value % 10));

  if (crlf)
  {
    *pstr++ = 13;
    *pstr++ = 10;
    digits += 2;
  }

  *pstr = 0;
  nc_format(nc_putc, digits);
}
//-----------------------------------------------------------------------------

void nc_u8sx(NC_PUTC nc_putc, u8 value, u8 digits, bool crlf) // Convert u8 value to hex
{
  char* pstr = nc_buffer;

  *pstr++ = NC_HEX_ARRAY[value >> 4];
  *pstr++ = NC_HEX_ARRAY[value & 0x0F];

  if (crlf)
  {
    *pstr++ = 13;
    *pstr++ = 10;
    digits += 2;
  }

  *pstr = 0;
  nc_format(nc_putc, digits);
}
//-----------------------------------------------------------------------------

void nc_u8sb(NC_PUTC nc_putc, u8 value)
{
  u8 n;

  for (n = 7; n < 8; n--)
  {
    if (value & (1 << n))
    {
      nc_putc('1');
    }
    else
    {
      nc_putc('0');
    }
  }
}
//-----------------------------------------------------------------------------

void nc_u16s(NC_PUTC nc_putc, u16 value, u8 digits, bool crlf) // Convert u16 value to string
{
  char* pstr = nc_buffer;

  if (value >= 10000) *pstr++ = (u8)('0' + (value / 10000));
  if (value >= 1000) *pstr++ = (u8)('0' + (value % 10000 / 1000));
  if (value >= 100) *pstr++ = (u8)('0' + (value % 1000 / 100));
  if (value >= 10) *pstr++ = (u8)('0' + (value % 100 / 10));

  *pstr++ = ('0' + (value % 10));

  if (crlf)
  {
    *pstr++ = 13;
    *pstr++ = 10;
    digits += 2;
  }

  *pstr = 0;
  nc_format(nc_putc, digits);
}
//-----------------------------------------------------------------------------

void nc_s16s(NC_PUTC nc_putc, s16 svalue, u8 digits, bool crlf) // Convert s16 value to string
{
  char* pstr = nc_buffer;
  u16 value;

  if (svalue < 0)
  {
    *pstr++ = '-';
    value = -svalue;
  }
  else
  {
    value = svalue;
  }

  if (value >= 10000) *pstr++ = (u8)('0' + (value / 10000));
  if (value >= 1000) *pstr++ = (u8)('0' + (value % 10000 / 1000));
  if (value >= 100) *pstr++ = (u8)('0' + (value % 1000 / 100));
  if (value >= 10) *pstr++ = (u8)('0' + (value % 100 / 10));

  *pstr++ = ('0' + (value % 10));

  if (crlf)
  {
    *pstr++ = 13;
    *pstr++ = 10;
    digits += 2;
  }

  *pstr = 0;
  nc_format(nc_putc, digits);
}
//-----------------------------------------------------------------------------

void nc_u16sx(NC_PUTC nc_putc, u16 value, u8 digits, bool crlf) // Convert u16 value to hex
{
  char* pstr = nc_buffer;

  *pstr++ = NC_HEX_ARRAY[(u8)(value >> 12)];
  *pstr++ = NC_HEX_ARRAY[(u8)((value >> 8) & 0x0F)];
  *pstr++ = NC_HEX_ARRAY[(u8)((value >> 4) & 0x0F)];
  *pstr++ = NC_HEX_ARRAY[(u8)(value & 0x0F)];

  if (crlf)
  {
    *pstr++ = 13;
    *pstr++ = 10;
    digits += 2;
  }

  *pstr = 0;
  nc_format(nc_putc, digits);
}
//-----------------------------------------------------------------------------

void nc_u32s(NC_PUTC nc_putc, u32 value, u8 digits, bool crlf) // Convert u32 value to string
{
  char* pstr = nc_buffer;

  if (value >= 1000000000) *pstr++ = (u8)('0' + (value / 1000000000));
  if (value >= 100000000) *pstr++ = (u8)('0' + (value % 1000000000 / 100000000));
  if (value >= 10000000) *pstr++ = (u8)('0' + (value % 100000000 / 10000000));
  if (value >= 1000000) *pstr++ = (u8)('0' + (value % 10000000 / 1000000));
  if (value >= 100000) *pstr++ = (u8)('0' + (value % 1000000 / 100000));
  if (value >= 10000) *pstr++ = (u8)('0' + (value % 100000 / 10000));
  if (value >= 1000) *pstr++ = (u8)('0' + (value % 10000 / 1000));
  if (value >= 100) *pstr++ = (u8)('0' + (value % 1000 / 100));
  if (value >= 10) *pstr++ = (u8)('0' + (value % 100 / 10));

  *pstr++ = ('0' + (value % 10));

  if (crlf)
  {
    *pstr++ = 13;
    *pstr++ = 10;
    digits += 2;
  }

  *pstr = 0;
  nc_format(nc_putc, digits);
}
//-----------------------------------------------------------------------------

void nc_s32s(NC_PUTC nc_putc, s32 svalue, u8 digits, bool crlf) // Convert s32 value to string
{
  char* pstr = nc_buffer;
  u32 value;

  if (svalue < 0)
  {
    *pstr++ = '-';
    value = -svalue;
  }
  else
  {
    value = svalue;
  }

  if (value >= 1000000000) *pstr++ = (u8)('0' + (value / 1000000000));
  if (value >= 100000000) *pstr++ = (u8)('0' + (value % 1000000000 / 100000000));
  if (value >= 10000000) *pstr++ = (u8)('0' + (value % 100000000 / 10000000));
  if (value >= 1000000) *pstr++ = (u8)('0' + (value % 10000000 / 1000000));
  if (value >= 100000) *pstr++ = (u8)('0' + (value % 1000000 / 100000));
  if (value >= 10000) *pstr++ = (u8)('0' + (value % 100000 / 10000));
  if (value >= 1000) *pstr++ = (u8)('0' + (value % 10000 / 1000));
  if (value >= 100) *pstr++ = (u8)('0' + (value % 1000 / 100));
  if (value >= 10) *pstr++ = (u8)('0' + (value % 100 / 10));

  *pstr++ = ('0' + (value % 10));

  if (crlf)
  {
    *pstr++ = 13;
    *pstr++ = 10;
    digits += 2;
  }

  *pstr = 0;
  nc_format(nc_putc, digits);
}
//-----------------------------------------------------------------------------

void nc_u32sx(NC_PUTC nc_putc, u32 value, u8 digits, bool crlf) // Convert u32 value to hex
{
  char* pstr = nc_buffer;

  *pstr++ = NC_HEX_ARRAY[(u8)(value >> 28)];
  *pstr++ = NC_HEX_ARRAY[(u8)((value >> 24) & 0x0F)];
  *pstr++ = NC_HEX_ARRAY[(u8)((value >> 20) & 0x0F)];
  *pstr++ = NC_HEX_ARRAY[(u8)((value >> 16) & 0x0F)];
  *pstr++ = NC_HEX_ARRAY[(u8)((value >> 12) & 0x0F)];
  *pstr++ = NC_HEX_ARRAY[(u8)((value >> 8) & 0x0F)];
  *pstr++ = NC_HEX_ARRAY[(u8)((value >> 4) & 0x0F)];
  *pstr++ = NC_HEX_ARRAY[(u8)(value & 0x0F)];

  if (crlf)
  {
    *pstr++ = 13;
    *pstr++ = 10;
    digits += 2;
  }

  *pstr = 0;
  nc_format(nc_putc, digits);
}
//-----------------------------------------------------------------------------

void nc_floats(NC_PUTC nc_putc, float value, u8 digits, u8 decimals, bool crlf)
{
  u8 int_digits[8];
  u8 dec_digits[8];
  float dec_part;
  u32 int_part;
  char* pstr = nc_buffer;
  s8 n;
  u8 int_count;
  u8 dec_count;

  if (isnan(value))
  {
    *pstr++ = 'n';
    *pstr++ = 'a';
    *pstr++ = 'n';

    if (crlf)
    {
      *pstr++ = 13;
      *pstr++ = 10;
      digits += 2;
    }

    *pstr = 0;
    nc_format(nc_putc, digits);

    return;
  }

  if (decimals > 6)
  {
    decimals = 6;
  }

  if (value < 0.0f)
  {
    *pstr++ = '-';
    value = -value;
  }

  int_part = (u32)value;
  dec_part = value - int_part;
  int_count = 0;
  dec_count = 0;

  if (int_part == 0)
  {
    *pstr++ = '0';
  }

  while (int_part > 0)
  {
    int_digits[int_count] = int_part % 10;
    int_part = int_part - int_digits[int_count];

    if (int_part > 0)
    {
      int_part = int_part / 10;
    }

    int_count++; // go to the next digit
  }

  while (dec_count < decimals)
  {
    dec_part = dec_part * 10.0f;
    dec_digits[dec_count] = (u8)dec_part;

    if (dec_digits[dec_count] > 0)
    {
      dec_part = dec_part - dec_digits[dec_count];
    }

    dec_count++;
  }

  for (n = int_count - 1; n > -1; n--)
  {
    *pstr++ = 48 + int_digits[n];
  }

  *pstr++ = '.';

  for (n = 0; n < dec_count; n++)
  {
    *pstr++ = 48 + dec_digits[n];
  }

  if (crlf)
  {
    *pstr++ = 13;
    *pstr++ = 10;
    digits += 2;
  }

  *pstr = 0;
  nc_format(nc_putc, digits);
}
//-----------------------------------------------------------------------------

int nc_atoi(const char* str)
{
  int val = 0;

  while (*str)
  {
    val = val * 10 + (*str++ - '0');
  }

  return val;
}
//-----------------------------------------------------------------------------

/*
  Write formatted string to device function nc_putc
  nc_fmts("%s", "String");       "String"
  nc_fmts("%c", 'a');                 "a"
  nc_fmts("%6d", -200);          "  -200"
  nc_fmts("%d", 12345678L);    "12345678"
  nc_fmts("%.2u", 5);                "05"
  nc_fmts("%8x", 0xBC);              "BC"
  nc_fmts("%16x", 0x3ABC);         "3ABC"
  nc_fmts("%32x", 0x123ABC);   "00123ABC"
  nc_fmts("%7.3f", -1.234f);    " -1.234"
  Param1: Pointer to output function
  Param2: Pointer to nc_format string
  Param3: ... Parameters
*/
void nc_fmts(NC_PUTC nc_putc, const char* fmt_str, ...)
{
  va_list ap;
  char* pstr;
  u8 chr;
  u8 ucchr;
  u8 width;
  u8 precision;

  va_start(ap, fmt_str);

  while ((chr = *fmt_str++) != 0)
  {
    if (chr != '%')
    {
      nc_putc(chr);

      continue;
    }

    // Get next character following the percent sign
    chr = *fmt_str++;

    // Preset fill character to default
    nc_fill_char = NC_STD_FILL_CHAR;

    // Check for fill character to be '0'
    if (chr == '.')
    {
      nc_fill_char = '0';
      chr = *fmt_str++;
    }

    // Preset width
    width = 0;

    // Check if width is specified
    while (chr >= '0' && chr <= '9')
    {
      width = width * 10 + chr - '0';
      chr = *fmt_str++;
    }

    // Preset precision
    precision = 6;

    // Check if precision is specified
    if (chr == '.')
    {
      chr = *fmt_str++;

      if (chr >= '0' && chr <= '9')
      {
        precision = chr - '0';
        chr = *fmt_str++;
      }
    }

    if (chr == 0)
    {
      break;
    }

    // Convert to uppercase
    ucchr = (u8)toupper(chr);

    switch (ucchr)
    {
      case 'C': // Character
        ucchr = va_arg(ap, u32); // Use ucchr as parameter variable
        nc_putc(ucchr);
      continue;

      case 'S': // String
        pstr = (char*)va_arg(ap, char*);

        while (*pstr)
        {
          nc_putc(*pstr++);
        }
      continue;

      case 'D': // Signed decimal
        nc_fill_char = ' '; // Dont�t use leading zeros
        nc_s32s(nc_putc, (s32)va_arg(ap, s32), width, 0);
      break;

      case 'U': // Unsigned decimal
        nc_u32s(nc_putc, (u32)va_arg(ap, u32), width, 0);
      break;

      case 'F': // Float
        nc_fill_char = ' '; // Dont�t use leading zeros with floating point
        nc_floats(nc_putc, (float)va_arg(ap, double), width, precision, 0);
      break;

      case 'X': // Hexdecimal
        switch (width)
        {
          case 8:
          default:
            nc_u8sx(nc_putc, va_arg(ap, u32), 2, 0);
          break;

          case 16:
            nc_u16sx(nc_putc, va_arg(ap, u32), 4, 0);
          break;

          case 32:
            nc_u32sx(nc_putc, va_arg(ap, u32), 8, 0);
          break;
        }
      break;

      default: // Unknown nc_format character or 2nd percent sign
        nc_putc(chr);
      continue;
    }
  }

  va_end(ap);

  // Set fill character to default
  nc_fill_char = NC_STD_FILL_CHAR;
}
//-----------------------------------------------------------------------------

void nc_format(NC_PUTC nc_putc, u8 digits)
{
  u8 len = (u8)strlen((const char*)nc_buffer);
  char* p;

  if (nc_putc != NULL)
  {
    // Fillup loop
    while (digits-- > len)
    {
      nc_putc(nc_fill_char);
    }

    p = (char*)&nc_buffer;

    // Output loop
    while (len--)
    {
      nc_putc(*p++);
    }
  }
}
//-----------------------------------------------------------------------------

float nc_atof(const char* s)
{
  float f;
  int nc, i, neg;

  f = 0.0f;

  if (s[0] == '-')
  {
    neg = 1;
  }
  else
  {
    neg = 0;
  }

  for (nc = neg; (isdigit((u8)s[nc]) && (u8)(s[nc] != '.') && (u8)(s[nc] != '\0')); nc++)
  {
  }

  for (i = neg; ((isdigit((u8)s[i]) || ((u8)s[i] == '.')) && ((u8)s[i] != '\0')); i++)
  {
    switch (nc - i)
    {
      case 0: break;
      case 1:f += (s[i] - '0');  break;
      case 2:f += (s[i] - '0') * 10.0f; break;
      case 3:f += (s[i] - '0') * 100.0f; break;
      case 4:f += (s[i] - '0') * 1000.0f; break;
      case 5:f += (s[i] - '0') * 10000.0f; break;
      case 6:f += (s[i] - '0') * 100000.0f; break;
      case 7:f += (s[i] - '0') * 1000000.0f; break;
      case -1:f += (s[i] - '0') * 0.1f; break;
      case -2:f += (s[i] - '0') * 0.01f; break;
      case -3:f += (s[i] - '0') * 0.001f; break;
      case -4:f += (s[i] - '0') * 0.0001f; break;
      case -5:f += (s[i] - '0') * 0.00001f; break;
      case -6:f += (s[i] - '0') * 0.000001f; break;
      case -7:f += (s[i] - '0') * 0.0000001f; break;
      default : break;
    }
  }

  if (neg) f *= -1.0f;

  return (f);
}
