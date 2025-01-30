// Header..: MACROS_GPIO_COMMON.H
// Version.: 1.0
// Compiler: GCC-ARM
// Chip....: STM32F10x
// Date....: January 2025
// Author..: Udo Juerss
//-----------------------------------------------------------------------------

#pragma once
//-----------------------------------------------------------------------------

// Clear masks
#define GPIO_MSK_CLR_0 (0xFFFFFFF0) // Clear mask for pin 0/8
#define GPIO_MSK_CLR_1 (0xFFFFFF0F) // Clear mask for pin 1/9
#define GPIO_MSK_CLR_2 (0xFFFFF0FF) // Clear mask for pin 2/10
#define GPIO_MSK_CLR_3 (0xFFFF0FFF) // Clear mask for pin 3/11
#define GPIO_MSK_CLR_4 (0xFFF0FFFF) // Clear mask for pin 4/12
#define GPIO_MSK_CLR_5 (0xFF0FFFFF) // Clear mask for pin 5/13
#define GPIO_MSK_CLR_6 (0xF0FFFFFF) // Clear mask for pin 6/14
#define GPIO_MSK_CLR_7 (0x0FFFFFFF) // Clear mask for pin 7/15

// Input type masks
#define GPIO_MSK_AN (0x00) // Mask for input analog
#define GPIO_MSK_FLT (0x04) // Mask for input floating
#define GPIO_MSK_PUD (0x08) // Mask for input with pull up/down

// Input pin masks
#define GPIO_MSK_AN_0 (uint32_t)(GPIO_MSK_AN)
#define GPIO_MSK_AN_1 (uint32_t)(GPIO_MSK_AN << 4)
#define GPIO_MSK_AN_2 (uint32_t)(GPIO_MSK_AN << 8)
#define GPIO_MSK_AN_3 (uint32_t)(GPIO_MSK_AN << 12)
#define GPIO_MSK_AN_4 (uint32_t)(GPIO_MSK_AN << 16)
#define GPIO_MSK_AN_5 (uint32_t)(GPIO_MSK_AN << 20)
#define GPIO_MSK_AN_6 (uint32_t)(GPIO_MSK_AN << 24)
#define GPIO_MSK_AN_7 (uint32_t)(GPIO_MSK_AN << 28)

#define GPIO_MSK_FLT_0 (uint32_t)(GPIO_MSK_FLT)
#define GPIO_MSK_FLT_1 (uint32_t)(GPIO_MSK_FLT << 4)
#define GPIO_MSK_FLT_2 (uint32_t)(GPIO_MSK_FLT << 8)
#define GPIO_MSK_FLT_3 (uint32_t)(GPIO_MSK_FLT << 12)
#define GPIO_MSK_FLT_4 (uint32_t)(GPIO_MSK_FLT << 16)
#define GPIO_MSK_FLT_5 (uint32_t)(GPIO_MSK_FLT << 20)
#define GPIO_MSK_FLT_6 (uint32_t)(GPIO_MSK_FLT << 24)
#define GPIO_MSK_FLT_7 (uint32_t)(GPIO_MSK_FLT << 28)

#define GPIO_MSK_PUD_0 (uint32_t)(GPIO_MSK_PUD)
#define GPIO_MSK_PUD_1 (uint32_t)(GPIO_MSK_PUD << 4)
#define GPIO_MSK_PUD_2 (uint32_t)(GPIO_MSK_PUD << 8)
#define GPIO_MSK_PUD_3 (uint32_t)(GPIO_MSK_PUD << 12)
#define GPIO_MSK_PUD_4 (uint32_t)(GPIO_MSK_PUD << 16)
#define GPIO_MSK_PUD_5 (uint32_t)(GPIO_MSK_PUD << 20)
#define GPIO_MSK_PUD_6 (uint32_t)(GPIO_MSK_PUD << 24)
#define GPIO_MSK_PUD_7 (uint32_t)(GPIO_MSK_PUD << 28)
//-----------------------------------------------------------------------------

// Output type masks
#define GPIO_2M (0x02) // Mask for 2MHz output speed
#define GPIO_10M (0x01) // Mask for 10MHz output speed
#define GPIO_50M (0x03) // Mask for 50MHz output speed

#define GPIO_MSK_PP_2M (GPIO_2M) // Output push/pull 2MHz
#define GPIO_MSK_PP_10M (GPIO_10M) // Output push/pull 10MHz
#define GPIO_MSK_PP_50M (GPIO_50M) // Output push/pull 50MHz

#define GPIO_MSK_OD_2M (BIT2 | GPIO_2M) // Output open drain 2MHz
#define GPIO_MSK_OD_10M (BIT2 | GPIO_10M) // Output open drain 10MHz
#define GPIO_MSK_OD_50M (BIT2 | GPIO_50M) // Output open drain 50MHz

#define GPIO_MSK_AFPP_2M (BIT3 | GPIO_2M) // Output alternate function push/pull 2MHz
#define GPIO_MSK_AFPP_10M (BIT3 | GPIO_10M) // Output alternate function push/pull 10MHz
#define GPIO_MSK_AFPP_50M (BIT3 | GPIO_50M) // Output alternate function push/pull 50MHz

#define GPIO_MSK_AFOD_2M (BIT3 | BIT2 | GPIO_2M) // Output alternate function open drain 2MHz
#define GPIO_MSK_AFOD_10M (BIT3 | BIT2 | GPIO_10M) // Output alternate function open drain 10MHz
#define GPIO_MSK_AFOD_50M (BIT3 | BIT2 | GPIO_50M) // Output alternate function open drain 50MHz

// Push/pull 2MHz pin masks
#define GPIO_MSK_PP_0_2M (uint32_t)(GPIO_MSK_PP_2M)
#define GPIO_MSK_PP_1_2M (uint32_t)(GPIO_MSK_PP_2M << 4)
#define GPIO_MSK_PP_2_2M (uint32_t)(GPIO_MSK_PP_2M << 8)
#define GPIO_MSK_PP_3_2M (uint32_t)(GPIO_MSK_PP_2M << 12)
#define GPIO_MSK_PP_4_2M (uint32_t)(GPIO_MSK_PP_2M << 16)
#define GPIO_MSK_PP_5_2M (uint32_t)(GPIO_MSK_PP_2M << 20)
#define GPIO_MSK_PP_6_2M (uint32_t)(GPIO_MSK_PP_2M << 24)
#define GPIO_MSK_PP_7_2M (uint32_t)(GPIO_MSK_PP_2M << 28)

// Push/pull 10MHz pin masks
#define GPIO_MSK_PP_0_10M (uint32_t)(GPIO_MSK_PP_10M)
#define GPIO_MSK_PP_1_10M (uint32_t)(GPIO_MSK_PP_10M << 4)
#define GPIO_MSK_PP_2_10M (uint32_t)(GPIO_MSK_PP_10M << 8)
#define GPIO_MSK_PP_3_10M (uint32_t)(GPIO_MSK_PP_10M << 12)
#define GPIO_MSK_PP_4_10M (uint32_t)(GPIO_MSK_PP_10M << 16)
#define GPIO_MSK_PP_5_10M (uint32_t)(GPIO_MSK_PP_10M << 20)
#define GPIO_MSK_PP_6_10M (uint32_t)(GPIO_MSK_PP_10M << 24)
#define GPIO_MSK_PP_7_10M (uint32_t)(GPIO_MSK_PP_10M << 28)

// Push/pull 50MHz pin masks
#define GPIO_MSK_PP_0_50M (uint32_t)(GPIO_MSK_PP_50M)
#define GPIO_MSK_PP_1_50M (uint32_t)(GPIO_MSK_PP_50M << 4)
#define GPIO_MSK_PP_2_50M (uint32_t)(GPIO_MSK_PP_50M << 8)
#define GPIO_MSK_PP_3_50M (uint32_t)(GPIO_MSK_PP_50M << 12)
#define GPIO_MSK_PP_4_50M (uint32_t)(GPIO_MSK_PP_50M << 16)
#define GPIO_MSK_PP_5_50M (uint32_t)(GPIO_MSK_PP_50M << 20)
#define GPIO_MSK_PP_6_50M (uint32_t)(GPIO_MSK_PP_50M << 24)
#define GPIO_MSK_PP_7_50M (uint32_t)(GPIO_MSK_PP_50M << 28)

// Open drain 2MHz pin masks
#define GPIO_MSK_OD_0_2M (uint32_t)(GPIO_MSK_OD_2M)
#define GPIO_MSK_OD_1_2M (uint32_t)(GPIO_MSK_OD_2M << 4)
#define GPIO_MSK_OD_2_2M (uint32_t)(GPIO_MSK_OD_2M << 8)
#define GPIO_MSK_OD_3_2M (uint32_t)(GPIO_MSK_OD_2M << 12)
#define GPIO_MSK_OD_4_2M (uint32_t)(GPIO_MSK_OD_2M << 16)
#define GPIO_MSK_OD_5_2M (uint32_t)(GPIO_MSK_OD_2M << 20)
#define GPIO_MSK_OD_6_2M (uint32_t)(GPIO_MSK_OD_2M << 24)
#define GPIO_MSK_OD_7_2M (uint32_t)(GPIO_MSK_OD_2M << 28)

// Open drain 10MHz pin masks
#define GPIO_MSK_OD_0_10M (uint32_t)(GPIO_MSK_OD_10M)
#define GPIO_MSK_OD_1_10M (uint32_t)(GPIO_MSK_OD_10M << 4)
#define GPIO_MSK_OD_2_10M (uint32_t)(GPIO_MSK_OD_10M << 8)
#define GPIO_MSK_OD_3_10M (uint32_t)(GPIO_MSK_OD_10M << 12)
#define GPIO_MSK_OD_4_10M (uint32_t)(GPIO_MSK_OD_10M << 16)
#define GPIO_MSK_OD_5_10M (uint32_t)(GPIO_MSK_OD_10M << 20)
#define GPIO_MSK_OD_6_10M (uint32_t)(GPIO_MSK_OD_10M << 24)
#define GPIO_MSK_OD_7_10M (uint32_t)(GPIO_MSK_OD_10M << 28)

// Open drain 50MHz pin masks
#define GPIO_MSK_OD_0_50M (uint32_t)(GPIO_MSK_OD_50M)
#define GPIO_MSK_OD_1_50M (uint32_t)(GPIO_MSK_OD_50M << 4)
#define GPIO_MSK_OD_2_50M (uint32_t)(GPIO_MSK_OD_50M << 8)
#define GPIO_MSK_OD_3_50M (uint32_t)(GPIO_MSK_OD_50M << 12)
#define GPIO_MSK_OD_4_50M (uint32_t)(GPIO_MSK_OD_50M << 16)
#define GPIO_MSK_OD_5_50M (uint32_t)(GPIO_MSK_OD_50M << 20)
#define GPIO_MSK_OD_6_50M (uint32_t)(GPIO_MSK_OD_50M << 24)
#define GPIO_MSK_OD_7_50M (uint32_t)(GPIO_MSK_OD_50M << 28)

// Alternate function push/pull 2MHz pin masks
#define GPIO_MSK_AFPP_0_2M (uint32_t)(GPIO_MSK_AFPP_2M)
#define GPIO_MSK_AFPP_1_2M (uint32_t)(GPIO_MSK_AFPP_2M << 4)
#define GPIO_MSK_AFPP_2_2M (uint32_t)(GPIO_MSK_AFPP_2M << 8)
#define GPIO_MSK_AFPP_3_2M (uint32_t)(GPIO_MSK_AFPP_2M << 12)
#define GPIO_MSK_AFPP_4_2M (uint32_t)(GPIO_MSK_AFPP_2M << 16)
#define GPIO_MSK_AFPP_5_2M (uint32_t)(GPIO_MSK_AFPP_2M << 20)
#define GPIO_MSK_AFPP_6_2M (uint32_t)(GPIO_MSK_AFPP_2M << 24)
#define GPIO_MSK_AFPP_7_2M (uint32_t)(GPIO_MSK_AFPP_2M << 28)

// Alternate function push/pull 10MHz pin masks
#define GPIO_MSK_AFPP_0_10M (uint32_t)(GPIO_MSK_AFPP_10M)
#define GPIO_MSK_AFPP_1_10M (uint32_t)(GPIO_MSK_AFPP_10M << 4)
#define GPIO_MSK_AFPP_2_10M (uint32_t)(GPIO_MSK_AFPP_10M << 8)
#define GPIO_MSK_AFPP_3_10M (uint32_t)(GPIO_MSK_AFPP_10M << 12)
#define GPIO_MSK_AFPP_4_10M (uint32_t)(GPIO_MSK_AFPP_10M << 16)
#define GPIO_MSK_AFPP_5_10M (uint32_t)(GPIO_MSK_AFPP_10M << 20)
#define GPIO_MSK_AFPP_6_10M (uint32_t)(GPIO_MSK_AFPP_10M << 24)
#define GPIO_MSK_AFPP_7_10M (uint32_t)(GPIO_MSK_AFPP_10M << 28)

// Alternate function push/pull 50MHz pin masks
#define GPIO_MSK_AFPP_0_50M (uint32_t)(GPIO_MSK_AFPP_50M)
#define GPIO_MSK_AFPP_1_50M (uint32_t)(GPIO_MSK_AFPP_50M << 4)
#define GPIO_MSK_AFPP_2_50M (uint32_t)(GPIO_MSK_AFPP_50M << 8)
#define GPIO_MSK_AFPP_3_50M (uint32_t)(GPIO_MSK_AFPP_50M << 12)
#define GPIO_MSK_AFPP_4_50M (uint32_t)(GPIO_MSK_AFPP_50M << 16)
#define GPIO_MSK_AFPP_5_50M (uint32_t)(GPIO_MSK_AFPP_50M << 20)
#define GPIO_MSK_AFPP_6_50M (uint32_t)(GPIO_MSK_AFPP_50M << 24)
#define GPIO_MSK_AFPP_7_50M (uint32_t)(GPIO_MSK_AFPP_50M << 28)

// Alternate function open drain 2MHz pin masks
#define GPIO_MSK_AFOD_0_2M (uint32_t)(GPIO_MSK_AFOD_2M)
#define GPIO_MSK_AFOD_1_2M (uint32_t)(GPIO_MSK_AFOD_2M << 4)
#define GPIO_MSK_AFOD_2_2M (uint32_t)(GPIO_MSK_AFOD_2M << 8)
#define GPIO_MSK_AFOD_3_2M (uint32_t)(GPIO_MSK_AFOD_2M << 12)
#define GPIO_MSK_AFOD_4_2M (uint32_t)(GPIO_MSK_AFOD_2M << 16)
#define GPIO_MSK_AFOD_5_2M (uint32_t)(GPIO_MSK_AFOD_2M << 20)
#define GPIO_MSK_AFOD_6_2M (uint32_t)(GPIO_MSK_AFOD_2M << 24)
#define GPIO_MSK_AFOD_7_2M (uint32_t)(GPIO_MSK_AFOD_2M << 28)

// Alternate function open drain 10MHz pin masks
#define GPIO_MSK_AFOD_0_10M (uint32_t)(GPIO_MSK_AFOD_10M)
#define GPIO_MSK_AFOD_1_10M (uint32_t)(GPIO_MSK_AFOD_10M << 4)
#define GPIO_MSK_AFOD_2_10M (uint32_t)(GPIO_MSK_AFOD_10M << 8)
#define GPIO_MSK_AFOD_3_10M (uint32_t)(GPIO_MSK_AFOD_10M << 12)
#define GPIO_MSK_AFOD_4_10M (uint32_t)(GPIO_MSK_AFOD_10M << 16)
#define GPIO_MSK_AFOD_5_10M (uint32_t)(GPIO_MSK_AFOD_10M << 20)
#define GPIO_MSK_AFOD_6_10M (uint32_t)(GPIO_MSK_AFOD_10M << 24)
#define GPIO_MSK_AFOD_7_10M (uint32_t)(GPIO_MSK_AFOD_10M << 28)

// Alternate function open drain 50MHz pin masks
#define GPIO_MSK_AFOD_0_50M (uint32_t)(GPIO_MSK_AFOD_50M)
#define GPIO_MSK_AFOD_1_50M (uint32_t)(GPIO_MSK_AFOD_50M << 4)
#define GPIO_MSK_AFOD_2_50M (uint32_t)(GPIO_MSK_AFOD_50M << 8)
#define GPIO_MSK_AFOD_3_50M (uint32_t)(GPIO_MSK_AFOD_50M << 12)
#define GPIO_MSK_AFOD_4_50M (uint32_t)(GPIO_MSK_AFOD_50M << 16)
#define GPIO_MSK_AFOD_5_50M (uint32_t)(GPIO_MSK_AFOD_50M << 20)
#define GPIO_MSK_AFOD_6_50M (uint32_t)(GPIO_MSK_AFOD_50M << 24)
#define GPIO_MSK_AFOD_7_50M (uint32_t)(GPIO_MSK_AFOD_50M << 28)
