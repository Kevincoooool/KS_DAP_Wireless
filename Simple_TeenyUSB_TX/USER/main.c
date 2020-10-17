/*
* @Descripttion: 
* @version: 
* @Author: Kevincoooool
* @Date: 2020-08-04 20:32:30
 * @LastEditors  : Kevincoooool
 * @LastEditTime : 2020-10-16 19:34:51
 * @FilePath     : \Simple_TeenyUSB_TX\USER\main.c
*/
#include "bsp_spi.h"
#include "hid_transfer.h"
#include "teeny_usb.h"
#include "tusbd_cdc_rndis.h"
#include "board_config.h"
#include "tusb_cdc.h"
#include "teeny_usb.h"
#include "tusbd_user.h"
#include "tusbd_hid.h"
#include "tusbd_cdc.h"
#include "tusbd_msc.h"
#include "DAP.h"
#include "usart.h"
#include "include.h"
#include "w25qxx.h"
#include "oled.h"
#include "string.h"
#include "swd_host.h"
#include "SWD_flash.h"
#include "SWD_opt.h"
#include "ff.h"     /* FatFs configurations and declarations */
#include "diskio.h" /* Declarations of low level disk I/O functions */
uint8_t FLASH_SWD(uint8_t *File);

/***********************文件系统使用定义************************/
FIL fnew; /* file objects */
FILINFO FileInfo;
DIR DirInfo;
FATFS fs; /* Work area (file system object) for logical drives */
FRESULT Res;
UINT br, bw; /* File R/W count */
/***********************变量定义************************/
char rData[1024] = "";
uint8_t readflag = 1;
uint32_t addr = 0;
uint32_t i = 0;
uint32_t select = 0;
uint8_t breakDebug = 0;
uint8_t debugMode = 0;
uint16_t bytesread;
uint8_t Logo[] = "BRONSON";
extern uint8_t MYUSB_Request[64 + 1];
extern uint8_t MYUSB_Response[64 + 1];
extern int hid_len, cdc_len;
extern uint8_t cdc_buf[32];
extern tusb_hid_device_t hid_dev;
extern tusb_cdc_device_t cdc_dev;
extern tusb_msc_device_t msc_dev;
extern tusb_device_config_t device_config;
uint8_t NRF_OK = 1;
uint8_t In_MYUSB_Response[64 + 3]; // Request  Buffer
uint8_t Out_MYUSB_Request[64 + 3]; // Response Buffer
extern uint8_t dealing_data;
uint8_t ccc[20];
unsigned char FlashLogo[]={
  0x00,0x00,0x00,0x00,0x80,0xC0,0xE0,0x70,0x38,0x38,0x1C,0x1C,0x0C,0x0C,0x0E,0x0E,
  0x0E,0x0E,0x8E,0xCC,0xEC,0xEC,0xEC,0xF8,0xF8,0xF8,0x7C,0xFE,0x8F,0x07,0x03,0x00,
  0x00,0x00,0xC0,0xFC,0xFF,0x0F,0x03,0x80,0x80,0xC0,0xC0,0xE0,0xF0,0xF8,0xF8,0xFC,
  0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xBF,0x8F,0x87,0x81,0x80,0x03,0x07,0x7F,0xFC,
  0xC0,0x00,0x00,0x07,0x7F,0xFF,0xE0,0x80,0x03,0x03,0xC3,0xE3,0xF3,0xFF,0xFF,0xFF,
  0xFF,0xFF,0xFF,0xFF,0x7F,0x7F,0x3F,0x1F,0x0F,0x0F,0x07,0x03,0x03,0x80,0xC0,0xFC,
  0x7F,0x0F,0x00,0x00,0x00,0x00,0xC1,0xE3,0xF7,0x7C,0x7F,0x3F,0x1F,0x6F,0x6F,0x6F,
  0x67,0xE3,0xC3,0xC1,0xC0,0xE0,0xE0,0x60,0x60,0x70,0x38,0x38,0x1C,0x0E,0x0F,0x03,
  0x01,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,
};
int main(void)
{
	uint8_t RES_FS = 0;
	char fat[6] ={ '1','2','3','4','5','6'};
	HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);
	BYTE work[FF_MAX_SS]; /* Work area (larger is better for processing time) */

	tusb_device_t *dev = tusb_get_device(TEST_APP_USB_CORE);
  tusb_set_device_config(dev, &device_config);
  tusb_open_device(dev);
    /* Format the default drive with default parameters */
    
  uint16_t cnt = 0;
  DAP_SPI_Init();
  DAP_Setup();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  W25QXX_Init();
  OLED_Init();
  OLED_Clear();                                //清空OLED屏幕
  OLED_ShowString(0, 0, "DAP Connect", 12, 1); //绘制提示词
	RES_FS = f_mount(&fs,"",1);
//f_mkfs("", 0, work, sizeof(work));
  if (RES_FS == FR_OK )                        /* 打开文件夹目录成功，目录信息已经在dir结构体中保存 */
  {
    OLED_ShowString(0, 10, "Fatfs success!", 12, 1);
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_14, GPIO_PIN_SET);
  }
  else if(RES_FS == FR_NO_FILESYSTEM )
  {
	  
	  OLED_ShowString(0, 10, "Fatfs geshihua..", 12, 1);
	  f_mkfs("", 0, work, sizeof(work));
    OLED_ShowString(0, 10, "geshihua finish", 12, 1);
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_14, GPIO_PIN_RESET);
  }
  else
  {

    OLED_ShowString(0, 10, "Fatfs failed..", 12, 1);
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_14, GPIO_PIN_RESET);
  }
	f_open(&fnew, (const TCHAR *)"22.txt", FA_CREATE_NEW | FA_WRITE);
 
    /* Write a message */
	f_write(&fnew, "nihaoya!", sizeof("nihaoya!")-1, &bw);
    
	f_close(&fnew);
	
  // NRF_OK = NRF_Check();
  // if (NRF_OK == 0)
  // {
  //     NRF_Init(MODEL_TX2, 51);
  // }
//	if (f_open(&fnew, (const TCHAR *)"22.txt", FA_READ) == FR_OK)
//	{
//		f_read(&fnew, rData, 20, (void *)&bytesread);
//		sprintf((char*)ccc,rData,20);
//		ccc[20]=0;
//		OLED_ShowString(0, 40, ccc, 12, 1);
//	}

  if (f_open(&fnew, (const TCHAR *)"ToyDog.bin", FA_READ) == FR_OK)
  {
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
    OLED_ShowString(0, 20, "AUTO FLASH", 12, 1);
    while (!FLASH_SWD("ToyDog.bin"))
    {
      uint8_t WaitTips[] = "...";
      OLED_ShowString(75, 30, "          ", 12, 1);
      OLED_ShowString(45, 30, "WAIT", 12, 1);
      for (i = 0; i < 3; i++)
      {
        OLED_ShowChar(69 + i * 6, 2, WaitTips[i], 12, 1);
        HAL_Delay(200);
      }
      OLED_ShowString(75, 30, "       ", 12, 1);
    }
    OLED_ShowString(98, 50, "BACK", 12, 1);
  }
  else
  {
    OLED_ShowString(0, 30, "Open Bin failed", 12, 1);
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
  }

  while (1)
  {

    cnt++;
    if (cnt > 500&&!dealing_data)
    {
      cnt = 0;

      if (swd_init_debug())
      {
		
        OLED_ShowString(0, 20, "CONNECT!!!!", 12, 1);
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_15, GPIO_PIN_RESET);
		  
      }
      else
      {
       OLED_ShowString(0, 20, "DISCONNECT!", 12, 1);
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_15, GPIO_PIN_SET);
      }
    }

    HAL_UART_Receive_DMA(&huart1, rx_buffer, BUFFER_SIZE);

#if !ONLINE
//    NRF_Check_Event(); //检测nrf数据
//    if (NRF_Connect() == 0)
//    {
//    }
#endif
#if !WIRELESS_RX
    if (hid_len)
    {
      hid_len = 0;
#if ONLINE
      usbd_hid_process_online();
#elif WIRELESS_TX
      usbd_hid_process_wireless_tx();
#endif
    }

#elif WIRELESS_RX
    usbd_hid_process_wireless_rx();
#endif
//    if (cdc_len)
//    {
//      tusb_cdc_device_send(&cdc_dev, cdc_buf, cdc_len);
//      cdc_len = 0;
//    }

    tusb_msc_device_loop(&msc_dev);
  }
}
uint32_t progess,address=0x0;
uint8_t FLASH_SWD(uint8_t *File)
{
	
  Res = f_open(&fnew, (const TCHAR *)File, FA_READ);
  if (Res == FR_OK)
  {
    readflag = 1;
 //   address = 0;
    if (swd_init_debug())
    {
      if (target_opt_init() == ERROR_SUCCESS)
      {
        if (target_opt_erase_chip() != ERROR_SUCCESS)
        {
          return 0;
        }
      }
      else
        return 0;
      target_opt_uninit();
      if (swd_init_debug())
      {
        if (target_flash_init(0x08000000) == ERROR_SUCCESS)
        {
          if (target_flash_erase_chip() == ERROR_SUCCESS)
          {
            while (readflag)
            {
              f_read(&fnew, rData, 1024, (void *)&bytesread);
				
				
				 
//				OLED_ShowNumber(0, 30, f_size(&fnew), 12, 12);
//				
              if (bytesread < 1024)
              {
                readflag = 0;
              }
              if (target_flash_program_page(0x08000000 + address, &rData[0], 1024) == ERROR_SUCCESS)
              {
				 address += 1024;
                progess = (((double)address / f_size(&fnew)) * 100);
                if (progess >= 10 && progess < 20)
                {
                  HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
                  OLED_ShowString(0, 40, "=", 12, 1);
                  OLED_ShowString(95, 40, "10%", 12, 1);
                }
                if (progess >= 20 && progess < 30)
                {
                  HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
                  OLED_ShowString(0, 40, "==", 12, 1);
                  OLED_ShowString(95, 40, "20%", 12, 1);
                }
                if (progess >= 30 && progess < 40)
                {
                  HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
                  OLED_ShowString(0, 40, "===", 12, 1);
                  OLED_ShowString(95, 40, "30%", 12, 1);
                }
                if (progess >= 40 && progess < 50)
                {
                  HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
                  OLED_ShowString(0, 40, "====", 12, 1);
                  OLED_ShowString(95, 40, "40%", 12, 1);
                }
                if (progess >= 50 && progess < 60)
                {
                  HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
                  OLED_ShowString(0, 40, "=====", 12, 1);
                  OLED_ShowString(95, 40, "50%", 12, 1);
                }
                if (progess >= 60 && progess < 70)
                {
                  HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
                  OLED_ShowString(0, 40, "======", 12, 1);
                  OLED_ShowString(95, 40, "60%", 12, 1);
                }
                if (progess >= 70 && progess < 80)
                {
                  HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
                  OLED_ShowString(0, 40, "=======", 12, 1);
                  OLED_ShowString(95, 40, "70%", 12, 1);
                }
                if (progess >= 80 && progess < 90)
                {
                  HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
                  OLED_ShowString(0, 40, "=======", 12, 1);
                  OLED_ShowString(95, 40, "80%", 12, 1);
                }
                if (progess >= 90 && progess < 100)
                {
                  HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
                  OLED_ShowString(0, 40, "=========", 12, 1);
                  OLED_ShowString(95, 40, "90%", 12, 1);
                }
				if (progess == 100)
				{
				OLED_ShowString(0, 40, "==========", 12, 1);
                  OLED_ShowString(95, 40, "100%", 12, 1);
				}
              }
              else
                return 0;
              
            }
            if (swd_init_debug())
            {
              HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
              swd_set_target_reset(0); //复位运行
              HAL_Delay(100);
              OLED_ShowString(0, 40, "==========", 12, 1);
              OLED_ShowString(0, 50, "DONE", 12, 1);
              return 1;
            }
            else
              return 0;
          }
          else
            return 0;
        }
        target_flash_uninit();
      }
      else
        return 0;
    }
    else
      return 0;
  }
  else
    return 0;
  return 0;
}
