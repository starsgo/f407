/**
 ****************************************************************************************************
 * @file        freertos.c
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.4
 * @date        2022-01-04
 * @brief       FreeRTOS 移植实验
 * @license     Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ****************************************************************************************************
 * @attention
 *
 * 实验平台:正点原子 探索者F407开发板
 * 在线视频:www.yuanzige.com
 * 技术论坛:www.openedv.com
 * 公司网址:www.alientek.com
 * 购买地址:openedv.taobao.com
 *
 ****************************************************************************************************
 */

#include "freertos_demo.h"
#include "./SYSTEM/usart/usart.h"
#include "./BSP/LED/led.h"
#include "./BSP/SDIO/sdio_sdcard.h"
#include "./BSP/KEY/key.h"
#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/delay/delay.h"
#include "./FATFS/exfuns/exfuns.h"//#include "./BSP/LCD/lcd.h"
/*FreeRTOS*********************************************************************************************/
#include "FreeRTOS.h"
#include "task.h"
#include "./BSP/NORFLASH/norflash.h"

#include "usbd_desc.h"
#include "usbd_msc.h"
#include "usbd_storage.h"
#include "usbd_conf.h"
#include "usbd_desc_cdc.h"
#include "usbd_cdc.h"
#include "usbd_cdc_interface_cdc.h"
#include "usbd_conf.h"

#include "freertos_handler.h"

extern USBD_DescriptorsTypeDef VCP_Desc;
/******************************************************************************************************/
/*FreeRTOS配置*/

/* START_TASK 任务 配置
 * 包括: 任务句柄 任务优先级 堆栈大小 创建任务
 */
#define START_TASK_PRIO 1                   /* 任务优先级 */
#define START_STK_SIZE  128                 /* 任务堆栈大小 */
TaskHandle_t            StartTask_Handler;  /* 任务句柄 */
void start_task(void *pvParameters);        /* 任务函数 */

///* TASK1 任务 配置
// * 包括: 任务句柄 任务优先级 堆栈大小 创建任务
// */
#define TASK1_PRIO      2                   /* 任务优先级 */
#define TASK1_STK_SIZE  128                 /* 任务堆栈大小 */
TaskHandle_t            Task1Task_Handler;  /* 任务句柄 */
void task1(void *pvParameters);             /* 任务函数 */

///* TASK2 任务 配置
// * 包括: 任务句柄 任务优先级 堆栈大小 创建任务
// */
//#define TASK2_PRIO      3                   /* 任务优先级 */
//#define TASK2_STK_SIZE  128                 /* 任务堆栈大小 */
//TaskHandle_t            Task2Task_Handler;  /* 任务句柄 */
//void task2(void *pvParameters);             /* 任务函数 */


//#define TASK_SDIO_PRIO      3                   /* 任务优先级 */
//#define TASK_SDIO_STK_SIZE  128                 /* 任务堆栈大小 */
//TaskHandle_t            TaskSDIOTask_Handler;  /* 任务句柄 */
//void task_sdio(void *pvParameters);             /* 任务函数 */

#define TASK_USBD_PRIO      3                   /* 任务优先级 */
#define TASK_USBD_STK_SIZE  256                 /* 任务堆栈大小 */
TaskHandle_t            TaskUSBDTask_Handler;  /* 任务句柄 */
void task_usbd(void *pvParameters);             /* 任务函数 */

#define TASK_FATFS_PRIO      3                   /* 任务优先级 */
#define TASK_FATFS_STK_SIZE  512                 /* 任务堆栈大小 */
TaskHandle_t            TaskFATFSTask_Handler;  /* 任务句柄 */
void task_fatfs(void *pvParameters);             /* 任务函数 */

/******************************************************************************************************/

/* LCD刷屏时使用的颜色 */
//uint16_t lcd_discolor[11] = {WHITE, BLACK, BLUE, RED,
//                             MAGENTA, GREEN, CYAN, YELLOW,
//                             BROWN, BRRED, GRAY};

/**
 * @brief       FreeRTOS例程入口函数
 * @param       无
 * @retval      无
 */
void freertos_demo(void)
{
		printf("freertos test\r\n");

    
    xTaskCreate((TaskFunction_t )start_task,            /* 任务函数 */
                (const char*    )"start_task",          /* 任务名称 */
                (uint16_t       )START_STK_SIZE,        /* 任务堆栈大小 */
                (void*          )NULL,                  /* 传入给任务函数的参数 */
                (UBaseType_t    )START_TASK_PRIO,       /* 任务优先级 */
                (TaskHandle_t*  )&StartTask_Handler);   /* 任务句柄 */
    vTaskStartScheduler();
}

/**
 * @brief       start_task
 * @param       pvParameters : 传入参数(未用到)
 * @retval      无
 */
void start_task(void *pvParameters)
{
		// turn off interrupt
    taskENTER_CRITICAL();           
		uint64_t id;
	
		//initialize SD
		while (sd_init()) 
    {
        delay_ms(500);
        delay_ms(500);
        LED0_TOGGLE();  /* LED0闪烁 */
				printf("loading sd\r\n");
			
				break;					//SD is not necessary
    }
		show_sdcard_info(); 
		
		//initialize SD
		norflash_init(); 		
		id = norflash_read_id();
		while ((id == 0) || (id == 0XFFFF)){
				printf("loading flash\r\n");
				norflash_init(); 		
				id = norflash_read_id();
//				break;					//flash is necessary
    }
		printf("flash success \r\n");

		usdb_handler_binarysema = xSemaphoreCreateBinary();
		if(usdb_handler_binarysema == NULL){
				printf("error create binarysema\r\n");
				return;
		}
		
    /* 创建任务1 */
//    xTaskCreate((TaskFunction_t )task1,
//                (const char*    )"task1",
//                (uint16_t       )TASK1_STK_SIZE,
//                (void*          )NULL,
//                (UBaseType_t    )TASK1_PRIO,
//                (TaskHandle_t*  )&Task1Task_Handler);
//    /* 创建任务2 */
//    xTaskCreate((TaskFunction_t )task2,
//                (const char*    )"task2",
//                (uint16_t       )TASK2_STK_SIZE,
//                (void*          )NULL,
//                (UBaseType_t    )TASK2_PRIO,
//                (TaskHandle_t*  )&Task2Task_Handler);
//		xTaskCreate((TaskFunction_t )task_sdio,
//                (const char*    )"task_sdoo",
//                (uint16_t       )TASK_SDIO_STK_SIZE,
//                (void*          )NULL,
//                (UBaseType_t    )TASK_SDIO_PRIO,
//                (TaskHandle_t*  )&TaskSDIOTask_Handler);
//		xTaskCreate((TaskFunction_t )OTG_FS_IRQHandler_Thread,
//                (const char*    )"task_usbd_hanlder",
//                (uint16_t       )TASK_USBD_HANDLER_STK_SIZE,
//                (void*          )NULL,
//                (UBaseType_t    )TASK_USBD_HANDLER_PRIO,
//                (TaskHandle_t*  )&TaskUSBDHandlerTask_Handler);
		xTaskCreate((TaskFunction_t )task_usbd,
                (const char*    )"task_usbd",
                (uint16_t       )TASK_USBD_STK_SIZE,
                (void*          )NULL,
                (UBaseType_t    )TASK_USBD_PRIO,
                (TaskHandle_t*  )&TaskUSBDTask_Handler);
		xTaskCreate((TaskFunction_t )task_fatfs,
                (const char*    )"task_fatfs",
                (uint16_t       )TASK_FATFS_STK_SIZE,
                (void*          )NULL,
                (UBaseType_t    )TASK_FATFS_PRIO,
                (TaskHandle_t*  )&TaskFATFSTask_Handler);
    vTaskDelete(StartTask_Handler); /* 删除开始任务 */
    taskEXIT_CRITICAL();            /* 退出临界区 */
}

/**
 * @brief       task1
 * @param       pvParameters : 传入参数(未用到)
 * @retval      无
 */
void task1(void *pvParameters)
{
    //uint32_t task1_num = 0;
    
    while(1)
    {
        printf("uart_task\r\n");
				LED0_TOGGLE();                                                  /* LED0闪烁 */
        vTaskDelay(1000);                                               /* 延时1000ticks */
    }
}

/**
 * @brief       task2
 * @param       pvParameters : 传入参数(未用到)
 * @retval      无
 */
void task2(void *pvParameters)
{
    float float_num = 0.0;
    
    while(1)
    {
        float_num += 0.01f;                         /* 更新数值 */
        printf("float_num: %0.4f\r\n", float_num);  /* 打印数值 */
        vTaskDelay(1000);                           /* 延时1000ticks */
    }
}

void task_sdio(void *pvParameters){
	
    /* 打印SD卡相关信息 */
		uint8_t key;
    uint8_t t = 0;
	
    show_sdcard_info(); 
   
    while (1)
    {
        key = key_scan(0);

        if (key == KEY0_PRES)       /* KEY0按下了 */
        {
            sd_test_read(0,1);      /* 从0扇区读取1*512字节的内容 */
        }

        t++;
        delay_ms(10);

        if (t == 20){
            t = 0;
        }
    }
}

extern USBD_HandleTypeDef USBD_Device;             /* USB Device处理结构体 */
extern volatile uint8_t g_usb_state_reg;    /* USB状态 */
extern volatile uint8_t g_device_state;     /* USB连接 情况 */

void task_usbd(void *pvParameters){
		printf("----------------task usbd start-------------\r\n");

	        
	
		uint16_t id;
		uint8_t offline_cnt = 0;
    uint8_t tct = 0;
    uint8_t usb_sta;
    uint8_t device_sta;
    uint64_t card_capacity; 
		
		USBD_Init(&USBD_Device, &MSC_Desc, 0);                              /* 初始化USB */
    USBD_RegisterClass(&USBD_Device, USBD_MSC_CLASS);                   /* 添加类 */
    USBD_MSC_RegisterStorage(&USBD_Device, &USBD_DISK_fops);            /* 为MSC类添加回调函数 */
    USBD_Start(&USBD_Device);                                           /* 开启USB */
//    delay_ms(1800);
		vTaskDelay(pdMS_TO_TICKS(1000));

    while (1)
    {
//        delay_ms(1);
				vTaskDelay(pdMS_TO_TICKS(10));
        if (usb_sta != g_usb_state_reg){
            if (g_usb_state_reg & 0x01){
                LED1(0);
            }
            if (g_usb_state_reg & 0x02){
                LED1(0);
            }
            if (g_usb_state_reg & 0x04){
            }
            else{
            }
            if (g_usb_state_reg & 0x08){
										printf("USBD_ReadErr\r\n");
            }
            else{
            }
            usb_sta = g_usb_state_reg; /* 记录最后的状态 */
        }

        if (device_sta != g_device_state){
            if (g_device_state == 1){
//								printf("USBD_BOTH_DIR Connected\r\n");
            }
            else{
//								printf("USBD_BOTH_DIR DisConnected\r\n");
            } 
            device_sta = g_device_state;
        }
        tct++;
        if (tct == 200){
            tct = 0;
            LED1(1);        /* 关闭 LED1 */
            LED0_TOGGLE();  /* LED0 闪烁 */
            if (g_usb_state_reg & 0x10){
                offline_cnt = 0;    /* USB连接了,则清除offline计数器 */
                g_device_state = 1;
            }
            else{
                offline_cnt++;
                if (offline_cnt > 10){
                    g_device_state = 0;/* 2s内没收到在线标记,代表USB被拔出了 */
                }
            }
            g_usb_state_reg = 0;
        }
    }
}

