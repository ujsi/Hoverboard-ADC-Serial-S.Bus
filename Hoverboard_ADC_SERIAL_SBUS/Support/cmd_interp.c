// Module..: CMD_INTERP.C
// Version.: 1.2
// Compiler: GCC-ARM
// Date....: January 2025
// Author..: Udo Juerss
//-----------------------------------------------------------------------------

static tCI_PARAM_ITEM params[CI_MAX_PARAMETERS]; // Parameter array
static u8 param_count; // Number of evaluated parameters
static u8 param_error; // Parameter error code (> 0 = index of bad parameter)
static bool param_hex_mode; // Flag for hexadecimal parameter input
//-----------------------------------------------------------------------------

pCI_TABLE cmd_table; // Command table pointer
//-----------------------------------------------------------------------------

void ci_init(void) // Initialize the Command Interpreter
{
  cmd_table = (pCI_TABLE)&CI_TABLE; // Validate table pointer
  param_hex_mode = 0; // Clear flag for hexadecimal parameter input
}
//-----------------------------------------------------------------------------

void ci_init_params(void) // Initialize parameter array
{
  for (param_count = 0; param_count < CI_MAX_PARAMETERS; param_count++)
  {
    params[param_count].f = 0.0f;
    params[param_count].i = 0;
    params[param_count].t = CI_UNKNOWN;
  }

  param_error = 0; // Reset parameter error index
  param_count = 0; // Reset parameter counter
}
//-----------------------------------------------------------------------------

void ci_set_table(pCI_TABLE tbl)
{
  cmd_table = (pCI_TABLE)tbl;
}
//-----------------------------------------------------------------------------

void ci_set_param_hex_mode(bool value)
{
  param_hex_mode = value;
}
//-----------------------------------------------------------------------------

u32 ci_get_param_count(void) // Get the number of evaluated parameters
{
  return (param_count);
}
//-----------------------------------------------------------------------------

u8 ci_get_param_error(void) // Get parameter error index (0 = no error, > 0 = parameter index + 1
{
  return (param_error);
}
//-----------------------------------------------------------------------------

u32 ci_get_param_type(u8 index) // Get parameter type (0 = CI_INT, 1 = CI_FLOAT, 2 = CI_STRING, 3 = CI_UNKNOWN)
{
  if (index < CI_MAX_PARAMETERS)
  {
    return (params[index].t);
  }
  else
  {
    return (params[0].t);
  }
}
//-----------------------------------------------------------------------------

s32 ci_get_param_int(u8 index) // Get integer parameter
{
  if (index < CI_MAX_PARAMETERS)
  {
    return (params[index].i);
  }
  else
  {
    return (params[0].i);
  }
}
//-----------------------------------------------------------------------------

float ci_get_param_float(u8 index) // Get float parameter
{
  if (index < CI_MAX_PARAMETERS)
  {
    return (params[index].f);
  }
  else
  {
    return (params[0].f);
  }
}
//-----------------------------------------------------------------------------

char* ci_get_param_str(u8 index) // Get string parameter
{
  if (index < CI_MAX_PARAMETERS)
  {
    return ((char*)params[index].i);
  }
  else
  {
    return ((char*)params[0].i);
  }
}
//-----------------------------------------------------------------------------

char* ci_eval_params(char* s, u8 param_index)
{
  s32 num;
  char* stmp = s;
  bool negative = 0;
  u8 c;

  if (param_index >= CI_MAX_PARAMETERS) // Exit if index of parameter is too large
  {
    return (s);
  }

  if (*s == '"') // Check for parameter string as string
  {
    s++; // Set parameter string to start position
    params[param_index].i = (s32)s;
    params[param_index].t = CI_STRING; // Set parameter type string

    while ((*s > 0) && (*s++ != '"'))
    {
    }

    s--;
    *s = 0; // Terminate string

    return (s);
  }
  else if (su_isfloat(s)) // Check if parameter is a float string
  {
    params[param_index].f = (float)nc_atof(s); // Convert to float
    params[param_index].i = (s32)params[param_index].f; // Convert to integer
    params[param_index].t = CI_FLOAT; // Set parameter type float

    return (s);
  }

  s = stmp;

  if ((*s == '0') && (*(s + 1) == 'x'))
  {
    s += 2;
    num = strtol(s, NULL, 16);
  }
  else if (*s == '$')
  {
    num = strtol(++s, NULL, 16);
  }
  else if (param_hex_mode)
  {
    num = strtol(s, NULL, 16);
  }
  else
  {
    if (*s == '-') // Check for negative sign
    {
      negative = 1;
      s++;
    }

    for (num = 0; isdigit(c = *s); s++) // Decimal conversion loop
    {
      num = num * 10 + (c - '0');
    }

    if (c > 0 && c != ',' && c != ' ') // Check for abort by invalid digit, set param_error if so
    {
      param_error = param_index + 1;
    }
  }

  if (negative) // Negate value if negative flag is set
  {
    num = -num;
  }

  params[param_index].i = num; // Assign integer parameter
  params[param_index].f = (float)num; // Assign float parameter
  params[param_index].t = CI_INT; // Set parameter type integer

  return (s);
}
//-----------------------------------------------------------------------------

u32 ci_parse_line(char* s) // Parser method of command interpreter
{
  s32FUNCvoid func; // Pointer to command function
  u32 hash_code = 0; // ASCII image of command string
  u32 hc; // ASCII image of table item
  char* sp; // Start position of command string
  u8 cmd_index = 0; // Command index
  u8 cmd_str_len;

  if (cmd_table == NULL) // Check for a command table assignment
  {
    return (0);
  }

  if (!*s) // Check for end of string
  {
    return CI_OK;
  }

  s = (char*)su_skip_blanks((char*)s); // Remove leading blanks
  sp = s; // Save line start position
  s = su_skip_chars(s); // Search for command string end
  cmd_str_len = (u8)(s - sp); // Get command string length
  *s++ = 0; // Terminate command string

  if (cmd_str_len > 4) // Limit string length to maximal 4 characters
  {
    cmd_str_len = 4;
  }

  switch (cmd_str_len) // Terminate command string (3x for single character commands)
  {
    case 1:
      hash_code = CI_HASH1(sp);
    break;
    case 2:
      hash_code = CI_HASH2(sp);
    break;
    case 3:
      hash_code = CI_HASH3(sp);
    break;
    case 4:
      hash_code = CI_HASH4(sp);
    break;

    default:
    break;
  }

  do // Compare command string image with command table image
  {
    hc = cmd_table[cmd_index++].hash_code;
  } while (hc && (hc != hash_code));

  if (hc == 0) // Check for a command match
  {
    return CI_COMMAND_ERROR;
  }
  else
  {
    cmd_index--; // The scan loop has incremented the cmd_index, so decrement it to fit
  }

  ci_init_params(); // Initialize parameter array

  while (*s && param_count < CI_MAX_PARAMETERS) // Parameter evaluate loop, check for line end and fl_max. parameter count
  {
    s = su_skip_blanks(s); // Search first none blank position

    if (*s != 0) // Check for end of string
    {
      s = ci_eval_params(s, param_count++); // Evaluate next parameter
      s = su_skip_chars(s); // Search end of parameter string in case of parameter error
    }
  }

  func = cmd_table[cmd_index].pFUNC;

  if (cmd_table[cmd_index].pFUNC != NULL) // Check the command table for a valid function
  {
    return (func()); // Execute command and return the result
  }
  else
  {
    return CI_COMMAND_ERROR;
  }
}
