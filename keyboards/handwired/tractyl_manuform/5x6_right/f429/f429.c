/* Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "tractyl_manuform.h"

void user_button_init(void) {
    // Pin needs to be configured as input low
#ifdef USER_BUTTON_PIN
    gpio_set_pin_input_high(USER_BUTTON_PIN);
#endif // USER_BUTTON_PIN
    gpio_set_pin_output(F7);
    gpio_write_pin_low(F7);
    gpio_set_pin_output(F8);
    gpio_write_pin_low(F8);
    gpio_set_pin_output(F9);
    gpio_write_pin_low(F9);
}

bool check_user_button_state(void) {
#ifdef DEBUG_LED_PIN
    gpio_write_pin(DEBUG_LED_PIN, is_keyboard_master());
#endif
#ifdef USER_BUTTON_PIN
    gpio_write_pin(F8, !gpio_read_pin(USER_BUTTON_PIN));
    return !gpio_read_pin(USER_BUTTON_PIN);
#endif // USER_BUTTON_PIN
    return false;
}

#if HAL_USE_SDRAM == TRUE
#    pragma message "Configured to use SDRAM"
/* SDRAM bank base address.*/
#    define SDRAM_BANK_ADDR ((uint32_t)0xD0000000)

/*
 *  FMC SDRAM Mode definition register defines
 */
#    define FMC_SDCMR_MRD_BURST_LENGTH_1 ((uint16_t)0x0000)
#    define FMC_SDCMR_MRD_BURST_LENGTH_2 ((uint16_t)0x0001)
#    define FMC_SDCMR_MRD_BURST_LENGTH_4 ((uint16_t)0x0002)
#    define FMC_SDCMR_MRD_BURST_LENGTH_8 ((uint16_t)0x0004)
#    define FMC_SDCMR_MRD_BURST_TYPE_SEQUENTIAL ((uint16_t)0x0000)
#    define FMC_SDCMR_MRD_BURST_TYPE_INTERLEAVED ((uint16_t)0x0008)
#    define FMC_SDCMR_MRD_CAS_LATENCY_2 ((uint16_t)0x0020)
#    define FMC_SDCMR_MRD_CAS_LATENCY_3 ((uint16_t)0x0030)
#    define FMC_SDCMR_MRD_OPERATING_MODE_STANDARD ((uint16_t)0x0000)
#    define FMC_SDCMR_MRD_WRITEBURST_MODE_PROGRAMMED ((uint16_t)0x0000)
#    define FMC_SDCMR_MRD_WRITEBURST_MODE_SINGLE ((uint16_t)0x0200)

/*
 * FMC_ReadPipe_Delay
 */
#    define FMC_ReadPipe_Delay_0 ((uint32_t)0x00000000)
#    define FMC_ReadPipe_Delay_1 ((uint32_t)0x00002000)
#    define FMC_ReadPipe_Delay_2 ((uint32_t)0x00004000)
#    define FMC_ReadPipe_Delay_Mask ((uint32_t)0x00006000)

/*
 * FMC_Read_Burst
 */
#    define FMC_Read_Burst_Disable ((uint32_t)0x00000000)
#    define FMC_Read_Burst_Enable ((uint32_t)0x00001000)
#    define FMC_Read_Burst_Mask ((uint32_t)0x00001000)

/*
 * FMC_SDClock_Period
 */
#    define FMC_SDClock_Disable ((uint32_t)0x00000000)
#    define FMC_SDClock_Period_2 ((uint32_t)0x00000800)
#    define FMC_SDClock_Period_3 ((uint32_t)0x00000C00)
#    define FMC_SDClock_Period_Mask ((uint32_t)0x00000C00)

/*
 * FMC_ColumnBits_Number
 */
#    define FMC_ColumnBits_Number_8b ((uint32_t)0x00000000)
#    define FMC_ColumnBits_Number_9b ((uint32_t)0x00000001)
#    define FMC_ColumnBits_Number_10b ((uint32_t)0x00000002)
#    define FMC_ColumnBits_Number_11b ((uint32_t)0x00000003)

/*
 * FMC_RowBits_Number
 */
#    define FMC_RowBits_Number_11b ((uint32_t)0x00000000)
#    define FMC_RowBits_Number_12b ((uint32_t)0x00000004)
#    define FMC_RowBits_Number_13b ((uint32_t)0x00000008)

/*
 * FMC_SDMemory_Data_Width
 */
#    define FMC_SDMemory_Width_8b ((uint32_t)0x00000000)
#    define FMC_SDMemory_Width_16b ((uint32_t)0x00000010)
#    define FMC_SDMemory_Width_32b ((uint32_t)0x00000020)

