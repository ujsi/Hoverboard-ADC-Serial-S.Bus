#pragma once
//-----------------------------------------------------------------------------

#ifndef CI_MAX_PARAMETERS
  #define CI_MAX_PARAMETERS (8)
#endif

#define CI_HASH1(s) (s[0] << 4) // Used to encode a command string
#define CI_HASH2(s) (s[0] << 4) + (s[1] << 6)
#define CI_HASH3(s) (s[0] << 4) + (s[1] << 6) + (s[2] << 8)
#define CI_HASH4(s) (s[0] << 4) + (s[1] << 6) + (s[2] << 8) + (s[3] << 10)
//-----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif
//-----------------------------------------------------------------------------

enum eCI_RESULT // Command interpreter results
{
  CI_OK = 0, // Command execution ok
  CI_COMMAND_ERROR, // Unknown command
  CI_PARAMETER_ERROR, // Invalid parameter
  CI_FUNCTION_ERROR, // Function error
  CI_MEMORY_ERROR, // Memory error
  CI_PERIPHERAL_ERROR, // Peripheral error
  CI_CHECKSUM_ERROR, // Invalid checksum
  CI_NO_UART_ACK // No UART acknowledge
};

enum eCI_PARAM_TYPE // Parameter types
{
  CI_INT = 0, // Integer type
  CI_FLOAT, // Float type
  CI_STRING, // String type
  CI_UNKNOWN // Unknown type
};
//-----------------------------------------------------------------------------

typedef u32 (*s32FUNCvoid)(void); // Command function pointer

typedef struct sCI_PARAM_ITEM // Structure of a parameter item
{
  float f; // Parameter of type float
  s32 i; // Parameter of type integer
  char* s; // Parameter of type string
  u32 t; // Parameter type
} tCI_PARAM_ITEM;

typedef struct sCI_ITEM // Structure of a command table item
{
  u32 hash_code; // ASCII code of command string
  bool visible; // Flag if item is visible
  u32 (*pFUNC)(void); // Pointer to command function
  const char* help_text; // Pointer to help text
} tCI_ITEM;

typedef tCI_ITEM* pCI_TABLE; // Table and table-pointer typedefs
//-----------------------------------------------------------------------------

extern const tCI_ITEM CI_TABLE[]; // Command table must be defined by the application
extern pCI_TABLE cmd_table; // Command table pointer
//-----------------------------------------------------------------------------

void ci_init(void); // Initialize the Command Interpreter
u32 ci_parse_line(char* s); // Parse an input line and execute command if present, return eCI_RESULT
void ci_disp_result(u32 r); // Display parser result
void ci_disp_help(void); // Display command table help
void ci_set_table(pCI_TABLE tbl); // Set command table pointer
pCI_TABLE ci_get_table(void); // Get command table pointer
void ci_set_param_hex_mode(bool value); // Set or clear the flag for hexadecimal parameter input
u32 ci_get_param_count(void); // Get the number of evaluated parameters
u8 ci_get_param_error(void); // Get parameter error index (0 = no error, > 0 = parameter index + 1
u32 ci_get_param_type(u8 index); // Get parameter type (0 = CI_INT, 1 = CI_FLOAT, 2 = CI_STRING, 3 = CI_UNKNOWN)
s32 ci_get_param_int(u8 index); // Get integer parameter
float ci_get_param_float(u8 index); // Get float parameter
char* ci_get_param_str(u8 index); // Get string parameter
//-----------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif
