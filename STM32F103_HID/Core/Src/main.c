/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "dma.h"
#include "fatfs.h"
#include "iwdg.h"
#include "spi.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "DAP_Common.h"
#include "DAP_config.h"
#include "hid_transfer.h"
#include "DAP.h"
#include "teeny_usb.h"
#include "tusbd_user.h"
#include "tusbd_hid.h"
#include "tusbd_cdc.h"
#include "tusbd_msc.h"
#include "tusbd_cdc_rndis.h"
#include "board_config.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

#define USER_RX_EP_SIZE 32
#define CDC_RX_EP_SIZE 32
#define HID_RX_EP_SIZE 64
#define HID_REPORT_DESC COMP_ReportDescriptor_if0
#define HID_REPORT_DESC_SIZE COMP_REPORT_DESCRIPTOR_SIZE_IF0

// allocate more buffer for better performance
__ALIGN_BEGIN uint8_t user_buf[USER_RX_EP_SIZE * 4] __ALIGN_END;

int user_recv_data(tusb_user_device_t *raw, const void *data, uint16_t len);
int user_send_done(tusb_user_device_t *raw);

tusb_user_device_t user_dev = {
    .backend = &user_device_backend,
    .ep_in = 3,
    .ep_out = 3,
    .on_recv_data = user_recv_data,
    .on_send_done = user_send_done,
    .rx_buf = user_buf,
    .rx_size = sizeof(user_buf),
};

// The HID recv buffer size must equal to the out report size
__ALIGN_BEGIN uint8_t hid_buf[HID_RX_EP_SIZE] __ALIGN_END;
int hid_recv_data(tusb_hid_device_t *hid, const void *data, uint16_t len);
int hid_send_done(tusb_hid_device_t *hid);

tusb_hid_device_t hid_dev = {
    .backend = &hid_device_backend,
    .ep_in = 2,
    .ep_out = 2,
    .on_recv_data = hid_recv_data,
    .on_send_done = hid_send_done,
    .rx_buf = hid_buf,
    .rx_size = sizeof(hid_buf),
    .report_desc = HID_REPORT_DESC,
    .report_desc_size = HID_REPORT_DESC_SIZE,
};

// The CDC recv buffer size should equal to the out endpoint size
// or we will need a timeout to flush the recv buffer
uint8_t cdc_buf[CDC_RX_EP_SIZE];

int cdc_recv_data(tusb_cdc_device_t *cdc, const void *data, uint16_t len);
int cdc_send_done(tusb_cdc_device_t *cdc);
void cdc_line_coding_change(tusb_cdc_device_t *cdc);

tusb_cdc_device_t cdc_dev = {
    .backend = &cdc_device_backend,
    .ep_in = 1,
    .ep_out = 1,
    .ep_int = 8,
    .on_recv_data = cdc_recv_data,
    .on_send_done = cdc_send_done,
    .on_line_coding_change = cdc_line_coding_change,
    .rx_buf = cdc_buf,
    .rx_size = sizeof(cdc_buf),
};

int msc_get_cap(tusb_msc_device_t *msc, uint8_t lun, uint32_t *block_num, uint32_t *block_size);
int msc_block_read(tusb_msc_device_t *msc, uint8_t lun, uint8_t *buf, uint32_t block_addr, uint16_t block_len);
int msc_block_write(tusb_msc_device_t *msc, uint8_t lun, const uint8_t *buf, uint32_t block_addr, uint16_t block_len);

tusb_msc_device_t msc_dev = {
    .backend = &msc_device_backend,
    .ep_in = 4,
    .ep_out = 4,
    .max_lun = 0, // 1 logic unit
    .get_cap = msc_get_cap,
    .block_read = msc_block_read,
    .block_write = msc_block_write,
};

// make sure the interface order is same in "composite_desc.lua"
static tusb_device_interface_t *device_interfaces[] = {
    (tusb_device_interface_t *)&hid_dev,
    (tusb_device_interface_t *)&cdc_dev,
    0, // CDC need two interfaces
       //  (tusb_device_interface_t*)&user_dev,
    (tusb_device_interface_t *)&msc_dev,
};

static void init_ep(tusb_device_t *dev)
{
  COMP_TUSB_INIT(dev);
}

tusb_device_config_t device_config = {
    .if_count = sizeof(device_interfaces) / sizeof(device_interfaces[0]),
    .interfaces = &device_interfaces[0],
    .ep_init = init_ep,
};

void tusb_delay_ms(uint32_t ms)
{
  uint32_t i, j;
  for (i = 0; i < ms; ++i)
    for (j = 0; j < 200; ++j)
      ;
}

//static int user_len = 0;
int user_recv_data(tusb_user_device_t *raw, const void *data, uint16_t len)
{
// user_len = (int)len;
  return 1; // return 1 means the recv buffer is busy
}

int user_send_done(tusb_user_device_t *raw)
{
  tusb_set_rx_valid(raw->dev, raw->ep_out);
  return 0;
}

static int hid_len = 0;
int hid_recv_data(tusb_hid_device_t *hid, const void *data, uint16_t len)
{
  hid_len = (int)len;
  HID_GetOutReport(hid_buf, len);
  return 1; // return 1 means the recv buffer is busy
}

int hid_send_done(tusb_hid_device_t *hid)
{
  tusb_set_rx_valid(hid->dev, hid->ep_out);
  HID_SetInReport();
  return 0;
}

static int cdc_len = 0;
int cdc_recv_data(tusb_cdc_device_t *cdc, const void *data, uint16_t len)
{
  cdc_len = (int)len;
  return 1; // return 1 means the recv buffer is busy
}

int cdc_send_done(tusb_cdc_device_t *cdc)
{
  tusb_set_rx_valid(cdc->dev, cdc->ep_out);
  return 0;
}

void cdc_line_coding_change(tusb_cdc_device_t *cdc)
{
  // TODO, handle the line coding change
  //cdc->line_coding.bitrate;
  //cdc->line_coding.databits;
  //cdc->line_coding.stopbits;
  //cdc->line_coding.parity;
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_SPI1_Init();
  MX_USART2_UART_Init();

  MX_SPI2_Init();
  MX_IWDG_Init();
  MX_FATFS_Init();
  /* USER CODE BEGIN 2 */
	tusb_device_t *dev = tusb_get_device(TEST_APP_USB_CORE);
	tusb_set_device_config(dev, &device_config);
	tusb_open_device(dev);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	if (hid_len)
    {
      usbd_hid_process();
    }
    //    if(user_len){
    //      for(int i=0;i<user_len;i++){
    // //       user_buf[i]+=1;
    //      }
    //      tusb_user_device_send(&user_dev, user_buf, user_len);
    //      user_len = 0;
    //    }

    if (cdc_len)
    {
      tusb_cdc_device_send(&cdc_dev, cdc_buf, cdc_len);
      cdc_len = 0;
    }

    tusb_msc_device_loop(&msc_dev);
  /* USER CODE END 3 */
}
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USB;
  PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_PLL_DIV1_5;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
