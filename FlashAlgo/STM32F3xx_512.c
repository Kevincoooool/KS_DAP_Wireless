/* Flash OS Routines (Automagically Generated)
 * Copyright (c) 2009-2015 ARM Limited
 */
#include "flash_blob.h"

static const uint32_t flash_code[] = {
    0xE00ABE00, 0x062D780D, 0x24084068, 0xD3000040, 0x1E644058, 0x1C49D1FA, 0x2A001E52, 0x4770D1F2,
    0x49364837, 0x49376041, 0x21006041, 0x68C16001, 0x43112214, 0x69C060C1, 0xD40605C0, 0x49324833,
    0x21066001, 0x49326041, 0x20006081, 0x482C4770, 0x22806901, 0x61014311, 0x47702000, 0x4828B510,
    0x24046901, 0x61014321, 0x22406901, 0x61014311, 0x4A264928, 0x6011E000, 0x07DB68C3, 0x6901D1FB,
    0x610143A1, 0xBD102000, 0x491DB510, 0x2402690A, 0x610A4322, 0x69086148, 0x43102240, 0x481D6108,
    0xE0004A1A, 0x68CB6010, 0xD1FB07DB, 0x43A06908, 0x20006108, 0xB570BD10, 0x08491C49, 0x26140049,
    0x23014D0F, 0x692CE016, 0x612C431C, 0x80048814, 0x07E468EC, 0x692CD1FC, 0x00640864, 0x68EC612C,
    0xD0044234, 0x433068E8, 0x200160E8, 0x1C80BD70, 0x1C921E89, 0xD1E62900, 0xBD702000, 0x45670123,
    0x40022000, 0xCDEF89AB, 0x00005555, 0x40003000, 0x00000FFF, 0x0000AAAA, 0x00000000
};

const program_target_t flash_algo = {
    0x20000021,  // Init
    0x2000004F,  // UnInit
    0x2000005D,  // EraseChip
    0x20000089,  // EraseSector
    0x200000B7,  // ProgramPage

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
    0x00000400,  // ram_to_flash_bytes_to_be_written
};
