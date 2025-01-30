// Module..: STR_UTIL.C
// Version.: 1.0
// Compiler: GCC-ARM
// Date....: January 2025
// Author..: Udo Juerss
//-----------------------------------------------------------------------------

// Trim leading and trailing blanks of a string
// Return: Pointer to string
// Param1: Pointer to string
char* su_trim(char* sp)
{
  char* tsp = sp;

  while (*tsp == ' ') // Remove leading blanks
  {
    tsp++;
  }

  sp = tsp; // Set string pointer

  while (*tsp++ != 0) // Seek string termination
  {
  }

  tsp--;

  while (*tsp == ' ') // Remove trailing blanks
  {
    tsp--;
  }

  tsp++; // Terminate string
  *tsp = 0;

  return (sp);
}
//-----------------------------------------------------------------------------

// Convert string to uppercase
// Return: Pointer to string
// Param1: Pointer to string
char* su_toupper(char* sp)
{
  char* tsp = sp;

  while (*tsp != 0) // Convert string to uppercase
  {
    *tsp = (char)toupper(*tsp);
    tsp++;
  }

  return (sp);
}
//-----------------------------------------------------------------------------

// Compares the two string s1 and s1 (non case sensitive) for n characters
// Return: True (match) or False (no match)
// Param1: Pointer to string s1
// Param2: Pointer to string s2
bool su_ncs_cmp(const char* s1, const char* s2, u8 n)
{
  u8 sv1, sv2;

  do
  {
    sv1 = ((*s1 <= 'Z') && (*s1 >= 'A')) ? *s1 + 'a' - 'A' : *s1;
    sv2 = ((*s2 <= 'Z') && (*s2 >= 'A')) ? *s2 + 'a' - 'A' : *s2;
    s1++;
    s2++;
  } while (--n > 0 && sv1 == sv2);

  return (sv1 == sv2);
}
//-----------------------------------------------------------------------------

void su_strcpyn(char* src, char* dest, u16 count)
{
  memcpy(dest, src, count);
}
//-----------------------------------------------------------------------------

bool su_isfloat(char* s)
{
  char c;

  if (*s == '-')
  {
    s++;
  }

  c = *s++;

  while (c != ' ' && c != ',' && c > 0) // Loop until string end or delimiter character
  {
    if (c == '.')
    {
      return (1);
    }

    c = *s++;
  }

  return (0);
}
//-----------------------------------------------------------------------------

bool su_ishex(char c)
{
  return (((c >= '0') && (c <= '9')) || ((c >= 'A') && (c <= 'F')));
}
//-----------------------------------------------------------------------------

u8 su_hex_lsn(char c)
{
  if ((c >= '0') && (c <= '9'))
  {
    c -= '0';
  }
  else if ((c >= 'A') && (c <= 'F'))
  {
    c -= 'A' - 10;
  }

  return (c);
}
//-----------------------------------------------------------------------------

u8 su_hex_msn(char c)
{
  return (su_hex_lsn(c) << 4);
}
//-----------------------------------------------------------------------------

char* su_skip_chars(char* s)
{
  while (*s && *s != ',' && *s != ' ')
  {
    s++;
  }

  return (s);
}
//-----------------------------------------------------------------------------

char* su_skip_blanks(char* s)
{
  while (*s == ' ' || *s == ',')
  {
    s++;
  }

  return (s);
}
