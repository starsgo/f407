#include "usbd_conf.h"
#include "usbd_core.h"
#include "usbd_def.h"
#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#define TASK_USBD_HANDLER_PRIO      4                   /* �������ȼ� */
#define TASK_USBD_HANDLER_STK_SIZE  128                 /* �����ջ��С */

extern TaskHandle_t            TaskUSBDHandlerTask_Handler;  /* ������ */

extern SemaphoreHandle_t usdb_handler_binarysema;

void OTG_FS_IRQHandler_Thread(void *pvParameters);