#pragma once
//-----------------------------------------------------------------------------

typedef struct // EEPROM Data Validation Structures
{
  u32 min;
  u32 std;
  u32 fl_max;
} tEEV_U32;

typedef struct
{
  s32 min;
  s32 std;
  s32 fl_max;
} tEEV_S32;

typedef struct
{
  float min;
  float std;
  float fl_max;
} tEEV_FLOAT;

typedef tEEV_U32* pEEV_U32; // Pointer types of EEPROM Data Validation Structures
typedef tEEV_S32* pEEV_S32;
typedef tEEV_FLOAT* pEEV_FLOAT;

typedef enum // Enumeration of EEPROM Data Validation types
{
  EEV_U32,
  EEV_S32,
  EEV_FLOAT
} eEEV_DATA_TYPE;
//-----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif
//-----------------------------------------------------------------------------

void ee_init(void);
u32 ee_validate_item(eEEV_DATA_TYPE data_type, void* value_ptr, void* eev_ptr);
//-----------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif
