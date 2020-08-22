"""
 Flash OS Routines (Automagically Generated)
 Copyright (c) 2017-2017 ARM Limited
"""

flash_algo = {
    'load_address' : 0x20000000,
    'instructions' : [
        0xE00ABE00, 0x062D780D, 0x24084068, 0xD3000040, 0x1E644058, 0x1C49D1FA, 0x2A001E52, 0x4770D1F2,
        0x4603B510, 0x4C442000, 0x48446020, 0x48446060, 0x46206060, 0xF01069C0, 0xD1080F04, 0x5055F245,
        0x60204C40, 0x60602006, 0x70FFF640, 0x200060A0, 0x4601BD10, 0x69004838, 0x0080F040, 0x61104A36,
        0x47702000, 0x69004834, 0x0004F040, 0x61084932, 0x69004608, 0x0040F040, 0xE0036108, 0x20AAF64A,
        0x60084930, 0x68C0482C, 0x0F01F010, 0x482AD1F6, 0xF0206900, 0x49280004, 0x20006108, 0x46014770,
        0x69004825, 0x0002F040, 0x61104A23, 0x61414610, 0xF0406900, 0x61100040, 0xF64AE003, 0x4A2120AA,
        0x481D6010, 0xF01068C0, 0xD1F60F01, 0x6900481A, 0x0002F020, 0x61104A18, 0x47702000, 0x4603B510,
        0xF0201C48, 0xE0220101, 0x69004813, 0x0001F040, 0x61204C11, 0x80188810, 0x480FBF00, 0xF01068C0,
        0xD1FA0F01, 0x6900480C, 0x0001F020, 0x61204C0A, 0x68C04620, 0x0F14F010, 0x4620D006, 0xF04068C0,
        0x60E00014, 0xBD102001, 0x1C921C9B, 0x29001E89, 0x2000D1DA, 0x0000E7F7, 0x40022000, 0x45670123,
        0xCDEF89AB, 0x40003000, 0x00000000
    ],

    'pc_Init'            : 0x20000021,
    'pc_UnInit'          : 0x20000053,
    'pc_EraseSector'     : 0x2000009F,
    'pc_ProgramPage'     : 0x200000DD,
    'pc_Verify'          : 0x12000001F,
    'pc_EraseChip'       : 0x20000065,
    'pc_BlankCheck'      : 0x12000001F,
    'pc_Read'            : 0x12000001F,
    
    'static_base'        : 0x20000400,
    'begin_data'         : 0x20000800,
    'begin_stack'        : 0x20001000,

    'analyzer_supported' : False,

    # Relative region addresses and sizes
    'ro_start'           : 0x00000000,
    'ro_size'            : 0x00000128,
    'rw_start'           : 0x00000128,
    'rw_size'            : 0x00000004,
    'zi_start'           : 0x0000012C,
    'zi_size'            : 0x00000000,

    # Flash information
    'flash_start'        : 0x08000000,
    'flash_size'         : 0x00080000,
    'flash_page_size'    : 0x00000400,
    'sector_sizes': (
        (0x00000, 0x00800),
    )
}
