///**
// ****************************************************************************************************
// * @file        freertos.c
// * @author      正点原子团队(ALIENTEK)
// * @version     V1.4
// * @date        2022-01-04
// * @brief       FreeRTOS 移植实验
// * @license     Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
// ****************************************************************************************************
// * @attention
// *
// * 实验平台:正点原子 探索者F407开发板
// * 在线视频:www.yuanzige.com
// * 技术论坛:www.openedv.com
// * 公司网址:www.alientek.com
// * 购买地址:openedv.taobao.com
// *
// ****************************************************************************************************
// */

//#include "freertos_demo.h"
//#include "./SYSTEM/usart/usart.h"
//#include "./BSP/LED/led.h"
//#include "./BSP/SDIO/sdio_sdcard.h"
//#include "./BSP/KEY/key.h"
//#include "./SYSTEM/sys/sys.h"
//#include "./SYSTEM/delay/delay.h"
////#include "./BSP/LCD/lcd.h"
///*FreeRTOS*********************************************************************************************/
//#include "FreeRTOS.h"
//#include "task.h"


//#include "usbd_desc.h"
//#include "usbd_msc.h"
//#include "usbd_storage.h"
//#include "usbd_conf.h"


///******************************************************************************************************/
///*FreeRTOS配置*/

///* START_TASK 任务 配置
// * 包括: 任务句柄 任务优先级 堆栈大小 创建任务
// */
//#define START_TASK_PRIO 1                   /* 任务优先级 */
//#define START_STK_SIZE  128                 /* 任务堆栈大小 */
//TaskHandle_t            StartTask_Handler;  /* 任务句柄 */
//void start_task(void *pvParameters);        /* 任务函数 */

///* TASK1 任务 配置
// * 包括: 任务句柄 任务优先级 堆栈大小 创建任务
// */
//#define TASK1_PRIO      2                   /* 任务优先级 */
//#define TASK1_STK_SIZE  128                 /* 任务堆栈大小 */
//TaskHandle_t            Task1Task_Handler;  /* 任务句柄 */
//void task1(void *pvParameters);             /* 任务函数 */

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

//#define TASK_USBD_PRIO      3                   /* 任务优先级 */
//#define TASK_USBD_STK_SIZE  128                 /* 任务堆栈大小 */
//TaskHandle_t            TaskUSBDTask_Handler;  /* 任务句柄 */
//void task_usbd(void *pvParameters);             /* 任务函数 */

///******************************************************************************************************/

///* LCD刷屏时使用的颜色 */
////uint16_t lcd_discolor[11] = {WHITE, BLACK, BLUE, RED,
////                             MAGENTA, GREEN, CYAN, YELLOW,
////                             BROWN, BRRED, GRAY};

///**
// * @brief       FreeRTOS例程入口函数
// * @param       无
// * @retval      无
// */
//void freertos_demo(void)
//{
//		printf("freertos test\r\n");
//    //lcd_show_string(10, 10, 220, 32, 32, "STM32", RED);
//    //lcd_show_string(10, 47, 220, 24, 24, "FreeRTOS Porting", RED);
//    //lcd_show_string(10, 76, 220, 16, 16, "ATOM@ALIENTEK", RED);
//    
//    xTaskCreate((TaskFunction_t )start_task,            /* 任务函数 */
//                (const char*    )"start_task",          /* 任务名称 */
//                (uint16_t       )START_STK_SIZE,        /* 任务堆栈大小 */
//                (void*          )NULL,                  /* 传入给任务函数的参数 */
//                (UBaseType_t    )START_TASK_PRIO,       /* 任务优先级 */
//                (TaskHandle_t*  )&StartTask_Handler);   /* 任务句柄 */
//    vTaskStartScheduler();
//}

