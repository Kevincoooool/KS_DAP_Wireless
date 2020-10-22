/* Flash OS Routines (Automagically Generated)
 * Copyright (c) 2009-2015 ARM Limited
 */
#include "flash_blob.h"

static const uint32_t flash_code[] = {
    0xE00ABE00, 0x062D780D, 0x24084068, 0xD3000040, 0x1E644058, 0x1C49D1FA, 0x2A001E52, 0x4770D1F2,
    0x8F4FF3BF, 0x03004770, 0x28400E00, 0x0980D302, 0x47701D00, 0x477008C0, 0x49274828, 0x49286041,
    0x21006041, 0x68C16001, 0x431122F0, 0x694060C1, 0xD4060680, 0x49234824, 0x21066001, 0x49236041,
    0x20006081, 0x481D4770, 0x05426901, 0x61014311, 0x47702000, 0x47702000, 0x4D18B5F0, 0x08891CC9,
    0x008968EB, 0x433B27F0, 0x230060EB, 0x4C18612B, 0x692BE01D, 0x43334E17, 0x6813612B, 0xF3BF6003,
    0x4B118F4F, 0x601CE000, 0x03F668EE, 0x692BD4FB, 0x005B085B, 0x68EB612B, 0x0F1B061B, 0x68E8D004,
    0x60E84338, 0xBDF02001, 0x1F091D00, 0x29001D12, 0x2000D1DF, 0x0000BDF0, 0x45670123, 0x40023C00,
    0xCDEF89AB, 0x00005555, 0x40003000, 0x00000FFF, 0x0000AAAA, 0x00000201, 0x00000000
};

const program_target_t flash_algo = {
    0x20000039,  // Init
    0x20000067,  // UnInit
    0x12000001F,  // EraseChip
    0x20000075,  // EraseSector
    0x20000079,  // ProgramPage

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
    0x00000410,  // ram_to_flash_bytes_to_be_written
};