void task_fatfs(void *pvParameters){
//		delay_ms(1000);
		vTaskDelay(pdMS_TO_TICKS(3000));

	  printf("----------------task fatfs start-------------\r\n");
	
		uint32_t total, free;
    uint8_t t = 0;
    uint8_t res = 0;
		uint8_t key;
		uint8_t buffer[24],i;
		unsigned int len;
	
	  exfuns_init();                  /* 为fatfs相关变量申请内存 */
	
		//mount flash
	  res = f_mount(fs[1], "1:", 1);  /* 挂载FLASH */	
		if(res == 0x00){
				printf("flash mounted\r\n");
		}
		if (res == 0X0D){                /* FLASH磁盘,FAT文件系统错误,重新格式化FLASH */
				printf("flash no file system\r\n");
    }
	
		f_mount(fs[0], "0:", 1);        /* 挂载SD卡 */
		if(res == 0x00){
				printf("sd mounted\r\n");
		}
		if (res == 0X0D){                /* FLASH磁盘,FAT文件系统错误,重新格式化FLASH */
				printf("sd no file system\r\n");
    }
		
		while (1){
        key = key_scan(0);
        if (key == KEY0_PRES){
//						printf("key pressed \r\n");
//						printf("task fatfs : make filesystem of flash\r\n");
//						MKFS_PARM defopt ;		
//						memset(&defopt, 0, sizeof(defopt));
//						defopt.fmt = FM_SFD;          // ??:Super Floppy ??
//						defopt.au_size = 4096; 		
//						res = f_mkfs("1	:", 0, 0, FF_MAX_SS);
						FIL file;
						res = f_open(&file, "1:\\test\\test.txt", FA_READ);
						if(res != FR_OK){
								printf("file open error\r\n");
						}
						f_read(&file, buffer, 24, &len);
						for(i = 0; i < len; i++){
								printf("%c",buffer[i]);
						}
						f_close(&file);
						vTaskDelay(pdMS_TO_TICKS(1000));
				}
				vTaskDelay(pdMS_TO_TICKS(500));
    }
}

//void task_usbd_cdc(void *pvParameters){
//	  uint16_t len;
//    uint16_t times = 0;
//    uint8_t usbstatus = 0;
//	
//		USBD_Init(&USBD_Device, &VCP_Desc, 0);                      /* 初始化USB */
//    USBD_RegisterClass(&USBD_Device, USBD_CDC_CLASS);           /* 添加类 */
//    USBD_CDC_RegisterInterface(&USBD_Device, &USBD_CDC_fops);   /* 为MSC类添加回调函数 */
//    USBD_Start(&USBD_Device);  
//	
//		while(1)
//    {
//        delay_ms(1);
//        if (usbstatus != g_device_state)    /* USB连接状态发生了改变 */
//        {
//            usbstatus = g_device_state;     /* 记录新的状态 */

//            if (usbstatus == 1){
//                LED1(0);    /* 绿灯亮 */
//            }
//            else{
//                LED1(1);    /* 绿灯灭 */
//            }
//        }

//        if (g_usb_usart_rx_sta & 0x8000)
//        {
//            len = g_usb_usart_rx_sta & 0x3FFF;  /* 得到此次接收到的数据长度 */
//            usb_printf("\r\n您发送的消息长度为:%d\r\n\r\n", len);
//            cdc_vcp_data_tx(g_usb_usart_rx_buffer, len);
//            usb_printf("\r\n\r\n");             /* 插入换行 */
//            g_usb_usart_rx_sta = 0;
//        }
//        else
//        {
//            times++;

//            if (times % 5000 == 0)
//            {
//                usb_printf("\r\nSTM32开发板USB虚拟串口实验\r\n");
//                usb_printf("正点原子@ALIENTEK\r\n\r\n");
//            }

//            if (times % 200 == 0)usb_printf("请输入数据,以回车键结束\r\n");

//            if (times % 30 == 0)
//            {
//                LED0_TOGGLE();  /* 闪烁LED,提示系统正在运行 */
//            }

//            delay_ms(10);
//        }
//    }
//		
//}

