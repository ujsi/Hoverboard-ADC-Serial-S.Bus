// Module..: EEPROM.C
// Version.: 2.0
// Compiler: GCC-ARM
// Chip....: STM32F10x
// Date....: January 2025
// Author..: Udo Juerss
//-----------------------------------------------------------------------------

// Constants for EEPROM Validation (min, std, max)
const tEEV_S32 EEV_CM = {1, 2, 3}; // Control modes: 1 = ADC, 2 = Serial, 3 = RC-S.BUS
const tEEV_S32 EEV_SPA = {0, 0, 15}; // S.Bus Speed Addr: 0..15
const tEEV_S32 EEV_STA = {0, 1, 15}; // S.Bus Steer Addr: 0..15
const tEEV_S32 EEV_SH = {0, 0, 1}; // S.Bus Hold on error: 0..1
const tEEV_FLOAT EEV_RES = {-65000.0f, 12345.0f, 65000.0f}; // Dummy Reserve values
//-----------------------------------------------------------------------------

tEE_DATA ee; // EEPROM data structure in RAM
//-----------------------------------------------------------------------------

bool ee_save(void)
{
  u64* src_ptr;
  u32 dest_addr;
  u32 n;
  bool result = 1;

  if (ee_erase())
  {
    src_ptr = (u64*)&ee;
    dest_addr = (u32)EEPROM_BASE_ADDR;

    HAL_FLASH_Unlock();

    for (n = 0; n < EEPROM_ITEMS; n++)
    {
      result &= (HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, dest_addr, *src_ptr++) == HAL_OK);
      dest_addr += 8;
    }

    HAL_FLASH_Lock();
  }

  return (result);
}
//-----------------------------------------------------------------------------

bool ee_erase(void)
{
  u32 status = HAL_ERROR;
  uint32_t page_error;
  FLASH_EraseInitTypeDef EraseInitStruct;

  HAL_FLASH_Unlock();
  EraseInitStruct.TypeErase = FLASH_TYPEERASE_PAGES;
  EraseInitStruct.Banks = FLASH_BANK_1;
  EraseInitStruct.PageAddress = EEPROM_BASE_ADDR;
  EraseInitStruct.NbPages = 1;
  status = HAL_FLASHEx_Erase(&EraseInitStruct, &page_error);
  HAL_FLASH_Lock();

  return (status == HAL_OK);
}
//-----------------------------------------------------------------------------

bool ee_validate(void)
{
  u32 ee_invalid_counter = 0;

  // Check EEPROM data
  ee_invalid_counter += ee_validate_item(EEV_S32, (s32*)&ee.ctrl_mode, (pEEV_S32)&EEV_CM);
  ee_invalid_counter += ee_validate_item(EEV_S32, (s32*)&ee.sbus_speed_addr, (pEEV_S32)&EEV_SPA);
  ee_invalid_counter += ee_validate_item(EEV_S32, (s32*)&ee.sbus_steer_addr, (pEEV_S32)&EEV_STA);
  ee_invalid_counter += ee_validate_item(EEV_S32, (s32*)&ee.sbus_hold, (pEEV_S32)&EEV_SH);
  ee_invalid_counter += ee_validate_item(EEV_FLOAT, (float*)&ee.res1, (pEEV_FLOAT)&EEV_RES);
  ee_invalid_counter += ee_validate_item(EEV_FLOAT, (float*)&ee.res2, (pEEV_FLOAT)&EEV_RES);
  ee_invalid_counter += ee_validate_item(EEV_FLOAT, (float*)&ee.res3, (pEEV_FLOAT)&EEV_RES);

  if (ee_invalid_counter > 0)
  {
    ee_save();
  }

  return (ee_invalid_counter == 0);
}