/*
 * FMC_InternalBank_Number
 */
#    define FMC_InternalBank_Number_2 ((uint32_t)0x00000000)
#    define FMC_InternalBank_Number_4 ((uint32_t)0x00000040)

/*
 * FMC_CAS_Latency
 */
#    define FMC_CAS_Latency_1 ((uint32_t)0x00000080)
#    define FMC_CAS_Latency_2 ((uint32_t)0x00000100)
#    define FMC_CAS_Latency_3 ((uint32_t)0x00000180)

/*
 * FMC_Write_Protection
 */
#    define FMC_Write_Protection_Disable ((uint32_t)0x00000000)
#    define FMC_Write_Protection_Enable ((uint32_t)0x00000200)

#    include "hal.h"

/*
 * SDRAM driver configuration structure.
 */
static const SDRAMConfig sdram_cfg = {
    // clang-format off
    .sdcr = (uint32_t)(FMC_ColumnBits_Number_8b |
                       FMC_RowBits_Number_12b |
                       FMC_SDMemory_Width_16b |
                       FMC_InternalBank_Number_4 |
                       FMC_CAS_Latency_3 |
                       FMC_Write_Protection_Disable |
                       FMC_SDClock_Period_2 |
                       FMC_Read_Burst_Disable |
                       FMC_ReadPipe_Delay_1),
    // clang-format on
    .sdtr = (uint32_t)((2 - 1) |   // FMC_LoadToActiveDelay = 2 (TMRD: 2 Clock cycles)
                       (7 << 4) |  // FMC_ExitSelfRefreshDelay = 7 (TXSR: min=70ns (7x11.11ns))
                       (4 << 8) |  // FMC_SelfRefreshTime = 4 (TRAS: min=42ns (4x11.11ns) max=120k (ns))
                       (7 << 12) | // FMC_RowCycleDelay = 7 (TRC:  min=70 (7x11.11ns))
                       (2 << 16) | // FMC_WriteRecoveryTime = 2 (TWR:  min=1+ 7ns (1+1x11.11ns))
                       (2 << 20) | // FMC_RPDelay = 2 (TRP:  20ns => 2x11.11ns)
                       (2 << 24)), // FMC_RCDDelay = 2 (TRCD: 20ns => 2x11.11ns)
   // clang-format off
    .sdcmr = (uint32_t)(((4 - 1) << 5) |
                      ((FMC_SDCMR_MRD_BURST_LENGTH_2 |
                        FMC_SDCMR_MRD_BURST_TYPE_SEQUENTIAL |
                        FMC_SDCMR_MRD_CAS_LATENCY_3 |
                        FMC_SDCMR_MRD_OPERATING_MODE_STANDARD |
                        FMC_SDCMR_MRD_WRITEBURST_MODE_SINGLE) << 9)),
                                   // clang-format on
    /* if (STM32_SYSCLK == 180000000) ->
       64ms / 4096 = 15.625us
       15.625us * 90MHz = 1406 - 20 = 1386 */
    //.sdrtr = (1386 << 1),
    .sdrtr = (uint32_t)(683 << 1),
};

/* SDRAM size, in bytes.*/
#    define IS42S16400J_SIZE (8 * 1024 * 1024)

/*
 * Erases the whole SDRAM bank.
 */
static void sdram_bulk_erase(void) {
    volatile uint8_t *p   = (volatile uint8_t *)SDRAM_BANK_ADDR;
    volatile uint8_t *end = p + IS42S16400J_SIZE;
    while (p < end)
        *p++ = 0xFF;
}

#    define FMC_SDRAM_D2_PIN D0
#    define FMC_SDRAM_D3_PIN D1
#    define FMC_SDRAM_D13_PIN D8
#    define FMC_SDRAM_D14_PIN D9
#    define FMC_SDRAM_D15_PIN D10
#    define FMC_SDRAM_D0_PIN D14
#    define FMC_SDRAM_D1_PIN D15
#    define FMC_SDRAM_NBL0_PIN E0
#    define FMC_SDRAM_NBL1_PIN E1
#    define FMC_SDRAM_D4_PIN E7
#    define FMC_SDRAM_D5_PIN E8
#    define FMC_SDRAM_D6_PIN E9
#    define FMC_SDRAM_D7_PIN E10
#    define FMC_SDRAM_D8_PIN E11
#    define FMC_SDRAM_D9_PIN E12
#    define FMC_SDRAM_D10_PIN E13
#    define FMC_SDRAM_D11_PIN E14
#    define FMC_SDRAM_D12_PIN E15

