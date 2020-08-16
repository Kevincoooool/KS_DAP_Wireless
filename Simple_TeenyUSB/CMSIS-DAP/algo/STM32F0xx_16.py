"""
 Flash OS Routines (Automagically Generated)
 Copyright (c) 2017-2017 ARM Limited
"""

flash_algo = {
    'load_address' : 0x20000000,
    'instructions' : [
        0xE00ABE00, 0x062D780D, 0x24084068, 0xD3000040, 0x1E644058, 0x1C49D1FA, 0x2A001E52, 0x4770D1F2,
        0x49454846, 0x49466041, 0x21006041, 0x68C16001, 0x43112214, 0x69C060C1, 0xD4060740, 0x49414842,
        0x21066001, 0x49416041, 0x20006081, 0x483B4770, 0x22806901, 0x61014311, 0x47702000, 0x4837B530,
        0x241468C1, 0x60C14321, 0x25046901, 0x61014329, 0x22406901, 0x61014311, 0x4A334935, 0x6011E000,
        0x07DB68C3, 0x6901D1FB, 0x610143A9, 0x422168C1, 0x68C1D004, 0x60C14321, 0xBD302001, 0xBD302000,
        0x4926B530, 0x231468CA, 0x60CA431A, 0x2402690A, 0x610A4322, 0x69086148, 0x43102240, 0x48246108,
        0xE0004A21, 0x68CD6010, 0xD1FB07ED, 0x43A06908, 0x68C86108, 0xD0034018, 0x431868C8, 0x200160C8,
        0xB5F0BD30, 0x1C494D15, 0x68EB0849, 0x24040049, 0x60EB4323, 0x4C162714, 0x692BE01A, 0x43332601,
        0x8813612B, 0x4B108003, 0x601CE000, 0x07F668EE, 0x692BD1FB, 0x005B085B, 0x68EB612B, 0xD004423B,
        0x433868E8, 0x200160E8, 0x1C80BDF0, 0x1E891C92, 0xD1E22900, 0xBDF02000, 0x45670123, 0x40022000,
        0xCDEF89AB, 0x00005555, 0x40003000, 0x00000FFF, 0x0000AAAA, 0x00000000
    ],

    'pc_Init'            : 0x20000021,
    'pc_UnInit'          : 0x2000004F,
    'pc_EraseSector'     : 0x200000A1,
    'pc_ProgramPage'     : 0x200000E3,
    'pc_Verify'          : 0x12000001F,
    'pc_EraseChip'       : 0x2000005D,
    'pc_BlankCheck'      : 0x12000001F,
    'pc_Read'            : 0x12000001F,
    
    'static_base'        : 0x20000400,
    'begin_data'         : 0x20000800,
    'begin_stack'        : 0x20001000,

    'analyzer_supported' : False,

    # Relative region addresses and sizes
    'ro_start'           : 0x00000000,
    'ro_size'            : 0x00000134,
    'rw_start'           : 0x00000134,
    'rw_size'            : 0x00000004,
    'zi_start'           : 0x00000138,
    'zi_size'            : 0x00000000,

    # Flash information
    'flash_start'        : 0x08000000,
    'flash_size'         : 0x00004000,
    'flash_page_size'    : 0x00000400,
    'sector_sizes': (
        (0x00000, 0x00400),
    )
}
