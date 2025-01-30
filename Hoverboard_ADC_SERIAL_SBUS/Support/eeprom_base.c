// Module..: EEPROM_BASE.C
// Version.: 1.1
// Compiler: GCC-ARM
// Date....: January 2025
// Author..: Udo Juerss
//-----------------------------------------------------------------------------

void ee_init(void)
{
  u32* src_ptr;
  u32* dest_ptr;
  u32 n;

  src_ptr = (u32*)EEPROM_BASE_ADDR; // Setup pointers
  dest_ptr = (u32*)&ee;

  for (n = 0; n < EEPROM_ITEMS; n++) // Read existing values
  {
    *dest_ptr++ = (*src_ptr++);
  }
}
//-----------------------------------------------------------------------------

u32 ee_validate_item(eEEV_DATA_TYPE data_type, void* value_ptr, void* eev_ptr)
{
  u32 ee_invalid_counter = 0;

  switch (data_type)
  {
    case EEV_U32:
      if (*(u32*)value_ptr < (*(pEEV_U32)eev_ptr).min || // Check for valid range
          *(u32*)value_ptr > (*(pEEV_U32)eev_ptr).fl_max)
      {
        *(u32*)value_ptr = (*(pEEV_U32)eev_ptr).std;
        ee_invalid_counter++;
      }
    break;

    case EEV_S32:
      if (*(s32*)value_ptr < (*(pEEV_S32)eev_ptr).min || // Check for valid range
          *(s32*)value_ptr > (*(pEEV_S32)eev_ptr).fl_max)
      {
        *(s32*)value_ptr = (*(pEEV_S32)eev_ptr).std;
        ee_invalid_counter++;
      }
    break;

    case EEV_FLOAT:
      if (isnan(*(float*)value_ptr)) // Check for NAN
      {
        *(float*)value_ptr = (*(pEEV_FLOAT)eev_ptr).std;
        ee_invalid_counter++;
      }

      if (*(float*)value_ptr < (*(pEEV_FLOAT)eev_ptr).min || // Check for valid range
          *(float*)value_ptr > (*(pEEV_FLOAT)eev_ptr).fl_max)
      {
        *(float*)value_ptr = (*(pEEV_FLOAT)eev_ptr).std;
        ee_invalid_counter++;
      }
    break;
  }

  return (ee_invalid_counter);
}
