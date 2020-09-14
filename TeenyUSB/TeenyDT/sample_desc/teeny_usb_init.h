/*
 * Name   :  teeny_usb_init.h
 * Author :  admin@xtoolbox.org
 * Date   :  2020-09-14 09:44:36

 * Desc   :  This file is auto generate by the TeenyDT
 *           Visit http://dt.tusb.org for more info
 */

/*
  Input source name:  descriptor.lua
  
  Content type is lua script:
  ------------- lua script begin ------------
local s = arg[1]:find("[^/\\]+$")
local sep = arg[1]:sub(s,s)
local p = arg[1]:sub(1, s-1) .. "?.lua"
package.path = package.path .. ";".. p

local desc_list = {
    { File = "composite_desc",     Description = "Composite"        },
    { File = "cdc_acm_desc",       Description = "CDC ACM"          },
    { File = "cdc_acm5_desc",      Description = "CDC ACM5"         },
    { File = "cdc_rndis_desc",     Description = "CDC RNDIS"        },
    { File = "winusb_desc",        Description = "WinUSB"           },
    { File = "winusb20_desc",      Description = "WinUSB20"         },
    { File = "hid_user_desc",      Description = "User HID"         },
    { File = "hid_kb_desc",        Description = "HID Keyboard"     },
    { File = "hid_mouse_desc",     Description = "HID Mouse"        },
    { File = "msc_desc",           Description = "Mass storage"     },
    { File = "daplinkv1_desc",     Description = "DAPLink V1"       },
    { File = "daplinkv2_desc",     Description = "DAPLink V2"       },
    { File = "multi_config_desc",  Description = "Multi Config"     },
    { File = "simplest_desc",      Description = "Simplest"         },
}

local descriptors = {}
for i,v in ipairs(desc_list) do
    descriptors[#descriptors+1] = require(v.File)
end

return descriptors


  ------------- lua script end   ------------
 */
/////////////////////////////////////////
//// Device 0
/////////////////////////////////////////
#ifndef __COMP_TEENY_USB_INIT_H__
#define __COMP_TEENY_USB_INIT_H__
// forward declare the tusb_descriptors struct
typedef struct _tusb_descriptors tusb_descriptors;

#define COMP_VID                                            0x0483
#define COMP_PID                                            0x0011
#define COMP_STRING_COUNT                                   (5)

// device.bmAttributes & 0x40   USB_CONFIG_SELF_POWERED
// device.bmAttributes & 0x20   USB_CONFIG_REMOTE_WAKEUP
#define COMP_DEV_STATUS                                    (0 | 0)


// Endpoint usage:
#define COMP_MAX_EP                                         (4)
#define COMP_EP_NUM                                         (COMP_MAX_EP + 1)

///////////////////////////////////////////////
//// Endpoint define for STM32 FS Core
///////////////////////////////////////////////

#ifdef COMP_BTABLE_ADDRESS
#undef COMP_BTABLE_ADDRESS
#endif
#define COMP_BTABLE_ADDRESS                                 (0)
#define COMP_EP_BUF_DESC_TABLE_SIZE                         (8)
// PMA buffer reserved for buffer description table
#define COMP_USB_BUF_START                                  (COMP_EP_BUF_DESC_TABLE_SIZE * COMP_EP_NUM)

// EndPoints 0 defines
#define COMP_EP0_RX_SIZE                                    (64)
#define COMP_EP0_RX_ADDR                                    (COMP_USB_BUF_START + (0))
#define COMP_EP0_TX_SIZE                                    (64)
#define COMP_EP0_TX_ADDR                                    (COMP_USB_BUF_START + (64))
#define COMP_EP0_RX_TYPE                                    USB_EP_CONTROL
#define COMP_EP0_TX_TYPE                                    USB_EP_CONTROL

#define COMP_EP0_TYPE                                       USB_EP_CONTROL
#define COMP_EP0_TX0_ADDR                                   (COMP_USB_BUF_START + (0))
#define COMP_EP0_TX1_ADDR                                   (COMP_USB_BUF_START + (64))
#define COMP_EP0_RX0_ADDR                                   (COMP_USB_BUF_START + (0))
#define COMP_EP0_RX1_ADDR                                   (COMP_USB_BUF_START + (64))

// EndPoints 1 defines
#define COMP_EP1_RX_SIZE                                    (32)
#define COMP_EP1_RX_ADDR                                    (COMP_USB_BUF_START + (128))
#define COMP_EP1_TX_SIZE                                    (32)
#define COMP_EP1_TX_ADDR                                    (COMP_USB_BUF_START + (160))
#define COMP_EP1_RX_TYPE                                    USB_EP_BULK
#define COMP_EP1_TX_TYPE                                    USB_EP_BULK

#define COMP_EP1_TYPE                                       USB_EP_BULK
#define COMP_EP1_TX0_ADDR                                   (COMP_USB_BUF_START + (128))
#define COMP_EP1_TX1_ADDR                                   (COMP_USB_BUF_START + (160))
#define COMP_EP1_RX0_ADDR                                   (COMP_USB_BUF_START + (128))
#define COMP_EP1_RX1_ADDR                                   (COMP_USB_BUF_START + (160))

// EndPoints 2 defines
#define COMP_EP2_RX_SIZE                                    (16)
#define COMP_EP2_RX_ADDR                                    (COMP_USB_BUF_START + (192))
#define COMP_EP2_TX_SIZE                                    (16)
#define COMP_EP2_TX_ADDR                                    (COMP_USB_BUF_START + (208))
#define COMP_EP2_RX_TYPE                                    USB_EP_INTERRUPT
#define COMP_EP2_TX_TYPE                                    USB_EP_INTERRUPT

#define COMP_EP2_TYPE                                       USB_EP_INTERRUPT
#define COMP_EP2_TX0_ADDR                                   (COMP_USB_BUF_START + (192))
#define COMP_EP2_TX1_ADDR                                   (COMP_USB_BUF_START + (208))
#define COMP_EP2_RX0_ADDR                                   (COMP_USB_BUF_START + (192))
#define COMP_EP2_RX1_ADDR                                   (COMP_USB_BUF_START + (208))

// EndPoints 3 defines
#define COMP_EP3_RX_SIZE                                    (32)
#define COMP_EP3_RX_ADDR                                    (COMP_USB_BUF_START + (224))
#define COMP_EP3_TX_SIZE                                    (32)
#define COMP_EP3_TX_ADDR                                    (COMP_USB_BUF_START + (256))
#define COMP_EP3_RX_TYPE                                    USB_EP_BULK
#define COMP_EP3_TX_TYPE                                    USB_EP_BULK

#define COMP_EP3_TYPE                                       USB_EP_BULK
#define COMP_EP3_TX0_ADDR                                   (COMP_USB_BUF_START + (224))
#define COMP_EP3_TX1_ADDR                                   (COMP_USB_BUF_START + (256))
#define COMP_EP3_RX0_ADDR                                   (COMP_USB_BUF_START + (224))
#define COMP_EP3_RX1_ADDR                                   (COMP_USB_BUF_START + (256))

// EndPoints 4 defines
#define COMP_EP4_RX_SIZE                                    (64)
#define COMP_EP4_RX_ADDR                                    (COMP_USB_BUF_START + (288))
#define COMP_EP4_TX_SIZE                                    (64)
#define COMP_EP4_TX_ADDR                                    (COMP_USB_BUF_START + (352))
#define COMP_EP4_RX_TYPE                                    USB_EP_BULK
#define COMP_EP4_TX_TYPE                                    USB_EP_BULK

#define COMP_EP4_TYPE                                       USB_EP_BULK
#define COMP_EP4_TX0_ADDR                                   (COMP_USB_BUF_START + (288))
#define COMP_EP4_TX1_ADDR                                   (COMP_USB_BUF_START + (352))
#define COMP_EP4_RX0_ADDR                                   (COMP_USB_BUF_START + (288))
#define COMP_EP4_RX1_ADDR                                   (COMP_USB_BUF_START + (352))


// EndPoint max packed sizes
extern const uint8_t COMP_txEpMaxSize[];
#define COMP_TXEP_MAX_SIZE                                  \
const uint8_t COMP_txEpMaxSize[] = \
{ COMP_EP0_TX_SIZE, COMP_EP1_TX_SIZE, COMP_EP2_TX_SIZE, COMP_EP3_TX_SIZE, COMP_EP4_TX_SIZE,  };
extern const uint8_t COMP_rxEpMaxSize[];
#define COMP_RXEP_MAX_SIZE                                  \
const uint8_t COMP_rxEpMaxSize[] = \
{ COMP_EP0_RX_SIZE, COMP_EP1_RX_SIZE, COMP_EP2_RX_SIZE, COMP_EP3_RX_SIZE, COMP_EP4_RX_SIZE,  };

// EndPoints init function for USB FS core
#define COMP_TUSB_INIT_EP_FS(dev) \
  do{\
    /* Init ep0 */ \
    INIT_EP_BiDirection(dev, PCD_ENDP0, COMP_EP0_TYPE);  \
    SET_TX_ADDR(dev, PCD_ENDP0, COMP_EP0_TX_ADDR);  \
    SET_RX_ADDR(dev, PCD_ENDP0, COMP_EP0_RX_ADDR);  \
    SET_RX_CNT(dev, PCD_ENDP0, COMP_EP0_RX_SIZE);  \
    /* Init ep1 */ \
    INIT_EP_BiDirection(dev, PCD_ENDP1, COMP_EP1_TYPE);  \
    SET_TX_ADDR(dev, PCD_ENDP1, COMP_EP1_TX_ADDR);  \
    SET_RX_ADDR(dev, PCD_ENDP1, COMP_EP1_RX_ADDR);  \
    SET_RX_CNT(dev, PCD_ENDP1, COMP_EP1_RX_SIZE);  \
    /* Init ep2 */ \
    INIT_EP_BiDirection(dev, PCD_ENDP2, COMP_EP2_TYPE);  \
    SET_TX_ADDR(dev, PCD_ENDP2, COMP_EP2_TX_ADDR);  \
    SET_RX_ADDR(dev, PCD_ENDP2, COMP_EP2_RX_ADDR);  \
    SET_RX_CNT(dev, PCD_ENDP2, COMP_EP2_RX_SIZE);  \
    /* Init ep3 */ \
    INIT_EP_BiDirection(dev, PCD_ENDP3, COMP_EP3_TYPE);  \
    SET_TX_ADDR(dev, PCD_ENDP3, COMP_EP3_TX_ADDR);  \
    SET_RX_ADDR(dev, PCD_ENDP3, COMP_EP3_RX_ADDR);  \
    SET_RX_CNT(dev, PCD_ENDP3, COMP_EP3_RX_SIZE);  \
    /* Init ep4 */ \
    INIT_EP_BiDirection(dev, PCD_ENDP4, COMP_EP4_TYPE);  \
    SET_TX_ADDR(dev, PCD_ENDP4, COMP_EP4_TX_ADDR);  \
    SET_RX_ADDR(dev, PCD_ENDP4, COMP_EP4_RX_ADDR);  \
    SET_RX_CNT(dev, PCD_ENDP4, COMP_EP4_RX_SIZE);  \
}while(0)

///////////////////////////////////////////////
//// Endpoint define for STM32 OTG Core
///////////////////////////////////////////////
#define COMP_OTG_MAX_OUT_SIZE                               (64)
#define COMP_OTG_CONTROL_EP_NUM                             (1)
#define COMP_OTG_OUT_EP_NUM                                 (4)
// RX FIFO size / 4 > (CONTROL_EP_NUM * 5 + 8) +  (MAX_OUT_SIZE / 4 + 1) + (OUT_EP_NUM*2) + 1 = 39

///////////////////////////////////////////////
//// Endpoint define for STM32 OTG FS Core
///////////////////////////////////////////////
#define COMP_OTG_RX_FIFO_SIZE_FS                            (256)
#define COMP_OTG_RX_FIFO_ADDR_FS                            (0)
// Sum of IN ep max packet size is 208
// Remain Fifo size is 1024 in bytes, Rx Used 256 bytes 

// TODO:
// I don't know why the max count of TX fifo should <= (7 * EpMaxPacket)
// But it seems the STM32F7xx can be large than (7 * EpMaxPacket)
#define COMP_EP0_TX_FIFO_ADDR_FS                            (256)
#define COMP_EP0_TX_FIFO_SIZE_FS                            (COMP_EP0_TX_SIZE * 4)
#define COMP_EP1_TX_FIFO_ADDR_FS                            (512)
#define COMP_EP1_TX_FIFO_SIZE_FS                            (COMP_EP1_TX_SIZE * 4)
#define COMP_EP2_TX_FIFO_ADDR_FS                            (640)
#define COMP_EP2_TX_FIFO_SIZE_FS                            (COMP_EP2_TX_SIZE * 4)
#define COMP_EP3_TX_FIFO_ADDR_FS                            (704)
#define COMP_EP3_TX_FIFO_SIZE_FS                            (COMP_EP3_TX_SIZE * 4)
#define COMP_EP4_TX_FIFO_ADDR_FS                            (832)
#define COMP_EP4_TX_FIFO_SIZE_FS                            (COMP_EP4_TX_SIZE * 4)
// EndPoints init function for USB OTG core
#if defined(USB_OTG_FS)
#define COMP_TUSB_INIT_EP_OTG_FS(dev) \
  do{\
    if(GetUSB(dev) == USB_OTG_FS) { \
      SET_RX_FIFO(dev, COMP_OTG_RX_FIFO_ADDR_FS, COMP_OTG_RX_FIFO_SIZE_FS);  \
      /* Init Ep0  */\
      INIT_EP_Tx(dev, PCD_ENDP0, COMP_EP0_TX_TYPE, COMP_EP0_TX_SIZE);  \
      SET_TX_FIFO(dev, PCD_ENDP0, COMP_EP0_TX_FIFO_ADDR_FS, COMP_EP0_TX_FIFO_SIZE_FS);  \
      INIT_EP_Rx(dev, PCD_ENDP0, COMP_EP0_RX_TYPE, COMP_EP0_RX_SIZE); \
      /* Init Ep1  */\
      INIT_EP_Tx(dev, PCD_ENDP1, COMP_EP1_TX_TYPE, COMP_EP1_TX_SIZE);  \
      SET_TX_FIFO(dev, PCD_ENDP1, COMP_EP1_TX_FIFO_ADDR_FS, COMP_EP1_TX_FIFO_SIZE_FS);  \
      INIT_EP_Rx(dev, PCD_ENDP1, COMP_EP1_RX_TYPE, COMP_EP1_RX_SIZE); \
      /* Init Ep2  */\
      INIT_EP_Tx(dev, PCD_ENDP2, COMP_EP2_TX_TYPE, COMP_EP2_TX_SIZE);  \
      SET_TX_FIFO(dev, PCD_ENDP2, COMP_EP2_TX_FIFO_ADDR_FS, COMP_EP2_TX_FIFO_SIZE_FS);  \
      INIT_EP_Rx(dev, PCD_ENDP2, COMP_EP2_RX_TYPE, COMP_EP2_RX_SIZE); \
      /* Init Ep3  */\
      INIT_EP_Tx(dev, PCD_ENDP3, COMP_EP3_TX_TYPE, COMP_EP3_TX_SIZE);  \
      SET_TX_FIFO(dev, PCD_ENDP3, COMP_EP3_TX_FIFO_ADDR_FS, COMP_EP3_TX_FIFO_SIZE_FS);  \
      INIT_EP_Rx(dev, PCD_ENDP3, COMP_EP3_RX_TYPE, COMP_EP3_RX_SIZE); \
      /* Init Ep4  */\
      INIT_EP_Tx(dev, PCD_ENDP4, COMP_EP4_TX_TYPE, COMP_EP4_TX_SIZE);  \
      SET_TX_FIFO(dev, PCD_ENDP4, COMP_EP4_TX_FIFO_ADDR_FS, COMP_EP4_TX_FIFO_SIZE_FS);  \
      INIT_EP_Rx(dev, PCD_ENDP4, COMP_EP4_RX_TYPE, COMP_EP4_RX_SIZE); \
    }\
  }while(0)

#else  // #if defined(USB_OTG_FS)
#define COMP_TUSB_INIT_EP_OTG_FS(dev) 
    
#endif  // #if defined(USB_OTG_FS)

///////////////////////////////////////////////
//// Endpoint define for STM32 OTG HS Core
///////////////////////////////////////////////
#define COMP_OTG_RX_FIFO_SIZE_HS                            (512)
#define COMP_OTG_RX_FIFO_ADDR_HS                            (0)
// Sum of IN ep max packet size is 208
// Remain Fifo size is 3584 in bytes, Rx Used 512 bytes 

// TODO:
// I don't know why the max count of TX fifo should <= (7 * EpMaxPacket)
// But it seems the STM32F7xx can be large than (7 * EpMaxPacket)
#define COMP_EP0_TX_FIFO_ADDR_HS                            (512)
#define COMP_EP0_TX_FIFO_SIZE_HS                            (COMP_EP0_TX_SIZE * 7)
#define COMP_EP1_TX_FIFO_ADDR_HS                            (960)
#define COMP_EP1_TX_FIFO_SIZE_HS                            (COMP_EP1_TX_SIZE * 7)
#define COMP_EP2_TX_FIFO_ADDR_HS                            (1184)
#define COMP_EP2_TX_FIFO_SIZE_HS                            (COMP_EP2_TX_SIZE * 7)
#define COMP_EP3_TX_FIFO_ADDR_HS                            (1296)
#define COMP_EP3_TX_FIFO_SIZE_HS                            (COMP_EP3_TX_SIZE * 7)
#define COMP_EP4_TX_FIFO_ADDR_HS                            (1520)
#define COMP_EP4_TX_FIFO_SIZE_HS                            (COMP_EP4_TX_SIZE * 7)
// EndPoints init function for USB OTG core
#if defined(USB_OTG_HS)
#define COMP_TUSB_INIT_EP_OTG_HS(dev) \
  do{\
    if(GetUSB(dev) == USB_OTG_HS) { \
      SET_RX_FIFO(dev, COMP_OTG_RX_FIFO_ADDR_HS, COMP_OTG_RX_FIFO_SIZE_HS);  \
      /* Init Ep0  */\
      INIT_EP_Tx(dev, PCD_ENDP0, COMP_EP0_TX_TYPE, COMP_EP0_TX_SIZE);  \
      SET_TX_FIFO(dev, PCD_ENDP0, COMP_EP0_TX_FIFO_ADDR_HS, COMP_EP0_TX_FIFO_SIZE_HS);  \
      INIT_EP_Rx(dev, PCD_ENDP0, COMP_EP0_RX_TYPE, COMP_EP0_RX_SIZE); \
      /* Init Ep1  */\
      INIT_EP_Tx(dev, PCD_ENDP1, COMP_EP1_TX_TYPE, COMP_EP1_TX_SIZE);  \
      SET_TX_FIFO(dev, PCD_ENDP1, COMP_EP1_TX_FIFO_ADDR_HS, COMP_EP1_TX_FIFO_SIZE_HS);  \
      INIT_EP_Rx(dev, PCD_ENDP1, COMP_EP1_RX_TYPE, COMP_EP1_RX_SIZE); \
      /* Init Ep2  */\
      INIT_EP_Tx(dev, PCD_ENDP2, COMP_EP2_TX_TYPE, COMP_EP2_TX_SIZE);  \
      SET_TX_FIFO(dev, PCD_ENDP2, COMP_EP2_TX_FIFO_ADDR_HS, COMP_EP2_TX_FIFO_SIZE_HS);  \
      INIT_EP_Rx(dev, PCD_ENDP2, COMP_EP2_RX_TYPE, COMP_EP2_RX_SIZE); \
      /* Init Ep3  */\
      INIT_EP_Tx(dev, PCD_ENDP3, COMP_EP3_TX_TYPE, COMP_EP3_TX_SIZE);  \
      SET_TX_FIFO(dev, PCD_ENDP3, COMP_EP3_TX_FIFO_ADDR_HS, COMP_EP3_TX_FIFO_SIZE_HS);  \
      INIT_EP_Rx(dev, PCD_ENDP3, COMP_EP3_RX_TYPE, COMP_EP3_RX_SIZE); \
      /* Init Ep4  */\
      INIT_EP_Tx(dev, PCD_ENDP4, COMP_EP4_TX_TYPE, COMP_EP4_TX_SIZE);  \
      SET_TX_FIFO(dev, PCD_ENDP4, COMP_EP4_TX_FIFO_ADDR_HS, COMP_EP4_TX_FIFO_SIZE_HS);  \
      INIT_EP_Rx(dev, PCD_ENDP4, COMP_EP4_RX_TYPE, COMP_EP4_RX_SIZE); \
    }\
  }while(0)

#else  // #if defined(USB_OTG_HS)
#define COMP_TUSB_INIT_EP_OTG_HS(dev) 
    
#endif  // #if defined(USB_OTG_HS)
#define COMP_TUSB_INIT_EP_OTG(dev) \
  do{\
    COMP_TUSB_INIT_EP_OTG_FS(dev); \
    COMP_TUSB_INIT_EP_OTG_HS(dev); \
  }while(0)


#if defined(USB)
#define COMP_TUSB_INIT_EP(dev) COMP_TUSB_INIT_EP_FS(dev)

// Teeny USB device init function for FS core
#define COMP_TUSB_INIT_DEVICE(dev) \
  do{\
    /* Init device features */       \
    memset(&dev->addr, 0, TUSB_DEVICE_SIZE);    \
    dev->status = COMP_DEV_STATUS;         \
    dev->rx_max_size = COMP_rxEpMaxSize;         \
    dev->tx_max_size = COMP_txEpMaxSize;         \
    dev->descriptors = &COMP_descriptors;         \
  }while(0)

#endif

#if defined(USB_OTG_FS) || defined(USB_OTG_HS)
#define COMP_TUSB_INIT_EP(dev) COMP_TUSB_INIT_EP_OTG(dev)

// Teeny USB device init function for OTG core
#define COMP_TUSB_INIT_DEVICE(dev) \
  do{\
    /* Init device features */       \
    memset(&dev->addr, 0, TUSB_DEVICE_SIZE);    \
    dev->status = COMP_DEV_STATUS;         \
    dev->descriptors = &COMP_descriptors;         \
  }while(0)

#endif

#define COMP_TUSB_INIT(dev) \
  do{\
    COMP_TUSB_INIT_EP(dev);   \
    COMP_TUSB_INIT_DEVICE(dev);   \
  }while(0)

// Get End Point count
#ifndef  EP_NUM
#define  EP_NUM 1
#endif
#if COMP_EP_NUM > EP_NUM
#undef   EP_NUM
#define  EP_NUM  COMP_EP_NUM
#endif

extern const uint8_t* const COMP_StringDescriptors[COMP_STRING_COUNT];
extern const tusb_descriptors COMP_descriptors;

#define COMP_REPORT_DESCRIPTOR_SIZE_IF0  (24)
extern const uint8_t COMP_ReportDescriptor_if0[COMP_REPORT_DESCRIPTOR_SIZE_IF0];

// Enable WCID related code
#define  HAS_WCID

#ifndef WCID_VENDOR_CODE
#define  WCID_VENDOR_CODE       0x17
extern const uint8_t WCID_StringDescriptor_MSOS[];
#endif


#endif   // #ifndef __COMP_TEENY_USB_INIT_H__
/////////////////////////////////////////
//// Device 1
/////////////////////////////////////////
#ifndef __CDC_ACM_TEENY_USB_INIT_H__
#define __CDC_ACM_TEENY_USB_INIT_H__
// forward declare the tusb_descriptors struct
typedef struct _tusb_descriptors tusb_descriptors;

#define CDC_ACM_VID                                            0x0483
#define CDC_ACM_PID                                            0x0011
#define CDC_ACM_STRING_COUNT                                   (4)

// device.bmAttributes & 0x40   USB_CONFIG_SELF_POWERED
// device.bmAttributes & 0x20   USB_CONFIG_REMOTE_WAKEUP
#define CDC_ACM_DEV_STATUS                                    (0 | 0)


// Endpoint usage:
#define CDC_ACM_MAX_EP                                         (1)
#define CDC_ACM_EP_NUM                                         (CDC_ACM_MAX_EP + 1)

///////////////////////////////////////////////
//// Endpoint define for STM32 FS Core
///////////////////////////////////////////////

#ifdef CDC_ACM_BTABLE_ADDRESS
#undef CDC_ACM_BTABLE_ADDRESS
#endif
#define CDC_ACM_BTABLE_ADDRESS                                 (0)
#define CDC_ACM_EP_BUF_DESC_TABLE_SIZE                         (8)
// PMA buffer reserved for buffer description table
#define CDC_ACM_USB_BUF_START                                  (CDC_ACM_EP_BUF_DESC_TABLE_SIZE * CDC_ACM_EP_NUM)

// EndPoints 0 defines
#define CDC_ACM_EP0_RX_SIZE                                    (64)
#define CDC_ACM_EP0_RX_ADDR                                    (CDC_ACM_USB_BUF_START + (0))
#define CDC_ACM_EP0_TX_SIZE                                    (64)
#define CDC_ACM_EP0_TX_ADDR                                    (CDC_ACM_USB_BUF_START + (64))
#define CDC_ACM_EP0_RX_TYPE                                    USB_EP_CONTROL
#define CDC_ACM_EP0_TX_TYPE                                    USB_EP_CONTROL

#define CDC_ACM_EP0_TYPE                                       USB_EP_CONTROL
#define CDC_ACM_EP0_TX0_ADDR                                   (CDC_ACM_USB_BUF_START + (0))
#define CDC_ACM_EP0_TX1_ADDR                                   (CDC_ACM_USB_BUF_START + (64))
#define CDC_ACM_EP0_RX0_ADDR                                   (CDC_ACM_USB_BUF_START + (0))
#define CDC_ACM_EP0_RX1_ADDR                                   (CDC_ACM_USB_BUF_START + (64))

// EndPoints 1 defines
#define CDC_ACM_EP1_RX_SIZE                                    (32)
#define CDC_ACM_EP1_RX_ADDR                                    (CDC_ACM_USB_BUF_START + (128))
#define CDC_ACM_EP1_TX_SIZE                                    (32)
#define CDC_ACM_EP1_TX_ADDR                                    (CDC_ACM_USB_BUF_START + (160))
#define CDC_ACM_EP1_RX_TYPE                                    USB_EP_BULK
#define CDC_ACM_EP1_TX_TYPE                                    USB_EP_BULK

#define CDC_ACM_EP1_TYPE                                       USB_EP_BULK
#define CDC_ACM_EP1_TX0_ADDR                                   (CDC_ACM_USB_BUF_START + (128))
#define CDC_ACM_EP1_TX1_ADDR                                   (CDC_ACM_USB_BUF_START + (160))
#define CDC_ACM_EP1_RX0_ADDR                                   (CDC_ACM_USB_BUF_START + (128))
#define CDC_ACM_EP1_RX1_ADDR                                   (CDC_ACM_USB_BUF_START + (160))


// EndPoint max packed sizes
extern const uint8_t CDC_ACM_txEpMaxSize[];
#define CDC_ACM_TXEP_MAX_SIZE                                  \
const uint8_t CDC_ACM_txEpMaxSize[] = \
{ CDC_ACM_EP0_TX_SIZE, CDC_ACM_EP1_TX_SIZE,  };
extern const uint8_t CDC_ACM_rxEpMaxSize[];
#define CDC_ACM_RXEP_MAX_SIZE                                  \
const uint8_t CDC_ACM_rxEpMaxSize[] = \
{ CDC_ACM_EP0_RX_SIZE, CDC_ACM_EP1_RX_SIZE,  };

// EndPoints init function for USB FS core
#define CDC_ACM_TUSB_INIT_EP_FS(dev) \
  do{\
    /* Init ep0 */ \
    INIT_EP_BiDirection(dev, PCD_ENDP0, CDC_ACM_EP0_TYPE);  \
    SET_TX_ADDR(dev, PCD_ENDP0, CDC_ACM_EP0_TX_ADDR);  \
    SET_RX_ADDR(dev, PCD_ENDP0, CDC_ACM_EP0_RX_ADDR);  \
    SET_RX_CNT(dev, PCD_ENDP0, CDC_ACM_EP0_RX_SIZE);  \
    /* Init ep1 */ \
    INIT_EP_BiDirection(dev, PCD_ENDP1, CDC_ACM_EP1_TYPE);  \
    SET_TX_ADDR(dev, PCD_ENDP1, CDC_ACM_EP1_TX_ADDR);  \
    SET_RX_ADDR(dev, PCD_ENDP1, CDC_ACM_EP1_RX_ADDR);  \
    SET_RX_CNT(dev, PCD_ENDP1, CDC_ACM_EP1_RX_SIZE);  \
}while(0)

///////////////////////////////////////////////
//// Endpoint define for STM32 OTG Core
///////////////////////////////////////////////
#define CDC_ACM_OTG_MAX_OUT_SIZE                               (32)
#define CDC_ACM_OTG_CONTROL_EP_NUM                             (1)
#define CDC_ACM_OTG_OUT_EP_NUM                                 (1)
// RX FIFO size / 4 > (CONTROL_EP_NUM * 5 + 8) +  (MAX_OUT_SIZE / 4 + 1) + (OUT_EP_NUM*2) + 1 = 25

///////////////////////////////////////////////
//// Endpoint define for STM32 OTG FS Core
///////////////////////////////////////////////
#define CDC_ACM_OTG_RX_FIFO_SIZE_FS                            (256)
#define CDC_ACM_OTG_RX_FIFO_ADDR_FS                            (0)
// Sum of IN ep max packet size is 96
// Remain Fifo size is 1024 in bytes, Rx Used 256 bytes 

// TODO:
// I don't know why the max count of TX fifo should <= (7 * EpMaxPacket)
// But it seems the STM32F7xx can be large than (7 * EpMaxPacket)
#define CDC_ACM_EP0_TX_FIFO_ADDR_FS                            (256)
#define CDC_ACM_EP0_TX_FIFO_SIZE_FS                            (CDC_ACM_EP0_TX_SIZE * 7)
#define CDC_ACM_EP1_TX_FIFO_ADDR_FS                            (704)
#define CDC_ACM_EP1_TX_FIFO_SIZE_FS                            (CDC_ACM_EP1_TX_SIZE * 7)
// EndPoints init function for USB OTG core
#if defined(USB_OTG_FS)
#define CDC_ACM_TUSB_INIT_EP_OTG_FS(dev) \
  do{\
    if(GetUSB(dev) == USB_OTG_FS) { \
      SET_RX_FIFO(dev, CDC_ACM_OTG_RX_FIFO_ADDR_FS, CDC_ACM_OTG_RX_FIFO_SIZE_FS);  \
      /* Init Ep0  */\
      INIT_EP_Tx(dev, PCD_ENDP0, CDC_ACM_EP0_TX_TYPE, CDC_ACM_EP0_TX_SIZE);  \
      SET_TX_FIFO(dev, PCD_ENDP0, CDC_ACM_EP0_TX_FIFO_ADDR_FS, CDC_ACM_EP0_TX_FIFO_SIZE_FS);  \
      INIT_EP_Rx(dev, PCD_ENDP0, CDC_ACM_EP0_RX_TYPE, CDC_ACM_EP0_RX_SIZE); \
      /* Init Ep1  */\
      INIT_EP_Tx(dev, PCD_ENDP1, CDC_ACM_EP1_TX_TYPE, CDC_ACM_EP1_TX_SIZE);  \
      SET_TX_FIFO(dev, PCD_ENDP1, CDC_ACM_EP1_TX_FIFO_ADDR_FS, CDC_ACM_EP1_TX_FIFO_SIZE_FS);  \
      INIT_EP_Rx(dev, PCD_ENDP1, CDC_ACM_EP1_RX_TYPE, CDC_ACM_EP1_RX_SIZE); \
    }\
  }while(0)

#else  // #if defined(USB_OTG_FS)
#define CDC_ACM_TUSB_INIT_EP_OTG_FS(dev) 
    
#endif  // #if defined(USB_OTG_FS)

///////////////////////////////////////////////
//// Endpoint define for STM32 OTG HS Core
///////////////////////////////////////////////
#define CDC_ACM_OTG_RX_FIFO_SIZE_HS                            (512)
#define CDC_ACM_OTG_RX_FIFO_ADDR_HS                            (0)
// Sum of IN ep max packet size is 96
// Remain Fifo size is 3584 in bytes, Rx Used 512 bytes 

// TODO:
// I don't know why the max count of TX fifo should <= (7 * EpMaxPacket)
// But it seems the STM32F7xx can be large than (7 * EpMaxPacket)
#define CDC_ACM_EP0_TX_FIFO_ADDR_HS                            (512)
#define CDC_ACM_EP0_TX_FIFO_SIZE_HS                            (CDC_ACM_EP0_TX_SIZE * 7)
#define CDC_ACM_EP1_TX_FIFO_ADDR_HS                            (960)
#define CDC_ACM_EP1_TX_FIFO_SIZE_HS                            (CDC_ACM_EP1_TX_SIZE * 7)
// EndPoints init function for USB OTG core
#if defined(USB_OTG_HS)
#define CDC_ACM_TUSB_INIT_EP_OTG_HS(dev) \
  do{\
    if(GetUSB(dev) == USB_OTG_HS) { \
      SET_RX_FIFO(dev, CDC_ACM_OTG_RX_FIFO_ADDR_HS, CDC_ACM_OTG_RX_FIFO_SIZE_HS);  \
      /* Init Ep0  */\
      INIT_EP_Tx(dev, PCD_ENDP0, CDC_ACM_EP0_TX_TYPE, CDC_ACM_EP0_TX_SIZE);  \
      SET_TX_FIFO(dev, PCD_ENDP0, CDC_ACM_EP0_TX_FIFO_ADDR_HS, CDC_ACM_EP0_TX_FIFO_SIZE_HS);  \
      INIT_EP_Rx(dev, PCD_ENDP0, CDC_ACM_EP0_RX_TYPE, CDC_ACM_EP0_RX_SIZE); \
      /* Init Ep1  */\
      INIT_EP_Tx(dev, PCD_ENDP1, CDC_ACM_EP1_TX_TYPE, CDC_ACM_EP1_TX_SIZE);  \
      SET_TX_FIFO(dev, PCD_ENDP1, CDC_ACM_EP1_TX_FIFO_ADDR_HS, CDC_ACM_EP1_TX_FIFO_SIZE_HS);  \
      INIT_EP_Rx(dev, PCD_ENDP1, CDC_ACM_EP1_RX_TYPE, CDC_ACM_EP1_RX_SIZE); \
    }\
  }while(0)

#else  // #if defined(USB_OTG_HS)
#define CDC_ACM_TUSB_INIT_EP_OTG_HS(dev) 
    
#endif  // #if defined(USB_OTG_HS)
#define CDC_ACM_TUSB_INIT_EP_OTG(dev) \
  do{\
    CDC_ACM_TUSB_INIT_EP_OTG_FS(dev); \
    CDC_ACM_TUSB_INIT_EP_OTG_HS(dev); \
  }while(0)


#if defined(USB)
#define CDC_ACM_TUSB_INIT_EP(dev) CDC_ACM_TUSB_INIT_EP_FS(dev)

// Teeny USB device init function for FS core
#define CDC_ACM_TUSB_INIT_DEVICE(dev) \
  do{\
    /* Init device features */       \
    memset(&dev->addr, 0, TUSB_DEVICE_SIZE);    \
    dev->status = CDC_ACM_DEV_STATUS;         \
    dev->rx_max_size = CDC_ACM_rxEpMaxSize;         \
    dev->tx_max_size = CDC_ACM_txEpMaxSize;         \
    dev->descriptors = &CDC_ACM_descriptors;         \
  }while(0)

#endif

#if defined(USB_OTG_FS) || defined(USB_OTG_HS)
#define CDC_ACM_TUSB_INIT_EP(dev) CDC_ACM_TUSB_INIT_EP_OTG(dev)

// Teeny USB device init function for OTG core
#define CDC_ACM_TUSB_INIT_DEVICE(dev) \
  do{\
    /* Init device features */       \
    memset(&dev->addr, 0, TUSB_DEVICE_SIZE);    \
    dev->status = CDC_ACM_DEV_STATUS;         \
    dev->descriptors = &CDC_ACM_descriptors;         \
  }while(0)

#endif

#define CDC_ACM_TUSB_INIT(dev) \
  do{\
    CDC_ACM_TUSB_INIT_EP(dev);   \
    CDC_ACM_TUSB_INIT_DEVICE(dev);   \
  }while(0)

// Get End Point count
#ifndef  EP_NUM
#define  EP_NUM 1
#endif
#if CDC_ACM_EP_NUM > EP_NUM
#undef   EP_NUM
#define  EP_NUM  CDC_ACM_EP_NUM
#endif

extern const uint8_t* const CDC_ACM_StringDescriptors[CDC_ACM_STRING_COUNT];
extern const tusb_descriptors CDC_ACM_descriptors;


#endif   // #ifndef __CDC_ACM_TEENY_USB_INIT_H__
/////////////////////////////////////////
//// Device 2
/////////////////////////////////////////
#ifndef __CDC_ACM5_TEENY_USB_INIT_H__
#define __CDC_ACM5_TEENY_USB_INIT_H__
// forward declare the tusb_descriptors struct
typedef struct _tusb_descriptors tusb_descriptors;

#define CDC_ACM5_VID                                            0x0483
#define CDC_ACM5_PID                                            0x0011
#define CDC_ACM5_STRING_COUNT                                   (4)

// device.bmAttributes & 0x40   USB_CONFIG_SELF_POWERED
// device.bmAttributes & 0x20   USB_CONFIG_REMOTE_WAKEUP
#define CDC_ACM5_DEV_STATUS                                    (0 | 0)


// Endpoint usage:
#define CDC_ACM5_MAX_EP                                         (5)
#define CDC_ACM5_EP_NUM                                         (CDC_ACM5_MAX_EP + 1)

///////////////////////////////////////////////
//// Endpoint define for STM32 FS Core
///////////////////////////////////////////////

#ifdef CDC_ACM5_BTABLE_ADDRESS
#undef CDC_ACM5_BTABLE_ADDRESS
#endif
#define CDC_ACM5_BTABLE_ADDRESS                                 (0)
#define CDC_ACM5_EP_BUF_DESC_TABLE_SIZE                         (8)
// PMA buffer reserved for buffer description table
#define CDC_ACM5_USB_BUF_START                                  (CDC_ACM5_EP_BUF_DESC_TABLE_SIZE * CDC_ACM5_EP_NUM)

// EndPoints 0 defines
#define CDC_ACM5_EP0_RX_SIZE                                    (64)
#define CDC_ACM5_EP0_RX_ADDR                                    (CDC_ACM5_USB_BUF_START + (0))
#define CDC_ACM5_EP0_TX_SIZE                                    (64)
#define CDC_ACM5_EP0_TX_ADDR                                    (CDC_ACM5_USB_BUF_START + (64))
#define CDC_ACM5_EP0_RX_TYPE                                    USB_EP_CONTROL
#define CDC_ACM5_EP0_TX_TYPE                                    USB_EP_CONTROL

#define CDC_ACM5_EP0_TYPE                                       USB_EP_CONTROL
#define CDC_ACM5_EP0_TX0_ADDR                                   (CDC_ACM5_USB_BUF_START + (0))
#define CDC_ACM5_EP0_TX1_ADDR                                   (CDC_ACM5_USB_BUF_START + (64))
#define CDC_ACM5_EP0_RX0_ADDR                                   (CDC_ACM5_USB_BUF_START + (0))
#define CDC_ACM5_EP0_RX1_ADDR                                   (CDC_ACM5_USB_BUF_START + (64))

// EndPoints 1 defines
#define CDC_ACM5_EP1_RX_SIZE                                    (32)
#define CDC_ACM5_EP1_RX_ADDR                                    (CDC_ACM5_USB_BUF_START + (128))
#define CDC_ACM5_EP1_TX_SIZE                                    (32)
#define CDC_ACM5_EP1_TX_ADDR                                    (CDC_ACM5_USB_BUF_START + (160))
#define CDC_ACM5_EP1_RX_TYPE                                    USB_EP_BULK
#define CDC_ACM5_EP1_TX_TYPE                                    USB_EP_BULK

#define CDC_ACM5_EP1_TYPE                                       USB_EP_BULK
#define CDC_ACM5_EP1_TX0_ADDR                                   (CDC_ACM5_USB_BUF_START + (128))
#define CDC_ACM5_EP1_TX1_ADDR                                   (CDC_ACM5_USB_BUF_START + (160))
#define CDC_ACM5_EP1_RX0_ADDR                                   (CDC_ACM5_USB_BUF_START + (128))
#define CDC_ACM5_EP1_RX1_ADDR                                   (CDC_ACM5_USB_BUF_START + (160))

// EndPoints 2 defines
#define CDC_ACM5_EP2_RX_SIZE                                    (32)
#define CDC_ACM5_EP2_RX_ADDR                                    (CDC_ACM5_USB_BUF_START + (192))
#define CDC_ACM5_EP2_TX_SIZE                                    (32)
#define CDC_ACM5_EP2_TX_ADDR                                    (CDC_ACM5_USB_BUF_START + (224))
#define CDC_ACM5_EP2_RX_TYPE                                    USB_EP_BULK
#define CDC_ACM5_EP2_TX_TYPE                                    USB_EP_BULK

#define CDC_ACM5_EP2_TYPE                                       USB_EP_BULK
#define CDC_ACM5_EP2_TX0_ADDR                                   (CDC_ACM5_USB_BUF_START + (192))
#define CDC_ACM5_EP2_TX1_ADDR                                   (CDC_ACM5_USB_BUF_START + (224))
#define CDC_ACM5_EP2_RX0_ADDR                                   (CDC_ACM5_USB_BUF_START + (192))
#define CDC_ACM5_EP2_RX1_ADDR                                   (CDC_ACM5_USB_BUF_START + (224))

// EndPoints 3 defines
#define CDC_ACM5_EP3_RX_SIZE                                    (32)
#define CDC_ACM5_EP3_RX_ADDR                                    (CDC_ACM5_USB_BUF_START + (256))
#define CDC_ACM5_EP3_TX_SIZE                                    (32)
#define CDC_ACM5_EP3_TX_ADDR                                    (CDC_ACM5_USB_BUF_START + (288))
#define CDC_ACM5_EP3_RX_TYPE                                    USB_EP_BULK
#define CDC_ACM5_EP3_TX_TYPE                                    USB_EP_BULK

#define CDC_ACM5_EP3_TYPE                                       USB_EP_BULK
#define CDC_ACM5_EP3_TX0_ADDR                                   (CDC_ACM5_USB_BUF_START + (256))
#define CDC_ACM5_EP3_TX1_ADDR                                   (CDC_ACM5_USB_BUF_START + (288))
#define CDC_ACM5_EP3_RX0_ADDR                                   (CDC_ACM5_USB_BUF_START + (256))
#define CDC_ACM5_EP3_RX1_ADDR                                   (CDC_ACM5_USB_BUF_START + (288))

// EndPoints 4 defines
#define CDC_ACM5_EP4_RX_SIZE                                    (32)
#define CDC_ACM5_EP4_RX_ADDR                                    (CDC_ACM5_USB_BUF_START + (320))
#define CDC_ACM5_EP4_TX_SIZE                                    (32)
#define CDC_ACM5_EP4_TX_ADDR                                    (CDC_ACM5_USB_BUF_START + (352))
#define CDC_ACM5_EP4_RX_TYPE                                    USB_EP_BULK
#define CDC_ACM5_EP4_TX_TYPE                                    USB_EP_BULK

#define CDC_ACM5_EP4_TYPE                                       USB_EP_BULK
#define CDC_ACM5_EP4_TX0_ADDR                                   (CDC_ACM5_USB_BUF_START + (320))
#define CDC_ACM5_EP4_TX1_ADDR                                   (CDC_ACM5_USB_BUF_START + (352))
#define CDC_ACM5_EP4_RX0_ADDR                                   (CDC_ACM5_USB_BUF_START + (320))
#define CDC_ACM5_EP4_RX1_ADDR                                   (CDC_ACM5_USB_BUF_START + (352))

// EndPoints 5 defines
#define CDC_ACM5_EP5_RX_SIZE                                    (32)
#define CDC_ACM5_EP5_RX_ADDR                                    (CDC_ACM5_USB_BUF_START + (384))
#define CDC_ACM5_EP5_TX_SIZE                                    (32)
#define CDC_ACM5_EP5_TX_ADDR                                    (CDC_ACM5_USB_BUF_START + (416))
#define CDC_ACM5_EP5_RX_TYPE                                    USB_EP_BULK
#define CDC_ACM5_EP5_TX_TYPE                                    USB_EP_BULK

#define CDC_ACM5_EP5_TYPE                                       USB_EP_BULK
#define CDC_ACM5_EP5_TX0_ADDR                                   (CDC_ACM5_USB_BUF_START + (384))
#define CDC_ACM5_EP5_TX1_ADDR                                   (CDC_ACM5_USB_BUF_START + (416))
#define CDC_ACM5_EP5_RX0_ADDR                                   (CDC_ACM5_USB_BUF_START + (384))
#define CDC_ACM5_EP5_RX1_ADDR                                   (CDC_ACM5_USB_BUF_START + (416))


// EndPoint max packed sizes
extern const uint8_t CDC_ACM5_txEpMaxSize[];
#define CDC_ACM5_TXEP_MAX_SIZE                                  \
const uint8_t CDC_ACM5_txEpMaxSize[] = \
{ CDC_ACM5_EP0_TX_SIZE, CDC_ACM5_EP1_TX_SIZE, CDC_ACM5_EP2_TX_SIZE, CDC_ACM5_EP3_TX_SIZE, CDC_ACM5_EP4_TX_SIZE, CDC_ACM5_EP5_TX_SIZE,  };
extern const uint8_t CDC_ACM5_rxEpMaxSize[];
#define CDC_ACM5_RXEP_MAX_SIZE                                  \
const uint8_t CDC_ACM5_rxEpMaxSize[] = \
{ CDC_ACM5_EP0_RX_SIZE, CDC_ACM5_EP1_RX_SIZE, CDC_ACM5_EP2_RX_SIZE, CDC_ACM5_EP3_RX_SIZE, CDC_ACM5_EP4_RX_SIZE, CDC_ACM5_EP5_RX_SIZE,  };

// EndPoints init function for USB FS core
#define CDC_ACM5_TUSB_INIT_EP_FS(dev) \
  do{\
    /* Init ep0 */ \
    INIT_EP_BiDirection(dev, PCD_ENDP0, CDC_ACM5_EP0_TYPE);  \
    SET_TX_ADDR(dev, PCD_ENDP0, CDC_ACM5_EP0_TX_ADDR);  \
    SET_RX_ADDR(dev, PCD_ENDP0, CDC_ACM5_EP0_RX_ADDR);  \
    SET_RX_CNT(dev, PCD_ENDP0, CDC_ACM5_EP0_RX_SIZE);  \
    /* Init ep1 */ \
    INIT_EP_BiDirection(dev, PCD_ENDP1, CDC_ACM5_EP1_TYPE);  \
    SET_TX_ADDR(dev, PCD_ENDP1, CDC_ACM5_EP1_TX_ADDR);  \
    SET_RX_ADDR(dev, PCD_ENDP1, CDC_ACM5_EP1_RX_ADDR);  \
    SET_RX_CNT(dev, PCD_ENDP1, CDC_ACM5_EP1_RX_SIZE);  \
    /* Init ep2 */ \
    INIT_EP_BiDirection(dev, PCD_ENDP2, CDC_ACM5_EP2_TYPE);  \
    SET_TX_ADDR(dev, PCD_ENDP2, CDC_ACM5_EP2_TX_ADDR);  \
    SET_RX_ADDR(dev, PCD_ENDP2, CDC_ACM5_EP2_RX_ADDR);  \
    SET_RX_CNT(dev, PCD_ENDP2, CDC_ACM5_EP2_RX_SIZE);  \
    /* Init ep3 */ \
    INIT_EP_BiDirection(dev, PCD_ENDP3, CDC_ACM5_EP3_TYPE);  \
    SET_TX_ADDR(dev, PCD_ENDP3, CDC_ACM5_EP3_TX_ADDR);  \
    SET_RX_ADDR(dev, PCD_ENDP3, CDC_ACM5_EP3_RX_ADDR);  \
    SET_RX_CNT(dev, PCD_ENDP3, CDC_ACM5_EP3_RX_SIZE);  \
    /* Init ep4 */ \
    INIT_EP_BiDirection(dev, PCD_ENDP4, CDC_ACM5_EP4_TYPE);  \
    SET_TX_ADDR(dev, PCD_ENDP4, CDC_ACM5_EP4_TX_ADDR);  \
    SET_RX_ADDR(dev, PCD_ENDP4, CDC_ACM5_EP4_RX_ADDR);  \
    SET_RX_CNT(dev, PCD_ENDP4, CDC_ACM5_EP4_RX_SIZE);  \
    /* Init ep5 */ \
    INIT_EP_BiDirection(dev, PCD_ENDP5, CDC_ACM5_EP5_TYPE);  \
    SET_TX_ADDR(dev, PCD_ENDP5, CDC_ACM5_EP5_TX_ADDR);  \
    SET_RX_ADDR(dev, PCD_ENDP5, CDC_ACM5_EP5_RX_ADDR);  \
    SET_RX_CNT(dev, PCD_ENDP5, CDC_ACM5_EP5_RX_SIZE);  \
}while(0)

///////////////////////////////////////////////
//// Endpoint define for STM32 OTG Core
///////////////////////////////////////////////
#define CDC_ACM5_OTG_MAX_OUT_SIZE                               (32)
#define CDC_ACM5_OTG_CONTROL_EP_NUM                             (1)
#define CDC_ACM5_OTG_OUT_EP_NUM                                 (5)
// RX FIFO size / 4 > (CONTROL_EP_NUM * 5 + 8) +  (MAX_OUT_SIZE / 4 + 1) + (OUT_EP_NUM*2) + 1 = 33

///////////////////////////////////////////////
//// Endpoint define for STM32 OTG FS Core
///////////////////////////////////////////////
#define CDC_ACM5_OTG_RX_FIFO_SIZE_FS                            (256)
#define CDC_ACM5_OTG_RX_FIFO_ADDR_FS                            (0)
// Sum of IN ep max packet size is 224
// Remain Fifo size is 1024 in bytes, Rx Used 256 bytes 

// TODO:
// I don't know why the max count of TX fifo should <= (7 * EpMaxPacket)
// But it seems the STM32F7xx can be large than (7 * EpMaxPacket)
#define CDC_ACM5_EP0_TX_FIFO_ADDR_FS                            (256)
#define CDC_ACM5_EP0_TX_FIFO_SIZE_FS                            (CDC_ACM5_EP0_TX_SIZE * 4)
#define CDC_ACM5_EP1_TX_FIFO_ADDR_FS                            (512)
#define CDC_ACM5_EP1_TX_FIFO_SIZE_FS                            (CDC_ACM5_EP1_TX_SIZE * 4)
#define CDC_ACM5_EP2_TX_FIFO_ADDR_FS                            (640)
#define CDC_ACM5_EP2_TX_FIFO_SIZE_FS                            (CDC_ACM5_EP2_TX_SIZE * 4)
#define CDC_ACM5_EP3_TX_FIFO_ADDR_FS                            (768)
#define CDC_ACM5_EP3_TX_FIFO_SIZE_FS                            (CDC_ACM5_EP3_TX_SIZE * 4)
#define CDC_ACM5_EP4_TX_FIFO_ADDR_FS                            (896)
#define CDC_ACM5_EP4_TX_FIFO_SIZE_FS                            (CDC_ACM5_EP4_TX_SIZE * 4)
#define CDC_ACM5_EP5_TX_FIFO_ADDR_FS                            (1024)
#define CDC_ACM5_EP5_TX_FIFO_SIZE_FS                            (CDC_ACM5_EP5_TX_SIZE * 4)
// EndPoints init function for USB OTG core
#if defined(USB_OTG_FS)
#define CDC_ACM5_TUSB_INIT_EP_OTG_FS(dev) \
  do{\
    if(GetUSB(dev) == USB_OTG_FS) { \
      SET_RX_FIFO(dev, CDC_ACM5_OTG_RX_FIFO_ADDR_FS, CDC_ACM5_OTG_RX_FIFO_SIZE_FS);  \
      /* Init Ep0  */\
      INIT_EP_Tx(dev, PCD_ENDP0, CDC_ACM5_EP0_TX_TYPE, CDC_ACM5_EP0_TX_SIZE);  \
      SET_TX_FIFO(dev, PCD_ENDP0, CDC_ACM5_EP0_TX_FIFO_ADDR_FS, CDC_ACM5_EP0_TX_FIFO_SIZE_FS);  \
      INIT_EP_Rx(dev, PCD_ENDP0, CDC_ACM5_EP0_RX_TYPE, CDC_ACM5_EP0_RX_SIZE); \
      /* Init Ep1  */\
      INIT_EP_Tx(dev, PCD_ENDP1, CDC_ACM5_EP1_TX_TYPE, CDC_ACM5_EP1_TX_SIZE);  \
      SET_TX_FIFO(dev, PCD_ENDP1, CDC_ACM5_EP1_TX_FIFO_ADDR_FS, CDC_ACM5_EP1_TX_FIFO_SIZE_FS);  \
      INIT_EP_Rx(dev, PCD_ENDP1, CDC_ACM5_EP1_RX_TYPE, CDC_ACM5_EP1_RX_SIZE); \
      /* Init Ep2  */\
      INIT_EP_Tx(dev, PCD_ENDP2, CDC_ACM5_EP2_TX_TYPE, CDC_ACM5_EP2_TX_SIZE);  \
      SET_TX_FIFO(dev, PCD_ENDP2, CDC_ACM5_EP2_TX_FIFO_ADDR_FS, CDC_ACM5_EP2_TX_FIFO_SIZE_FS);  \
      INIT_EP_Rx(dev, PCD_ENDP2, CDC_ACM5_EP2_RX_TYPE, CDC_ACM5_EP2_RX_SIZE); \
      /* Init Ep3  */\
      INIT_EP_Tx(dev, PCD_ENDP3, CDC_ACM5_EP3_TX_TYPE, CDC_ACM5_EP3_TX_SIZE);  \
      SET_TX_FIFO(dev, PCD_ENDP3, CDC_ACM5_EP3_TX_FIFO_ADDR_FS, CDC_ACM5_EP3_TX_FIFO_SIZE_FS);  \
      INIT_EP_Rx(dev, PCD_ENDP3, CDC_ACM5_EP3_RX_TYPE, CDC_ACM5_EP3_RX_SIZE); \
      /* Init Ep4  */\
      INIT_EP_Tx(dev, PCD_ENDP4, CDC_ACM5_EP4_TX_TYPE, CDC_ACM5_EP4_TX_SIZE);  \
      SET_TX_FIFO(dev, PCD_ENDP4, CDC_ACM5_EP4_TX_FIFO_ADDR_FS, CDC_ACM5_EP4_TX_FIFO_SIZE_FS);  \
      INIT_EP_Rx(dev, PCD_ENDP4, CDC_ACM5_EP4_RX_TYPE, CDC_ACM5_EP4_RX_SIZE); \
      /* Init Ep5  */\
      INIT_EP_Tx(dev, PCD_ENDP5, CDC_ACM5_EP5_TX_TYPE, CDC_ACM5_EP5_TX_SIZE);  \
      SET_TX_FIFO(dev, PCD_ENDP5, CDC_ACM5_EP5_TX_FIFO_ADDR_FS, CDC_ACM5_EP5_TX_FIFO_SIZE_FS);  \
      INIT_EP_Rx(dev, PCD_ENDP5, CDC_ACM5_EP5_RX_TYPE, CDC_ACM5_EP5_RX_SIZE); \
    }\
  }while(0)

#else  // #if defined(USB_OTG_FS)
#define CDC_ACM5_TUSB_INIT_EP_OTG_FS(dev) 
    
#endif  // #if defined(USB_OTG_FS)

///////////////////////////////////////////////
//// Endpoint define for STM32 OTG HS Core
///////////////////////////////////////////////
#define CDC_ACM5_OTG_RX_FIFO_SIZE_HS                            (512)
#define CDC_ACM5_OTG_RX_FIFO_ADDR_HS                            (0)
// Sum of IN ep max packet size is 224
// Remain Fifo size is 3584 in bytes, Rx Used 512 bytes 

