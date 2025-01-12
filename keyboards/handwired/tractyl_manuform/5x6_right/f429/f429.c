// Copyright 2025 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#include "tractyl_manuform.h"

void user_button_init(void) {
    // Pin needs to be configured as input low
#ifdef USER_BUTTON_PIN
    gpio_set_pin_input_high(USER_BUTTON_PIN);
#endif // USER_BUTTON_PIN
}

bool check_user_button_state(void) {
#ifdef DEBUG_LED_PIN
    gpio_write_pin(DEBUG_LED_PIN, !is_keyboard_master());
#endif
#ifdef USER_BUTTON_PIN
    gpio_write_pin(USER_BUTTON_PIN, !gpio_read_pin(USER_BUTTON_PIN));
    return !gpio_read_pin(USER_BUTTON_PIN);
#endif // USER_BUTTON_PIN
    return false;
}

void early_hardware_init_post(void) {
    // D-  white
    palSetLineMode(B14, PAL_MODE_ALTERNATE(12) | PAL_STM32_OTYPE_PUSHPULL | PAL_STM32_OSPEED_HIGHEST | PAL_STM32_PUPDR_FLOATING);
    // D+  blue
    palSetLineMode(B15, PAL_MODE_ALTERNATE(12) | PAL_STM32_OTYPE_PUSHPULL | PAL_STM32_OSPEED_HIGHEST | PAL_STM32_PUPDR_FLOATING);
}

#if HAL_USE_FSMC == TRUE
#    if HAL_USE_SDRAM == TRUE
#        pragma message "Configured to use SDRAM"
/* SDRAM bank base address.*/
#        define SDRAM_BANK_ADDR ((uint32_t)0xD0000000)

/*
 *  FMC SDRAM Mode definition register defines
 */
#        define FMC_SDCMR_MRD_BURST_LENGTH_1 ((uint16_t)0x0000)
#        define FMC_SDCMR_MRD_BURST_LENGTH_2 ((uint16_t)0x0001)
#        define FMC_SDCMR_MRD_BURST_LENGTH_4 ((uint16_t)0x0002)
#        define FMC_SDCMR_MRD_BURST_LENGTH_8 ((uint16_t)0x0004)
#        define FMC_SDCMR_MRD_BURST_TYPE_SEQUENTIAL ((uint16_t)0x0000)
#        define FMC_SDCMR_MRD_BURST_TYPE_INTERLEAVED ((uint16_t)0x0008)
#        define FMC_SDCMR_MRD_CAS_LATENCY_2 ((uint16_t)0x0020)
#        define FMC_SDCMR_MRD_CAS_LATENCY_3 ((uint16_t)0x0030)
#        define FMC_SDCMR_MRD_OPERATING_MODE_STANDARD ((uint16_t)0x0000)
#        define FMC_SDCMR_MRD_WRITEBURST_MODE_PROGRAMMED ((uint16_t)0x0000)
#        define FMC_SDCMR_MRD_WRITEBURST_MODE_SINGLE ((uint16_t)0x0200)

/*
 * FMC_ReadPipe_Delay
 */
#        define FMC_ReadPipe_Delay_0 ((uint32_t)0x00000000)
#        define FMC_ReadPipe_Delay_1 ((uint32_t)0x00002000)
#        define FMC_ReadPipe_Delay_2 ((uint32_t)0x00004000)
#        define FMC_ReadPipe_Delay_Mask ((uint32_t)0x00006000)

/*
 * FMC_Read_Burst
 */
#        define FMC_Read_Burst_Disable ((uint32_t)0x00000000)
#        define FMC_Read_Burst_Enable ((uint32_t)0x00001000)
#        define FMC_Read_Burst_Mask ((uint32_t)0x00001000)

/*
 * FMC_SDClock_Period
 */
#        define FMC_SDClock_Disable ((uint32_t)0x00000000)
#        define FMC_SDClock_Period_2 ((uint32_t)0x00000800)
#        define FMC_SDClock_Period_3 ((uint32_t)0x00000C00)
#        define FMC_SDClock_Period_Mask ((uint32_t)0x00000C00)

/*
 * FMC_ColumnBits_Number
 */
#        define FMC_ColumnBits_Number_8b ((uint32_t)0x00000000)
#        define FMC_ColumnBits_Number_9b ((uint32_t)0x00000001)
#        define FMC_ColumnBits_Number_10b ((uint32_t)0x00000002)
#        define FMC_ColumnBits_Number_11b ((uint32_t)0x00000003)

/*
 * FMC_RowBits_Number
 */
#        define FMC_RowBits_Number_11b ((uint32_t)0x00000000)
#        define FMC_RowBits_Number_12b ((uint32_t)0x00000004)
#        define FMC_RowBits_Number_13b ((uint32_t)0x00000008)

/*
 * FMC_SDMemory_Data_Width
 */
#        define FMC_SDMemory_Width_8b ((uint32_t)0x00000000)
#        define FMC_SDMemory_Width_16b ((uint32_t)0x00000010)
#        define FMC_SDMemory_Width_32b ((uint32_t)0x00000020)

/*
 * FMC_InternalBank_Number
 */
#        define FMC_InternalBank_Number_2 ((uint32_t)0x00000000)
#        define FMC_InternalBank_Number_4 ((uint32_t)0x00000040)

/*
 * FMC_CAS_Latency
 */
#        define FMC_CAS_Latency_1 ((uint32_t)0x00000080)
#        define FMC_CAS_Latency_2 ((uint32_t)0x00000100)
#        define FMC_CAS_Latency_3 ((uint32_t)0x00000180)

/*
 * FMC_Write_Protection
 */
#        define FMC_Write_Protection_Disable ((uint32_t)0x00000000)
#        define FMC_Write_Protection_Enable ((uint32_t)0x00000200)

#        include "hal.h"

/*
 * SDRAM driver configuration structure.
 */
static const SDRAMConfig sdram_cfg = {
    // clang-format off
    .sdcr = (uint32_t)(FMC_ColumnBits_Number_9b |
                       FMC_RowBits_Number_13b |
                       FMC_SDMemory_Width_16b |
                       FMC_InternalBank_Number_4 |
                       FMC_CAS_Latency_3 |
                       FMC_Write_Protection_Disable |
                       FMC_SDClock_Period_2 |
                       FMC_Read_Burst_Disable |
                       FMC_ReadPipe_Delay_1),
    // clang-format on
    .sdtr = (uint32_t)((2 - 1) |     // TMRD: 2 cycles (tMRD >= 2 tCK)
                       ((7) << 4) |  // TXSR: 8 cycles (95.2ns >= tXSR=72ns @ 84MHz/11.905ns)
                       ((4) << 8) |  // TRAS: 5 cycles (59.5ns >= tRAS=42ns @ 84MHz)
                       ((7) << 12) | // TRC:  8 cycles (95.2ns >= tRC=60ns @ 84MHz)
                       ((2) << 16) | // TWR:  3 cycles (>= 2 tCK)
                       ((2) << 20) | // TRP:  3 cycles (35.7ns >= tRP=15ns @ 84MHz)
                       ((2) << 24)), // TRCD: 3 cycles (35.7ns >= tRCD=15ns @ 84MHz)
                                     // clang-format off
    .sdcmr = (uint32_t)(((4 - 1) << 5) |
                      ((FMC_SDCMR_MRD_BURST_LENGTH_2 |
                        FMC_SDCMR_MRD_BURST_TYPE_SEQUENTIAL |
                        FMC_SDCMR_MRD_CAS_LATENCY_3 |
                        FMC_SDCMR_MRD_OPERATING_MODE_STANDARD |
                        FMC_SDCMR_MRD_WRITEBURST_MODE_SINGLE) << 9)),
                                     // clang-format on
    /* STM32_SYSCLK = 168MHz, FMC_SDClock_Period_2 -> SDCLK = 84MHz
       W9825G6KH has 8192 rows (8K refresh cycles / 64ms)
       64ms / 8192 = 7.8125us
       7.8125us * 84MHz = 656.25 - 20 = 636 */
    .sdrtr = (uint32_t)(636 << 1),
};

/* SDRAM size, in bytes.*/
#        define W9825G6KH_6_SIZE (32 * 1024 * 1024)

/*
 * Erases the whole SDRAM bank.
 */
static void sdram_bulk_erase(void) {
    volatile uint8_t *p   = (volatile uint8_t *)SDRAM_BANK_ADDR;
    volatile uint8_t *end = p + W9825G6KH_6_SIZE;
    while (p < end)
        *p++ = 0xFF;
}

#        define FMC_SDRAM_D0_PIN D14
#        define FMC_SDRAM_D1_PIN D15
#        define FMC_SDRAM_D2_PIN D0
#        define FMC_SDRAM_D3_PIN D1
#        define FMC_SDRAM_D4_PIN E7
#        define FMC_SDRAM_D5_PIN E8
#        define FMC_SDRAM_D6_PIN E9
#        define FMC_SDRAM_D7_PIN E10
#        define FMC_SDRAM_D8_PIN E11
#        define FMC_SDRAM_D9_PIN E12
#        define FMC_SDRAM_D10_PIN E13
#        define FMC_SDRAM_D11_PIN E14
#        define FMC_SDRAM_D12_PIN E15
#        define FMC_SDRAM_D13_PIN D8
#        define FMC_SDRAM_D14_PIN D9
#        define FMC_SDRAM_D15_PIN D10

#        define FMC_SDRAM_A0_PIN F0
#        define FMC_SDRAM_A1_PIN F1
#        define FMC_SDRAM_A2_PIN F2
#        define FMC_SDRAM_A3_PIN F3
#        define FMC_SDRAM_A4_PIN F4
#        define FMC_SDRAM_A5_PIN F5
#        define FMC_SDRAM_A6_PIN F12
#        define FMC_SDRAM_A7_PIN F13
#        define FMC_SDRAM_A8_PIN F14
#        define FMC_SDRAM_A9_PIN F15
#        define FMC_SDRAM_A10_PIN G0
#        define FMC_SDRAM_A11_PIN G1
#        define FMC_SDRAM_A12_PIN G2

#        define FMC_SDRAM_BA0_PIN G4
#        define FMC_SDRAM_BA1_PIN G5

#        define FMC_SDRAM_SDCKE1_PIN H7
#        define FMC_SDRAM_SDNWE_PIN C0
#        define FMC_SDRAM_SDNRAS_PIN F11
#        define FMC_SDRAM_SDNCAS_PIN G15
#        define FMC_SDRAM_SDCLK_PIN G8
#        define FMC_SDRAM_SDNE1_PIN H6

#        define FMC_SDRAM_NBL0_PIN E0
#        define FMC_SDRAM_NBL1_PIN E1

const pin_t fmc_sdram_pin_array[] = {
    FMC_SDRAM_D0_PIN, FMC_SDRAM_D1_PIN, FMC_SDRAM_D2_PIN, FMC_SDRAM_D3_PIN, FMC_SDRAM_D4_PIN, FMC_SDRAM_D5_PIN, FMC_SDRAM_D6_PIN, FMC_SDRAM_D7_PIN, FMC_SDRAM_D8_PIN, FMC_SDRAM_D9_PIN, FMC_SDRAM_D10_PIN, FMC_SDRAM_D11_PIN, FMC_SDRAM_D12_PIN, FMC_SDRAM_D13_PIN, FMC_SDRAM_D14_PIN, FMC_SDRAM_D15_PIN, FMC_SDRAM_A0_PIN, FMC_SDRAM_A1_PIN, FMC_SDRAM_A2_PIN, FMC_SDRAM_A3_PIN, FMC_SDRAM_A4_PIN, FMC_SDRAM_A5_PIN, FMC_SDRAM_A6_PIN, FMC_SDRAM_A7_PIN, FMC_SDRAM_A8_PIN, FMC_SDRAM_A9_PIN, FMC_SDRAM_A10_PIN, FMC_SDRAM_A11_PIN, FMC_SDRAM_A12_PIN, FMC_SDRAM_BA0_PIN, FMC_SDRAM_BA1_PIN, FMC_SDRAM_SDNRAS_PIN, FMC_SDRAM_SDCLK_PIN, FMC_SDRAM_SDNCAS_PIN, FMC_SDRAM_SDNWE_PIN, FMC_SDRAM_SDNE1_PIN, FMC_SDRAM_SDCKE1_PIN, FMC_SDRAM_NBL0_PIN, FMC_SDRAM_NBL1_PIN,
};
#    endif // HAL_USE_SDRAM == TRUE

#    if HAL_USE_NAND == TRUE
#        pragma message "Configured to use NAND"

/* NAND bank base address */
#        define NAND_BANK_ADDR ((uint32_t)0x80000000)

/*
 * Winbond W29N01HVSINA - 1Gbit NAND Flash
 * Organization: 8192 blocks × 64 pages/block × 2048 bytes/page + 64 bytes spare
 * Total capacity: 1,073,741,824 bytes (1GB)
 * Data width: 16-bit
 * Row address cycles: 3 (for 8192 blocks × 64 pages)
 * Column address cycles: 2 (for 2048 + 64 bytes)
 */

/* Timing parameters (STM32 FSMC NAND controller timing cycles) */
#        define FSMCNAND_TIME_SET ((uint32_t)2)  /* Setup time (~8ns) */
#        define FSMCNAND_TIME_WAIT ((uint32_t)6) /* Access/Wait time (~30ns) */
#        define FSMCNAND_TIME_HOLD ((uint32_t)1) /* Hold time (~5ns) */
#        define FSMCNAND_TIME_HIZ ((uint32_t)4)  /* High-impedance time (~20ns) */

/* Memory organization constants */
#        define NAND_DIES_COUNT 1
#        define NAND_LOGUNS_COUNT 1
#        define NAND_PLANES_COUNT 1
#        define NAND_BLOCKS_COUNT 8192   /* 8192 blocks */
#        define NAND_PAGE_DATA_SIZE 2048 /* 2048 bytes data per page */
#        define NAND_PAGE_SPARE_SIZE 64  /* 64 bytes spare area per page */
#        define NAND_PAGE_SIZE (NAND_PAGE_SPARE_SIZE + NAND_PAGE_DATA_SIZE)
#        define NAND_PAGES_PER_BLOCK 64 /* 64 pages per block */
#        define NAND_ROW_WRITE_CYCLES 3 /* 3 row address cycles (24 bits) */
#        define NAND_COL_WRITE_CYCLES 2 /* 2 column address cycles (16 bits) */

/*
 * NAND driver configuration structure.
 */
static const NANDConfig nand_cfg = {.dies = NAND_DIES_COUNT, .loguns = NAND_LOGUNS_COUNT, .planes = NAND_PLANES_COUNT, .blocks = NAND_BLOCKS_COUNT, .page_data_size = NAND_PAGE_DATA_SIZE, .page_spare_size = NAND_PAGE_SPARE_SIZE, .pages_per_block = NAND_PAGES_PER_BLOCK, .rowcycles = NAND_ROW_WRITE_CYCLES, .colcycles = NAND_COL_WRITE_CYCLES, .pmem = ((FSMCNAND_TIME_HIZ << 24) | (FSMCNAND_TIME_HOLD << 16) | (FSMCNAND_TIME_WAIT << 8) | FSMCNAND_TIME_SET)};

/* NAND data pins (shared with SDRAM) */
#        define FMC_NAND_D0_PIN D14
#        define FMC_NAND_D1_PIN D15
#        define FMC_NAND_D2_PIN D0
#        define FMC_NAND_D3_PIN D1
#        define FMC_NAND_D4_PIN E7
#        define FMC_NAND_D5_PIN E8
#        define FMC_NAND_D6_PIN E9
#        define FMC_NAND_D7_PIN E10
#        define FMC_NAND_D8_PIN E11
#        define FMC_NAND_D9_PIN E12
#        define FMC_NAND_D10_PIN E13
#        define FMC_NAND_D11_PIN E14
#        define FMC_NAND_D12_PIN E15
#        define FMC_NAND_D13_PIN D8
#        define FMC_NAND_D14_PIN D9
#        define FMC_NAND_D15_PIN D10

/* NAND control pins */
#        define FMC_NAND_NCE_PIN G9    /* Chip Enable */
#        define FMC_NAND_NRE_PIN D4    /* Read Enable */
#        define FMC_NAND_NWE_PIN D5    /* Write Enable */
#        define FMC_NAND_NWAIT_PIN B13 /* Ready/Busy */
#        define FMC_NAND_CLE_PIN D11   /* Command Latch Enable */
#        define FMC_NAND_ALE_PIN D12   /* Address Latch Enable */

const pin_t fmc_nand_pin_array[] = {
    FMC_NAND_D0_PIN, FMC_NAND_D1_PIN, FMC_NAND_D2_PIN, FMC_NAND_D3_PIN, FMC_NAND_D4_PIN, FMC_NAND_D5_PIN, FMC_NAND_D6_PIN, FMC_NAND_D7_PIN, FMC_NAND_D8_PIN, FMC_NAND_D9_PIN, FMC_NAND_D10_PIN, FMC_NAND_D11_PIN, FMC_NAND_D12_PIN, FMC_NAND_D13_PIN, FMC_NAND_D14_PIN, FMC_NAND_D15_PIN, FMC_NAND_NCE_PIN, FMC_NAND_NRE_PIN, FMC_NAND_NWE_PIN, FMC_NAND_NWAIT_PIN, FMC_NAND_CLE_PIN, FMC_NAND_ALE_PIN,
};
#    endif // HAL_USE_NAND == TRUE

void board_init(void) {

// init FSMC pins first, since the FSMC peripherals share pins. Make sure all of the pins are initialized before starting any of the peripherals.
#if HAL_USE_SDRAM == TRUE
    for (uint8_t i = 0; i < ARRAY_SIZE(fmc_sdram_pin_array); i++) {
        palSetLineMode(fmc_sdram_pin_array[i], (PAL_MODE_ALTERNATE(12) | PAL_STM32_OTYPE_PUSHPULL | PAL_STM32_OSPEED_HIGHEST | PAL_STM32_PUPDR_FLOATING));
    }
    xprintf("SDRAM Init: Pins\n");
#endif // HAL_USE_SDRAM == TRUE
#if HAL_USE_NAND == TRUE
    for (uint8_t i = 0; i < ARRAY_SIZE(fmc_nand_pin_array); i++) {
        palSetLineMode(fmc_nand_pin_array[i], (PAL_MODE_ALTERNATE(12) | PAL_STM32_OTYPE_OPENDRAIN | PAL_STM32_OSPEED_HIGHEST | PAL_STM32_PUPDR_FLOATING));
    }
    xprintf("NAND Init: Pins\n");
#endif // HAL_USE_NAND == TRUE

// now that pins are initialized, we can start the peripherals

#if HAL_USE_SDRAM == TRUE
    sdramInit();
    sdramStart(&SDRAMD1, &sdram_cfg);
    xprintf("SDRAM Init: Device\n");
    xprintf("SDRAM Init: Full Erase Start\n");
    sdram_bulk_erase();
    xprintf("SDRAM Init: Full Erase Finish\n");
#endif // HAL_USE_SDRAM == TRUE

#if HAL_USE_NAND == TRUE
    nandInit();
    nandStart(&NANDD1, &nand_cfg, NULL);
    xprintf("NAND Init: Device\n");
    // we need a lot more here before nand is working. Including keeping track of bad blocks (or reading at each startup. )
#endif // HAL_USE_NAND == TRUE
}

#endif
