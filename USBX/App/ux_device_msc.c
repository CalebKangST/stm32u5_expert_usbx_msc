/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    ux_device_msc.c
  * @author  MCD Application Team
  * @brief   USBX Device applicative file
  ******************************************************************************
   * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "ux_device_msc.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
/* USER CODE BEGIN PFP */
#define FAT_BLOCK_SIZE    (512)
#define FAT_BLOCK_NUMBER  (128)
static uint8_t fat_memory[FAT_BLOCK_SIZE * FAT_BLOCK_NUMBER]={0x00};
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
/**
  * @brief  Function implementing app_usb_device_thread_media_status.
  * @param arg: Not used
  * @retval status
  */
UINT  STORAGE_GetBlockNbr(void)
{
  return FAT_BLOCK_NUMBER;
}

UINT  STORAGE_GetBlockSize(void)
{
  return FAT_BLOCK_SIZE;
}


UINT STORAGE_Status(VOID *storage, ULONG lun, ULONG media_id, ULONG *media_status)
{

  /* The ATA drive never fails. This is just for app_usb_device only !!!! */
  return (UX_SUCCESS);
}

/**
  * @brief  Function implementing app_usb_device_thread_media_read.
  * @param  storage : Not used
  * @param  lun: Logical unit number
  * @param  lba: Logical block address
  * @param  number_blocks: Blocks number
  * @param  data_pointer: Data
  * @param  media_status: Not used
  * @retval Status (0 : OK / -1 : Error)
  */
UINT STORAGE_Read(VOID *storage, ULONG lun, UCHAR *data_pointer,
                  ULONG number_blocks, ULONG lba, ULONG *media_status)
{
  UINT status = UX_SUCCESS;

  if((lba * FAT_BLOCK_SIZE + number_blocks*FAT_BLOCK_SIZE) >=  (FAT_BLOCK_SIZE * FAT_BLOCK_NUMBER))
    return UX_ERROR;

  memcpy(data_pointer, &fat_memory[lba*FAT_BLOCK_SIZE], number_blocks*FAT_BLOCK_SIZE);

  return (status);
}


/**
  * @brief  Function implementing app_usb_device_thread_media_write.
  * @param  storage : Not used
  * @param  lun: Logical unit number
  * @param  lba: Logical block address
  * @param  number_blocks: Blocks number
  * @param  data_pointer: Data
  * @param  media_status: Not used
  * @retval Status (0 : OK / -1 : Error)
  */
UINT STORAGE_Write(VOID *storage, ULONG lun, UCHAR *data_pointer,
                   ULONG number_blocks, ULONG lba, ULONG *media_status)
{
  UINT status = UX_SUCCESS;

  if((lba * FAT_BLOCK_SIZE + number_blocks*FAT_BLOCK_SIZE) >=  (FAT_BLOCK_SIZE * FAT_BLOCK_NUMBER))
    return UX_ERROR;

  memcpy(&fat_memory[lba*FAT_BLOCK_SIZE], data_pointer, number_blocks*FAT_BLOCK_SIZE);

  return (status);
}

/* USER CODE END 0 */

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