// TODO:
// I don't know why the max count of TX fifo should <= (7 * EpMaxPacket)
// But it seems the STM32F7xx can be large than (7 * EpMaxPacket)
#define CDC_ACM5_EP0_TX_FIFO_ADDR_HS                            (512)
#define CDC_ACM5_EP0_TX_FIFO_SIZE_HS                            (CDC_ACM5_EP0_TX_SIZE * 7)
#define CDC_ACM5_EP1_TX_FIFO_ADDR_HS                            (960)
#define CDC_ACM5_EP1_TX_FIFO_SIZE_HS                            (CDC_ACM5_EP1_TX_SIZE * 7)
#define CDC_ACM5_EP2_TX_FIFO_ADDR_HS                            (1184)
#define CDC_ACM5_EP2_TX_FIFO_SIZE_HS                            (CDC_ACM5_EP2_TX_SIZE * 7)
#define CDC_ACM5_EP3_TX_FIFO_ADDR_HS                            (1408)
#define CDC_ACM5_EP3_TX_FIFO_SIZE_HS                            (CDC_ACM5_EP3_TX_SIZE * 7)
#define CDC_ACM5_EP4_TX_FIFO_ADDR_HS                            (1632)
#define CDC_ACM5_EP4_TX_FIFO_SIZE_HS                            (CDC_ACM5_EP4_TX_SIZE * 7)
#define CDC_ACM5_EP5_TX_FIFO_ADDR_HS                            (1856)
#define CDC_ACM5_EP5_TX_FIFO_SIZE_HS                            (CDC_ACM5_EP5_TX_SIZE * 7)
// EndPoints init function for USB OTG core
#if defined(USB_OTG_HS)
#define CDC_ACM5_TUSB_INIT_EP_OTG_HS(dev) \
  do{\
    if(GetUSB(dev) == USB_OTG_HS) { \
      SET_RX_FIFO(dev, CDC_ACM5_OTG_RX_FIFO_ADDR_HS, CDC_ACM5_OTG_RX_FIFO_SIZE_HS);  \
      /* Init Ep0  */\
      INIT_EP_Tx(dev, PCD_ENDP0, CDC_ACM5_EP0_TX_TYPE, CDC_ACM5_EP0_TX_SIZE);  \
      SET_TX_FIFO(dev, PCD_ENDP0, CDC_ACM5_EP0_TX_FIFO_ADDR_HS, CDC_ACM5_EP0_TX_FIFO_SIZE_HS);  \
      INIT_EP_Rx(dev, PCD_ENDP0, CDC_ACM5_EP0_RX_TYPE, CDC_ACM5_EP0_RX_SIZE); \
      /* Init Ep1  */\
      INIT_EP_Tx(dev, PCD_ENDP1, CDC_ACM5_EP1_TX_TYPE, CDC_ACM5_EP1_TX_SIZE);  \
      SET_TX_FIFO(dev, PCD_ENDP1, CDC_ACM5_EP1_TX_FIFO_ADDR_HS, CDC_ACM5_EP1_TX_FIFO_SIZE_HS);  \
      INIT_EP_Rx(dev, PCD_ENDP1, CDC_ACM5_EP1_RX_TYPE, CDC_ACM5_EP1_RX_SIZE); \
      /* Init Ep2  */\
      INIT_EP_Tx(dev, PCD_ENDP2, CDC_ACM5_EP2_TX_TYPE, CDC_ACM5_EP2_TX_SIZE);  \
      SET_TX_FIFO(dev, PCD_ENDP2, CDC_ACM5_EP2_TX_FIFO_ADDR_HS, CDC_ACM5_EP2_TX_FIFO_SIZE_HS);  \
      INIT_EP_Rx(dev, PCD_ENDP2, CDC_ACM5_EP2_RX_TYPE, CDC_ACM5_EP2_RX_SIZE); \
      /* Init Ep3  */\
      INIT_EP_Tx(dev, PCD_ENDP3, CDC_ACM5_EP3_TX_TYPE, CDC_ACM5_EP3_TX_SIZE);  \
      SET_TX_FIFO(dev, PCD_ENDP3, CDC_ACM5_EP3_TX_FIFO_ADDR_HS, CDC_ACM5_EP3_TX_FIFO_SIZE_HS);  \
      INIT_EP_Rx(dev, PCD_ENDP3, CDC_ACM5_EP3_RX_TYPE, CDC_ACM5_EP3_RX_SIZE); \
      /* Init Ep4  */\
      INIT_EP_Tx(dev, PCD_ENDP4, CDC_ACM5_EP4_TX_TYPE, CDC_ACM5_EP4_TX_SIZE);  \
      SET_TX_FIFO(dev, PCD_ENDP4, CDC_ACM5_EP4_TX_FIFO_ADDR_HS, CDC_ACM5_EP4_TX_FIFO_SIZE_HS);  \
      INIT_EP_Rx(dev, PCD_ENDP4, CDC_ACM5_EP4_RX_TYPE, CDC_ACM5_EP4_RX_SIZE); \
      /* Init Ep5  */\
      INIT_EP_Tx(dev, PCD_ENDP5, CDC_ACM5_EP5_TX_TYPE, CDC_ACM5_EP5_TX_SIZE);  \
      SET_TX_FIFO(dev, PCD_ENDP5, CDC_ACM5_EP5_TX_FIFO_ADDR_HS, CDC_ACM5_EP5_TX_FIFO_SIZE_HS);  \
      INIT_EP_Rx(dev, PCD_ENDP5, CDC_ACM5_EP5_RX_TYPE, CDC_ACM5_EP5_RX_SIZE); \
    }\
  }while(0)

#else  // #if defined(USB_OTG_HS)
#define CDC_ACM5_TUSB_INIT_EP_OTG_HS(dev) 
    
#endif  // #if defined(USB_OTG_HS)
#define CDC_ACM5_TUSB_INIT_EP_OTG(dev) \
  do{\
    CDC_ACM5_TUSB_INIT_EP_OTG_FS(dev); \
    CDC_ACM5_TUSB_INIT_EP_OTG_HS(dev); \
  }while(0)


#if defined(USB)
#define CDC_ACM5_TUSB_INIT_EP(dev) CDC_ACM5_TUSB_INIT_EP_FS(dev)

// Teeny USB device init function for FS core
#define CDC_ACM5_TUSB_INIT_DEVICE(dev) \
  do{\
    /* Init device features */       \
    memset(&dev->addr, 0, TUSB_DEVICE_SIZE);    \
    dev->status = CDC_ACM5_DEV_STATUS;         \
    dev->rx_max_size = CDC_ACM5_rxEpMaxSize;         \
    dev->tx_max_size = CDC_ACM5_txEpMaxSize;         \
    dev->descriptors = &CDC_ACM5_descriptors;         \
  }while(0)

#endif

#if defined(USB_OTG_FS) || defined(USB_OTG_HS)
#define CDC_ACM5_TUSB_INIT_EP(dev) CDC_ACM5_TUSB_INIT_EP_OTG(dev)

// Teeny USB device init function for OTG core
#define CDC_ACM5_TUSB_INIT_DEVICE(dev) \
  do{\
    /* Init device features */       \
    memset(&dev->addr, 0, TUSB_DEVICE_SIZE);    \
    dev->status = CDC_ACM5_DEV_STATUS;         \
    dev->descriptors = &CDC_ACM5_descriptors;         \
  }while(0)

#endif

#define CDC_ACM5_TUSB_INIT(dev) \
  do{\
    CDC_ACM5_TUSB_INIT_EP(dev);   \
    CDC_ACM5_TUSB_INIT_DEVICE(dev);   \
  }while(0)

// Get End Point count
#ifndef  EP_NUM
#define  EP_NUM 1
#endif
#if CDC_ACM5_EP_NUM > EP_NUM
#undef   EP_NUM
#define  EP_NUM  CDC_ACM5_EP_NUM
#endif

extern const uint8_t* const CDC_ACM5_StringDescriptors[CDC_ACM5_STRING_COUNT];
extern const tusb_descriptors CDC_ACM5_descriptors;


#endif   // #ifndef __CDC_ACM5_TEENY_USB_INIT_H__
/////////////////////////////////////////
//// Device 3
/////////////////////////////////////////
#ifndef __CDC_RNDIS_TEENY_USB_INIT_H__
#define __CDC_RNDIS_TEENY_USB_INIT_H__
// forward declare the tusb_descriptors struct
typedef struct _tusb_descriptors tusb_descriptors;

#define CDC_RNDIS_VID                                            0x0483
#define CDC_RNDIS_PID                                            0x0011
#define CDC_RNDIS_STRING_COUNT                                   (4)

// device.bmAttributes & 0x40   USB_CONFIG_SELF_POWERED
// device.bmAttributes & 0x20   USB_CONFIG_REMOTE_WAKEUP
#define CDC_RNDIS_DEV_STATUS                                    (0 | 0)


// Endpoint usage:
#define CDC_RNDIS_MAX_EP                                         (3)
#define CDC_RNDIS_EP_NUM                                         (CDC_RNDIS_MAX_EP + 1)

///////////////////////////////////////////////
//// Endpoint define for STM32 FS Core
///////////////////////////////////////////////

#ifdef CDC_RNDIS_BTABLE_ADDRESS
#undef CDC_RNDIS_BTABLE_ADDRESS
#endif
#define CDC_RNDIS_BTABLE_ADDRESS                                 (0)
#define CDC_RNDIS_EP_BUF_DESC_TABLE_SIZE                         (8)
// PMA buffer reserved for buffer description table
#define CDC_RNDIS_USB_BUF_START                                  (CDC_RNDIS_EP_BUF_DESC_TABLE_SIZE * CDC_RNDIS_EP_NUM)

// EndPoints 0 defines
#define CDC_RNDIS_EP0_RX_SIZE                                    (64)
#define CDC_RNDIS_EP0_RX_ADDR                                    (CDC_RNDIS_USB_BUF_START + (0))
#define CDC_RNDIS_EP0_TX_SIZE                                    (64)
#define CDC_RNDIS_EP0_TX_ADDR                                    (CDC_RNDIS_USB_BUF_START + (64))
#define CDC_RNDIS_EP0_RX_TYPE                                    USB_EP_CONTROL
#define CDC_RNDIS_EP0_TX_TYPE                                    USB_EP_CONTROL

#define CDC_RNDIS_EP0_TYPE                                       USB_EP_CONTROL
#define CDC_RNDIS_EP0_TX0_ADDR                                   (CDC_RNDIS_USB_BUF_START + (0))
#define CDC_RNDIS_EP0_TX1_ADDR                                   (CDC_RNDIS_USB_BUF_START + (64))
#define CDC_RNDIS_EP0_RX0_ADDR                                   (CDC_RNDIS_USB_BUF_START + (0))
#define CDC_RNDIS_EP0_RX1_ADDR                                   (CDC_RNDIS_USB_BUF_START + (64))

// EndPoints 1 defines
#define CDC_RNDIS_EP1_RX_SIZE                                    (64)
#define CDC_RNDIS_EP1_RX_ADDR                                    (CDC_RNDIS_USB_BUF_START + (128))
#define CDC_RNDIS_EP1_TX_SIZE                                    (64)
#define CDC_RNDIS_EP1_TX_ADDR                                    (CDC_RNDIS_USB_BUF_START + (192))
#define CDC_RNDIS_EP1_RX_TYPE                                    USB_EP_BULK
#define CDC_RNDIS_EP1_TX_TYPE                                    USB_EP_BULK

#define CDC_RNDIS_EP1_TYPE                                       USB_EP_BULK
#define CDC_RNDIS_EP1_TX0_ADDR                                   (CDC_RNDIS_USB_BUF_START + (128))
#define CDC_RNDIS_EP1_TX1_ADDR                                   (CDC_RNDIS_USB_BUF_START + (192))
#define CDC_RNDIS_EP1_RX0_ADDR                                   (CDC_RNDIS_USB_BUF_START + (128))
#define CDC_RNDIS_EP1_RX1_ADDR                                   (CDC_RNDIS_USB_BUF_START + (192))

// EndPoints 2 defines
#define CDC_RNDIS_EP2_RX_SIZE                                    (0)
#define CDC_RNDIS_EP2_RX_ADDR                                    (CDC_RNDIS_USB_BUF_START + (256))
#define CDC_RNDIS_EP2_TX_SIZE                                    (0)
#define CDC_RNDIS_EP2_TX_ADDR                                    (CDC_RNDIS_USB_BUF_START + (256))
#define CDC_RNDIS_EP2_RX_TYPE                                    USB_EP_Invalid
#define CDC_RNDIS_EP2_TX_TYPE                                    USB_EP_Invalid

#define CDC_RNDIS_EP2_TYPE                                       USB_EP_Invalid
#define CDC_RNDIS_EP2_TX0_ADDR                                   (CDC_RNDIS_USB_BUF_START + (256))
#define CDC_RNDIS_EP2_TX1_ADDR                                   (CDC_RNDIS_USB_BUF_START + (256))
#define CDC_RNDIS_EP2_RX0_ADDR                                   (CDC_RNDIS_USB_BUF_START + (256))
#define CDC_RNDIS_EP2_RX1_ADDR                                   (CDC_RNDIS_USB_BUF_START + (256))

// EndPoints 3 defines
#define CDC_RNDIS_EP3_RX_SIZE                                    (0)
#define CDC_RNDIS_EP3_RX_ADDR                                    (CDC_RNDIS_USB_BUF_START + (256))
#define CDC_RNDIS_EP3_TX_SIZE                                    (16)
#define CDC_RNDIS_EP3_TX_ADDR                                    (CDC_RNDIS_USB_BUF_START + (256))
#define CDC_RNDIS_EP3_RX_TYPE                                    USB_EP_Invalid
#define CDC_RNDIS_EP3_TX_TYPE                                    USB_EP_INTERRUPT

#define CDC_RNDIS_EP3_TYPE                                       USB_EP_INTERRUPT
#define CDC_RNDIS_EP3_TX0_ADDR                                   (CDC_RNDIS_USB_BUF_START + (256))
#define CDC_RNDIS_EP3_TX1_ADDR                                   (CDC_RNDIS_USB_BUF_START + (272))
#define CDC_RNDIS_EP3_RX0_ADDR                                   (CDC_RNDIS_USB_BUF_START + (256))
#define CDC_RNDIS_EP3_RX1_ADDR                                   (CDC_RNDIS_USB_BUF_START + (272))


// EndPoint max packed sizes
extern const uint8_t CDC_RNDIS_txEpMaxSize[];
#define CDC_RNDIS_TXEP_MAX_SIZE                                  \
const uint8_t CDC_RNDIS_txEpMaxSize[] = \
{ CDC_RNDIS_EP0_TX_SIZE, CDC_RNDIS_EP1_TX_SIZE, 0, CDC_RNDIS_EP3_TX_SIZE,  };
extern const uint8_t CDC_RNDIS_rxEpMaxSize[];
#define CDC_RNDIS_RXEP_MAX_SIZE                                  \
const uint8_t CDC_RNDIS_rxEpMaxSize[] = \
{ CDC_RNDIS_EP0_RX_SIZE, CDC_RNDIS_EP1_RX_SIZE, 0, 0,  };

// EndPoints init function for USB FS core
#define CDC_RNDIS_TUSB_INIT_EP_FS(dev) \
  do{\
    /* Init ep0 */ \
    INIT_EP_BiDirection(dev, PCD_ENDP0, CDC_RNDIS_EP0_TYPE);  \
    SET_TX_ADDR(dev, PCD_ENDP0, CDC_RNDIS_EP0_TX_ADDR);  \
    SET_RX_ADDR(dev, PCD_ENDP0, CDC_RNDIS_EP0_RX_ADDR);  \
    SET_RX_CNT(dev, PCD_ENDP0, CDC_RNDIS_EP0_RX_SIZE);  \
    /* Init ep1 */ \
    INIT_EP_BiDirection(dev, PCD_ENDP1, CDC_RNDIS_EP1_TYPE);  \
    SET_TX_ADDR(dev, PCD_ENDP1, CDC_RNDIS_EP1_TX_ADDR);  \
    SET_RX_ADDR(dev, PCD_ENDP1, CDC_RNDIS_EP1_RX_ADDR);  \
    SET_RX_CNT(dev, PCD_ENDP1, CDC_RNDIS_EP1_RX_SIZE);  \
    /* Init ep2 */ \
    /* Init ep3 */ \
    INIT_EP_TxOnly(dev, PCD_ENDP3, CDC_RNDIS_EP3_TYPE);  \
    SET_TX_ADDR(dev, PCD_ENDP3, CDC_RNDIS_EP3_TX_ADDR);  \
}while(0)

///////////////////////////////////////////////
//// Endpoint define for STM32 OTG Core
///////////////////////////////////////////////
#define CDC_RNDIS_OTG_MAX_OUT_SIZE                               (64)
#define CDC_RNDIS_OTG_CONTROL_EP_NUM                             (1)
#define CDC_RNDIS_OTG_OUT_EP_NUM                                 (1)
// RX FIFO size / 4 > (CONTROL_EP_NUM * 5 + 8) +  (MAX_OUT_SIZE / 4 + 1) + (OUT_EP_NUM*2) + 1 = 33

///////////////////////////////////////////////
//// Endpoint define for STM32 OTG FS Core
///////////////////////////////////////////////
#define CDC_RNDIS_OTG_RX_FIFO_SIZE_FS                            (256)
#define CDC_RNDIS_OTG_RX_FIFO_ADDR_FS                            (0)
// Sum of IN ep max packet size is 144
// Remain Fifo size is 1024 in bytes, Rx Used 256 bytes 

// TODO:
// I don't know why the max count of TX fifo should <= (7 * EpMaxPacket)
// But it seems the STM32F7xx can be large than (7 * EpMaxPacket)
#define CDC_RNDIS_EP0_TX_FIFO_ADDR_FS                            (256)
#define CDC_RNDIS_EP0_TX_FIFO_SIZE_FS                            (CDC_RNDIS_EP0_TX_SIZE * 7)
#define CDC_RNDIS_EP1_TX_FIFO_ADDR_FS                            (704)
#define CDC_RNDIS_EP1_TX_FIFO_SIZE_FS                            (CDC_RNDIS_EP1_TX_SIZE * 7)
#define CDC_RNDIS_EP3_TX_FIFO_ADDR_FS                            (1152)
#define CDC_RNDIS_EP3_TX_FIFO_SIZE_FS                            (CDC_RNDIS_EP3_TX_SIZE * 7)
// EndPoints init function for USB OTG core
#if defined(USB_OTG_FS)
#define CDC_RNDIS_TUSB_INIT_EP_OTG_FS(dev) \
  do{\
    if(GetUSB(dev) == USB_OTG_FS) { \
      SET_RX_FIFO(dev, CDC_RNDIS_OTG_RX_FIFO_ADDR_FS, CDC_RNDIS_OTG_RX_FIFO_SIZE_FS);  \
      /* Init Ep0  */\
      INIT_EP_Tx(dev, PCD_ENDP0, CDC_RNDIS_EP0_TX_TYPE, CDC_RNDIS_EP0_TX_SIZE);  \
      SET_TX_FIFO(dev, PCD_ENDP0, CDC_RNDIS_EP0_TX_FIFO_ADDR_FS, CDC_RNDIS_EP0_TX_FIFO_SIZE_FS);  \
      INIT_EP_Rx(dev, PCD_ENDP0, CDC_RNDIS_EP0_RX_TYPE, CDC_RNDIS_EP0_RX_SIZE); \
      /* Init Ep1  */\
      INIT_EP_Tx(dev, PCD_ENDP1, CDC_RNDIS_EP1_TX_TYPE, CDC_RNDIS_EP1_TX_SIZE);  \
      SET_TX_FIFO(dev, PCD_ENDP1, CDC_RNDIS_EP1_TX_FIFO_ADDR_FS, CDC_RNDIS_EP1_TX_FIFO_SIZE_FS);  \
      INIT_EP_Rx(dev, PCD_ENDP1, CDC_RNDIS_EP1_RX_TYPE, CDC_RNDIS_EP1_RX_SIZE); \
      /* Init Ep3  */\
      INIT_EP_Tx(dev, PCD_ENDP3, CDC_RNDIS_EP3_TX_TYPE, CDC_RNDIS_EP3_TX_SIZE);  \
      SET_TX_FIFO(dev, PCD_ENDP3, CDC_RNDIS_EP3_TX_FIFO_ADDR_FS, CDC_RNDIS_EP3_TX_FIFO_SIZE_FS);  \
    }\
  }while(0)

#else  // #if defined(USB_OTG_FS)
#define CDC_RNDIS_TUSB_INIT_EP_OTG_FS(dev) 
    
#endif  // #if defined(USB_OTG_FS)

///////////////////////////////////////////////
//// Endpoint define for STM32 OTG HS Core
///////////////////////////////////////////////
#define CDC_RNDIS_OTG_RX_FIFO_SIZE_HS                            (512)
#define CDC_RNDIS_OTG_RX_FIFO_ADDR_HS                            (0)
// Sum of IN ep max packet size is 144
// Remain Fifo size is 3584 in bytes, Rx Used 512 bytes 

// TODO:
// I don't know why the max count of TX fifo should <= (7 * EpMaxPacket)
// But it seems the STM32F7xx can be large than (7 * EpMaxPacket)
#define CDC_RNDIS_EP0_TX_FIFO_ADDR_HS                            (512)
#define CDC_RNDIS_EP0_TX_FIFO_SIZE_HS                            (CDC_RNDIS_EP0_TX_SIZE * 7)
#define CDC_RNDIS_EP1_TX_FIFO_ADDR_HS                            (960)
#define CDC_RNDIS_EP1_TX_FIFO_SIZE_HS                            (CDC_RNDIS_EP1_TX_SIZE * 7)
#define CDC_RNDIS_EP3_TX_FIFO_ADDR_HS                            (1408)
#define CDC_RNDIS_EP3_TX_FIFO_SIZE_HS                            (CDC_RNDIS_EP3_TX_SIZE * 7)
// EndPoints init function for USB OTG core
#if defined(USB_OTG_HS)
#define CDC_RNDIS_TUSB_INIT_EP_OTG_HS(dev) \
  do{\
    if(GetUSB(dev) == USB_OTG_HS) { \
      SET_RX_FIFO(dev, CDC_RNDIS_OTG_RX_FIFO_ADDR_HS, CDC_RNDIS_OTG_RX_FIFO_SIZE_HS);  \
      /* Init Ep0  */\
      INIT_EP_Tx(dev, PCD_ENDP0, CDC_RNDIS_EP0_TX_TYPE, CDC_RNDIS_EP0_TX_SIZE);  \
      SET_TX_FIFO(dev, PCD_ENDP0, CDC_RNDIS_EP0_TX_FIFO_ADDR_HS, CDC_RNDIS_EP0_TX_FIFO_SIZE_HS);  \
      INIT_EP_Rx(dev, PCD_ENDP0, CDC_RNDIS_EP0_RX_TYPE, CDC_RNDIS_EP0_RX_SIZE); \
      /* Init Ep1  */\
      INIT_EP_Tx(dev, PCD_ENDP1, CDC_RNDIS_EP1_TX_TYPE, CDC_RNDIS_EP1_TX_SIZE);  \
      SET_TX_FIFO(dev, PCD_ENDP1, CDC_RNDIS_EP1_TX_FIFO_ADDR_HS, CDC_RNDIS_EP1_TX_FIFO_SIZE_HS);  \
      INIT_EP_Rx(dev, PCD_ENDP1, CDC_RNDIS_EP1_RX_TYPE, CDC_RNDIS_EP1_RX_SIZE); \
      /* Init Ep3  */\
      INIT_EP_Tx(dev, PCD_ENDP3, CDC_RNDIS_EP3_TX_TYPE, CDC_RNDIS_EP3_TX_SIZE);  \
      SET_TX_FIFO(dev, PCD_ENDP3, CDC_RNDIS_EP3_TX_FIFO_ADDR_HS, CDC_RNDIS_EP3_TX_FIFO_SIZE_HS);  \
    }\
  }while(0)

#else  // #if defined(USB_OTG_HS)
#define CDC_RNDIS_TUSB_INIT_EP_OTG_HS(dev) 
    
#endif  // #if defined(USB_OTG_HS)
#define CDC_RNDIS_TUSB_INIT_EP_OTG(dev) \
  do{\
    CDC_RNDIS_TUSB_INIT_EP_OTG_FS(dev); \
    CDC_RNDIS_TUSB_INIT_EP_OTG_HS(dev); \
  }while(0)


#if defined(USB)
#define CDC_RNDIS_TUSB_INIT_EP(dev) CDC_RNDIS_TUSB_INIT_EP_FS(dev)

// Teeny USB device init function for FS core
#define CDC_RNDIS_TUSB_INIT_DEVICE(dev) \
  do{\
    /* Init device features */       \
    memset(&dev->addr, 0, TUSB_DEVICE_SIZE);    \
    dev->status = CDC_RNDIS_DEV_STATUS;         \
    dev->rx_max_size = CDC_RNDIS_rxEpMaxSize;         \
    dev->tx_max_size = CDC_RNDIS_txEpMaxSize;         \
    dev->descriptors = &CDC_RNDIS_descriptors;         \
  }while(0)

#endif

#if defined(USB_OTG_FS) || defined(USB_OTG_HS)
#define CDC_RNDIS_TUSB_INIT_EP(dev) CDC_RNDIS_TUSB_INIT_EP_OTG(dev)

// Teeny USB device init function for OTG core
#define CDC_RNDIS_TUSB_INIT_DEVICE(dev) \
  do{\
    /* Init device features */       \
    memset(&dev->addr, 0, TUSB_DEVICE_SIZE);    \
    dev->status = CDC_RNDIS_DEV_STATUS;         \
    dev->descriptors = &CDC_RNDIS_descriptors;         \
  }while(0)

#endif

#define CDC_RNDIS_TUSB_INIT(dev) \
  do{\
    CDC_RNDIS_TUSB_INIT_EP(dev);   \
    CDC_RNDIS_TUSB_INIT_DEVICE(dev);   \
  }while(0)

// Get End Point count
#ifndef  EP_NUM
#define  EP_NUM 1
#endif
#if CDC_RNDIS_EP_NUM > EP_NUM
#undef   EP_NUM
#define  EP_NUM  CDC_RNDIS_EP_NUM
#endif

extern const uint8_t* const CDC_RNDIS_StringDescriptors[CDC_RNDIS_STRING_COUNT];
extern const tusb_descriptors CDC_RNDIS_descriptors;

// Enable WCID related code
#define  HAS_WCID

#ifndef WCID_VENDOR_CODE
#define  WCID_VENDOR_CODE       0x17
extern const uint8_t WCID_StringDescriptor_MSOS[];
#endif


#endif   // #ifndef __CDC_RNDIS_TEENY_USB_INIT_H__
/////////////////////////////////////////
//// Device 4
/////////////////////////////////////////
#ifndef __WINUSB_TEENY_USB_INIT_H__
#define __WINUSB_TEENY_USB_INIT_H__
// forward declare the tusb_descriptors struct
typedef struct _tusb_descriptors tusb_descriptors;

#define WINUSB_VID                                            0x0483
#define WINUSB_PID                                            0x0011
#define WINUSB_STRING_COUNT                                   (6)

// device.bmAttributes & 0x40   USB_CONFIG_SELF_POWERED
// device.bmAttributes & 0x20   USB_CONFIG_REMOTE_WAKEUP
#define WINUSB_DEV_STATUS                                    (0 | 0)


// Endpoint usage:
#define WINUSB_MAX_EP                                         (3)
#define WINUSB_EP_NUM                                         (WINUSB_MAX_EP + 1)

///////////////////////////////////////////////
//// Endpoint define for STM32 FS Core
///////////////////////////////////////////////

#ifdef WINUSB_BTABLE_ADDRESS
#undef WINUSB_BTABLE_ADDRESS
#endif
#define WINUSB_BTABLE_ADDRESS                                 (0)
#define WINUSB_EP_BUF_DESC_TABLE_SIZE                         (8)
// PMA buffer reserved for buffer description table
#define WINUSB_USB_BUF_START                                  (WINUSB_EP_BUF_DESC_TABLE_SIZE * WINUSB_EP_NUM)

// EndPoints 0 defines
#define WINUSB_EP0_RX_SIZE                                    (64)
#define WINUSB_EP0_RX_ADDR                                    (WINUSB_USB_BUF_START + (0))
#define WINUSB_EP0_TX_SIZE                                    (64)
#define WINUSB_EP0_TX_ADDR                                    (WINUSB_USB_BUF_START + (64))
#define WINUSB_EP0_RX_TYPE                                    USB_EP_CONTROL
#define WINUSB_EP0_TX_TYPE                                    USB_EP_CONTROL

#define WINUSB_EP0_TYPE                                       USB_EP_CONTROL
#define WINUSB_EP0_TX0_ADDR                                   (WINUSB_USB_BUF_START + (0))
#define WINUSB_EP0_TX1_ADDR                                   (WINUSB_USB_BUF_START + (64))
#define WINUSB_EP0_RX0_ADDR                                   (WINUSB_USB_BUF_START + (0))
#define WINUSB_EP0_RX1_ADDR                                   (WINUSB_USB_BUF_START + (64))

// EndPoints 1 defines
#define WINUSB_EP1_RX_SIZE                                    (32)
#define WINUSB_EP1_RX_ADDR                                    (WINUSB_USB_BUF_START + (128))
#define WINUSB_EP1_TX_SIZE                                    (32)
#define WINUSB_EP1_TX_ADDR                                    (WINUSB_USB_BUF_START + (160))
#define WINUSB_EP1_RX_TYPE                                    USB_EP_BULK
#define WINUSB_EP1_TX_TYPE                                    USB_EP_BULK

#define WINUSB_EP1_TYPE                                       USB_EP_BULK
#define WINUSB_EP1_TX0_ADDR                                   (WINUSB_USB_BUF_START + (128))
#define WINUSB_EP1_TX1_ADDR                                   (WINUSB_USB_BUF_START + (160))
#define WINUSB_EP1_RX0_ADDR                                   (WINUSB_USB_BUF_START + (128))
#define WINUSB_EP1_RX1_ADDR                                   (WINUSB_USB_BUF_START + (160))

// EndPoints 2 defines
#define WINUSB_EP2_RX_SIZE                                    (32)
#define WINUSB_EP2_RX_ADDR                                    (WINUSB_USB_BUF_START + (192))
#define WINUSB_EP2_TX_SIZE                                    (32)
#define WINUSB_EP2_TX_ADDR                                    (WINUSB_USB_BUF_START + (224))
#define WINUSB_EP2_RX_TYPE                                    USB_EP_BULK
#define WINUSB_EP2_TX_TYPE                                    USB_EP_BULK

#define WINUSB_EP2_TYPE                                       USB_EP_BULK
#define WINUSB_EP2_TX0_ADDR                                   (WINUSB_USB_BUF_START + (192))
#define WINUSB_EP2_TX1_ADDR                                   (WINUSB_USB_BUF_START + (224))
#define WINUSB_EP2_RX0_ADDR                                   (WINUSB_USB_BUF_START + (192))
#define WINUSB_EP2_RX1_ADDR                                   (WINUSB_USB_BUF_START + (224))

// EndPoints 3 defines
#define WINUSB_EP3_RX_SIZE                                    (32)
#define WINUSB_EP3_RX_ADDR                                    (WINUSB_USB_BUF_START + (256))
#define WINUSB_EP3_TX_SIZE                                    (32)
#define WINUSB_EP3_TX_ADDR                                    (WINUSB_USB_BUF_START + (288))
#define WINUSB_EP3_RX_TYPE                                    USB_EP_BULK
#define WINUSB_EP3_TX_TYPE                                    USB_EP_BULK

#define WINUSB_EP3_TYPE                                       USB_EP_BULK
#define WINUSB_EP3_TX0_ADDR                                   (WINUSB_USB_BUF_START + (256))
#define WINUSB_EP3_TX1_ADDR                                   (WINUSB_USB_BUF_START + (288))
#define WINUSB_EP3_RX0_ADDR                                   (WINUSB_USB_BUF_START + (256))
#define WINUSB_EP3_RX1_ADDR                                   (WINUSB_USB_BUF_START + (288))


// EndPoint max packed sizes
extern const uint8_t WINUSB_txEpMaxSize[];
#define WINUSB_TXEP_MAX_SIZE                                  \
const uint8_t WINUSB_txEpMaxSize[] = \
{ WINUSB_EP0_TX_SIZE, WINUSB_EP1_TX_SIZE, WINUSB_EP2_TX_SIZE, WINUSB_EP3_TX_SIZE,  };
extern const uint8_t WINUSB_rxEpMaxSize[];
#define WINUSB_RXEP_MAX_SIZE                                  \
const uint8_t WINUSB_rxEpMaxSize[] = \
{ WINUSB_EP0_RX_SIZE, WINUSB_EP1_RX_SIZE, WINUSB_EP2_RX_SIZE, WINUSB_EP3_RX_SIZE,  };

// EndPoints init function for USB FS core
#define WINUSB_TUSB_INIT_EP_FS(dev) \
  do{\
    /* Init ep0 */ \
    INIT_EP_BiDirection(dev, PCD_ENDP0, WINUSB_EP0_TYPE);  \
    SET_TX_ADDR(dev, PCD_ENDP0, WINUSB_EP0_TX_ADDR);  \
    SET_RX_ADDR(dev, PCD_ENDP0, WINUSB_EP0_RX_ADDR);  \
    SET_RX_CNT(dev, PCD_ENDP0, WINUSB_EP0_RX_SIZE);  \
    /* Init ep1 */ \
    INIT_EP_BiDirection(dev, PCD_ENDP1, WINUSB_EP1_TYPE);  \
    SET_TX_ADDR(dev, PCD_ENDP1, WINUSB_EP1_TX_ADDR);  \
    SET_RX_ADDR(dev, PCD_ENDP1, WINUSB_EP1_RX_ADDR);  \
    SET_RX_CNT(dev, PCD_ENDP1, WINUSB_EP1_RX_SIZE);  \
    /* Init ep2 */ \
    INIT_EP_BiDirection(dev, PCD_ENDP2, WINUSB_EP2_TYPE);  \
    SET_TX_ADDR(dev, PCD_ENDP2, WINUSB_EP2_TX_ADDR);  \
    SET_RX_ADDR(dev, PCD_ENDP2, WINUSB_EP2_RX_ADDR);  \
    SET_RX_CNT(dev, PCD_ENDP2, WINUSB_EP2_RX_SIZE);  \
    /* Init ep3 */ \
    INIT_EP_BiDirection(dev, PCD_ENDP3, WINUSB_EP3_TYPE);  \
    SET_TX_ADDR(dev, PCD_ENDP3, WINUSB_EP3_TX_ADDR);  \
    SET_RX_ADDR(dev, PCD_ENDP3, WINUSB_EP3_RX_ADDR);  \
    SET_RX_CNT(dev, PCD_ENDP3, WINUSB_EP3_RX_SIZE);  \
}while(0)

///////////////////////////////////////////////
//// Endpoint define for STM32 OTG Core
///////////////////////////////////////////////
#define WINUSB_OTG_MAX_OUT_SIZE                               (32)
#define WINUSB_OTG_CONTROL_EP_NUM                             (1)
#define WINUSB_OTG_OUT_EP_NUM                                 (3)
// RX FIFO size / 4 > (CONTROL_EP_NUM * 5 + 8) +  (MAX_OUT_SIZE / 4 + 1) + (OUT_EP_NUM*2) + 1 = 29

///////////////////////////////////////////////
//// Endpoint define for STM32 OTG FS Core
///////////////////////////////////////////////
#define WINUSB_OTG_RX_FIFO_SIZE_FS                            (256)
#define WINUSB_OTG_RX_FIFO_ADDR_FS                            (0)
// Sum of IN ep max packet size is 160
// Remain Fifo size is 1024 in bytes, Rx Used 256 bytes 

// TODO:
// I don't know why the max count of TX fifo should <= (7 * EpMaxPacket)
// But it seems the STM32F7xx can be large than (7 * EpMaxPacket)
#define WINUSB_EP0_TX_FIFO_ADDR_FS                            (256)
#define WINUSB_EP0_TX_FIFO_SIZE_FS                            (WINUSB_EP0_TX_SIZE * 6)
#define WINUSB_EP1_TX_FIFO_ADDR_FS                            (640)
#define WINUSB_EP1_TX_FIFO_SIZE_FS                            (WINUSB_EP1_TX_SIZE * 6)
#define WINUSB_EP2_TX_FIFO_ADDR_FS                            (832)
#define WINUSB_EP2_TX_FIFO_SIZE_FS                            (WINUSB_EP2_TX_SIZE * 6)
#define WINUSB_EP3_TX_FIFO_ADDR_FS                            (1024)
#define WINUSB_EP3_TX_FIFO_SIZE_FS                            (WINUSB_EP3_TX_SIZE * 6)
// EndPoints init function for USB OTG core
#if defined(USB_OTG_FS)
#define WINUSB_TUSB_INIT_EP_OTG_FS(dev) \
  do{\
    if(GetUSB(dev) == USB_OTG_FS) { \
      SET_RX_FIFO(dev, WINUSB_OTG_RX_FIFO_ADDR_FS, WINUSB_OTG_RX_FIFO_SIZE_FS);  \
      /* Init Ep0  */\
      INIT_EP_Tx(dev, PCD_ENDP0, WINUSB_EP0_TX_TYPE, WINUSB_EP0_TX_SIZE);  \
      SET_TX_FIFO(dev, PCD_ENDP0, WINUSB_EP0_TX_FIFO_ADDR_FS, WINUSB_EP0_TX_FIFO_SIZE_FS);  \
      INIT_EP_Rx(dev, PCD_ENDP0, WINUSB_EP0_RX_TYPE, WINUSB_EP0_RX_SIZE); \
      /* Init Ep1  */\
      INIT_EP_Tx(dev, PCD_ENDP1, WINUSB_EP1_TX_TYPE, WINUSB_EP1_TX_SIZE);  \
      SET_TX_FIFO(dev, PCD_ENDP1, WINUSB_EP1_TX_FIFO_ADDR_FS, WINUSB_EP1_TX_FIFO_SIZE_FS);  \
      INIT_EP_Rx(dev, PCD_ENDP1, WINUSB_EP1_RX_TYPE, WINUSB_EP1_RX_SIZE); \
      /* Init Ep2  */\
      INIT_EP_Tx(dev, PCD_ENDP2, WINUSB_EP2_TX_TYPE, WINUSB_EP2_TX_SIZE);  \
      SET_TX_FIFO(dev, PCD_ENDP2, WINUSB_EP2_TX_FIFO_ADDR_FS, WINUSB_EP2_TX_FIFO_SIZE_FS);  \
      INIT_EP_Rx(dev, PCD_ENDP2, WINUSB_EP2_RX_TYPE, WINUSB_EP2_RX_SIZE); \
      /* Init Ep3  */\
      INIT_EP_Tx(dev, PCD_ENDP3, WINUSB_EP3_TX_TYPE, WINUSB_EP3_TX_SIZE);  \
      SET_TX_FIFO(dev, PCD_ENDP3, WINUSB_EP3_TX_FIFO_ADDR_FS, WINUSB_EP3_TX_FIFO_SIZE_FS);  \
      INIT_EP_Rx(dev, PCD_ENDP3, WINUSB_EP3_RX_TYPE, WINUSB_EP3_RX_SIZE); \
    }\
  }while(0)

#else  // #if defined(USB_OTG_FS)
#define WINUSB_TUSB_INIT_EP_OTG_FS(dev) 
    
#endif  // #if defined(USB_OTG_FS)

///////////////////////////////////////////////
//// Endpoint define for STM32 OTG HS Core
///////////////////////////////////////////////
#define WINUSB_OTG_RX_FIFO_SIZE_HS                            (512)
#define WINUSB_OTG_RX_FIFO_ADDR_HS                            (0)
// Sum of IN ep max packet size is 160
// Remain Fifo size is 3584 in bytes, Rx Used 512 bytes 

// TODO:
// I don't know why the max count of TX fifo should <= (7 * EpMaxPacket)
// But it seems the STM32F7xx can be large than (7 * EpMaxPacket)
#define WINUSB_EP0_TX_FIFO_ADDR_HS                            (512)
#define WINUSB_EP0_TX_FIFO_SIZE_HS                            (WINUSB_EP0_TX_SIZE * 7)
#define WINUSB_EP1_TX_FIFO_ADDR_HS                            (960)
#define WINUSB_EP1_TX_FIFO_SIZE_HS                            (WINUSB_EP1_TX_SIZE * 7)
#define WINUSB_EP2_TX_FIFO_ADDR_HS                            (1184)
#define WINUSB_EP2_TX_FIFO_SIZE_HS                            (WINUSB_EP2_TX_SIZE * 7)
#define WINUSB_EP3_TX_FIFO_ADDR_HS                            (1408)
#define WINUSB_EP3_TX_FIFO_SIZE_HS                            (WINUSB_EP3_TX_SIZE * 7)
// EndPoints init function for USB OTG core
#if defined(USB_OTG_HS)
#define WINUSB_TUSB_INIT_EP_OTG_HS(dev) \
  do{\
    if(GetUSB(dev) == USB_OTG_HS) { \
      SET_RX_FIFO(dev, WINUSB_OTG_RX_FIFO_ADDR_HS, WINUSB_OTG_RX_FIFO_SIZE_HS);  \
      /* Init Ep0  */\
      INIT_EP_Tx(dev, PCD_ENDP0, WINUSB_EP0_TX_TYPE, WINUSB_EP0_TX_SIZE);  \
      SET_TX_FIFO(dev, PCD_ENDP0, WINUSB_EP0_TX_FIFO_ADDR_HS, WINUSB_EP0_TX_FIFO_SIZE_HS);  \
      INIT_EP_Rx(dev, PCD_ENDP0, WINUSB_EP0_RX_TYPE, WINUSB_EP0_RX_SIZE); \
      /* Init Ep1  */\
      INIT_EP_Tx(dev, PCD_ENDP1, WINUSB_EP1_TX_TYPE, WINUSB_EP1_TX_SIZE);  \
      SET_TX_FIFO(dev, PCD_ENDP1, WINUSB_EP1_TX_FIFO_ADDR_HS, WINUSB_EP1_TX_FIFO_SIZE_HS);  \
      INIT_EP_Rx(dev, PCD_ENDP1, WINUSB_EP1_RX_TYPE, WINUSB_EP1_RX_SIZE); \
      /* Init Ep2  */\
      INIT_EP_Tx(dev, PCD_ENDP2, WINUSB_EP2_TX_TYPE, WINUSB_EP2_TX_SIZE);  \
      SET_TX_FIFO(dev, PCD_ENDP2, WINUSB_EP2_TX_FIFO_ADDR_HS, WINUSB_EP2_TX_FIFO_SIZE_HS);  \
      INIT_EP_Rx(dev, PCD_ENDP2, WINUSB_EP2_RX_TYPE, WINUSB_EP2_RX_SIZE); \
      /* Init Ep3  */\
      INIT_EP_Tx(dev, PCD_ENDP3, WINUSB_EP3_TX_TYPE, WINUSB_EP3_TX_SIZE);  \
      SET_TX_FIFO(dev, PCD_ENDP3, WINUSB_EP3_TX_FIFO_ADDR_HS, WINUSB_EP3_TX_FIFO_SIZE_HS);  \
      INIT_EP_Rx(dev, PCD_ENDP3, WINUSB_EP3_RX_TYPE, WINUSB_EP3_RX_SIZE); \
    }\
  }while(0)

#else  // #if defined(USB_OTG_HS)
#define WINUSB_TUSB_INIT_EP_OTG_HS(dev) 
    
#endif  // #if defined(USB_OTG_HS)
#define WINUSB_TUSB_INIT_EP_OTG(dev) \
  do{\
    WINUSB_TUSB_INIT_EP_OTG_FS(dev); \
    WINUSB_TUSB_INIT_EP_OTG_HS(dev); \
  }while(0)


#if defined(USB)
#define WINUSB_TUSB_INIT_EP(dev) WINUSB_TUSB_INIT_EP_FS(dev)

// Teeny USB device init function for FS core
#define WINUSB_TUSB_INIT_DEVICE(dev) \
  do{\
    /* Init device features */       \
    memset(&dev->addr, 0, TUSB_DEVICE_SIZE);    \
    dev->status = WINUSB_DEV_STATUS;         \
    dev->rx_max_size = WINUSB_rxEpMaxSize;         \
    dev->tx_max_size = WINUSB_txEpMaxSize;         \
    dev->descriptors = &WINUSB_descriptors;         \
  }while(0)

#endif

#if defined(USB_OTG_FS) || defined(USB_OTG_HS)
#define WINUSB_TUSB_INIT_EP(dev) WINUSB_TUSB_INIT_EP_OTG(dev)

// Teeny USB device init function for OTG core
#define WINUSB_TUSB_INIT_DEVICE(dev) \
  do{\
    /* Init device features */       \
    memset(&dev->addr, 0, TUSB_DEVICE_SIZE);    \
    dev->status = WINUSB_DEV_STATUS;         \
    dev->descriptors = &WINUSB_descriptors;         \
  }while(0)

#endif

#define WINUSB_TUSB_INIT(dev) \
  do{\
    WINUSB_TUSB_INIT_EP(dev);   \
    WINUSB_TUSB_INIT_DEVICE(dev);   \
  }while(0)

// Get End Point count
#ifndef  EP_NUM
#define  EP_NUM 1
#endif
#if WINUSB_EP_NUM > EP_NUM
#undef   EP_NUM
#define  EP_NUM  WINUSB_EP_NUM
#endif

extern const uint8_t* const WINUSB_StringDescriptors[WINUSB_STRING_COUNT];
extern const tusb_descriptors WINUSB_descriptors;

// Enable WCID related code
#define  HAS_WCID

#ifndef WCID_VENDOR_CODE
#define  WCID_VENDOR_CODE       0x17
extern const uint8_t WCID_StringDescriptor_MSOS[];
#endif


#endif   // #ifndef __WINUSB_TEENY_USB_INIT_H__
/////////////////////////////////////////
//// Device 5
/////////////////////////////////////////
#ifndef __WINUSB20_TEENY_USB_INIT_H__
#define __WINUSB20_TEENY_USB_INIT_H__
// forward declare the tusb_descriptors struct
typedef struct _tusb_descriptors tusb_descriptors;

#define WINUSB20_VID                                            0x0483
#define WINUSB20_PID                                            0x0011
#define WINUSB20_STRING_COUNT                                   (6)

// device.bmAttributes & 0x40   USB_CONFIG_SELF_POWERED
// device.bmAttributes & 0x20   USB_CONFIG_REMOTE_WAKEUP
#define WINUSB20_DEV_STATUS                                    (0 | 0)


// Endpoint usage:
#define WINUSB20_MAX_EP                                         (3)
#define WINUSB20_EP_NUM                                         (WINUSB20_MAX_EP + 1)

///////////////////////////////////////////////
//// Endpoint define for STM32 FS Core
///////////////////////////////////////////////

#ifdef WINUSB20_BTABLE_ADDRESS
#undef WINUSB20_BTABLE_ADDRESS
#endif
#define WINUSB20_BTABLE_ADDRESS                                 (0)
#define WINUSB20_EP_BUF_DESC_TABLE_SIZE                         (8)
// PMA buffer reserved for buffer description table
#define WINUSB20_USB_BUF_START                                  (WINUSB20_EP_BUF_DESC_TABLE_SIZE * WINUSB20_EP_NUM)

// EndPoints 0 defines
#define WINUSB20_EP0_RX_SIZE                                    (64)
#define WINUSB20_EP0_RX_ADDR                                    (WINUSB20_USB_BUF_START + (0))
#define WINUSB20_EP0_TX_SIZE                                    (64)
#define WINUSB20_EP0_TX_ADDR                                    (WINUSB20_USB_BUF_START + (64))
#define WINUSB20_EP0_RX_TYPE                                    USB_EP_CONTROL
#define WINUSB20_EP0_TX_TYPE                                    USB_EP_CONTROL

#define WINUSB20_EP0_TYPE                                       USB_EP_CONTROL
#define WINUSB20_EP0_TX0_ADDR                                   (WINUSB20_USB_BUF_START + (0))
#define WINUSB20_EP0_TX1_ADDR                                   (WINUSB20_USB_BUF_START + (64))
#define WINUSB20_EP0_RX0_ADDR                                   (WINUSB20_USB_BUF_START + (0))
#define WINUSB20_EP0_RX1_ADDR                                   (WINUSB20_USB_BUF_START + (64))

// EndPoints 1 defines
#define WINUSB20_EP1_RX_SIZE                                    (32)
#define WINUSB20_EP1_RX_ADDR                                    (WINUSB20_USB_BUF_START + (128))
#define WINUSB20_EP1_TX_SIZE                                    (32)
#define WINUSB20_EP1_TX_ADDR                                    (WINUSB20_USB_BUF_START + (160))
#define WINUSB20_EP1_RX_TYPE                                    USB_EP_BULK
#define WINUSB20_EP1_TX_TYPE                                    USB_EP_BULK

#define WINUSB20_EP1_TYPE                                       USB_EP_BULK
#define WINUSB20_EP1_TX0_ADDR                                   (WINUSB20_USB_BUF_START + (128))
#define WINUSB20_EP1_TX1_ADDR                                   (WINUSB20_USB_BUF_START + (160))
#define WINUSB20_EP1_RX0_ADDR                                   (WINUSB20_USB_BUF_START + (128))
#define WINUSB20_EP1_RX1_ADDR                                   (WINUSB20_USB_BUF_START + (160))

// EndPoints 2 defines
#define WINUSB20_EP2_RX_SIZE                                    (32)
#define WINUSB20_EP2_RX_ADDR                                    (WINUSB20_USB_BUF_START + (192))
#define WINUSB20_EP2_TX_SIZE                                    (32)
#define WINUSB20_EP2_TX_ADDR                                    (WINUSB20_USB_BUF_START + (224))
#define WINUSB20_EP2_RX_TYPE                                    USB_EP_BULK
#define WINUSB20_EP2_TX_TYPE                                    USB_EP_BULK

#define WINUSB20_EP2_TYPE                                       USB_EP_BULK
#define WINUSB20_EP2_TX0_ADDR                                   (WINUSB20_USB_BUF_START + (192))
#define WINUSB20_EP2_TX1_ADDR                                   (WINUSB20_USB_BUF_START + (224))
#define WINUSB20_EP2_RX0_ADDR                                   (WINUSB20_USB_BUF_START + (192))
#define WINUSB20_EP2_RX1_ADDR                                   (WINUSB20_USB_BUF_START + (224))

// EndPoints 3 defines
#define WINUSB20_EP3_RX_SIZE                                    (32)
#define WINUSB20_EP3_RX_ADDR                                    (WINUSB20_USB_BUF_START + (256))
#define WINUSB20_EP3_TX_SIZE                                    (32)
#define WINUSB20_EP3_TX_ADDR                                    (WINUSB20_USB_BUF_START + (288))
#define WINUSB20_EP3_RX_TYPE                                    USB_EP_BULK
#define WINUSB20_EP3_TX_TYPE                                    USB_EP_BULK

#define WINUSB20_EP3_TYPE                                       USB_EP_BULK
#define WINUSB20_EP3_TX0_ADDR                                   (WINUSB20_USB_BUF_START + (256))
#define WINUSB20_EP3_TX1_ADDR                                   (WINUSB20_USB_BUF_START + (288))
#define WINUSB20_EP3_RX0_ADDR                                   (WINUSB20_USB_BUF_START + (256))
#define WINUSB20_EP3_RX1_ADDR                                   (WINUSB20_USB_BUF_START + (288))


// EndPoint max packed sizes
extern const uint8_t WINUSB20_txEpMaxSize[];
#define WINUSB20_TXEP_MAX_SIZE                                  \
const uint8_t WINUSB20_txEpMaxSize[] = \
{ WINUSB20_EP0_TX_SIZE, WINUSB20_EP1_TX_SIZE, WINUSB20_EP2_TX_SIZE, WINUSB20_EP3_TX_SIZE,  };
extern const uint8_t WINUSB20_rxEpMaxSize[];
#define WINUSB20_RXEP_MAX_SIZE                                  \
const uint8_t WINUSB20_rxEpMaxSize[] = \
{ WINUSB20_EP0_RX_SIZE, WINUSB20_EP1_RX_SIZE, WINUSB20_EP2_RX_SIZE, WINUSB20_EP3_RX_SIZE,  };

// EndPoints init function for USB FS core
#define WINUSB20_TUSB_INIT_EP_FS(dev) \
  do{\
    /* Init ep0 */ \
    INIT_EP_BiDirection(dev, PCD_ENDP0, WINUSB20_EP0_TYPE);  \
    SET_TX_ADDR(dev, PCD_ENDP0, WINUSB20_EP0_TX_ADDR);  \
    SET_RX_ADDR(dev, PCD_ENDP0, WINUSB20_EP0_RX_ADDR);  \
    SET_RX_CNT(dev, PCD_ENDP0, WINUSB20_EP0_RX_SIZE);  \
    /* Init ep1 */ \
    INIT_EP_BiDirection(dev, PCD_ENDP1, WINUSB20_EP1_TYPE);  \
    SET_TX_ADDR(dev, PCD_ENDP1, WINUSB20_EP1_TX_ADDR);  \
    SET_RX_ADDR(dev, PCD_ENDP1, WINUSB20_EP1_RX_ADDR);  \
    SET_RX_CNT(dev, PCD_ENDP1, WINUSB20_EP1_RX_SIZE);  \
    /* Init ep2 */ \
    INIT_EP_BiDirection(dev, PCD_ENDP2, WINUSB20_EP2_TYPE);  \
    SET_TX_ADDR(dev, PCD_ENDP2, WINUSB20_EP2_TX_ADDR);  \
    SET_RX_ADDR(dev, PCD_ENDP2, WINUSB20_EP2_RX_ADDR);  \
    SET_RX_CNT(dev, PCD_ENDP2, WINUSB20_EP2_RX_SIZE);  \
    /* Init ep3 */ \
    INIT_EP_BiDirection(dev, PCD_ENDP3, WINUSB20_EP3_TYPE);  \
    SET_TX_ADDR(dev, PCD_ENDP3, WINUSB20_EP3_TX_ADDR);  \
    SET_RX_ADDR(dev, PCD_ENDP3, WINUSB20_EP3_RX_ADDR);  \
    SET_RX_CNT(dev, PCD_ENDP3, WINUSB20_EP3_RX_SIZE);  \
}while(0)

///////////////////////////////////////////////
//// Endpoint define for STM32 OTG Core
///////////////////////////////////////////////
#define WINUSB20_OTG_MAX_OUT_SIZE                               (32)
#define WINUSB20_OTG_CONTROL_EP_NUM                             (1)
#define WINUSB20_OTG_OUT_EP_NUM                                 (3)
// RX FIFO size / 4 > (CONTROL_EP_NUM * 5 + 8) +  (MAX_OUT_SIZE / 4 + 1) + (OUT_EP_NUM*2) + 1 = 29

///////////////////////////////////////////////
//// Endpoint define for STM32 OTG FS Core
///////////////////////////////////////////////
#define WINUSB20_OTG_RX_FIFO_SIZE_FS                            (256)
#define WINUSB20_OTG_RX_FIFO_ADDR_FS                            (0)
// Sum of IN ep max packet size is 160
// Remain Fifo size is 1024 in bytes, Rx Used 256 bytes 

// TODO:
// I don't know why the max count of TX fifo should <= (7 * EpMaxPacket)
// But it seems the STM32F7xx can be large than (7 * EpMaxPacket)
#define WINUSB20_EP0_TX_FIFO_ADDR_FS                            (256)
#define WINUSB20_EP0_TX_FIFO_SIZE_FS                            (WINUSB20_EP0_TX_SIZE * 6)
#define WINUSB20_EP1_TX_FIFO_ADDR_FS                            (640)
#define WINUSB20_EP1_TX_FIFO_SIZE_FS                            (WINUSB20_EP1_TX_SIZE * 6)
#define WINUSB20_EP2_TX_FIFO_ADDR_FS                            (832)
#define WINUSB20_EP2_TX_FIFO_SIZE_FS                            (WINUSB20_EP2_TX_SIZE * 6)
#define WINUSB20_EP3_TX_FIFO_ADDR_FS                            (1024)
#define WINUSB20_EP3_TX_FIFO_SIZE_FS                            (WINUSB20_EP3_TX_SIZE * 6)
// EndPoints init function for USB OTG core
#if defined(USB_OTG_FS)
#define WINUSB20_TUSB_INIT_EP_OTG_FS(dev) \
  do{\
    if(GetUSB(dev) == USB_OTG_FS) { \
      SET_RX_FIFO(dev, WINUSB20_OTG_RX_FIFO_ADDR_FS, WINUSB20_OTG_RX_FIFO_SIZE_FS);  \
      /* Init Ep0  */\
      INIT_EP_Tx(dev, PCD_ENDP0, WINUSB20_EP0_TX_TYPE, WINUSB20_EP0_TX_SIZE);  \
      SET_TX_FIFO(dev, PCD_ENDP0, WINUSB20_EP0_TX_FIFO_ADDR_FS, WINUSB20_EP0_TX_FIFO_SIZE_FS);  \
      INIT_EP_Rx(dev, PCD_ENDP0, WINUSB20_EP0_RX_TYPE, WINUSB20_EP0_RX_SIZE); \
      /* Init Ep1  */\
      INIT_EP_Tx(dev, PCD_ENDP1, WINUSB20_EP1_TX_TYPE, WINUSB20_EP1_TX_SIZE);  \
      SET_TX_FIFO(dev, PCD_ENDP1, WINUSB20_EP1_TX_FIFO_ADDR_FS, WINUSB20_EP1_TX_FIFO_SIZE_FS);  \
      INIT_EP_Rx(dev, PCD_ENDP1, WINUSB20_EP1_RX_TYPE, WINUSB20_EP1_RX_SIZE); \
      /* Init Ep2  */\
      INIT_EP_Tx(dev, PCD_ENDP2, WINUSB20_EP2_TX_TYPE, WINUSB20_EP2_TX_SIZE);  \
      SET_TX_FIFO(dev, PCD_ENDP2, WINUSB20_EP2_TX_FIFO_ADDR_FS, WINUSB20_EP2_TX_FIFO_SIZE_FS);  \
      INIT_EP_Rx(dev, PCD_ENDP2, WINUSB20_EP2_RX_TYPE, WINUSB20_EP2_RX_SIZE); \
      /* Init Ep3  */\
      INIT_EP_Tx(dev, PCD_ENDP3, WINUSB20_EP3_TX_TYPE, WINUSB20_EP3_TX_SIZE);  \
      SET_TX_FIFO(dev, PCD_ENDP3, WINUSB20_EP3_TX_FIFO_ADDR_FS, WINUSB20_EP3_TX_FIFO_SIZE_FS);  \
      INIT_EP_Rx(dev, PCD_ENDP3, WINUSB20_EP3_RX_TYPE, WINUSB20_EP3_RX_SIZE); \
    }\
  }while(0)

#else  // #if defined(USB_OTG_FS)
#define WINUSB20_TUSB_INIT_EP_OTG_FS(dev) 
    
#endif  // #if defined(USB_OTG_FS)

///////////////////////////////////////////////
//// Endpoint define for STM32 OTG HS Core
///////////////////////////////////////////////
#define WINUSB20_OTG_RX_FIFO_SIZE_HS                            (512)
#define WINUSB20_OTG_RX_FIFO_ADDR_HS                            (0)
// Sum of IN ep max packet size is 160
// Remain Fifo size is 3584 in bytes, Rx Used 512 bytes 

// TODO:
// I don't know why the max count of TX fifo should <= (7 * EpMaxPacket)
// But it seems the STM32F7xx can be large than (7 * EpMaxPacket)
#define WINUSB20_EP0_TX_FIFO_ADDR_HS                            (512)
#define WINUSB20_EP0_TX_FIFO_SIZE_HS                            (WINUSB20_EP0_TX_SIZE * 7)
#define WINUSB20_EP1_TX_FIFO_ADDR_HS                            (960)
#define WINUSB20_EP1_TX_FIFO_SIZE_HS                            (WINUSB20_EP1_TX_SIZE * 7)
#define WINUSB20_EP2_TX_FIFO_ADDR_HS                            (1184)
#define WINUSB20_EP2_TX_FIFO_SIZE_HS                            (WINUSB20_EP2_TX_SIZE * 7)
#define WINUSB20_EP3_TX_FIFO_ADDR_HS                            (1408)
#define WINUSB20_EP3_TX_FIFO_SIZE_HS                            (WINUSB20_EP3_TX_SIZE * 7)
// EndPoints init function for USB OTG core
#if defined(USB_OTG_HS)
#define WINUSB20_TUSB_INIT_EP_OTG_HS(dev) \
  do{\
    if(GetUSB(dev) == USB_OTG_HS) { \
      SET_RX_FIFO(dev, WINUSB20_OTG_RX_FIFO_ADDR_HS, WINUSB20_OTG_RX_FIFO_SIZE_HS);  \
      /* Init Ep0  */\
      INIT_EP_Tx(dev, PCD_ENDP0, WINUSB20_EP0_TX_TYPE, WINUSB20_EP0_TX_SIZE);  \
      SET_TX_FIFO(dev, PCD_ENDP0, WINUSB20_EP0_TX_FIFO_ADDR_HS, WINUSB20_EP0_TX_FIFO_SIZE_HS);  \
      INIT_EP_Rx(dev, PCD_ENDP0, WINUSB20_EP0_RX_TYPE, WINUSB20_EP0_RX_SIZE); \
      /* Init Ep1  */\
      INIT_EP_Tx(dev, PCD_ENDP1, WINUSB20_EP1_TX_TYPE, WINUSB20_EP1_TX_SIZE);  \
      SET_TX_FIFO(dev, PCD_ENDP1, WINUSB20_EP1_TX_FIFO_ADDR_HS, WINUSB20_EP1_TX_FIFO_SIZE_HS);  \
      INIT_EP_Rx(dev, PCD_ENDP1, WINUSB20_EP1_RX_TYPE, WINUSB20_EP1_RX_SIZE); \
      /* Init Ep2  */\
      INIT_EP_Tx(dev, PCD_ENDP2, WINUSB20_EP2_TX_TYPE, WINUSB20_EP2_TX_SIZE);  \
      SET_TX_FIFO(dev, PCD_ENDP2, WINUSB20_EP2_TX_FIFO_ADDR_HS, WINUSB20_EP2_TX_FIFO_SIZE_HS);  \
      INIT_EP_Rx(dev, PCD_ENDP2, WINUSB20_EP2_RX_TYPE, WINUSB20_EP2_RX_SIZE); \
      /* Init Ep3  */\
      INIT_EP_Tx(dev, PCD_ENDP3, WINUSB20_EP3_TX_TYPE, WINUSB20_EP3_TX_SIZE);  \
      SET_TX_FIFO(dev, PCD_ENDP3, WINUSB20_EP3_TX_FIFO_ADDR_HS, WINUSB20_EP3_TX_FIFO_SIZE_HS);  \
      INIT_EP_Rx(dev, PCD_ENDP3, WINUSB20_EP3_RX_TYPE, WINUSB20_EP3_RX_SIZE); \
    }\
  }while(0)

#else  // #if defined(USB_OTG_HS)
#define WINUSB20_TUSB_INIT_EP_OTG_HS(dev) 
    
#endif  // #if defined(USB_OTG_HS)
#define WINUSB20_TUSB_INIT_EP_OTG(dev) \
  do{\
    WINUSB20_TUSB_INIT_EP_OTG_FS(dev); \
    WINUSB20_TUSB_INIT_EP_OTG_HS(dev); \
  }while(0)


#if defined(USB)
#define WINUSB20_TUSB_INIT_EP(dev) WINUSB20_TUSB_INIT_EP_FS(dev)

// Teeny USB device init function for FS core
#define WINUSB20_TUSB_INIT_DEVICE(dev) \
  do{\
    /* Init device features */       \
    memset(&dev->addr, 0, TUSB_DEVICE_SIZE);    \
    dev->status = WINUSB20_DEV_STATUS;         \
    dev->rx_max_size = WINUSB20_rxEpMaxSize;         \
    dev->tx_max_size = WINUSB20_txEpMaxSize;         \
    dev->descriptors = &WINUSB20_descriptors;         \
  }while(0)

#endif

#if defined(USB_OTG_FS) || defined(USB_OTG_HS)
#define WINUSB20_TUSB_INIT_EP(dev) WINUSB20_TUSB_INIT_EP_OTG(dev)

// Teeny USB device init function for OTG core
#define WINUSB20_TUSB_INIT_DEVICE(dev) \
  do{\
    /* Init device features */       \
    memset(&dev->addr, 0, TUSB_DEVICE_SIZE);    \
    dev->status = WINUSB20_DEV_STATUS;         \
    dev->descriptors = &WINUSB20_descriptors;         \
  }while(0)

#endif

#define WINUSB20_TUSB_INIT(dev) \
  do{\
    WINUSB20_TUSB_INIT_EP(dev);   \
    WINUSB20_TUSB_INIT_DEVICE(dev);   \
  }while(0)

// Get End Point count
#ifndef  EP_NUM
#define  EP_NUM 1
#endif
#if WINUSB20_EP_NUM > EP_NUM
#undef   EP_NUM
#define  EP_NUM  WINUSB20_EP_NUM
#endif

extern const uint8_t* const WINUSB20_StringDescriptors[WINUSB20_STRING_COUNT];
extern const tusb_descriptors WINUSB20_descriptors;

// Enable WCID related code
#define  HAS_WCID_20

#ifndef WCID_VENDOR_CODE
#define  WCID_VENDOR_CODE       0x17
extern const uint8_t WCID_StringDescriptor_MSOS[];
#endif


#endif   // #ifndef __WINUSB20_TEENY_USB_INIT_H__
/////////////////////////////////////////
//// Device 6
/////////////////////////////////////////
#ifndef __USER_HID_TEENY_USB_INIT_H__
#define __USER_HID_TEENY_USB_INIT_H__
// forward declare the tusb_descriptors struct
typedef struct _tusb_descriptors tusb_descriptors;

#define USER_HID_VID                                            0x0483
#define USER_HID_PID                                            0x0011
#define USER_HID_STRING_COUNT                                   (4)

// device.bmAttributes & 0x40   USB_CONFIG_SELF_POWERED
// device.bmAttributes & 0x20   USB_CONFIG_REMOTE_WAKEUP
#define USER_HID_DEV_STATUS                                    (0 | 0)


// Endpoint usage:
#define USER_HID_MAX_EP                                         (1)
#define USER_HID_EP_NUM                                         (USER_HID_MAX_EP + 1)

///////////////////////////////////////////////
//// Endpoint define for STM32 FS Core
///////////////////////////////////////////////

#ifdef USER_HID_BTABLE_ADDRESS
#undef USER_HID_BTABLE_ADDRESS
#endif
#define USER_HID_BTABLE_ADDRESS                                 (0)
#define USER_HID_EP_BUF_DESC_TABLE_SIZE                         (8)
// PMA buffer reserved for buffer description table
#define USER_HID_USB_BUF_START                                  (USER_HID_EP_BUF_DESC_TABLE_SIZE * USER_HID_EP_NUM)

// EndPoints 0 defines
#define USER_HID_EP0_RX_SIZE                                    (64)
#define USER_HID_EP0_RX_ADDR                                    (USER_HID_USB_BUF_START + (0))
#define USER_HID_EP0_TX_SIZE                                    (64)
#define USER_HID_EP0_TX_ADDR                                    (USER_HID_USB_BUF_START + (64))
#define USER_HID_EP0_RX_TYPE                                    USB_EP_CONTROL
#define USER_HID_EP0_TX_TYPE                                    USB_EP_CONTROL

#define USER_HID_EP0_TYPE                                       USB_EP_CONTROL
#define USER_HID_EP0_TX0_ADDR                                   (USER_HID_USB_BUF_START + (0))
#define USER_HID_EP0_TX1_ADDR                                   (USER_HID_USB_BUF_START + (64))
#define USER_HID_EP0_RX0_ADDR                                   (USER_HID_USB_BUF_START + (0))
#define USER_HID_EP0_RX1_ADDR                                   (USER_HID_USB_BUF_START + (64))

// EndPoints 1 defines
#define USER_HID_EP1_RX_SIZE                                    (64)
#define USER_HID_EP1_RX_ADDR                                    (USER_HID_USB_BUF_START + (128))
#define USER_HID_EP1_TX_SIZE                                    (64)
#define USER_HID_EP1_TX_ADDR                                    (USER_HID_USB_BUF_START + (192))
#define USER_HID_EP1_RX_TYPE                                    USB_EP_INTERRUPT
#define USER_HID_EP1_TX_TYPE                                    USB_EP_INTERRUPT

#define USER_HID_EP1_TYPE                                       USB_EP_INTERRUPT
#define USER_HID_EP1_TX0_ADDR                                   (USER_HID_USB_BUF_START + (128))
#define USER_HID_EP1_TX1_ADDR                                   (USER_HID_USB_BUF_START + (192))
#define USER_HID_EP1_RX0_ADDR                                   (USER_HID_USB_BUF_START + (128))
#define USER_HID_EP1_RX1_ADDR                                   (USER_HID_USB_BUF_START + (192))


// EndPoint max packed sizes
extern const uint8_t USER_HID_txEpMaxSize[];
#define USER_HID_TXEP_MAX_SIZE                                  \
const uint8_t USER_HID_txEpMaxSize[] = \
{ USER_HID_EP0_TX_SIZE, USER_HID_EP1_TX_SIZE,  };
extern const uint8_t USER_HID_rxEpMaxSize[];
#define USER_HID_RXEP_MAX_SIZE                                  \
const uint8_t USER_HID_rxEpMaxSize[] = \
{ USER_HID_EP0_RX_SIZE, USER_HID_EP1_RX_SIZE,  };

// EndPoints init function for USB FS core
#define USER_HID_TUSB_INIT_EP_FS(dev) \
  do{\
    /* Init ep0 */ \
    INIT_EP_BiDirection(dev, PCD_ENDP0, USER_HID_EP0_TYPE);  \
    SET_TX_ADDR(dev, PCD_ENDP0, USER_HID_EP0_TX_ADDR);  \
    SET_RX_ADDR(dev, PCD_ENDP0, USER_HID_EP0_RX_ADDR);  \
    SET_RX_CNT(dev, PCD_ENDP0, USER_HID_EP0_RX_SIZE);  \
    /* Init ep1 */ \
    INIT_EP_BiDirection(dev, PCD_ENDP1, USER_HID_EP1_TYPE);  \
    SET_TX_ADDR(dev, PCD_ENDP1, USER_HID_EP1_TX_ADDR);  \
    SET_RX_ADDR(dev, PCD_ENDP1, USER_HID_EP1_RX_ADDR);  \
    SET_RX_CNT(dev, PCD_ENDP1, USER_HID_EP1_RX_SIZE);  \
}while(0)

///////////////////////////////////////////////
//// Endpoint define for STM32 OTG Core
///////////////////////////////////////////////
#define USER_HID_OTG_MAX_OUT_SIZE                               (64)
#define USER_HID_OTG_CONTROL_EP_NUM                             (1)
#define USER_HID_OTG_OUT_EP_NUM                                 (1)
// RX FIFO size / 4 > (CONTROL_EP_NUM * 5 + 8) +  (MAX_OUT_SIZE / 4 + 1) + (OUT_EP_NUM*2) + 1 = 33

///////////////////////////////////////////////
//// Endpoint define for STM32 OTG FS Core
///////////////////////////////////////////////
#define USER_HID_OTG_RX_FIFO_SIZE_FS                            (256)
#define USER_HID_OTG_RX_FIFO_ADDR_FS                            (0)
// Sum of IN ep max packet size is 128
// Remain Fifo size is 1024 in bytes, Rx Used 256 bytes 

// TODO:
// I don't know why the max count of TX fifo should <= (7 * EpMaxPacket)
// But it seems the STM32F7xx can be large than (7 * EpMaxPacket)
#define USER_HID_EP0_TX_FIFO_ADDR_FS                            (256)
#define USER_HID_EP0_TX_FIFO_SIZE_FS                            (USER_HID_EP0_TX_SIZE * 7)
#define USER_HID_EP1_TX_FIFO_ADDR_FS                            (704)
#define USER_HID_EP1_TX_FIFO_SIZE_FS                            (USER_HID_EP1_TX_SIZE * 7)
// EndPoints init function for USB OTG core
#if defined(USB_OTG_FS)
#define USER_HID_TUSB_INIT_EP_OTG_FS(dev) \
  do{\
    if(GetUSB(dev) == USB_OTG_FS) { \
      SET_RX_FIFO(dev, USER_HID_OTG_RX_FIFO_ADDR_FS, USER_HID_OTG_RX_FIFO_SIZE_FS);  \
      /* Init Ep0  */\
      INIT_EP_Tx(dev, PCD_ENDP0, USER_HID_EP0_TX_TYPE, USER_HID_EP0_TX_SIZE);  \
      SET_TX_FIFO(dev, PCD_ENDP0, USER_HID_EP0_TX_FIFO_ADDR_FS, USER_HID_EP0_TX_FIFO_SIZE_FS);  \
      INIT_EP_Rx(dev, PCD_ENDP0, USER_HID_EP0_RX_TYPE, USER_HID_EP0_RX_SIZE); \
      /* Init Ep1  */\
      INIT_EP_Tx(dev, PCD_ENDP1, USER_HID_EP1_TX_TYPE, USER_HID_EP1_TX_SIZE);  \
      SET_TX_FIFO(dev, PCD_ENDP1, USER_HID_EP1_TX_FIFO_ADDR_FS, USER_HID_EP1_TX_FIFO_SIZE_FS);  \
      INIT_EP_Rx(dev, PCD_ENDP1, USER_HID_EP1_RX_TYPE, USER_HID_EP1_RX_SIZE); \
    }\
  }while(0)

#else  // #if defined(USB_OTG_FS)
#define USER_HID_TUSB_INIT_EP_OTG_FS(dev) 
    
#endif  // #if defined(USB_OTG_FS)

///////////////////////////////////////////////
//// Endpoint define for STM32 OTG HS Core
///////////////////////////////////////////////
#define USER_HID_OTG_RX_FIFO_SIZE_HS                            (512)
#define USER_HID_OTG_RX_FIFO_ADDR_HS                            (0)
// Sum of IN ep max packet size is 128
// Remain Fifo size is 3584 in bytes, Rx Used 512 bytes 

// TODO:
// I don't know why the max count of TX fifo should <= (7 * EpMaxPacket)
// But it seems the STM32F7xx can be large than (7 * EpMaxPacket)
#define USER_HID_EP0_TX_FIFO_ADDR_HS                            (512)
#define USER_HID_EP0_TX_FIFO_SIZE_HS                            (USER_HID_EP0_TX_SIZE * 7)
#define USER_HID_EP1_TX_FIFO_ADDR_HS                            (960)
#define USER_HID_EP1_TX_FIFO_SIZE_HS                            (USER_HID_EP1_TX_SIZE * 7)
// EndPoints init function for USB OTG core
#if defined(USB_OTG_HS)
#define USER_HID_TUSB_INIT_EP_OTG_HS(dev) \
  do{\
    if(GetUSB(dev) == USB_OTG_HS) { \
      SET_RX_FIFO(dev, USER_HID_OTG_RX_FIFO_ADDR_HS, USER_HID_OTG_RX_FIFO_SIZE_HS);  \
      /* Init Ep0  */\
      INIT_EP_Tx(dev, PCD_ENDP0, USER_HID_EP0_TX_TYPE, USER_HID_EP0_TX_SIZE);  \
      SET_TX_FIFO(dev, PCD_ENDP0, USER_HID_EP0_TX_FIFO_ADDR_HS, USER_HID_EP0_TX_FIFO_SIZE_HS);  \
      INIT_EP_Rx(dev, PCD_ENDP0, USER_HID_EP0_RX_TYPE, USER_HID_EP0_RX_SIZE); \
      /* Init Ep1  */\
      INIT_EP_Tx(dev, PCD_ENDP1, USER_HID_EP1_TX_TYPE, USER_HID_EP1_TX_SIZE);  \
      SET_TX_FIFO(dev, PCD_ENDP1, USER_HID_EP1_TX_FIFO_ADDR_HS, USER_HID_EP1_TX_FIFO_SIZE_HS);  \
      INIT_EP_Rx(dev, PCD_ENDP1, USER_HID_EP1_RX_TYPE, USER_HID_EP1_RX_SIZE); \
    }\
  }while(0)

#else  // #if defined(USB_OTG_HS)
#define USER_HID_TUSB_INIT_EP_OTG_HS(dev) 
    
#endif  // #if defined(USB_OTG_HS)
#define USER_HID_TUSB_INIT_EP_OTG(dev) \
  do{\
    USER_HID_TUSB_INIT_EP_OTG_FS(dev); \
    USER_HID_TUSB_INIT_EP_OTG_HS(dev); \
  }while(0)


#if defined(USB)
#define USER_HID_TUSB_INIT_EP(dev) USER_HID_TUSB_INIT_EP_FS(dev)

// Teeny USB device init function for FS core
#define USER_HID_TUSB_INIT_DEVICE(dev) \
  do{\
    /* Init device features */       \
    memset(&dev->addr, 0, TUSB_DEVICE_SIZE);    \
    dev->status = USER_HID_DEV_STATUS;         \
    dev->rx_max_size = USER_HID_rxEpMaxSize;         \
    dev->tx_max_size = USER_HID_txEpMaxSize;         \
    dev->descriptors = &USER_HID_descriptors;         \
  }while(0)

#endif

#if defined(USB_OTG_FS) || defined(USB_OTG_HS)
#define USER_HID_TUSB_INIT_EP(dev) USER_HID_TUSB_INIT_EP_OTG(dev)

// Teeny USB device init function for OTG core
#define USER_HID_TUSB_INIT_DEVICE(dev) \
  do{\
    /* Init device features */       \
    memset(&dev->addr, 0, TUSB_DEVICE_SIZE);    \
    dev->status = USER_HID_DEV_STATUS;         \
    dev->descriptors = &USER_HID_descriptors;         \
  }while(0)

#endif

#define USER_HID_TUSB_INIT(dev) \
  do{\
    USER_HID_TUSB_INIT_EP(dev);   \
    USER_HID_TUSB_INIT_DEVICE(dev);   \
  }while(0)

// Get End Point count
#ifndef  EP_NUM
#define  EP_NUM 1
#endif
#if USER_HID_EP_NUM > EP_NUM
#undef   EP_NUM
#define  EP_NUM  USER_HID_EP_NUM
#endif

extern const uint8_t* const USER_HID_StringDescriptors[USER_HID_STRING_COUNT];
extern const tusb_descriptors USER_HID_descriptors;

#define USER_HID_REPORT_DESCRIPTOR_SIZE_IF0  (24)
extern const uint8_t USER_HID_ReportDescriptor_if0[USER_HID_REPORT_DESCRIPTOR_SIZE_IF0];


#endif   // #ifndef __USER_HID_TEENY_USB_INIT_H__
/////////////////////////////////////////
//// Device 7
/////////////////////////////////////////
#ifndef __KB_TEENY_USB_INIT_H__
#define __KB_TEENY_USB_INIT_H__
// forward declare the tusb_descriptors struct
typedef struct _tusb_descriptors tusb_descriptors;

#define KB_VID                                            0x0483
#define KB_PID                                            0x0011
#define KB_STRING_COUNT                                   (4)

// device.bmAttributes & 0x40   USB_CONFIG_SELF_POWERED
// device.bmAttributes & 0x20   USB_CONFIG_REMOTE_WAKEUP
#define KB_DEV_STATUS                                    (0 | 0)


// Endpoint usage:
#define KB_MAX_EP                                         (1)
#define KB_EP_NUM                                         (KB_MAX_EP + 1)

///////////////////////////////////////////////
//// Endpoint define for STM32 FS Core
///////////////////////////////////////////////

#ifdef KB_BTABLE_ADDRESS
#undef KB_BTABLE_ADDRESS
#endif
#define KB_BTABLE_ADDRESS                                 (0)
#define KB_EP_BUF_DESC_TABLE_SIZE                         (8)
// PMA buffer reserved for buffer description table
#define KB_USB_BUF_START                                  (KB_EP_BUF_DESC_TABLE_SIZE * KB_EP_NUM)

// EndPoints 0 defines
#define KB_EP0_RX_SIZE                                    (64)
#define KB_EP0_RX_ADDR                                    (KB_USB_BUF_START + (0))
#define KB_EP0_TX_SIZE                                    (64)
#define KB_EP0_TX_ADDR                                    (KB_USB_BUF_START + (64))
#define KB_EP0_RX_TYPE                                    USB_EP_CONTROL
#define KB_EP0_TX_TYPE                                    USB_EP_CONTROL

#define KB_EP0_TYPE                                       USB_EP_CONTROL
#define KB_EP0_TX0_ADDR                                   (KB_USB_BUF_START + (0))
#define KB_EP0_TX1_ADDR                                   (KB_USB_BUF_START + (64))
#define KB_EP0_RX0_ADDR                                   (KB_USB_BUF_START + (0))
#define KB_EP0_RX1_ADDR                                   (KB_USB_BUF_START + (64))

// EndPoints 1 defines
#define KB_EP1_RX_SIZE                                    (8)
#define KB_EP1_RX_ADDR                                    (KB_USB_BUF_START + (128))
#define KB_EP1_TX_SIZE                                    (8)
#define KB_EP1_TX_ADDR                                    (KB_USB_BUF_START + (136))
#define KB_EP1_RX_TYPE                                    USB_EP_INTERRUPT
#define KB_EP1_TX_TYPE                                    USB_EP_INTERRUPT

#define KB_EP1_TYPE                                       USB_EP_INTERRUPT
#define KB_EP1_TX0_ADDR                                   (KB_USB_BUF_START + (128))
#define KB_EP1_TX1_ADDR                                   (KB_USB_BUF_START + (136))
#define KB_EP1_RX0_ADDR                                   (KB_USB_BUF_START + (128))
#define KB_EP1_RX1_ADDR                                   (KB_USB_BUF_START + (136))


// EndPoint max packed sizes
extern const uint8_t KB_txEpMaxSize[];
#define KB_TXEP_MAX_SIZE                                  \
const uint8_t KB_txEpMaxSize[] = \
{ KB_EP0_TX_SIZE, KB_EP1_TX_SIZE,  };
extern const uint8_t KB_rxEpMaxSize[];
#define KB_RXEP_MAX_SIZE                                  \
const uint8_t KB_rxEpMaxSize[] = \
{ KB_EP0_RX_SIZE, KB_EP1_RX_SIZE,  };

// EndPoints init function for USB FS core
#define KB_TUSB_INIT_EP_FS(dev) \
  do{\
    /* Init ep0 */ \
    INIT_EP_BiDirection(dev, PCD_ENDP0, KB_EP0_TYPE);  \
    SET_TX_ADDR(dev, PCD_ENDP0, KB_EP0_TX_ADDR);  \
    SET_RX_ADDR(dev, PCD_ENDP0, KB_EP0_RX_ADDR);  \
    SET_RX_CNT(dev, PCD_ENDP0, KB_EP0_RX_SIZE);  \
    /* Init ep1 */ \
    INIT_EP_BiDirection(dev, PCD_ENDP1, KB_EP1_TYPE);  \
    SET_TX_ADDR(dev, PCD_ENDP1, KB_EP1_TX_ADDR);  \
    SET_RX_ADDR(dev, PCD_ENDP1, KB_EP1_RX_ADDR);  \
    SET_RX_CNT(dev, PCD_ENDP1, KB_EP1_RX_SIZE);  \
}while(0)

///////////////////////////////////////////////
//// Endpoint define for STM32 OTG Core
///////////////////////////////////////////////
#define KB_OTG_MAX_OUT_SIZE                               (8)
#define KB_OTG_CONTROL_EP_NUM                             (1)
#define KB_OTG_OUT_EP_NUM                                 (1)
// RX FIFO size / 4 > (CONTROL_EP_NUM * 5 + 8) +  (MAX_OUT_SIZE / 4 + 1) + (OUT_EP_NUM*2) + 1 = 19

///////////////////////////////////////////////
//// Endpoint define for STM32 OTG FS Core
///////////////////////////////////////////////
#define KB_OTG_RX_FIFO_SIZE_FS                            (256)
#define KB_OTG_RX_FIFO_ADDR_FS                            (0)
// Sum of IN ep max packet size is 72
// Remain Fifo size is 1024 in bytes, Rx Used 256 bytes 

// TODO:
// I don't know why the max count of TX fifo should <= (7 * EpMaxPacket)
// But it seems the STM32F7xx can be large than (7 * EpMaxPacket)
#define KB_EP0_TX_FIFO_ADDR_FS                            (256)
#define KB_EP0_TX_FIFO_SIZE_FS                            (KB_EP0_TX_SIZE * 7)
#define KB_EP1_TX_FIFO_ADDR_FS                            (704)
#define KB_EP1_TX_FIFO_SIZE_FS                            (KB_EP1_TX_SIZE * 7)
// EndPoints init function for USB OTG core
#if defined(USB_OTG_FS)
#define KB_TUSB_INIT_EP_OTG_FS(dev) \
  do{\
    if(GetUSB(dev) == USB_OTG_FS) { \
      SET_RX_FIFO(dev, KB_OTG_RX_FIFO_ADDR_FS, KB_OTG_RX_FIFO_SIZE_FS);  \
      /* Init Ep0  */\
      INIT_EP_Tx(dev, PCD_ENDP0, KB_EP0_TX_TYPE, KB_EP0_TX_SIZE);  \
      SET_TX_FIFO(dev, PCD_ENDP0, KB_EP0_TX_FIFO_ADDR_FS, KB_EP0_TX_FIFO_SIZE_FS);  \
      INIT_EP_Rx(dev, PCD_ENDP0, KB_EP0_RX_TYPE, KB_EP0_RX_SIZE); \
      /* Init Ep1  */\
      INIT_EP_Tx(dev, PCD_ENDP1, KB_EP1_TX_TYPE, KB_EP1_TX_SIZE);  \
      SET_TX_FIFO(dev, PCD_ENDP1, KB_EP1_TX_FIFO_ADDR_FS, KB_EP1_TX_FIFO_SIZE_FS);  \
      INIT_EP_Rx(dev, PCD_ENDP1, KB_EP1_RX_TYPE, KB_EP1_RX_SIZE); \
    }\
  }while(0)

#else  // #if defined(USB_OTG_FS)
#define KB_TUSB_INIT_EP_OTG_FS(dev) 
    
#endif  // #if defined(USB_OTG_FS)

///////////////////////////////////////////////
//// Endpoint define for STM32 OTG HS Core
///////////////////////////////////////////////
#define KB_OTG_RX_FIFO_SIZE_HS                            (512)
#define KB_OTG_RX_FIFO_ADDR_HS                            (0)
// Sum of IN ep max packet size is 72
// Remain Fifo size is 3584 in bytes, Rx Used 512 bytes 

// TODO:
// I don't know why the max count of TX fifo should <= (7 * EpMaxPacket)
// But it seems the STM32F7xx can be large than (7 * EpMaxPacket)
#define KB_EP0_TX_FIFO_ADDR_HS                            (512)
#define KB_EP0_TX_FIFO_SIZE_HS                            (KB_EP0_TX_SIZE * 7)
#define KB_EP1_TX_FIFO_ADDR_HS                            (960)
#define KB_EP1_TX_FIFO_SIZE_HS                            (KB_EP1_TX_SIZE * 7)
// EndPoints init function for USB OTG core
#if defined(USB_OTG_HS)
#define KB_TUSB_INIT_EP_OTG_HS(dev) \
  do{\
    if(GetUSB(dev) == USB_OTG_HS) { \
      SET_RX_FIFO(dev, KB_OTG_RX_FIFO_ADDR_HS, KB_OTG_RX_FIFO_SIZE_HS);  \
      /* Init Ep0  */\
      INIT_EP_Tx(dev, PCD_ENDP0, KB_EP0_TX_TYPE, KB_EP0_TX_SIZE);  \
      SET_TX_FIFO(dev, PCD_ENDP0, KB_EP0_TX_FIFO_ADDR_HS, KB_EP0_TX_FIFO_SIZE_HS);  \
      INIT_EP_Rx(dev, PCD_ENDP0, KB_EP0_RX_TYPE, KB_EP0_RX_SIZE); \
      /* Init Ep1  */\
      INIT_EP_Tx(dev, PCD_ENDP1, KB_EP1_TX_TYPE, KB_EP1_TX_SIZE);  \
      SET_TX_FIFO(dev, PCD_ENDP1, KB_EP1_TX_FIFO_ADDR_HS, KB_EP1_TX_FIFO_SIZE_HS);  \
      INIT_EP_Rx(dev, PCD_ENDP1, KB_EP1_RX_TYPE, KB_EP1_RX_SIZE); \
    }\
  }while(0)

#else  // #if defined(USB_OTG_HS)
#define KB_TUSB_INIT_EP_OTG_HS(dev) 
    
#endif  // #if defined(USB_OTG_HS)
#define KB_TUSB_INIT_EP_OTG(dev) \
  do{\
    KB_TUSB_INIT_EP_OTG_FS(dev); \
    KB_TUSB_INIT_EP_OTG_HS(dev); \
  }while(0)


#if defined(USB)
#define KB_TUSB_INIT_EP(dev) KB_TUSB_INIT_EP_FS(dev)

// Teeny USB device init function for FS core
#define KB_TUSB_INIT_DEVICE(dev) \
  do{\
    /* Init device features */       \
    memset(&dev->addr, 0, TUSB_DEVICE_SIZE);    \
    dev->status = KB_DEV_STATUS;         \
    dev->rx_max_size = KB_rxEpMaxSize;         \
    dev->tx_max_size = KB_txEpMaxSize;         \
    dev->descriptors = &KB_descriptors;         \
  }while(0)

#endif

#if defined(USB_OTG_FS) || defined(USB_OTG_HS)
#define KB_TUSB_INIT_EP(dev) KB_TUSB_INIT_EP_OTG(dev)

// Teeny USB device init function for OTG core
#define KB_TUSB_INIT_DEVICE(dev) \
  do{\
    /* Init device features */       \
    memset(&dev->addr, 0, TUSB_DEVICE_SIZE);    \
    dev->status = KB_DEV_STATUS;         \
    dev->descriptors = &KB_descriptors;         \
  }while(0)

#endif

#define KB_TUSB_INIT(dev) \
  do{\
    KB_TUSB_INIT_EP(dev);   \
    KB_TUSB_INIT_DEVICE(dev);   \
  }while(0)

// Get End Point count
#ifndef  EP_NUM
#define  EP_NUM 1
#endif
#if KB_EP_NUM > EP_NUM
#undef   EP_NUM
#define  EP_NUM  KB_EP_NUM
#endif

extern const uint8_t* const KB_StringDescriptors[KB_STRING_COUNT];
extern const tusb_descriptors KB_descriptors;

#define KB_REPORT_DESCRIPTOR_SIZE_IF0  (63)
extern const uint8_t KB_ReportDescriptor_if0[KB_REPORT_DESCRIPTOR_SIZE_IF0];


#endif   // #ifndef __KB_TEENY_USB_INIT_H__
/////////////////////////////////////////
//// Device 8
/////////////////////////////////////////
#ifndef __MOUSE_TEENY_USB_INIT_H__
#define __MOUSE_TEENY_USB_INIT_H__
// forward declare the tusb_descriptors struct
typedef struct _tusb_descriptors tusb_descriptors;

#define MOUSE_VID                                            0x0483
#define MOUSE_PID                                            0x0011
#define MOUSE_STRING_COUNT                                   (4)

// device.bmAttributes & 0x40   USB_CONFIG_SELF_POWERED
// device.bmAttributes & 0x20   USB_CONFIG_REMOTE_WAKEUP
#define MOUSE_DEV_STATUS                                    (0 | 0)


// Endpoint usage:
#define MOUSE_MAX_EP                                         (1)
#define MOUSE_EP_NUM                                         (MOUSE_MAX_EP + 1)

///////////////////////////////////////////////
//// Endpoint define for STM32 FS Core
///////////////////////////////////////////////

#ifdef MOUSE_BTABLE_ADDRESS
#undef MOUSE_BTABLE_ADDRESS
#endif
#define MOUSE_BTABLE_ADDRESS                                 (0)
#define MOUSE_EP_BUF_DESC_TABLE_SIZE                         (8)
// PMA buffer reserved for buffer description table
#define MOUSE_USB_BUF_START                                  (MOUSE_EP_BUF_DESC_TABLE_SIZE * MOUSE_EP_NUM)

// EndPoints 0 defines
#define MOUSE_EP0_RX_SIZE                                    (64)
#define MOUSE_EP0_RX_ADDR                                    (MOUSE_USB_BUF_START + (0))
#define MOUSE_EP0_TX_SIZE                                    (64)
#define MOUSE_EP0_TX_ADDR                                    (MOUSE_USB_BUF_START + (64))
#define MOUSE_EP0_RX_TYPE                                    USB_EP_CONTROL
#define MOUSE_EP0_TX_TYPE                                    USB_EP_CONTROL

#define MOUSE_EP0_TYPE                                       USB_EP_CONTROL
#define MOUSE_EP0_TX0_ADDR                                   (MOUSE_USB_BUF_START + (0))
#define MOUSE_EP0_TX1_ADDR                                   (MOUSE_USB_BUF_START + (64))
#define MOUSE_EP0_RX0_ADDR                                   (MOUSE_USB_BUF_START + (0))
#define MOUSE_EP0_RX1_ADDR                                   (MOUSE_USB_BUF_START + (64))

// EndPoints 1 defines
#define MOUSE_EP1_RX_SIZE                                    (8)
#define MOUSE_EP1_RX_ADDR                                    (MOUSE_USB_BUF_START + (128))
#define MOUSE_EP1_TX_SIZE                                    (8)
#define MOUSE_EP1_TX_ADDR                                    (MOUSE_USB_BUF_START + (136))
#define MOUSE_EP1_RX_TYPE                                    USB_EP_INTERRUPT
#define MOUSE_EP1_TX_TYPE                                    USB_EP_INTERRUPT

#define MOUSE_EP1_TYPE                                       USB_EP_INTERRUPT
#define MOUSE_EP1_TX0_ADDR                                   (MOUSE_USB_BUF_START + (128))
#define MOUSE_EP1_TX1_ADDR                                   (MOUSE_USB_BUF_START + (136))
#define MOUSE_EP1_RX0_ADDR                                   (MOUSE_USB_BUF_START + (128))
#define MOUSE_EP1_RX1_ADDR                                   (MOUSE_USB_BUF_START + (136))


// EndPoint max packed sizes
extern const uint8_t MOUSE_txEpMaxSize[];
#define MOUSE_TXEP_MAX_SIZE                                  \
const uint8_t MOUSE_txEpMaxSize[] = \
{ MOUSE_EP0_TX_SIZE, MOUSE_EP1_TX_SIZE,  };
extern const uint8_t MOUSE_rxEpMaxSize[];
#define MOUSE_RXEP_MAX_SIZE                                  \
const uint8_t MOUSE_rxEpMaxSize[] = \
{ MOUSE_EP0_RX_SIZE, MOUSE_EP1_RX_SIZE,  };

// EndPoints init function for USB FS core
#define MOUSE_TUSB_INIT_EP_FS(dev) \
  do{\
    /* Init ep0 */ \
    INIT_EP_BiDirection(dev, PCD_ENDP0, MOUSE_EP0_TYPE);  \
    SET_TX_ADDR(dev, PCD_ENDP0, MOUSE_EP0_TX_ADDR);  \
    SET_RX_ADDR(dev, PCD_ENDP0, MOUSE_EP0_RX_ADDR);  \
    SET_RX_CNT(dev, PCD_ENDP0, MOUSE_EP0_RX_SIZE);  \
    /* Init ep1 */ \
    INIT_EP_BiDirection(dev, PCD_ENDP1, MOUSE_EP1_TYPE);  \
    SET_TX_ADDR(dev, PCD_ENDP1, MOUSE_EP1_TX_ADDR);  \
    SET_RX_ADDR(dev, PCD_ENDP1, MOUSE_EP1_RX_ADDR);  \
    SET_RX_CNT(dev, PCD_ENDP1, MOUSE_EP1_RX_SIZE);  \
}while(0)

///////////////////////////////////////////////
//// Endpoint define for STM32 OTG Core
///////////////////////////////////////////////
#define MOUSE_OTG_MAX_OUT_SIZE                               (8)
#define MOUSE_OTG_CONTROL_EP_NUM                             (1)
#define MOUSE_OTG_OUT_EP_NUM                                 (1)
// RX FIFO size / 4 > (CONTROL_EP_NUM * 5 + 8) +  (MAX_OUT_SIZE / 4 + 1) + (OUT_EP_NUM*2) + 1 = 19

///////////////////////////////////////////////
//// Endpoint define for STM32 OTG FS Core
///////////////////////////////////////////////
#define MOUSE_OTG_RX_FIFO_SIZE_FS                            (256)
#define MOUSE_OTG_RX_FIFO_ADDR_FS                            (0)
// Sum of IN ep max packet size is 72
// Remain Fifo size is 1024 in bytes, Rx Used 256 bytes 

// TODO:
// I don't know why the max count of TX fifo should <= (7 * EpMaxPacket)
// But it seems the STM32F7xx can be large than (7 * EpMaxPacket)
#define MOUSE_EP0_TX_FIFO_ADDR_FS                            (256)
#define MOUSE_EP0_TX_FIFO_SIZE_FS                            (MOUSE_EP0_TX_SIZE * 7)
#define MOUSE_EP1_TX_FIFO_ADDR_FS                            (704)
#define MOUSE_EP1_TX_FIFO_SIZE_FS                            (MOUSE_EP1_TX_SIZE * 7)
// EndPoints init function for USB OTG core
#if defined(USB_OTG_FS)
#define MOUSE_TUSB_INIT_EP_OTG_FS(dev) \
  do{\
    if(GetUSB(dev) == USB_OTG_FS) { \
      SET_RX_FIFO(dev, MOUSE_OTG_RX_FIFO_ADDR_FS, MOUSE_OTG_RX_FIFO_SIZE_FS);  \
      /* Init Ep0  */\
      INIT_EP_Tx(dev, PCD_ENDP0, MOUSE_EP0_TX_TYPE, MOUSE_EP0_TX_SIZE);  \
      SET_TX_FIFO(dev, PCD_ENDP0, MOUSE_EP0_TX_FIFO_ADDR_FS, MOUSE_EP0_TX_FIFO_SIZE_FS);  \
      INIT_EP_Rx(dev, PCD_ENDP0, MOUSE_EP0_RX_TYPE, MOUSE_EP0_RX_SIZE); \
      /* Init Ep1  */\
      INIT_EP_Tx(dev, PCD_ENDP1, MOUSE_EP1_TX_TYPE, MOUSE_EP1_TX_SIZE);  \
      SET_TX_FIFO(dev, PCD_ENDP1, MOUSE_EP1_TX_FIFO_ADDR_FS, MOUSE_EP1_TX_FIFO_SIZE_FS);  \
      INIT_EP_Rx(dev, PCD_ENDP1, MOUSE_EP1_RX_TYPE, MOUSE_EP1_RX_SIZE); \
    }\
  }while(0)

#else  // #if defined(USB_OTG_FS)
#define MOUSE_TUSB_INIT_EP_OTG_FS(dev) 
    
#endif  // #if defined(USB_OTG_FS)

///////////////////////////////////////////////
//// Endpoint define for STM32 OTG HS Core
///////////////////////////////////////////////
#define MOUSE_OTG_RX_FIFO_SIZE_HS                            (512)
#define MOUSE_OTG_RX_FIFO_ADDR_HS                            (0)
// Sum of IN ep max packet size is 72
// Remain Fifo size is 3584 in bytes, Rx Used 512 bytes 

// TODO:
// I don't know why the max count of TX fifo should <= (7 * EpMaxPacket)
// But it seems the STM32F7xx can be large than (7 * EpMaxPacket)
#define MOUSE_EP0_TX_FIFO_ADDR_HS                            (512)
#define MOUSE_EP0_TX_FIFO_SIZE_HS                            (MOUSE_EP0_TX_SIZE * 7)
#define MOUSE_EP1_TX_FIFO_ADDR_HS                            (960)
#define MOUSE_EP1_TX_FIFO_SIZE_HS                            (MOUSE_EP1_TX_SIZE * 7)
// EndPoints init function for USB OTG core
#if defined(USB_OTG_HS)
#define MOUSE_TUSB_INIT_EP_OTG_HS(dev) \
  do{\
    if(GetUSB(dev) == USB_OTG_HS) { \
      SET_RX_FIFO(dev, MOUSE_OTG_RX_FIFO_ADDR_HS, MOUSE_OTG_RX_FIFO_SIZE_HS);  \
      /* Init Ep0  */\
      INIT_EP_Tx(dev, PCD_ENDP0, MOUSE_EP0_TX_TYPE, MOUSE_EP0_TX_SIZE);  \
      SET_TX_FIFO(dev, PCD_ENDP0, MOUSE_EP0_TX_FIFO_ADDR_HS, MOUSE_EP0_TX_FIFO_SIZE_HS);  \
      INIT_EP_Rx(dev, PCD_ENDP0, MOUSE_EP0_RX_TYPE, MOUSE_EP0_RX_SIZE); \
      /* Init Ep1  */\
      INIT_EP_Tx(dev, PCD_ENDP1, MOUSE_EP1_TX_TYPE, MOUSE_EP1_TX_SIZE);  \
      SET_TX_FIFO(dev, PCD_ENDP1, MOUSE_EP1_TX_FIFO_ADDR_HS, MOUSE_EP1_TX_FIFO_SIZE_HS);  \
      INIT_EP_Rx(dev, PCD_ENDP1, MOUSE_EP1_RX_TYPE, MOUSE_EP1_RX_SIZE); \
    }\
  }while(0)

#else  // #if defined(USB_OTG_HS)
#define MOUSE_TUSB_INIT_EP_OTG_HS(dev) 
    
#endif  // #if defined(USB_OTG_HS)
#define MOUSE_TUSB_INIT_EP_OTG(dev) \
  do{\
    MOUSE_TUSB_INIT_EP_OTG_FS(dev); \
    MOUSE_TUSB_INIT_EP_OTG_HS(dev); \
  }while(0)


#if defined(USB)
#define MOUSE_TUSB_INIT_EP(dev) MOUSE_TUSB_INIT_EP_FS(dev)

// Teeny USB device init function for FS core
#define MOUSE_TUSB_INIT_DEVICE(dev) \
  do{\
    /* Init device features */       \
    memset(&dev->addr, 0, TUSB_DEVICE_SIZE);    \
    dev->status = MOUSE_DEV_STATUS;         \
    dev->rx_max_size = MOUSE_rxEpMaxSize;         \
    dev->tx_max_size = MOUSE_txEpMaxSize;         \
    dev->descriptors = &MOUSE_descriptors;         \
  }while(0)

#endif

#if defined(USB_OTG_FS) || defined(USB_OTG_HS)
#define MOUSE_TUSB_INIT_EP(dev) MOUSE_TUSB_INIT_EP_OTG(dev)

// Teeny USB device init function for OTG core
#define MOUSE_TUSB_INIT_DEVICE(dev) \
  do{\
    /* Init device features */       \
    memset(&dev->addr, 0, TUSB_DEVICE_SIZE);    \
    dev->status = MOUSE_DEV_STATUS;         \
    dev->descriptors = &MOUSE_descriptors;         \
  }while(0)

#endif

#define MOUSE_TUSB_INIT(dev) \
  do{\
    MOUSE_TUSB_INIT_EP(dev);   \
    MOUSE_TUSB_INIT_DEVICE(dev);   \
  }while(0)

// Get End Point count
#ifndef  EP_NUM
#define  EP_NUM 1
#endif
#if MOUSE_EP_NUM > EP_NUM
#undef   EP_NUM
#define  EP_NUM  MOUSE_EP_NUM
#endif

extern const uint8_t* const MOUSE_StringDescriptors[MOUSE_STRING_COUNT];
extern const tusb_descriptors MOUSE_descriptors;

#define MOUSE_REPORT_DESCRIPTOR_SIZE_IF0  (50)
extern const uint8_t MOUSE_ReportDescriptor_if0[MOUSE_REPORT_DESCRIPTOR_SIZE_IF0];


#endif   // #ifndef __MOUSE_TEENY_USB_INIT_H__
/////////////////////////////////////////
//// Device 9
/////////////////////////////////////////
#ifndef __MSC_TEENY_USB_INIT_H__
#define __MSC_TEENY_USB_INIT_H__
// forward declare the tusb_descriptors struct
typedef struct _tusb_descriptors tusb_descriptors;

#define MSC_VID                                            0x0483
#define MSC_PID                                            0x0011
#define MSC_STRING_COUNT                                   (4)

// device.bmAttributes & 0x40   USB_CONFIG_SELF_POWERED
// device.bmAttributes & 0x20   USB_CONFIG_REMOTE_WAKEUP
#define MSC_DEV_STATUS                                    (0 | 0)


// Endpoint usage:
#define MSC_MAX_EP                                         (2)
#define MSC_EP_NUM                                         (MSC_MAX_EP + 1)

///////////////////////////////////////////////
//// Endpoint define for STM32 FS Core
///////////////////////////////////////////////

#ifdef MSC_BTABLE_ADDRESS
#undef MSC_BTABLE_ADDRESS
#endif
#define MSC_BTABLE_ADDRESS                                 (0)
#define MSC_EP_BUF_DESC_TABLE_SIZE                         (8)
// PMA buffer reserved for buffer description table
#define MSC_USB_BUF_START                                  (MSC_EP_BUF_DESC_TABLE_SIZE * MSC_EP_NUM)

// EndPoints 0 defines
#define MSC_EP0_RX_SIZE                                    (64)
#define MSC_EP0_RX_ADDR                                    (MSC_USB_BUF_START + (0))
#define MSC_EP0_TX_SIZE                                    (64)
#define MSC_EP0_TX_ADDR                                    (MSC_USB_BUF_START + (64))
#define MSC_EP0_RX_TYPE                                    USB_EP_CONTROL
#define MSC_EP0_TX_TYPE                                    USB_EP_CONTROL

#define MSC_EP0_TYPE                                       USB_EP_CONTROL
#define MSC_EP0_TX0_ADDR                                   (MSC_USB_BUF_START + (0))
#define MSC_EP0_TX1_ADDR                                   (MSC_USB_BUF_START + (64))
#define MSC_EP0_RX0_ADDR                                   (MSC_USB_BUF_START + (0))
#define MSC_EP0_RX1_ADDR                                   (MSC_USB_BUF_START + (64))

// EndPoints 1 defines
#define MSC_EP1_RX_SIZE                                    (0)
#define MSC_EP1_RX_ADDR                                    (MSC_USB_BUF_START + (128))
#define MSC_EP1_TX_SIZE                                    (64)
#define MSC_EP1_TX_ADDR                                    (MSC_USB_BUF_START + (128))
#define MSC_EP1_RX_TYPE                                    USB_EP_Invalid
#define MSC_EP1_TX_TYPE                                    USB_EP_BULK

#define MSC_EP1_TYPE                                       USB_EP_BULK
#define MSC_EP1_TX0_ADDR                                   (MSC_USB_BUF_START + (128))
#define MSC_EP1_TX1_ADDR                                   (MSC_USB_BUF_START + (192))
#define MSC_EP1_RX0_ADDR                                   (MSC_USB_BUF_START + (128))
#define MSC_EP1_RX1_ADDR                                   (MSC_USB_BUF_START + (192))

// EndPoints 2 defines
#define MSC_EP2_RX_SIZE                                    (64)
#define MSC_EP2_RX_ADDR                                    (MSC_USB_BUF_START + (256))
#define MSC_EP2_TX_SIZE                                    (0)
#define MSC_EP2_TX_ADDR                                    (MSC_USB_BUF_START + (320))
#define MSC_EP2_RX_TYPE                                    USB_EP_BULK
#define MSC_EP2_TX_TYPE                                    USB_EP_Invalid

#define MSC_EP2_TYPE                                       USB_EP_BULK
#define MSC_EP2_TX0_ADDR                                   (MSC_USB_BUF_START + (256))
#define MSC_EP2_TX1_ADDR                                   (MSC_USB_BUF_START + (320))
#define MSC_EP2_RX0_ADDR                                   (MSC_USB_BUF_START + (256))
#define MSC_EP2_RX1_ADDR                                   (MSC_USB_BUF_START + (320))


// EndPoint max packed sizes
extern const uint8_t MSC_txEpMaxSize[];
#define MSC_TXEP_MAX_SIZE                                  \
const uint8_t MSC_txEpMaxSize[] = \
{ MSC_EP0_TX_SIZE, MSC_EP1_TX_SIZE, 0,  };
extern const uint8_t MSC_rxEpMaxSize[];
#define MSC_RXEP_MAX_SIZE                                  \
const uint8_t MSC_rxEpMaxSize[] = \
{ MSC_EP0_RX_SIZE, 0, MSC_EP2_RX_SIZE,  };

// EndPoints init function for USB FS core
#define MSC_TUSB_INIT_EP_FS(dev) \
  do{\
    /* Init ep0 */ \
    INIT_EP_BiDirection(dev, PCD_ENDP0, MSC_EP0_TYPE);  \
    SET_TX_ADDR(dev, PCD_ENDP0, MSC_EP0_TX_ADDR);  \
    SET_RX_ADDR(dev, PCD_ENDP0, MSC_EP0_RX_ADDR);  \
    SET_RX_CNT(dev, PCD_ENDP0, MSC_EP0_RX_SIZE);  \
    /* Init ep1 */ \
    INIT_EP_TxDouble(dev, PCD_ENDP1, MSC_EP1_TYPE);     \
    SET_DOUBLE_ADDR(dev, PCD_ENDP1, MSC_EP1_TX0_ADDR, MSC_EP1_TX1_ADDR);  \
    SET_DBL_TX_CNT(dev, PCD_ENDP1, 0);     \
    /* Init ep2 */ \
    INIT_EP_RxDouble(dev, PCD_ENDP2, MSC_EP2_TYPE);     \
    SET_DOUBLE_ADDR(dev, PCD_ENDP2, MSC_EP2_RX0_ADDR, MSC_EP2_RX1_ADDR);  \
    SET_DBL_RX_CNT(dev, PCD_ENDP2, MSC_EP2_RX_SIZE);     \
}while(0)

///////////////////////////////////////////////
//// Endpoint define for STM32 OTG Core
///////////////////////////////////////////////
#define MSC_OTG_MAX_OUT_SIZE                               (64)
#define MSC_OTG_CONTROL_EP_NUM                             (1)
#define MSC_OTG_OUT_EP_NUM                                 (1)
// RX FIFO size / 4 > (CONTROL_EP_NUM * 5 + 8) +  (MAX_OUT_SIZE / 4 + 1) + (OUT_EP_NUM*2) + 1 = 33

///////////////////////////////////////////////
//// Endpoint define for STM32 OTG FS Core
///////////////////////////////////////////////
#define MSC_OTG_RX_FIFO_SIZE_FS                            (256)
#define MSC_OTG_RX_FIFO_ADDR_FS                            (0)
// Sum of IN ep max packet size is 128
// Remain Fifo size is 1024 in bytes, Rx Used 256 bytes 

// TODO:
// I don't know why the max count of TX fifo should <= (7 * EpMaxPacket)
// But it seems the STM32F7xx can be large than (7 * EpMaxPacket)
#define MSC_EP0_TX_FIFO_ADDR_FS                            (256)
#define MSC_EP0_TX_FIFO_SIZE_FS                            (MSC_EP0_TX_SIZE * 7)
#define MSC_EP1_TX_FIFO_ADDR_FS                            (704)
#define MSC_EP1_TX_FIFO_SIZE_FS                            (MSC_EP1_TX_SIZE * 7)
// EndPoints init function for USB OTG core
#if defined(USB_OTG_FS)
#define MSC_TUSB_INIT_EP_OTG_FS(dev) \
  do{\
    if(GetUSB(dev) == USB_OTG_FS) { \
      SET_RX_FIFO(dev, MSC_OTG_RX_FIFO_ADDR_FS, MSC_OTG_RX_FIFO_SIZE_FS);  \
      /* Init Ep0  */\
      INIT_EP_Tx(dev, PCD_ENDP0, MSC_EP0_TX_TYPE, MSC_EP0_TX_SIZE);  \
      SET_TX_FIFO(dev, PCD_ENDP0, MSC_EP0_TX_FIFO_ADDR_FS, MSC_EP0_TX_FIFO_SIZE_FS);  \
      INIT_EP_Rx(dev, PCD_ENDP0, MSC_EP0_RX_TYPE, MSC_EP0_RX_SIZE); \
      /* Init Ep1  */\
      INIT_EP_Tx(dev, PCD_ENDP1, MSC_EP1_TX_TYPE, MSC_EP1_TX_SIZE);  \
      SET_TX_FIFO(dev, PCD_ENDP1, MSC_EP1_TX_FIFO_ADDR_FS, MSC_EP1_TX_FIFO_SIZE_FS);  \
      /* Init Ep2  */\
      INIT_EP_Rx(dev, PCD_ENDP2, MSC_EP2_RX_TYPE, MSC_EP2_RX_SIZE); \
    }\
  }while(0)

#else  // #if defined(USB_OTG_FS)
#define MSC_TUSB_INIT_EP_OTG_FS(dev) 
    
#endif  // #if defined(USB_OTG_FS)

///////////////////////////////////////////////
//// Endpoint define for STM32 OTG HS Core
///////////////////////////////////////////////
#define MSC_OTG_RX_FIFO_SIZE_HS                            (512)
#define MSC_OTG_RX_FIFO_ADDR_HS                            (0)
// Sum of IN ep max packet size is 128
// Remain Fifo size is 3584 in bytes, Rx Used 512 bytes 

// TODO:
// I don't know why the max count of TX fifo should <= (7 * EpMaxPacket)
// But it seems the STM32F7xx can be large than (7 * EpMaxPacket)
#define MSC_EP0_TX_FIFO_ADDR_HS                            (512)
#define MSC_EP0_TX_FIFO_SIZE_HS                            (MSC_EP0_TX_SIZE * 7)
#define MSC_EP1_TX_FIFO_ADDR_HS                            (960)
#define MSC_EP1_TX_FIFO_SIZE_HS                            (MSC_EP1_TX_SIZE * 7)
// EndPoints init function for USB OTG core
#if defined(USB_OTG_HS)
#define MSC_TUSB_INIT_EP_OTG_HS(dev) \
  do{\
    if(GetUSB(dev) == USB_OTG_HS) { \
      SET_RX_FIFO(dev, MSC_OTG_RX_FIFO_ADDR_HS, MSC_OTG_RX_FIFO_SIZE_HS);  \
      /* Init Ep0  */\
      INIT_EP_Tx(dev, PCD_ENDP0, MSC_EP0_TX_TYPE, MSC_EP0_TX_SIZE);  \
      SET_TX_FIFO(dev, PCD_ENDP0, MSC_EP0_TX_FIFO_ADDR_HS, MSC_EP0_TX_FIFO_SIZE_HS);  \
      INIT_EP_Rx(dev, PCD_ENDP0, MSC_EP0_RX_TYPE, MSC_EP0_RX_SIZE); \
      /* Init Ep1  */\
      INIT_EP_Tx(dev, PCD_ENDP1, MSC_EP1_TX_TYPE, MSC_EP1_TX_SIZE);  \
      SET_TX_FIFO(dev, PCD_ENDP1, MSC_EP1_TX_FIFO_ADDR_HS, MSC_EP1_TX_FIFO_SIZE_HS);  \
      /* Init Ep2  */\
      INIT_EP_Rx(dev, PCD_ENDP2, MSC_EP2_RX_TYPE, MSC_EP2_RX_SIZE); \
    }\
  }while(0)

#else  // #if defined(USB_OTG_HS)
#define MSC_TUSB_INIT_EP_OTG_HS(dev) 
    
#endif  // #if defined(USB_OTG_HS)
#define MSC_TUSB_INIT_EP_OTG(dev) \
  do{\
    MSC_TUSB_INIT_EP_OTG_FS(dev); \
    MSC_TUSB_INIT_EP_OTG_HS(dev); \
  }while(0)


#if defined(USB)
#define MSC_TUSB_INIT_EP(dev) MSC_TUSB_INIT_EP_FS(dev)

// Teeny USB device init function for FS core
#define MSC_TUSB_INIT_DEVICE(dev) \
  do{\
    /* Init device features */       \
    memset(&dev->addr, 0, TUSB_DEVICE_SIZE);    \
    dev->status = MSC_DEV_STATUS;         \
    dev->rx_max_size = MSC_rxEpMaxSize;         \
    dev->tx_max_size = MSC_txEpMaxSize;         \
    dev->descriptors = &MSC_descriptors;         \
  }while(0)

#endif

#if defined(USB_OTG_FS) || defined(USB_OTG_HS)
#define MSC_TUSB_INIT_EP(dev) MSC_TUSB_INIT_EP_OTG(dev)

// Teeny USB device init function for OTG core
#define MSC_TUSB_INIT_DEVICE(dev) \
  do{\
    /* Init device features */       \
    memset(&dev->addr, 0, TUSB_DEVICE_SIZE);    \
    dev->status = MSC_DEV_STATUS;         \
    dev->descriptors = &MSC_descriptors;         \
  }while(0)

#endif

#define MSC_TUSB_INIT(dev) \
  do{\
    MSC_TUSB_INIT_EP(dev);   \
    MSC_TUSB_INIT_DEVICE(dev);   \
  }while(0)

// Get End Point count
#ifndef  EP_NUM
#define  EP_NUM 1
#endif
#if MSC_EP_NUM > EP_NUM
#undef   EP_NUM
#define  EP_NUM  MSC_EP_NUM
#endif

// Enable double buffer related code
#define  HAS_DOUBLE_BUFFER

extern const uint8_t* const MSC_StringDescriptors[MSC_STRING_COUNT];
extern const tusb_descriptors MSC_descriptors;


#endif   // #ifndef __MSC_TEENY_USB_INIT_H__
/////////////////////////////////////////
//// Device 10
/////////////////////////////////////////
#ifndef __DAPV1_TEENY_USB_INIT_H__
#define __DAPV1_TEENY_USB_INIT_H__
// forward declare the tusb_descriptors struct
typedef struct _tusb_descriptors tusb_descriptors;

#define DAPV1_VID                                            0x0d28
#define DAPV1_PID                                            0x0204
#define DAPV1_STRING_COUNT                                   (4)

// device.bmAttributes & 0x40   USB_CONFIG_SELF_POWERED
// device.bmAttributes & 0x20   USB_CONFIG_REMOTE_WAKEUP
#define DAPV1_DEV_STATUS                                    (0 | 0)


// Endpoint usage:
#define DAPV1_MAX_EP                                         (2)
#define DAPV1_EP_NUM                                         (DAPV1_MAX_EP + 1)

///////////////////////////////////////////////
//// Endpoint define for STM32 FS Core
///////////////////////////////////////////////

#ifdef DAPV1_BTABLE_ADDRESS
#undef DAPV1_BTABLE_ADDRESS
#endif
#define DAPV1_BTABLE_ADDRESS                                 (0)
#define DAPV1_EP_BUF_DESC_TABLE_SIZE                         (8)
// PMA buffer reserved for buffer description table
#define DAPV1_USB_BUF_START                                  (DAPV1_EP_BUF_DESC_TABLE_SIZE * DAPV1_EP_NUM)

// EndPoints 0 defines
#define DAPV1_EP0_RX_SIZE                                    (64)
#define DAPV1_EP0_RX_ADDR                                    (DAPV1_USB_BUF_START + (0))
#define DAPV1_EP0_TX_SIZE                                    (64)
#define DAPV1_EP0_TX_ADDR                                    (DAPV1_USB_BUF_START + (64))
#define DAPV1_EP0_RX_TYPE                                    USB_EP_CONTROL
#define DAPV1_EP0_TX_TYPE                                    USB_EP_CONTROL

#define DAPV1_EP0_TYPE                                       USB_EP_CONTROL
#define DAPV1_EP0_TX0_ADDR                                   (DAPV1_USB_BUF_START + (0))
#define DAPV1_EP0_TX1_ADDR                                   (DAPV1_USB_BUF_START + (64))
#define DAPV1_EP0_RX0_ADDR                                   (DAPV1_USB_BUF_START + (0))
#define DAPV1_EP0_RX1_ADDR                                   (DAPV1_USB_BUF_START + (64))

// EndPoints 1 defines
#define DAPV1_EP1_RX_SIZE                                    (64)
#define DAPV1_EP1_RX_ADDR                                    (DAPV1_USB_BUF_START + (128))
#define DAPV1_EP1_TX_SIZE                                    (0)
#define DAPV1_EP1_TX_ADDR                                    (DAPV1_USB_BUF_START + (192))
#define DAPV1_EP1_RX_TYPE                                    USB_EP_INTERRUPT
#define DAPV1_EP1_TX_TYPE                                    USB_EP_Invalid

#define DAPV1_EP1_TYPE                                       USB_EP_INTERRUPT
#define DAPV1_EP1_TX0_ADDR                                   (DAPV1_USB_BUF_START + (128))
#define DAPV1_EP1_TX1_ADDR                                   (DAPV1_USB_BUF_START + (192))
#define DAPV1_EP1_RX0_ADDR                                   (DAPV1_USB_BUF_START + (128))
#define DAPV1_EP1_RX1_ADDR                                   (DAPV1_USB_BUF_START + (192))

// EndPoints 2 defines
#define DAPV1_EP2_RX_SIZE                                    (0)
#define DAPV1_EP2_RX_ADDR                                    (DAPV1_USB_BUF_START + (192))
#define DAPV1_EP2_TX_SIZE                                    (64)
#define DAPV1_EP2_TX_ADDR                                    (DAPV1_USB_BUF_START + (192))
#define DAPV1_EP2_RX_TYPE                                    USB_EP_Invalid
#define DAPV1_EP2_TX_TYPE                                    USB_EP_INTERRUPT

#define DAPV1_EP2_TYPE                                       USB_EP_INTERRUPT
#define DAPV1_EP2_TX0_ADDR                                   (DAPV1_USB_BUF_START + (192))
#define DAPV1_EP2_TX1_ADDR                                   (DAPV1_USB_BUF_START + (256))
#define DAPV1_EP2_RX0_ADDR                                   (DAPV1_USB_BUF_START + (192))
#define DAPV1_EP2_RX1_ADDR                                   (DAPV1_USB_BUF_START + (256))


// EndPoint max packed sizes
extern const uint8_t DAPV1_txEpMaxSize[];
#define DAPV1_TXEP_MAX_SIZE                                  \
const uint8_t DAPV1_txEpMaxSize[] = \
{ DAPV1_EP0_TX_SIZE, 0, DAPV1_EP2_TX_SIZE,  };
extern const uint8_t DAPV1_rxEpMaxSize[];
#define DAPV1_RXEP_MAX_SIZE                                  \
const uint8_t DAPV1_rxEpMaxSize[] = \
{ DAPV1_EP0_RX_SIZE, DAPV1_EP1_RX_SIZE, 0,  };

// EndPoints init function for USB FS core
#define DAPV1_TUSB_INIT_EP_FS(dev) \
  do{\
    /* Init ep0 */ \
    INIT_EP_BiDirection(dev, PCD_ENDP0, DAPV1_EP0_TYPE);  \
    SET_TX_ADDR(dev, PCD_ENDP0, DAPV1_EP0_TX_ADDR);  \
    SET_RX_ADDR(dev, PCD_ENDP0, DAPV1_EP0_RX_ADDR);  \
    SET_RX_CNT(dev, PCD_ENDP0, DAPV1_EP0_RX_SIZE);  \
    /* Init ep1 */ \
    INIT_EP_RxOnly(dev, PCD_ENDP1, DAPV1_EP1_TYPE);  \
    SET_RX_ADDR(dev, PCD_ENDP1, DAPV1_EP1_RX_ADDR);  \
    SET_RX_CNT(dev, PCD_ENDP1, DAPV1_EP1_RX_SIZE);  \
    /* Init ep2 */ \
    INIT_EP_TxOnly(dev, PCD_ENDP2, DAPV1_EP2_TYPE);  \
    SET_TX_ADDR(dev, PCD_ENDP2, DAPV1_EP2_TX_ADDR);  \
}while(0)

///////////////////////////////////////////////
//// Endpoint define for STM32 OTG Core
///////////////////////////////////////////////
#define DAPV1_OTG_MAX_OUT_SIZE                               (64)
#define DAPV1_OTG_CONTROL_EP_NUM                             (1)
#define DAPV1_OTG_OUT_EP_NUM                                 (1)
// RX FIFO size / 4 > (CONTROL_EP_NUM * 5 + 8) +  (MAX_OUT_SIZE / 4 + 1) + (OUT_EP_NUM*2) + 1 = 33

///////////////////////////////////////////////
//// Endpoint define for STM32 OTG FS Core
///////////////////////////////////////////////
#define DAPV1_OTG_RX_FIFO_SIZE_FS                            (256)
#define DAPV1_OTG_RX_FIFO_ADDR_FS                            (0)
// Sum of IN ep max packet size is 128
// Remain Fifo size is 1024 in bytes, Rx Used 256 bytes 

// TODO:
// I don't know why the max count of TX fifo should <= (7 * EpMaxPacket)
// But it seems the STM32F7xx can be large than (7 * EpMaxPacket)
#define DAPV1_EP0_TX_FIFO_ADDR_FS                            (256)
#define DAPV1_EP0_TX_FIFO_SIZE_FS                            (DAPV1_EP0_TX_SIZE * 7)
#define DAPV1_EP2_TX_FIFO_ADDR_FS                            (704)
#define DAPV1_EP2_TX_FIFO_SIZE_FS                            (DAPV1_EP2_TX_SIZE * 7)
// EndPoints init function for USB OTG core
#if defined(USB_OTG_FS)
#define DAPV1_TUSB_INIT_EP_OTG_FS(dev) \
  do{\
    if(GetUSB(dev) == USB_OTG_FS) { \
      SET_RX_FIFO(dev, DAPV1_OTG_RX_FIFO_ADDR_FS, DAPV1_OTG_RX_FIFO_SIZE_FS);  \
      /* Init Ep0  */\
      INIT_EP_Tx(dev, PCD_ENDP0, DAPV1_EP0_TX_TYPE, DAPV1_EP0_TX_SIZE);  \
      SET_TX_FIFO(dev, PCD_ENDP0, DAPV1_EP0_TX_FIFO_ADDR_FS, DAPV1_EP0_TX_FIFO_SIZE_FS);  \
      INIT_EP_Rx(dev, PCD_ENDP0, DAPV1_EP0_RX_TYPE, DAPV1_EP0_RX_SIZE); \
      /* Init Ep1  */\
      INIT_EP_Rx(dev, PCD_ENDP1, DAPV1_EP1_RX_TYPE, DAPV1_EP1_RX_SIZE); \
      /* Init Ep2  */\
      INIT_EP_Tx(dev, PCD_ENDP2, DAPV1_EP2_TX_TYPE, DAPV1_EP2_TX_SIZE);  \
      SET_TX_FIFO(dev, PCD_ENDP2, DAPV1_EP2_TX_FIFO_ADDR_FS, DAPV1_EP2_TX_FIFO_SIZE_FS);  \
    }\
  }while(0)

#else  // #if defined(USB_OTG_FS)
#define DAPV1_TUSB_INIT_EP_OTG_FS(dev) 
    
#endif  // #if defined(USB_OTG_FS)

///////////////////////////////////////////////
//// Endpoint define for STM32 OTG HS Core
///////////////////////////////////////////////
#define DAPV1_OTG_RX_FIFO_SIZE_HS                            (512)
#define DAPV1_OTG_RX_FIFO_ADDR_HS                            (0)
// Sum of IN ep max packet size is 128
// Remain Fifo size is 3584 in bytes, Rx Used 512 bytes 

// TODO:
// I don't know why the max count of TX fifo should <= (7 * EpMaxPacket)
// But it seems the STM32F7xx can be large than (7 * EpMaxPacket)
#define DAPV1_EP0_TX_FIFO_ADDR_HS                            (512)
#define DAPV1_EP0_TX_FIFO_SIZE_HS                            (DAPV1_EP0_TX_SIZE * 7)
#define DAPV1_EP2_TX_FIFO_ADDR_HS                            (960)
#define DAPV1_EP2_TX_FIFO_SIZE_HS                            (DAPV1_EP2_TX_SIZE * 7)
// EndPoints init function for USB OTG core
#if defined(USB_OTG_HS)
#define DAPV1_TUSB_INIT_EP_OTG_HS(dev) \
  do{\
    if(GetUSB(dev) == USB_OTG_HS) { \
      SET_RX_FIFO(dev, DAPV1_OTG_RX_FIFO_ADDR_HS, DAPV1_OTG_RX_FIFO_SIZE_HS);  \
      /* Init Ep0  */\
      INIT_EP_Tx(dev, PCD_ENDP0, DAPV1_EP0_TX_TYPE, DAPV1_EP0_TX_SIZE);  \
      SET_TX_FIFO(dev, PCD_ENDP0, DAPV1_EP0_TX_FIFO_ADDR_HS, DAPV1_EP0_TX_FIFO_SIZE_HS);  \
      INIT_EP_Rx(dev, PCD_ENDP0, DAPV1_EP0_RX_TYPE, DAPV1_EP0_RX_SIZE); \
      /* Init Ep1  */\
      INIT_EP_Rx(dev, PCD_ENDP1, DAPV1_EP1_RX_TYPE, DAPV1_EP1_RX_SIZE); \
      /* Init Ep2  */\
      INIT_EP_Tx(dev, PCD_ENDP2, DAPV1_EP2_TX_TYPE, DAPV1_EP2_TX_SIZE);  \
      SET_TX_FIFO(dev, PCD_ENDP2, DAPV1_EP2_TX_FIFO_ADDR_HS, DAPV1_EP2_TX_FIFO_SIZE_HS);  \
    }\
  }while(0)

#else  // #if defined(USB_OTG_HS)
#define DAPV1_TUSB_INIT_EP_OTG_HS(dev) 
    
#endif  // #if defined(USB_OTG_HS)
#define DAPV1_TUSB_INIT_EP_OTG(dev) \
  do{\
    DAPV1_TUSB_INIT_EP_OTG_FS(dev); \
    DAPV1_TUSB_INIT_EP_OTG_HS(dev); \
  }while(0)


#if defined(USB)
#define DAPV1_TUSB_INIT_EP(dev) DAPV1_TUSB_INIT_EP_FS(dev)

// Teeny USB device init function for FS core
#define DAPV1_TUSB_INIT_DEVICE(dev) \
  do{\
    /* Init device features */       \
    memset(&dev->addr, 0, TUSB_DEVICE_SIZE);    \
    dev->status = DAPV1_DEV_STATUS;         \
    dev->rx_max_size = DAPV1_rxEpMaxSize;         \
    dev->tx_max_size = DAPV1_txEpMaxSize;         \
    dev->descriptors = &DAPV1_descriptors;         \
  }while(0)

#endif

#if defined(USB_OTG_FS) || defined(USB_OTG_HS)
#define DAPV1_TUSB_INIT_EP(dev) DAPV1_TUSB_INIT_EP_OTG(dev)

// Teeny USB device init function for OTG core
#define DAPV1_TUSB_INIT_DEVICE(dev) \
  do{\
    /* Init device features */       \
    memset(&dev->addr, 0, TUSB_DEVICE_SIZE);    \
    dev->status = DAPV1_DEV_STATUS;         \
    dev->descriptors = &DAPV1_descriptors;         \
  }while(0)

#endif

#define DAPV1_TUSB_INIT(dev) \
  do{\
    DAPV1_TUSB_INIT_EP(dev);   \
    DAPV1_TUSB_INIT_DEVICE(dev);   \
  }while(0)

// Get End Point count
#ifndef  EP_NUM
#define  EP_NUM 1
#endif
#if DAPV1_EP_NUM > EP_NUM
#undef   EP_NUM
#define  EP_NUM  DAPV1_EP_NUM
#endif

extern const uint8_t* const DAPV1_StringDescriptors[DAPV1_STRING_COUNT];
extern const tusb_descriptors DAPV1_descriptors;

#define DAPV1_REPORT_DESCRIPTOR_SIZE_IF0  (33)
extern const uint8_t DAPV1_ReportDescriptor_if0[DAPV1_REPORT_DESCRIPTOR_SIZE_IF0];


#endif   // #ifndef __DAPV1_TEENY_USB_INIT_H__
/////////////////////////////////////////
//// Device 11
/////////////////////////////////////////
#ifndef __DAPV2_TEENY_USB_INIT_H__
#define __DAPV2_TEENY_USB_INIT_H__
// forward declare the tusb_descriptors struct
typedef struct _tusb_descriptors tusb_descriptors;

#define DAPV2_VID                                            0x0d28
#define DAPV2_PID                                            0x0204
#define DAPV2_STRING_COUNT                                   (5)

// device.bmAttributes & 0x40   USB_CONFIG_SELF_POWERED
// device.bmAttributes & 0x20   USB_CONFIG_REMOTE_WAKEUP
#define DAPV2_DEV_STATUS                                    (0 | 0)


// Endpoint usage:
#define DAPV2_MAX_EP                                         (2)
#define DAPV2_EP_NUM                                         (DAPV2_MAX_EP + 1)

///////////////////////////////////////////////
//// Endpoint define for STM32 FS Core
///////////////////////////////////////////////

#ifdef DAPV2_BTABLE_ADDRESS
#undef DAPV2_BTABLE_ADDRESS
#endif
#define DAPV2_BTABLE_ADDRESS                                 (0)
#define DAPV2_EP_BUF_DESC_TABLE_SIZE                         (8)
// PMA buffer reserved for buffer description table
#define DAPV2_USB_BUF_START                                  (DAPV2_EP_BUF_DESC_TABLE_SIZE * DAPV2_EP_NUM)

// EndPoints 0 defines
#define DAPV2_EP0_RX_SIZE                                    (64)
#define DAPV2_EP0_RX_ADDR                                    (DAPV2_USB_BUF_START + (0))
#define DAPV2_EP0_TX_SIZE                                    (64)
#define DAPV2_EP0_TX_ADDR                                    (DAPV2_USB_BUF_START + (64))
#define DAPV2_EP0_RX_TYPE                                    USB_EP_CONTROL
#define DAPV2_EP0_TX_TYPE                                    USB_EP_CONTROL

#define DAPV2_EP0_TYPE                                       USB_EP_CONTROL
#define DAPV2_EP0_TX0_ADDR                                   (DAPV2_USB_BUF_START + (0))
#define DAPV2_EP0_TX1_ADDR                                   (DAPV2_USB_BUF_START + (64))
#define DAPV2_EP0_RX0_ADDR                                   (DAPV2_USB_BUF_START + (0))
#define DAPV2_EP0_RX1_ADDR                                   (DAPV2_USB_BUF_START + (64))

// EndPoints 1 defines
#define DAPV2_EP1_RX_SIZE                                    (512)
#define DAPV2_EP1_RX_ADDR                                    (DAPV2_USB_BUF_START + (128))
#define DAPV2_EP1_TX_SIZE                                    (0)
#define DAPV2_EP1_TX_ADDR                                    (DAPV2_USB_BUF_START + (640))
#define DAPV2_EP1_RX_TYPE                                    USB_EP_BULK
#define DAPV2_EP1_TX_TYPE                                    USB_EP_Invalid

#define DAPV2_EP1_TYPE                                       USB_EP_BULK
#define DAPV2_EP1_TX0_ADDR                                   (DAPV2_USB_BUF_START + (128))
#define DAPV2_EP1_TX1_ADDR                                   (DAPV2_USB_BUF_START + (640))
#define DAPV2_EP1_RX0_ADDR                                   (DAPV2_USB_BUF_START + (128))
#define DAPV2_EP1_RX1_ADDR                                   (DAPV2_USB_BUF_START + (640))

// EndPoints 2 defines
#define DAPV2_EP2_RX_SIZE                                    (0)
#define DAPV2_EP2_RX_ADDR                                    (DAPV2_USB_BUF_START + (640))
#define DAPV2_EP2_TX_SIZE                                    (512)
#define DAPV2_EP2_TX_ADDR                                    (DAPV2_USB_BUF_START + (640))
#define DAPV2_EP2_RX_TYPE                                    USB_EP_Invalid
#define DAPV2_EP2_TX_TYPE                                    USB_EP_BULK

#define DAPV2_EP2_TYPE                                       USB_EP_BULK
#define DAPV2_EP2_TX0_ADDR                                   (DAPV2_USB_BUF_START + (640))
#define DAPV2_EP2_TX1_ADDR                                   (DAPV2_USB_BUF_START + (1152))
#define DAPV2_EP2_RX0_ADDR                                   (DAPV2_USB_BUF_START + (640))
#define DAPV2_EP2_RX1_ADDR                                   (DAPV2_USB_BUF_START + (1152))


// EndPoint max packed sizes
extern const uint16_t DAPV2_txEpMaxSize[];
#define DAPV2_TXEP_MAX_SIZE                                  \
const uint16_t DAPV2_txEpMaxSize[] = \
{ DAPV2_EP0_TX_SIZE, 0, DAPV2_EP2_TX_SIZE,  };
extern const uint16_t DAPV2_rxEpMaxSize[];
#define DAPV2_RXEP_MAX_SIZE                                  \
const uint16_t DAPV2_rxEpMaxSize[] = \
{ DAPV2_EP0_RX_SIZE, DAPV2_EP1_RX_SIZE, 0,  };

// EndPoints init function for USB FS core
#define DAPV2_TUSB_INIT_EP_FS(dev) \
  do{\
    /* Init ep0 */ \
    INIT_EP_BiDirection(dev, PCD_ENDP0, DAPV2_EP0_TYPE);  \
    SET_TX_ADDR(dev, PCD_ENDP0, DAPV2_EP0_TX_ADDR);  \
    SET_RX_ADDR(dev, PCD_ENDP0, DAPV2_EP0_RX_ADDR);  \
    SET_RX_CNT(dev, PCD_ENDP0, DAPV2_EP0_RX_SIZE);  \
    /* Init ep1 */ \
    INIT_EP_RxOnly(dev, PCD_ENDP1, DAPV2_EP1_TYPE);  \
    SET_RX_ADDR(dev, PCD_ENDP1, DAPV2_EP1_RX_ADDR);  \
    SET_RX_CNT(dev, PCD_ENDP1, DAPV2_EP1_RX_SIZE);  \
    /* Init ep2 */ \
    INIT_EP_TxOnly(dev, PCD_ENDP2, DAPV2_EP2_TYPE);  \
    SET_TX_ADDR(dev, PCD_ENDP2, DAPV2_EP2_TX_ADDR);  \
}while(0)

///////////////////////////////////////////////
//// Endpoint define for STM32 OTG Core
///////////////////////////////////////////////
#define DAPV2_OTG_MAX_OUT_SIZE                               (512)
#define DAPV2_OTG_CONTROL_EP_NUM                             (1)
#define DAPV2_OTG_OUT_EP_NUM                                 (1)
// RX FIFO size / 4 > (CONTROL_EP_NUM * 5 + 8) +  (MAX_OUT_SIZE / 4 + 1) + (OUT_EP_NUM*2) + 1 = 145

///////////////////////////////////////////////
//// Endpoint define for STM32 OTG FS Core
///////////////////////////////////////////////
#define DAPV2_OTG_RX_FIFO_SIZE_FS                            (580)
#define DAPV2_OTG_RX_FIFO_ADDR_FS                            (0)
// Sum of IN ep max packet size is 576
// Remain Fifo size is 700 in bytes, Rx Used 580 bytes 

// TODO:
// I don't know why the max count of TX fifo should <= (7 * EpMaxPacket)
// But it seems the STM32F7xx can be large than (7 * EpMaxPacket)
#define DAPV2_EP0_TX_FIFO_ADDR_FS                            (580)
#define DAPV2_EP0_TX_FIFO_SIZE_FS                            (DAPV2_EP0_TX_SIZE * 1)
#define DAPV2_EP2_TX_FIFO_ADDR_FS                            (644)
#define DAPV2_EP2_TX_FIFO_SIZE_FS                            (DAPV2_EP2_TX_SIZE * 1)
// EndPoints init function for USB OTG core
#if defined(USB_OTG_FS)
#define DAPV2_TUSB_INIT_EP_OTG_FS(dev) \
  do{\
    if(GetUSB(dev) == USB_OTG_FS) { \
      SET_RX_FIFO(dev, DAPV2_OTG_RX_FIFO_ADDR_FS, DAPV2_OTG_RX_FIFO_SIZE_FS);  \
      /* Init Ep0  */\
      INIT_EP_Tx(dev, PCD_ENDP0, DAPV2_EP0_TX_TYPE, DAPV2_EP0_TX_SIZE);  \
      SET_TX_FIFO(dev, PCD_ENDP0, DAPV2_EP0_TX_FIFO_ADDR_FS, DAPV2_EP0_TX_FIFO_SIZE_FS);  \
      INIT_EP_Rx(dev, PCD_ENDP0, DAPV2_EP0_RX_TYPE, DAPV2_EP0_RX_SIZE); \
      /* Init Ep1  */\
      INIT_EP_Rx(dev, PCD_ENDP1, DAPV2_EP1_RX_TYPE, DAPV2_EP1_RX_SIZE); \
      /* Init Ep2  */\
      INIT_EP_Tx(dev, PCD_ENDP2, DAPV2_EP2_TX_TYPE, DAPV2_EP2_TX_SIZE);  \
      SET_TX_FIFO(dev, PCD_ENDP2, DAPV2_EP2_TX_FIFO_ADDR_FS, DAPV2_EP2_TX_FIFO_SIZE_FS);  \
    }\
  }while(0)

#else  // #if defined(USB_OTG_FS)
#define DAPV2_TUSB_INIT_EP_OTG_FS(dev) 
    
#endif  // #if defined(USB_OTG_FS)

///////////////////////////////////////////////
//// Endpoint define for STM32 OTG HS Core
///////////////////////////////////////////////
#define DAPV2_OTG_RX_FIFO_SIZE_HS                            (580)
#define DAPV2_OTG_RX_FIFO_ADDR_HS                            (0)
// Sum of IN ep max packet size is 576
// Remain Fifo size is 3516 in bytes, Rx Used 580 bytes 

// TODO:
// I don't know why the max count of TX fifo should <= (7 * EpMaxPacket)
// But it seems the STM32F7xx can be large than (7 * EpMaxPacket)
#define DAPV2_EP0_TX_FIFO_ADDR_HS                            (580)
#define DAPV2_EP0_TX_FIFO_SIZE_HS                            (DAPV2_EP0_TX_SIZE * 6)
#define DAPV2_EP2_TX_FIFO_ADDR_HS                            (964)
#define DAPV2_EP2_TX_FIFO_SIZE_HS                            (DAPV2_EP2_TX_SIZE * 6)
// EndPoints init function for USB OTG core
#if defined(USB_OTG_HS)
#define DAPV2_TUSB_INIT_EP_OTG_HS(dev) \
  do{\
    if(GetUSB(dev) == USB_OTG_HS) { \
      SET_RX_FIFO(dev, DAPV2_OTG_RX_FIFO_ADDR_HS, DAPV2_OTG_RX_FIFO_SIZE_HS);  \
      /* Init Ep0  */\
      INIT_EP_Tx(dev, PCD_ENDP0, DAPV2_EP0_TX_TYPE, DAPV2_EP0_TX_SIZE);  \
      SET_TX_FIFO(dev, PCD_ENDP0, DAPV2_EP0_TX_FIFO_ADDR_HS, DAPV2_EP0_TX_FIFO_SIZE_HS);  \
      INIT_EP_Rx(dev, PCD_ENDP0, DAPV2_EP0_RX_TYPE, DAPV2_EP0_RX_SIZE); \
      /* Init Ep1  */\
      INIT_EP_Rx(dev, PCD_ENDP1, DAPV2_EP1_RX_TYPE, DAPV2_EP1_RX_SIZE); \
      /* Init Ep2  */\
      INIT_EP_Tx(dev, PCD_ENDP2, DAPV2_EP2_TX_TYPE, DAPV2_EP2_TX_SIZE);  \
      SET_TX_FIFO(dev, PCD_ENDP2, DAPV2_EP2_TX_FIFO_ADDR_HS, DAPV2_EP2_TX_FIFO_SIZE_HS);  \
    }\
  }while(0)

#else  // #if defined(USB_OTG_HS)
#define DAPV2_TUSB_INIT_EP_OTG_HS(dev) 
    
#endif  // #if defined(USB_OTG_HS)
#define DAPV2_TUSB_INIT_EP_OTG(dev) \
  do{\
    DAPV2_TUSB_INIT_EP_OTG_FS(dev); \
    DAPV2_TUSB_INIT_EP_OTG_HS(dev); \
  }while(0)


#if defined(USB)
#define DAPV2_TUSB_INIT_EP(dev) DAPV2_TUSB_INIT_EP_FS(dev)

// Teeny USB device init function for FS core
#define DAPV2_TUSB_INIT_DEVICE(dev) \
  do{\
    /* Init device features */       \
    memset(&dev->addr, 0, TUSB_DEVICE_SIZE);    \
    dev->status = DAPV2_DEV_STATUS;         \
    dev->rx_max_size = DAPV2_rxEpMaxSize;         \
    dev->tx_max_size = DAPV2_txEpMaxSize;         \
    dev->descriptors = &DAPV2_descriptors;         \
  }while(0)

#endif

#if defined(USB_OTG_FS) || defined(USB_OTG_HS)
#define DAPV2_TUSB_INIT_EP(dev) DAPV2_TUSB_INIT_EP_OTG(dev)

// Teeny USB device init function for OTG core
#define DAPV2_TUSB_INIT_DEVICE(dev) \
  do{\
    /* Init device features */       \
    memset(&dev->addr, 0, TUSB_DEVICE_SIZE);    \
    dev->status = DAPV2_DEV_STATUS;         \
    dev->descriptors = &DAPV2_descriptors;         \
  }while(0)

#endif

#define DAPV2_TUSB_INIT(dev) \
  do{\
    DAPV2_TUSB_INIT_EP(dev);   \
    DAPV2_TUSB_INIT_DEVICE(dev);   \
  }while(0)

// Get End Point count
#ifndef  EP_NUM
#define  EP_NUM 1
#endif
#if DAPV2_EP_NUM > EP_NUM
#undef   EP_NUM
#define  EP_NUM  DAPV2_EP_NUM
#endif

extern const uint8_t* const DAPV2_StringDescriptors[DAPV2_STRING_COUNT];
extern const tusb_descriptors DAPV2_descriptors;

// Enable WCID related code
#define  HAS_WCID

#ifndef WCID_VENDOR_CODE
#define  WCID_VENDOR_CODE       0x17
extern const uint8_t WCID_StringDescriptor_MSOS[];
#endif


#endif   // #ifndef __DAPV2_TEENY_USB_INIT_H__
/////////////////////////////////////////
//// Device 12
/////////////////////////////////////////
#ifndef __MULCFG_TEENY_USB_INIT_H__
#define __MULCFG_TEENY_USB_INIT_H__
// forward declare the tusb_descriptors struct
typedef struct _tusb_descriptors tusb_descriptors;

#define MULCFG_VID                                            0x0483
#define MULCFG_PID                                            0x0011
#define MULCFG_STRING_COUNT                                   (5)

// device.bmAttributes & 0x40   USB_CONFIG_SELF_POWERED
// device.bmAttributes & 0x20   USB_CONFIG_REMOTE_WAKEUP
#define MULCFG_DEV_STATUS                                    (0 | 0)


// Endpoint usage:
#define MULCFG_MAX_EP                                         (4)
#define MULCFG_EP_NUM                                         (MULCFG_MAX_EP + 1)

///////////////////////////////////////////////
//// Endpoint define for STM32 FS Core
///////////////////////////////////////////////

#ifdef MULCFG_BTABLE_ADDRESS
#undef MULCFG_BTABLE_ADDRESS
#endif
#define MULCFG_BTABLE_ADDRESS                                 (0)
#define MULCFG_EP_BUF_DESC_TABLE_SIZE                         (8)
// PMA buffer reserved for buffer description table
#define MULCFG_USB_BUF_START                                  (MULCFG_EP_BUF_DESC_TABLE_SIZE * MULCFG_EP_NUM)

// EndPoints 0 defines
#define MULCFG_EP0_RX_SIZE                                    (64)
#define MULCFG_EP0_RX_ADDR                                    (MULCFG_USB_BUF_START + (0))
#define MULCFG_EP0_TX_SIZE                                    (64)
#define MULCFG_EP0_TX_ADDR                                    (MULCFG_USB_BUF_START + (64))
#define MULCFG_EP0_RX_TYPE                                    USB_EP_CONTROL
#define MULCFG_EP0_TX_TYPE                                    USB_EP_CONTROL

#define MULCFG_EP0_TYPE                                       USB_EP_CONTROL
#define MULCFG_EP0_TX0_ADDR                                   (MULCFG_USB_BUF_START + (0))
#define MULCFG_EP0_TX1_ADDR                                   (MULCFG_USB_BUF_START + (64))
#define MULCFG_EP0_RX0_ADDR                                   (MULCFG_USB_BUF_START + (0))
#define MULCFG_EP0_RX1_ADDR                                   (MULCFG_USB_BUF_START + (64))

// EndPoints 1 defines
#define MULCFG_EP1_RX_SIZE                                    (32)
#define MULCFG_EP1_RX_ADDR                                    (MULCFG_USB_BUF_START + (128))
#define MULCFG_EP1_TX_SIZE                                    (32)
#define MULCFG_EP1_TX_ADDR                                    (MULCFG_USB_BUF_START + (160))
#define MULCFG_EP1_RX_TYPE                                    USB_EP_BULK
#define MULCFG_EP1_TX_TYPE                                    USB_EP_BULK

#define MULCFG_EP1_TYPE                                       USB_EP_BULK
#define MULCFG_EP1_TX0_ADDR                                   (MULCFG_USB_BUF_START + (128))
#define MULCFG_EP1_TX1_ADDR                                   (MULCFG_USB_BUF_START + (160))
#define MULCFG_EP1_RX0_ADDR                                   (MULCFG_USB_BUF_START + (128))
#define MULCFG_EP1_RX1_ADDR                                   (MULCFG_USB_BUF_START + (160))

// EndPoints 2 defines
#define MULCFG_EP2_RX_SIZE                                    (64)
#define MULCFG_EP2_RX_ADDR                                    (MULCFG_USB_BUF_START + (192))
#define MULCFG_EP2_TX_SIZE                                    (64)
#define MULCFG_EP2_TX_ADDR                                    (MULCFG_USB_BUF_START + (256))
#define MULCFG_EP2_RX_TYPE                                    USB_EP_BULK
#define MULCFG_EP2_TX_TYPE                                    USB_EP_BULK

#define MULCFG_EP2_TYPE                                       USB_EP_BULK
#define MULCFG_EP2_TX0_ADDR                                   (MULCFG_USB_BUF_START + (192))
#define MULCFG_EP2_TX1_ADDR                                   (MULCFG_USB_BUF_START + (256))
#define MULCFG_EP2_RX0_ADDR                                   (MULCFG_USB_BUF_START + (192))
#define MULCFG_EP2_RX1_ADDR                                   (MULCFG_USB_BUF_START + (256))

// EndPoints 3 defines
#define MULCFG_EP3_RX_SIZE                                    (16)
#define MULCFG_EP3_RX_ADDR                                    (MULCFG_USB_BUF_START + (320))
#define MULCFG_EP3_TX_SIZE                                    (16)
#define MULCFG_EP3_TX_ADDR                                    (MULCFG_USB_BUF_START + (336))
#define MULCFG_EP3_RX_TYPE                                    USB_EP_INTERRUPT
#define MULCFG_EP3_TX_TYPE                                    USB_EP_INTERRUPT

#define MULCFG_EP3_TYPE                                       USB_EP_INTERRUPT
#define MULCFG_EP3_TX0_ADDR                                   (MULCFG_USB_BUF_START + (320))
#define MULCFG_EP3_TX1_ADDR                                   (MULCFG_USB_BUF_START + (336))
#define MULCFG_EP3_RX0_ADDR                                   (MULCFG_USB_BUF_START + (320))
#define MULCFG_EP3_RX1_ADDR                                   (MULCFG_USB_BUF_START + (336))

// EndPoints 4 defines
#define MULCFG_EP4_RX_SIZE                                    (64)
#define MULCFG_EP4_RX_ADDR                                    (MULCFG_USB_BUF_START + (352))
#define MULCFG_EP4_TX_SIZE                                    (64)
#define MULCFG_EP4_TX_ADDR                                    (MULCFG_USB_BUF_START + (416))
#define MULCFG_EP4_RX_TYPE                                    USB_EP_BULK
#define MULCFG_EP4_TX_TYPE                                    USB_EP_BULK

#define MULCFG_EP4_TYPE                                       USB_EP_BULK
#define MULCFG_EP4_TX0_ADDR                                   (MULCFG_USB_BUF_START + (352))
#define MULCFG_EP4_TX1_ADDR                                   (MULCFG_USB_BUF_START + (416))
#define MULCFG_EP4_RX0_ADDR                                   (MULCFG_USB_BUF_START + (352))
#define MULCFG_EP4_RX1_ADDR                                   (MULCFG_USB_BUF_START + (416))


// EndPoint max packed sizes
extern const uint8_t MULCFG_txEpMaxSize[];
#define MULCFG_TXEP_MAX_SIZE                                  \
const uint8_t MULCFG_txEpMaxSize[] = \
{ MULCFG_EP0_TX_SIZE, MULCFG_EP1_TX_SIZE, MULCFG_EP2_TX_SIZE, MULCFG_EP3_TX_SIZE, MULCFG_EP4_TX_SIZE,  };
extern const uint8_t MULCFG_rxEpMaxSize[];
#define MULCFG_RXEP_MAX_SIZE                                  \
const uint8_t MULCFG_rxEpMaxSize[] = \
{ MULCFG_EP0_RX_SIZE, MULCFG_EP1_RX_SIZE, MULCFG_EP2_RX_SIZE, MULCFG_EP3_RX_SIZE, MULCFG_EP4_RX_SIZE,  };

// EndPoints init function for USB FS core
#define MULCFG_TUSB_INIT_EP_FS(dev) \
  do{\
    /* Init ep0 */ \
    INIT_EP_BiDirection(dev, PCD_ENDP0, MULCFG_EP0_TYPE);  \
    SET_TX_ADDR(dev, PCD_ENDP0, MULCFG_EP0_TX_ADDR);  \
    SET_RX_ADDR(dev, PCD_ENDP0, MULCFG_EP0_RX_ADDR);  \
    SET_RX_CNT(dev, PCD_ENDP0, MULCFG_EP0_RX_SIZE);  \
    /* Init ep1 */ \
    INIT_EP_BiDirection(dev, PCD_ENDP1, MULCFG_EP1_TYPE);  \
    SET_TX_ADDR(dev, PCD_ENDP1, MULCFG_EP1_TX_ADDR);  \
    SET_RX_ADDR(dev, PCD_ENDP1, MULCFG_EP1_RX_ADDR);  \
    SET_RX_CNT(dev, PCD_ENDP1, MULCFG_EP1_RX_SIZE);  \
    /* Init ep2 */ \
    INIT_EP_BiDirection(dev, PCD_ENDP2, MULCFG_EP2_TYPE);  \
    SET_TX_ADDR(dev, PCD_ENDP2, MULCFG_EP2_TX_ADDR);  \
    SET_RX_ADDR(dev, PCD_ENDP2, MULCFG_EP2_RX_ADDR);  \
    SET_RX_CNT(dev, PCD_ENDP2, MULCFG_EP2_RX_SIZE);  \
    /* Init ep3 */ \
    INIT_EP_BiDirection(dev, PCD_ENDP3, MULCFG_EP3_TYPE);  \
    SET_TX_ADDR(dev, PCD_ENDP3, MULCFG_EP3_TX_ADDR);  \
    SET_RX_ADDR(dev, PCD_ENDP3, MULCFG_EP3_RX_ADDR);  \
    SET_RX_CNT(dev, PCD_ENDP3, MULCFG_EP3_RX_SIZE);  \
    /* Init ep4 */ \
    INIT_EP_BiDirection(dev, PCD_ENDP4, MULCFG_EP4_TYPE);  \
    SET_TX_ADDR(dev, PCD_ENDP4, MULCFG_EP4_TX_ADDR);  \
    SET_RX_ADDR(dev, PCD_ENDP4, MULCFG_EP4_RX_ADDR);  \
    SET_RX_CNT(dev, PCD_ENDP4, MULCFG_EP4_RX_SIZE);  \
}while(0)

///////////////////////////////////////////////
//// Endpoint define for STM32 OTG Core
///////////////////////////////////////////////
#define MULCFG_OTG_MAX_OUT_SIZE                               (64)
#define MULCFG_OTG_CONTROL_EP_NUM                             (1)
#define MULCFG_OTG_OUT_EP_NUM                                 (4)
// RX FIFO size / 4 > (CONTROL_EP_NUM * 5 + 8) +  (MAX_OUT_SIZE / 4 + 1) + (OUT_EP_NUM*2) + 1 = 39

///////////////////////////////////////////////
//// Endpoint define for STM32 OTG FS Core
///////////////////////////////////////////////
#define MULCFG_OTG_RX_FIFO_SIZE_FS                            (256)
#define MULCFG_OTG_RX_FIFO_ADDR_FS                            (0)
// Sum of IN ep max packet size is 240
// Remain Fifo size is 1024 in bytes, Rx Used 256 bytes 

// TODO:
// I don't know why the max count of TX fifo should <= (7 * EpMaxPacket)
// But it seems the STM32F7xx can be large than (7 * EpMaxPacket)
#define MULCFG_EP0_TX_FIFO_ADDR_FS                            (256)
#define MULCFG_EP0_TX_FIFO_SIZE_FS                            (MULCFG_EP0_TX_SIZE * 4)
#define MULCFG_EP1_TX_FIFO_ADDR_FS                            (512)
#define MULCFG_EP1_TX_FIFO_SIZE_FS                            (MULCFG_EP1_TX_SIZE * 4)
#define MULCFG_EP2_TX_FIFO_ADDR_FS                            (640)
#define MULCFG_EP2_TX_FIFO_SIZE_FS                            (MULCFG_EP2_TX_SIZE * 4)
#define MULCFG_EP3_TX_FIFO_ADDR_FS                            (896)
#define MULCFG_EP3_TX_FIFO_SIZE_FS                            (MULCFG_EP3_TX_SIZE * 4)
#define MULCFG_EP4_TX_FIFO_ADDR_FS                            (960)
#define MULCFG_EP4_TX_FIFO_SIZE_FS                            (MULCFG_EP4_TX_SIZE * 4)
// EndPoints init function for USB OTG core
#if defined(USB_OTG_FS)
#define MULCFG_TUSB_INIT_EP_OTG_FS(dev) \
  do{\
    if(GetUSB(dev) == USB_OTG_FS) { \
      SET_RX_FIFO(dev, MULCFG_OTG_RX_FIFO_ADDR_FS, MULCFG_OTG_RX_FIFO_SIZE_FS);  \
      /* Init Ep0  */\
      INIT_EP_Tx(dev, PCD_ENDP0, MULCFG_EP0_TX_TYPE, MULCFG_EP0_TX_SIZE);  \
      SET_TX_FIFO(dev, PCD_ENDP0, MULCFG_EP0_TX_FIFO_ADDR_FS, MULCFG_EP0_TX_FIFO_SIZE_FS);  \
      INIT_EP_Rx(dev, PCD_ENDP0, MULCFG_EP0_RX_TYPE, MULCFG_EP0_RX_SIZE); \
      /* Init Ep1  */\
      INIT_EP_Tx(dev, PCD_ENDP1, MULCFG_EP1_TX_TYPE, MULCFG_EP1_TX_SIZE);  \
      SET_TX_FIFO(dev, PCD_ENDP1, MULCFG_EP1_TX_FIFO_ADDR_FS, MULCFG_EP1_TX_FIFO_SIZE_FS);  \
      INIT_EP_Rx(dev, PCD_ENDP1, MULCFG_EP1_RX_TYPE, MULCFG_EP1_RX_SIZE); \
      /* Init Ep2  */\
      INIT_EP_Tx(dev, PCD_ENDP2, MULCFG_EP2_TX_TYPE, MULCFG_EP2_TX_SIZE);  \
      SET_TX_FIFO(dev, PCD_ENDP2, MULCFG_EP2_TX_FIFO_ADDR_FS, MULCFG_EP2_TX_FIFO_SIZE_FS);  \
      INIT_EP_Rx(dev, PCD_ENDP2, MULCFG_EP2_RX_TYPE, MULCFG_EP2_RX_SIZE); \
      /* Init Ep3  */\
      INIT_EP_Tx(dev, PCD_ENDP3, MULCFG_EP3_TX_TYPE, MULCFG_EP3_TX_SIZE);  \
      SET_TX_FIFO(dev, PCD_ENDP3, MULCFG_EP3_TX_FIFO_ADDR_FS, MULCFG_EP3_TX_FIFO_SIZE_FS);  \
      INIT_EP_Rx(dev, PCD_ENDP3, MULCFG_EP3_RX_TYPE, MULCFG_EP3_RX_SIZE); \
      /* Init Ep4  */\
      INIT_EP_Tx(dev, PCD_ENDP4, MULCFG_EP4_TX_TYPE, MULCFG_EP4_TX_SIZE);  \
      SET_TX_FIFO(dev, PCD_ENDP4, MULCFG_EP4_TX_FIFO_ADDR_FS, MULCFG_EP4_TX_FIFO_SIZE_FS);  \
      INIT_EP_Rx(dev, PCD_ENDP4, MULCFG_EP4_RX_TYPE, MULCFG_EP4_RX_SIZE); \
    }\
  }while(0)

#else  // #if defined(USB_OTG_FS)
#define MULCFG_TUSB_INIT_EP_OTG_FS(dev) 
    
#endif  // #if defined(USB_OTG_FS)

///////////////////////////////////////////////
//// Endpoint define for STM32 OTG HS Core
///////////////////////////////////////////////
#define MULCFG_OTG_RX_FIFO_SIZE_HS                            (512)
#define MULCFG_OTG_RX_FIFO_ADDR_HS                            (0)
// Sum of IN ep max packet size is 240
// Remain Fifo size is 3584 in bytes, Rx Used 512 bytes 

// TODO:
// I don't know why the max count of TX fifo should <= (7 * EpMaxPacket)
// But it seems the STM32F7xx can be large than (7 * EpMaxPacket)
#define MULCFG_EP0_TX_FIFO_ADDR_HS                            (512)
#define MULCFG_EP0_TX_FIFO_SIZE_HS                            (MULCFG_EP0_TX_SIZE * 7)
#define MULCFG_EP1_TX_FIFO_ADDR_HS                            (960)
#define MULCFG_EP1_TX_FIFO_SIZE_HS                            (MULCFG_EP1_TX_SIZE * 7)
#define MULCFG_EP2_TX_FIFO_ADDR_HS                            (1184)
#define MULCFG_EP2_TX_FIFO_SIZE_HS                            (MULCFG_EP2_TX_SIZE * 7)
#define MULCFG_EP3_TX_FIFO_ADDR_HS                            (1632)
#define MULCFG_EP3_TX_FIFO_SIZE_HS                            (MULCFG_EP3_TX_SIZE * 7)
#define MULCFG_EP4_TX_FIFO_ADDR_HS                            (1744)
#define MULCFG_EP4_TX_FIFO_SIZE_HS                            (MULCFG_EP4_TX_SIZE * 7)
// EndPoints init function for USB OTG core
#if defined(USB_OTG_HS)
#define MULCFG_TUSB_INIT_EP_OTG_HS(dev) \
  do{\
    if(GetUSB(dev) == USB_OTG_HS) { \
      SET_RX_FIFO(dev, MULCFG_OTG_RX_FIFO_ADDR_HS, MULCFG_OTG_RX_FIFO_SIZE_HS);  \
      /* Init Ep0  */\
      INIT_EP_Tx(dev, PCD_ENDP0, MULCFG_EP0_TX_TYPE, MULCFG_EP0_TX_SIZE);  \
      SET_TX_FIFO(dev, PCD_ENDP0, MULCFG_EP0_TX_FIFO_ADDR_HS, MULCFG_EP0_TX_FIFO_SIZE_HS);  \
      INIT_EP_Rx(dev, PCD_ENDP0, MULCFG_EP0_RX_TYPE, MULCFG_EP0_RX_SIZE); \
      /* Init Ep1  */\
      INIT_EP_Tx(dev, PCD_ENDP1, MULCFG_EP1_TX_TYPE, MULCFG_EP1_TX_SIZE);  \
      SET_TX_FIFO(dev, PCD_ENDP1, MULCFG_EP1_TX_FIFO_ADDR_HS, MULCFG_EP1_TX_FIFO_SIZE_HS);  \
      INIT_EP_Rx(dev, PCD_ENDP1, MULCFG_EP1_RX_TYPE, MULCFG_EP1_RX_SIZE); \
      /* Init Ep2  */\
      INIT_EP_Tx(dev, PCD_ENDP2, MULCFG_EP2_TX_TYPE, MULCFG_EP2_TX_SIZE);  \
      SET_TX_FIFO(dev, PCD_ENDP2, MULCFG_EP2_TX_FIFO_ADDR_HS, MULCFG_EP2_TX_FIFO_SIZE_HS);  \
      INIT_EP_Rx(dev, PCD_ENDP2, MULCFG_EP2_RX_TYPE, MULCFG_EP2_RX_SIZE); \
      /* Init Ep3  */\
      INIT_EP_Tx(dev, PCD_ENDP3, MULCFG_EP3_TX_TYPE, MULCFG_EP3_TX_SIZE);  \
      SET_TX_FIFO(dev, PCD_ENDP3, MULCFG_EP3_TX_FIFO_ADDR_HS, MULCFG_EP3_TX_FIFO_SIZE_HS);  \
      INIT_EP_Rx(dev, PCD_ENDP3, MULCFG_EP3_RX_TYPE, MULCFG_EP3_RX_SIZE); \
      /* Init Ep4  */\
      INIT_EP_Tx(dev, PCD_ENDP4, MULCFG_EP4_TX_TYPE, MULCFG_EP4_TX_SIZE);  \
      SET_TX_FIFO(dev, PCD_ENDP4, MULCFG_EP4_TX_FIFO_ADDR_HS, MULCFG_EP4_TX_FIFO_SIZE_HS);  \
      INIT_EP_Rx(dev, PCD_ENDP4, MULCFG_EP4_RX_TYPE, MULCFG_EP4_RX_SIZE); \
    }\
  }while(0)

#else  // #if defined(USB_OTG_HS)
#define MULCFG_TUSB_INIT_EP_OTG_HS(dev) 
    
#endif  // #if defined(USB_OTG_HS)
#define MULCFG_TUSB_INIT_EP_OTG(dev) \
  do{\
    MULCFG_TUSB_INIT_EP_OTG_FS(dev); \
    MULCFG_TUSB_INIT_EP_OTG_HS(dev); \
  }while(0)


#if defined(USB)
#define MULCFG_TUSB_INIT_EP(dev) MULCFG_TUSB_INIT_EP_FS(dev)

// Teeny USB device init function for FS core
#define MULCFG_TUSB_INIT_DEVICE(dev) \
  do{\
    /* Init device features */       \
    memset(&dev->addr, 0, TUSB_DEVICE_SIZE);    \
    dev->status = MULCFG_DEV_STATUS;         \
    dev->rx_max_size = MULCFG_rxEpMaxSize;         \
    dev->tx_max_size = MULCFG_txEpMaxSize;         \
    dev->descriptors = &MULCFG_descriptors;         \
  }while(0)

#endif

#if defined(USB_OTG_FS) || defined(USB_OTG_HS)
#define MULCFG_TUSB_INIT_EP(dev) MULCFG_TUSB_INIT_EP_OTG(dev)

// Teeny USB device init function for OTG core
#define MULCFG_TUSB_INIT_DEVICE(dev) \
  do{\
    /* Init device features */       \
    memset(&dev->addr, 0, TUSB_DEVICE_SIZE);    \
    dev->status = MULCFG_DEV_STATUS;         \
    dev->descriptors = &MULCFG_descriptors;         \
  }while(0)

#endif

#define MULCFG_TUSB_INIT(dev) \
  do{\
    MULCFG_TUSB_INIT_EP(dev);   \
    MULCFG_TUSB_INIT_DEVICE(dev);   \
  }while(0)

// Get End Point count
#ifndef  EP_NUM
#define  EP_NUM 1
#endif
#if MULCFG_EP_NUM > EP_NUM
#undef   EP_NUM
#define  EP_NUM  MULCFG_EP_NUM
#endif

extern const uint8_t* const MULCFG_StringDescriptors[MULCFG_STRING_COUNT];
extern const tusb_descriptors MULCFG_descriptors;

#define MULCFG_REPORT_DESCRIPTOR_SIZE_IF0  (24)
extern const uint8_t MULCFG_ReportDescriptor_if0[MULCFG_REPORT_DESCRIPTOR_SIZE_IF0];

#define MULCFG_REPORT_DESCRIPTOR_SIZE_IF2  (24)
extern const uint8_t MULCFG_ReportDescriptor_if2[MULCFG_REPORT_DESCRIPTOR_SIZE_IF2];

// Enable WCID related code
#define  HAS_WCID

#ifndef WCID_VENDOR_CODE
#define  WCID_VENDOR_CODE       0x17
extern const uint8_t WCID_StringDescriptor_MSOS[];
#endif


#endif   // #ifndef __MULCFG_TEENY_USB_INIT_H__
/////////////////////////////////////////
//// Device 13
/////////////////////////////////////////
#ifndef __TEENY_USB_INIT_H__
#define __TEENY_USB_INIT_H__
// forward declare the tusb_descriptors struct
typedef struct _tusb_descriptors tusb_descriptors;

#define VID                                            0x2017
#define PID                                            0x0924
#define STRING_COUNT                                   (1)

// device.bmAttributes & 0x40   USB_CONFIG_SELF_POWERED
// device.bmAttributes & 0x20   USB_CONFIG_REMOTE_WAKEUP
#define DEV_STATUS                                    (0 | 0)


// Endpoint usage:
#define MAX_EP                                         (0)
#define EP_NUM                                         (MAX_EP + 1)

///////////////////////////////////////////////
//// Endpoint define for STM32 FS Core
///////////////////////////////////////////////

#ifdef BTABLE_ADDRESS
#undef BTABLE_ADDRESS
#endif
#define BTABLE_ADDRESS                                 (0)
#define EP_BUF_DESC_TABLE_SIZE                         (8)
// PMA buffer reserved for buffer description table
#define USB_BUF_START                                  (EP_BUF_DESC_TABLE_SIZE * EP_NUM)

// EndPoints 0 defines
#define EP0_RX_SIZE                                    (64)
#define EP0_RX_ADDR                                    (USB_BUF_START + (0))
#define EP0_TX_SIZE                                    (64)
#define EP0_TX_ADDR                                    (USB_BUF_START + (64))
#define EP0_RX_TYPE                                    USB_EP_CONTROL
#define EP0_TX_TYPE                                    USB_EP_CONTROL

#define EP0_TYPE                                       USB_EP_CONTROL
#define EP0_TX0_ADDR                                   (USB_BUF_START + (0))
#define EP0_TX1_ADDR                                   (USB_BUF_START + (64))
#define EP0_RX0_ADDR                                   (USB_BUF_START + (0))
#define EP0_RX1_ADDR                                   (USB_BUF_START + (64))


// EndPoint max packed sizes
extern const uint8_t txEpMaxSize[];
#define TXEP_MAX_SIZE                                  \
const uint8_t txEpMaxSize[] = \
{ EP0_TX_SIZE,  };
extern const uint8_t rxEpMaxSize[];
#define RXEP_MAX_SIZE                                  \
const uint8_t rxEpMaxSize[] = \
{ EP0_RX_SIZE,  };

// EndPoints init function for USB FS core
#define TUSB_INIT_EP_FS(dev) \
  do{\
    /* Init ep0 */ \
    INIT_EP_BiDirection(dev, PCD_ENDP0, EP0_TYPE);  \
    SET_TX_ADDR(dev, PCD_ENDP0, EP0_TX_ADDR);  \
    SET_RX_ADDR(dev, PCD_ENDP0, EP0_RX_ADDR);  \
    SET_RX_CNT(dev, PCD_ENDP0, EP0_RX_SIZE);  \
}while(0)

///////////////////////////////////////////////
//// Endpoint define for STM32 OTG Core
///////////////////////////////////////////////
#define OTG_MAX_OUT_SIZE                               (0)
#define OTG_CONTROL_EP_NUM                             (1)
#define OTG_OUT_EP_NUM                                 (0)
// RX FIFO size / 4 > (CONTROL_EP_NUM * 5 + 8) +  (MAX_OUT_SIZE / 4 + 1) + (OUT_EP_NUM*2) + 1 = 15

///////////////////////////////////////////////
//// Endpoint define for STM32 OTG FS Core
///////////////////////////////////////////////
#define OTG_RX_FIFO_SIZE_FS                            (256)
#define OTG_RX_FIFO_ADDR_FS                            (0)
// Sum of IN ep max packet size is 64
// Remain Fifo size is 1024 in bytes, Rx Used 256 bytes 

// TODO:
// I don't know why the max count of TX fifo should <= (7 * EpMaxPacket)
// But it seems the STM32F7xx can be large than (7 * EpMaxPacket)
#define EP0_TX_FIFO_ADDR_FS                            (256)
#define EP0_TX_FIFO_SIZE_FS                            (EP0_TX_SIZE * 7)
// EndPoints init function for USB OTG core
#if defined(USB_OTG_FS)
#define TUSB_INIT_EP_OTG_FS(dev) \
  do{\
    if(GetUSB(dev) == USB_OTG_FS) { \
      SET_RX_FIFO(dev, OTG_RX_FIFO_ADDR_FS, OTG_RX_FIFO_SIZE_FS);  \
      /* Init Ep0  */\
      INIT_EP_Tx(dev, PCD_ENDP0, EP0_TX_TYPE, EP0_TX_SIZE);  \
      SET_TX_FIFO(dev, PCD_ENDP0, EP0_TX_FIFO_ADDR_FS, EP0_TX_FIFO_SIZE_FS);  \
      INIT_EP_Rx(dev, PCD_ENDP0, EP0_RX_TYPE, EP0_RX_SIZE); \
    }\
  }while(0)

#else  // #if defined(USB_OTG_FS)
#define TUSB_INIT_EP_OTG_FS(dev) 
    
#endif  // #if defined(USB_OTG_FS)

///////////////////////////////////////////////
//// Endpoint define for STM32 OTG HS Core
///////////////////////////////////////////////
#define OTG_RX_FIFO_SIZE_HS                            (512)
#define OTG_RX_FIFO_ADDR_HS                            (0)
// Sum of IN ep max packet size is 64
// Remain Fifo size is 3584 in bytes, Rx Used 512 bytes 

// TODO:
// I don't know why the max count of TX fifo should <= (7 * EpMaxPacket)
// But it seems the STM32F7xx can be large than (7 * EpMaxPacket)
#define EP0_TX_FIFO_ADDR_HS                            (512)
#define EP0_TX_FIFO_SIZE_HS                            (EP0_TX_SIZE * 7)
// EndPoints init function for USB OTG core
#if defined(USB_OTG_HS)
#define TUSB_INIT_EP_OTG_HS(dev) \
  do{\
    if(GetUSB(dev) == USB_OTG_HS) { \
      SET_RX_FIFO(dev, OTG_RX_FIFO_ADDR_HS, OTG_RX_FIFO_SIZE_HS);  \
      /* Init Ep0  */\
      INIT_EP_Tx(dev, PCD_ENDP0, EP0_TX_TYPE, EP0_TX_SIZE);  \
      SET_TX_FIFO(dev, PCD_ENDP0, EP0_TX_FIFO_ADDR_HS, EP0_TX_FIFO_SIZE_HS);  \
      INIT_EP_Rx(dev, PCD_ENDP0, EP0_RX_TYPE, EP0_RX_SIZE); \
    }\
  }while(0)

#else  // #if defined(USB_OTG_HS)
#define TUSB_INIT_EP_OTG_HS(dev) 
    
#endif  // #if defined(USB_OTG_HS)
#define TUSB_INIT_EP_OTG(dev) \
  do{\
    TUSB_INIT_EP_OTG_FS(dev); \
    TUSB_INIT_EP_OTG_HS(dev); \
  }while(0)


#if defined(USB)
#define TUSB_INIT_EP(dev) TUSB_INIT_EP_FS(dev)

// Teeny USB device init function for FS core
#define TUSB_INIT_DEVICE(dev) \
  do{\
    /* Init device features */       \
    memset(&dev->addr, 0, TUSB_DEVICE_SIZE);    \
    dev->status = DEV_STATUS;         \
    dev->rx_max_size = rxEpMaxSize;         \
    dev->tx_max_size = txEpMaxSize;         \
    dev->descriptors = &descriptors;         \
  }while(0)

#endif

#if defined(USB_OTG_FS) || defined(USB_OTG_HS)
#define TUSB_INIT_EP(dev) TUSB_INIT_EP_OTG(dev)

// Teeny USB device init function for OTG core
#define TUSB_INIT_DEVICE(dev) \
  do{\
    /* Init device features */       \
    memset(&dev->addr, 0, TUSB_DEVICE_SIZE);    \
    dev->status = DEV_STATUS;         \
    dev->descriptors = &descriptors;         \
  }while(0)

#endif

#define TUSB_INIT(dev) \
  do{\
    TUSB_INIT_EP(dev);   \
    TUSB_INIT_DEVICE(dev);   \
  }while(0)

// Get End Point count
#ifndef  EP_NUM
#define  EP_NUM 1
#endif
#if EP_NUM > EP_NUM
#undef   EP_NUM
#define  EP_NUM  EP_NUM
#endif

extern const uint8_t* const StringDescriptors[STRING_COUNT];
extern const tusb_descriptors descriptors;


#endif   // #ifndef __TEENY_USB_INIT_H__