///**
// * @brief       start_task
// * @param       pvParameters : 传入参数(未用到)
// * @retval      无
// */
//void start_task(void *pvParameters)
//{
//    taskENTER_CRITICAL();           /* 进入临界区 */
//    /* 创建任务1 */
////    xTaskCreate((TaskFunction_t )task1,
////                (const char*    )"task1",
////                (uint16_t       )TASK1_STK_SIZE,
////                (void*          )NULL,
////                (UBaseType_t    )TASK1_PRIO,
////                (TaskHandle_t*  )&Task1Task_Handler);
////    /* 创建任务2 */
////    xTaskCreate((TaskFunction_t )task2,
////                (const char*    )"task2",
////                (uint16_t       )TASK2_STK_SIZE,
////                (void*          )NULL,
////                (UBaseType_t    )TASK2_PRIO,
////                (TaskHandle_t*  )&Task2Task_Handler);
////		xTaskCreate((TaskFunction_t )task_sdio,
////                (const char*    )"task_sdoo",
////                (uint16_t       )TASK_SDIO_STK_SIZE,
////                (void*          )NULL,
////                (UBaseType_t    )TASK_SDIO_PRIO,
////                (TaskHandle_t*  )&TaskSDIOTask_Handler);
//		xTaskCreate((TaskFunction_t )task_usbd,
//                (const char*    )"task_usbd",
//                (uint16_t       )TASK_USBD_STK_SIZE,
//                (void*          )NULL,
//                (UBaseType_t    )TASK_USBD_PRIO,
//                (TaskHandle_t*  )&TaskUSBDTask_Handler);
//    vTaskDelete(StartTask_Handler); /* 删除开始任务 */
//    taskEXIT_CRITICAL();            /* 退出临界区 */
//}

///**
// * @brief       task1
// * @param       pvParameters : 传入参数(未用到)
// * @retval      无
// */
//void task1(void *pvParameters)
//{
//    //uint32_t task1_num = 0;
//    
//    while(1)
//    {
//        //lcd_clear(lcd_discolor[++task1_num % 14]);                      /* 刷新屏幕 */
//        //lcd_show_string(10, 10, 220, 32, 32, "STM32", RED);
//        //lcd_show_string(10, 47, 220, 24, 24, "FreeRTOS Porting", RED);
//        //lcd_show_string(10, 76, 220, 16, 16, "ATOM@ALIENTEK", RED);
//        printf("uart_task\r\n");
//				LED0_TOGGLE();                                                  /* LED0闪烁 */
//        vTaskDelay(1000);                                               /* 延时1000ticks */
//    }
//}

///**
// * @brief       task2
// * @param       pvParameters : 传入参数(未用到)
// * @retval      无
// */
//void task2(void *pvParameters)
//{
//    float float_num = 0.0;
//    
//    while(1)
//    {
//        float_num += 0.01f;                         /* 更新数值 */
//        printf("float_num: %0.4f\r\n", float_num);  /* 打印数值 */
//        vTaskDelay(1000);                           /* 延时1000ticks */
//    }
//}

//void task_sdio(void *pvParameters){
//	
//    /* 打印SD卡相关信息 */
//		uint8_t key;
//    uint8_t t = 0;
//	
//		while (sd_init())   /* 检测不到SD卡 */
//    {
//				//lcd_show_string(30, 130, 200, 16, 16, "SD Card Error!", RED);
//        delay_ms(500);
//        //lcd_show_string(30, 130, 200, 16, 16, "Please Check! ", RED);
//        delay_ms(500);
//        //LED0_TOGGLE();  /* 红灯闪烁 */
//    }
//    show_sdcard_info(); 
//    
//    /* 检测SD卡成功 */
//    //lcd_show_string(30, 130, 200, 16, 16, "SD Card OK    ", BLUE);
//    //lcd_show_string(30, 150, 200, 16, 16, "SD Card Size:     MB", BLUE);
//    //lcd_show_num(30 + 13 * 8, 150, g_sd_card_info.CardCapacity >> 20, 5, 16, BLUE); /* 显示SD卡容量 */

//    while (1)
//    {
//        key = key_scan(0);

//        if (key == KEY0_PRES)       /* KEY0按下了 */
//        {
//            sd_test_read(0,1);      /* 从0扇区读取1*512字节的内容 */
//        }

//        t++;
//        delay_ms(10);