#    define FMC_SDRAM_A0_PIN F0
#    define FMC_SDRAM_A1_PIN F1
#    define FMC_SDRAM_A2_PIN F2
#    define FMC_SDRAM_A3_PIN F3
#    define FMC_SDRAM_A4_PIN F4
#    define FMC_SDRAM_A5_PIN F5
#    define FMC_SDRAM_SDNRAS_PIN F11
#    define FMC_SDRAM_A6_PIN F12
#    define FMC_SDRAM_A7_PIN F13
#    define FMC_SDRAM_A8_PIN F14
#    define FMC_SDRAM_A9_PIN F15
#    define FMC_SDRAM_A10_PIN G0
#    define FMC_SDRAM_A11_PIN G1
#    define FMC_SDRAM_BA0_PIN G4
#    define FMC_SDRAM_BA1_PIN G5

#    define FMC_SDRAM_SDCLK_PIN G8
#    define FMC_SDRAM_SDNCAS_PIN G15
#    define FMC_SDRAM_SDNWE_PIN H5
#    define FMC_SDRAM_SDNE1_PIN H6
#    define FMC_SDRAM_SDCKE1_PIN H3

const pin_t fmc_sdram_pin_array[] = {
    FMC_SDRAM_D0_PIN, FMC_SDRAM_D1_PIN, FMC_SDRAM_D2_PIN, FMC_SDRAM_D3_PIN, FMC_SDRAM_D4_PIN, FMC_SDRAM_D5_PIN, FMC_SDRAM_D6_PIN, FMC_SDRAM_D7_PIN, FMC_SDRAM_D8_PIN, FMC_SDRAM_D9_PIN, FMC_SDRAM_D10_PIN, FMC_SDRAM_D11_PIN, FMC_SDRAM_D12_PIN, FMC_SDRAM_A0_PIN, FMC_SDRAM_A1_PIN, FMC_SDRAM_A2_PIN, FMC_SDRAM_A3_PIN, FMC_SDRAM_A4_PIN, FMC_SDRAM_A5_PIN, FMC_SDRAM_A6_PIN, FMC_SDRAM_A7_PIN, FMC_SDRAM_A8_PIN, FMC_SDRAM_A9_PIN, FMC_SDRAM_A10_PIN, FMC_SDRAM_A11_PIN, FMC_SDRAM_BA0_PIN, FMC_SDRAM_BA1_PIN, FMC_SDRAM_SDNRAS_PIN, FMC_SDRAM_SDCLK_PIN, FMC_SDRAM_SDNCAS_PIN, FMC_SDRAM_SDNWE_PIN, FMC_SDRAM_SDNE1_PIN, FMC_SDRAM_SDCKE1_PIN, FMC_SDRAM_NBL0_PIN, FMC_SDRAM_NBL1_PIN,
};

void board_init(void) {
    /*
     * Initialise FSMC for SDRAM.
     */
    for (uint8_t i = 0; i < ARRAY_SIZE(fmc_sdram_pin_array); i++) {
        palSetLineMode(fmc_sdram_pin_array[i], (PAL_MODE_ALTERNATE(12) | PAL_STM32_OTYPE_PUSHPULL | PAL_STM32_OSPEED_HIGHEST | PAL_STM32_PUPDR_FLOATING));
    }
    xprintf("SDRAM Init: Pins\n");

    sdramInit();
    sdramStart(&SDRAMD1, &sdram_cfg);
    xprintf("SDRAM Init: Device\n");
    xprintf("SDRAM Init: Full Erase Start\n");
    sdram_bulk_erase();
    xprintf("SDRAM Init: Full Erase Finish\n");
    // // Board setup sets these pins as SPI, but we aren't using them as such.
    // // So to prevent them from misbehaving, we need to set them to a different, non-spi mode.
    // // This is a bit of a hack, but nothing else runs soon enough, without re-implementing spi_init().
    // gpio_set_pin_input(A5);
    // gpio_set_pin_input(A6);
    // gpio_set_pin_input(A7);
}
#else // HAL_USE_SDRAM == TRUE

void board_init(void) {
    // Board setup sets these pins as SPI, but we aren't using them as such.
    // So to prevent them from misbehaving, we need to set them to a different, non-spi mode.
    // This is a bit of a hack, but nothing else runs soon enough, without re-implementing spi_init().
//     gpio_set_pin_input(A5);
//     gpio_set_pin_input(A6);
//     gpio_set_pin_input(A7);
}
#endif // HAL_USE_SDRAM == TRUE
