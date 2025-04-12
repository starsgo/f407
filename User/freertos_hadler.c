
#include "freertos_handler.h"


TaskHandle_t            TaskUSBDHandlerTask_Handler;  /* ÈÎÎñ¾ä±ú */

SemaphoreHandle_t usdb_handler_binarysema;

void OTG_FS_IRQHandler_Thread(void *pvParameters){
	
		while(1){
				xSemaphoreTake(usdb_handler_binarysema, portMAX_DELAY);
				HAL_PCD_IRQHandler(&g_hpcd);
		}
}