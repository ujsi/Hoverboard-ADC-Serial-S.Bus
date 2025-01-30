#pragma once
//-----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif
//-----------------------------------------------------------------------------

char* su_trim(char* sp);
char* su_toupper(char* sp);
bool su_ncs_cmp(const char* s1, const char* s2, u8 n);
void su_strcpyn(char* src, char* dest, u16 count);
bool su_isfloat(char* s);
bool su_ishex(char c);
u8 su_hex_lsn(char c);
u8 su_hex_msn(char c);
char* su_skip_chars(char* s);
char* su_skip_blanks(char* s);
//-----------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif
