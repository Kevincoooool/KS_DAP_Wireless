/* Flash OS Routines (Automagically Generated)
 * Copyright (c) 2009-2015 ARM Limited
 */
#include "flash_blob.h"

static const uint32_t flash_code[] = {
    0xE00ABE00, 0x062D780D, 0x24084068, 0xD3000040, 0x1E644058, 0x1C49D1FA, 0x2A001E52, 0x4770D1F2,
    0x03004601, 0x28200E00, 0x0940D302, 0xE0051D00, 0xD3022810, 0x1CC00900, 0x0880E000, 0xD50102C9,
    0x43082110, 0x482C4770, 0x6081492A, 0x6081492B, 0x22F068C1, 0x60C14311, 0x06806940, 0x4829D406,
    0x60014927, 0x60412106, 0x60814927, 0x47702000, 0x69414821, 0x43112201, 0x20006141, 0x481E4770,
    0x21F068C2, 0x60C2430A, 0x61424A20, 0x23026942, 0x6142431A, 0x061268C2, 0xD0040F12, 0x430A68C2,
    0x200160C2, 0x20004770, 0x20004770, 0x48124770, 0x68C36811, 0x431322F0, 0x4B1560C3, 0x1C894019,
    0x68C16141, 0xD4FC03C9, 0x060968C1, 0xD0040F09, 0x431168C1, 0x200160C1, 0x20004770, 0xB5104770,
    0x68124C05, 0x69644B0A, 0x401C401A, 0xD10042A2, 0xBD101840, 0x08192A3B, 0x40023C00, 0x4C5D6E7F,
    0x00005555, 0x40003000, 0x00000FFF, 0x0FFFAAEC, 0x0FFFFFFC, 0x00000000
};

const program_target_t flash_algo = {
    0x20000047,  // Init
    0x20000071,  // UnInit
    0x2000007F,  // EraseChip
    0x200000AB,  // EraseSector
    0x200000AF,  // ProgramPage

    // BKPT : start of blob + 1
    // RSB  : address to access global/static data
    // RSP  : stack pointer
    {
        0x20000001,
        0x20000C00,
        0x20001000
    },

    0x20000400,  // mem buffer location
    0x20000000,  // location to write prog_blob in target RAM
    sizeof(flash_code),  // prog_blob size
    flash_code,  // address of prog_blob
    0x00000004,  // ram_to_flash_bytes_to_be_written
};
