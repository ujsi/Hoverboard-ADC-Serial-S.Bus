#pragma once
//-----------------------------------------------------------------------------

// Mathematical constants
#define MF_PI (3.1415926535897932384626433832795f)
#define MF_2PI (6.283185307179586476925286766559f)
#define MF_HALF_PI (1.5707963267948966192313216916398f)
#define MF_QUAD_PI (MF_HALF_PI / 2.0f)
#define MF_PI_15 (MF_PI * 1.5f)
#define MF_R2D (180.0f / MF_PI)
#define MF_D2R (MF_PI / 180.0f)
#define MF_G (9.80665f) // Gravity
#define MF_G_SQR (MF_G * MF_G)

#define MF_10_D2R (10.0f * MF_D2R)
#define MF_15_D2R (15.0f * MF_D2R)
#define MF_20_D2R (20.0f * MF_D2R)
#define MF_25_D2R (25.0f * MF_D2R)
#define MF_30_D2R (30.0f * MF_D2R)
#define MF_35_D2R (35.0f * MF_D2R)
#define MF_40_D2R (40.0f * MF_D2R)
#define MF_45_D2R (45.0f * MF_D2R)
#define MF_50_D2R (50.0f * MF_D2R)
#define MF_55_D2R (55.0f * MF_D2R)
#define MF_60_D2R (60.0f * MF_D2R)
#define MF_90_D2R (90.0f * MF_D2R)
#define MF_180_D2R (180.0f * MF_D2R)
#define MF_200_D2R (200.0f * MF_D2R)
#define MF_360_D2R (360.0f * MF_D2R)
//-----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif
//-----------------------------------------------------------------------------

float mf_angular_limit_pi(float angle); // Limit angle within -pi and +pi
float mf_length2(float a, float b); // Return length of a and b
float mf_length3(float a, float b, float c); // Return length of a, b and c
float mf_limit(float value, float limit); // Limit float value
u8 mf_limit_u8_up_down(u8 value, u8 up, u8 down); // Limit u8 value to upper and lower limit
s16 mf_limit_s16(s16 value, s16 limit); // Limit s16 value
s32 mf_limit_s32(s32 value, s32 limit); // Limit s32 value
float mf_limit_up_down(float value, float up, float down); // Clip value to upper and lower limit
float mf_min_2(float a, float b); // Return lowest value of a and b
float mf_max_2(float a, float b); // Return highest value of a and b
float mf_max_3(float a, float b, float c); // Return highest value of a, b and c
float mf_mix(float mix1, float mix2, float percent); // At 0 percent mix1 is returned, at 100 percent mix2 is returned
u8 mf_calc_checksum_u8(pu8 array, u8 limit); // Checksum calculation Sum + Complement
u8 calc_checksum_xor_u8(pu8 array, u8 limit); // Checksum calculation XOR + 1
//-----------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif
