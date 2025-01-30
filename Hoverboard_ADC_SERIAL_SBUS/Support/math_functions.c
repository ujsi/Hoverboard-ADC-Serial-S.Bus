// Module..: MATH_FUNCTIONS.C
// Version.: 1.1
// Compiler: GCC-ARM
// Date....: January 2025
// Author..: Udo Juerss
//-----------------------------------------------------------------------------

float mf_length2(float a, float b) // Return length of a and b
{
  return sqrt(a * a + b * b);
}
//-----------------------------------------------------------------------------

float mf_length3(float a, float b, float c) // Return length of a, b and c
{
  return sqrt(a * a + b * b + c * c);
}
//-----------------------------------------------------------------------------

float mf_limit(float value, float limit) // Limit float value
{
  if (value < -limit)
  {
    return (-limit);
  }

  if (value > limit)
  {
    return (limit);
  }

  return (value);
}
//-----------------------------------------------------------------------------

u8 mf_limit_u8_up_down(u8 value, u8 up, u8 down) // Limit u8 value to upper and lower limit
{
  if (value < down)
  {
    return (down);
  }

  if (value > up)
  {
    return (up);
  }

  return (value);
}
//-----------------------------------------------------------------------------

s16 mf_limit_s16(s16 value, s16 limit) // Limit s32 value
{
  if (value > limit)
  {
    value = limit;
  }

  if (value < -limit)
  {
    value = -limit;
  }

  return (value);
}
//-----------------------------------------------------------------------------

s32 mf_limit_s32(s32 value, s32 limit) // Limit s32 value
{
  if (value < -limit)
  {
    return -limit;
  }

  if (value > limit)
  {
    return limit;
  }

  return (value);
}
//-----------------------------------------------------------------------------

float mf_limit_up_down(float value, float up, float down) // Clip value to upper and lower limit
{
  if (value > up)
  {
    return (up);
  }

  if (value < down)
  {
    return down;
  }

  return (value);
}
//-----------------------------------------------------------------------------

float mf_min_2(float a, float b) // Return lowest value of a and b
{
  if (a < b)
  {
    return (a);
  }

  return (b);
}
//-----------------------------------------------------------------------------

float mf_max_2(float a, float b) // Return highest value of a and b
{
  if (a > b)
  {
    return (a);
  }

  return (b);
}
//-----------------------------------------------------------------------------

float mf_max_3(float a, float b, float c) // Return highest value of a, b and c
{
  if (a > b)
  {
    if (a > c)
    {
      return (a);
    }
    else
    {
      return (c);
    }
  }
  else
  {
    if (b > c)
    {
      return (b);
    }
    else
    {
      return (c);
    }
  }
}
//-----------------------------------------------------------------------------

// Mix the two values mix1 and mix2 depending on percent
// At 0 percent mix1 is returned, at 100 percent mix2 is returned
float mf_mix(float mix1, float mix2, float percent)
{
  if (percent > 100)
  {
    percent = 100;
  }

  return (mix1 * (100 - percent) * 0.01f + (mix2 * percent * 0.01f));
}
//-----------------------------------------------------------------------------

u8 mf_calc_checksum_u8(pu8 array, u8 limit) // Checksum calculation Sum + Complement
{
  u8 checksum = 0;

  for (u8 n = 0; n < limit; n++)
  {
    checksum += *array++;
  }

  return (~checksum);
}
//-----------------------------------------------------------------------------

u8 calc_checksum_xor_u8(pu8 array, u8 limit) // Checksum calculation XOR + 1
{
  u8 checksum = 0;

  for (u8 n = 0; n < limit; n++)
  {
    checksum ^= *array++ + 1;
  }

  return (checksum);
}
