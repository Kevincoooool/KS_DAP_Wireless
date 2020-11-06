/* Flash OS Routines (Automagically Generated)
 * Copyright (c) 2009-2015 ARM Limited
 */
#include "flash_blob.h"

static const uint32_t flash_code_F7[] = {
    0xE00ABE00, 0x062D780D, 0x24084068, 0xD3000040, 0x1E644058, 0x1C49D1FA, 0x2A001E52, 0x4770D1F2,
    0x8F4FF3BF, 0x03004770, 0x28400E00, 0x0980D302, 0x47701D00, 0x477008C0, 0x49304831, 0x49316081,
    0x68C16081, 0x431122F0, 0x694060C1, 0xD4060680, 0x492D482E, 0x21066001, 0x492D6041, 0x20006081,
    0x48274770, 0x22016941, 0x61414311, 0x47702000, 0x68C24823, 0x430A21F0, 0x4A2660C2, 0x4A266182,
    0x69426142, 0x431A2302, 0x68C26142, 0x0F120612, 0x68C2D004, 0x60C2430A, 0x47702001, 0x47702000,
    0x47702000, 0x4816B510, 0x68C4CA06, 0x431C23F0, 0x618260C4, 0x40114A19, 0x61411C89, 0x03C968C1,
    0x68C1D4FC, 0x0F090609, 0x68C1D004, 0x60C14319, 0xBD102001, 0xBD102000, 0x4C09B570, 0x4E0F6813,
    0x69656852, 0x40354033, 0xD10342AB, 0x429369A3, 0x1C40D001, 0x1840BD70, 0x0000BD70, 0x08192A3B,
    0x40023C00, 0x4C5D6E7F, 0x00005555, 0x40003000, 0x00000FFF, 0x00400080, 0xC0FFAAFC, 0xC0FFFFFC,
    0x00000000
};

const program_target_t flash_algo_F7 = {
    0x20000039,  // Init
    0x20000063,  // UnInit
    0x20000071,  // EraseChip
    0x200000A1,  // EraseSector
    0x200000A5,  // ProgramPage

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
    sizeof(flash_code_F7),  // prog_blob size
    flash_code_F7,  // address of prog_blob
    0x00000008,  // ram_to_flash_bytes_to_be_written
};