//        if (t == 20)
//        {
//            //LED0_TOGGLE();          /* 红灯闪烁 */
//            t = 0;
//        }
//    }
//}

//USBD_HandleTypeDef USBD_Device;             /* USB Device处理结构体 */
//extern volatile uint8_t g_usb_state_reg;    /* USB状态 */
//extern volatile uint8_t g_device_state;     /* USB连接 情况 */

//void task_usbd(void *pvParameters){
//	
//		sd_init();
//	
//		uint8_t offline_cnt = 0;
//    uint8_t tct = 0;
//    uint8_t usb_sta;
//    uint8_t device_sta;
//    uint64_t card_capacity; 
//	
//		USBD_Init(&USBD_Device, &MSC_Desc, 0);                              /* 初始化USB */
//    USBD_RegisterClass(&USBD_Device, USBD_MSC_CLASS);                   /* 添加类 */
//    USBD_MSC_RegisterStorage(&USBD_Device, &USBD_DISK_fops);            /* 为MSC类添加回调函数 */
//    USBD_Start(&USBD_Device);                                           /* 开启USB */
//    delay_ms(1800);

//    while (1)
//    {
//        delay_ms(1);

//        if (usb_sta != g_usb_state_reg)   /* 状态改变了 */
//        {
//            //lcd_fill(30, 210, 240, 210 + 16, WHITE); /* 清除显示 */

//            if (g_usb_state_reg & 0x01)   /* 正在写 */
//            {
//                LED1(0);
//                //lcd_show_string(30, 210, 200, 16, 16, "USB Writing...", RED); /* 提示USB正在写入数据 */
//            }

//            if (g_usb_state_reg & 0x02)   /* 正在读 */
//            {
//                LED1(0);
//                //lcd_show_string(30, 210, 200, 16, 16, "USB Reading...", RED); /* 提示USB正在读出数据 */
//            }

//            if (g_usb_state_reg & 0x04)
//            {
//                //lcd_show_string(30, 230, 200, 16, 16, "USB Write Err ", RED); /* 提示写入错误 */
//            }
//            else
//            {
//                //lcd_fill(30, 230, 240, 230 + 16, WHITE); /* 清除显示 */
//            }
//            
//            if (g_usb_state_reg & 0x08)
//            {
//                //lcd_show_string(30, 250, 200, 16, 16, "USB Read  Err ", RED); /* 提示读出错误 */
//										printf("USBD_ReadErr\r\n");
//            }
//            else
//            {
//                //lcd_fill(30, 250, 240, 250 + 16, WHITE); /* 清除显示 */
//            }
//            
//            usb_sta = g_usb_state_reg; /* 记录最后的状态 */
//        }

//        if (device_sta != g_device_state)
//        {
//            if (g_device_state == 1)
//            {
//                //lcd_show_string(30, 190, 200, 16, 16, "USB Connected    ", RED);    /* 提示USB连接已经建立 */
//								printf("USBD_BOTH_DIR Connected\r\n");
//            }
//            else
//            {
//                //lcd_show_string(30, 190, 200, 16, 16, "USB DisConnected ", RED);    /* 提示USB被拔出了 */
//															printf("USBD_BOTH_DIR DisConnected\r\n");

//            }
//            
//            device_sta = g_device_state;
//        }

//        tct++;

//        if (tct == 200)
//        {
//            tct = 0;
//            LED1(1);        /* 关闭 LED1 */
//            LED0_TOGGLE();  /* LED0 闪烁 */

//            if (g_usb_state_reg & 0x10)
//            {
//                offline_cnt = 0;    /* USB连接了,则清除offline计数器 */
//															printf("offline_cnt\r\n");

//                g_device_state = 1;
//            }
//            else    /* 没有得到轮询 */
//            {
//                offline_cnt++;

//                if (offline_cnt > 10)
//                {
//                    g_device_state = 0;/* 2s内没收到在线标记,代表USB被拔出了 */
//																	printf("no offcnt\r\n");

//                }
//            }

//            g_usb_state_reg = 0;
//        }
//    }
//}