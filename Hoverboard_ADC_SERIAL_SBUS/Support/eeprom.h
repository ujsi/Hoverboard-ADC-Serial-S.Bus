#pragma once
//-----------------------------------------------------------------------------

#define EEPROM_BASE_ADDR (u32)0x0801FC00;
#define EEPROM_ITEMS (sizeof(tEE_DATA) / 4)
//-----------------------------------------------------------------------------

typedef struct sEE_DATA // EEPROM data structure
{
  s32 ctrl_mode;
  s32 sbus_speed_addr;
  s32 sbus_steer_addr;
  s32 sbus_hold;
  float res1;
  float res2;
  float res3;
} tEE_DATA;
//-----------------------------------------------------------------------------

extern tEE_DATA ee;
//-----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif
//-----------------------------------------------------------------------------

bool ee_save(void);
bool ee_erase(void);
bool ee_validate(void);
//-----------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif
