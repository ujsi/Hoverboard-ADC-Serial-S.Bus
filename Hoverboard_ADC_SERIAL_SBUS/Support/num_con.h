#pragma once
//-----------------------------------------------------------------------------

#define NC_BUFFER_LENGTH (18) // Conversion buffer size
#define NC_STD_FILL_CHAR (32) // Character for post digits
#define NC_FLOAT_MAX_EXP (38)
#define NC_FLOAT_MIN (1.175494351e-38f)
#define NC_FLOAT_MIN_EXP (-37)
//-----------------------------------------------------------------------------

typedef void(*NC_PUTC)(char);
//-----------------------------------------------------------------------------

extern char nc_fill_char;
//-----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif
//-----------------------------------------------------------------------------

void nc_init(void);
void nc_u8s(NC_PUTC putc, u8 value, u8 digits, bool crlf);
void nc_s8s(NC_PUTC putc, s8 svalue, u8 digits, bool crlf);
void nc_u8sx(NC_PUTC putc, u8 value, u8 digits, bool crlf);
void nc_u8sb(NC_PUTC putc, u8 value);
void nc_u16s(NC_PUTC putc, u16 value, u8 digits, bool crlf);
void nc_s16s(NC_PUTC putc, s16 svalue, u8 digits, bool crlf);
void nc_u16sx(NC_PUTC putc, u16 value, u8 digits, bool crlf);
void nc_u32s(NC_PUTC putc, u32 value, u8 digits, bool crlf);
void nc_s32s(NC_PUTC putc, s32 svalue, u8 digits, bool crlf);
void nc_u32sx(NC_PUTC putc, u32 value, u8 digits, bool crlf);
void nc_floats(NC_PUTC putc, float value, u8 digits, u8 decimals, bool crlf);
void nc_fmts(NC_PUTC putc, const char* fmt_str, ...);
int nc_atoi(const char* str);
void nc_set_fill_char(char c);
void nc_format(NC_PUTC, u8);
float nc_atof(const char* s);
//-----------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif
