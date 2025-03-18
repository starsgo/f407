///**
// ****************************************************************************************************
// * @file        freertos.c
// * @author      ����ԭ���Ŷ�(ALIENTEK)
// * @version     V1.4
// * @date        2022-01-04
// * @brief       FreeRTOS ��ֲʵ��
// * @license     Copyright (c) 2020-2032, ������������ӿƼ����޹�˾
// ****************************************************************************************************
// * @attention
// *
// * ʵ��ƽ̨:����ԭ�� ̽����F407������
// * ������Ƶ:www.yuanzige.com
// * ������̳:www.openedv.com
// * ��˾��ַ:www.alientek.com
// * �����ַ:openedv.taobao.com
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
///*FreeRTOS����*/

///* START_TASK ���� ����
// * ����: ������ �������ȼ� ��ջ��С ��������
// */
//#define START_TASK_PRIO 1                   /* �������ȼ� */
//#define START_STK_SIZE  128                 /* �����ջ��С */
//TaskHandle_t            StartTask_Handler;  /* ������ */
//void start_task(void *pvParameters);        /* ������ */

///* TASK1 ���� ����
// * ����: ������ �������ȼ� ��ջ��С ��������
// */
//#define TASK1_PRIO      2                   /* �������ȼ� */
//#define TASK1_STK_SIZE  128                 /* �����ջ��С */
//TaskHandle_t            Task1Task_Handler;  /* ������ */
//void task1(void *pvParameters);             /* ������ */

///* TASK2 ���� ����
// * ����: ������ �������ȼ� ��ջ��С ��������
// */
//#define TASK2_PRIO      3                   /* �������ȼ� */
//#define TASK2_STK_SIZE  128                 /* �����ջ��С */
//TaskHandle_t            Task2Task_Handler;  /* ������ */
//void task2(void *pvParameters);             /* ������ */


//#define TASK_SDIO_PRIO      3                   /* �������ȼ� */
//#define TASK_SDIO_STK_SIZE  128                 /* �����ջ��С */
//TaskHandle_t            TaskSDIOTask_Handler;  /* ������ */
//void task_sdio(void *pvParameters);             /* ������ */

//#define TASK_USBD_PRIO      3                   /* �������ȼ� */
//#define TASK_USBD_STK_SIZE  128                 /* �����ջ��С */
//TaskHandle_t            TaskUSBDTask_Handler;  /* ������ */
//void task_usbd(void *pvParameters);             /* ������ */

///******************************************************************************************************/

///* LCDˢ��ʱʹ�õ���ɫ */
////uint16_t lcd_discolor[11] = {WHITE, BLACK, BLUE, RED,
////                             MAGENTA, GREEN, CYAN, YELLOW,
////                             BROWN, BRRED, GRAY};

///**
// * @brief       FreeRTOS������ں���
// * @param       ��
// * @retval      ��
// */
//void freertos_demo(void)
//{
//		printf("freertos test\r\n");
//    //lcd_show_string(10, 10, 220, 32, 32, "STM32", RED);
//    //lcd_show_string(10, 47, 220, 24, 24, "FreeRTOS Porting", RED);
//    //lcd_show_string(10, 76, 220, 16, 16, "ATOM@ALIENTEK", RED);
//    
//    xTaskCreate((TaskFunction_t )start_task,            /* ������ */
//                (const char*    )"start_task",          /* �������� */
//                (uint16_t       )START_STK_SIZE,        /* �����ջ��С */
//                (void*          )NULL,                  /* ������������Ĳ��� */
//                (UBaseType_t    )START_TASK_PRIO,       /* �������ȼ� */
//                (TaskHandle_t*  )&StartTask_Handler);   /* ������ */
//    vTaskStartScheduler();
//}

///**
// * @brief       start_task
// * @param       pvParameters : �������(δ�õ�)
// * @retval      ��
// */
//void start_task(void *pvParameters)
//{
//    taskENTER_CRITICAL();           /* �����ٽ��� */
//    /* ��������1 */
////    xTaskCreate((TaskFunction_t )task1,
////                (const char*    )"task1",
////                (uint16_t       )TASK1_STK_SIZE,
////                (void*          )NULL,
////                (UBaseType_t    )TASK1_PRIO,
////                (TaskHandle_t*  )&Task1Task_Handler);
////    /* ��������2 */
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
//    vTaskDelete(StartTask_Handler); /* ɾ����ʼ���� */
//    taskEXIT_CRITICAL();            /* �˳��ٽ��� */
//}

///**
// * @brief       task1
// * @param       pvParameters : �������(δ�õ�)
// * @retval      ��
// */
//void task1(void *pvParameters)
//{
//    //uint32_t task1_num = 0;
//    
//    while(1)
//    {
//        //lcd_clear(lcd_discolor[++task1_num % 14]);                      /* ˢ����Ļ */
//        //lcd_show_string(10, 10, 220, 32, 32, "STM32", RED);
//        //lcd_show_string(10, 47, 220, 24, 24, "FreeRTOS Porting", RED);
//        //lcd_show_string(10, 76, 220, 16, 16, "ATOM@ALIENTEK", RED);
//        printf("uart_task\r\n");
//				LED0_TOGGLE();                                                  /* LED0��˸ */
//        vTaskDelay(1000);                                               /* ��ʱ1000ticks */
//    }
//}

///**
// * @brief       task2
// * @param       pvParameters : �������(δ�õ�)
// * @retval      ��
// */
//void task2(void *pvParameters)
//{
//    float float_num = 0.0;
//    
//    while(1)
//    {
//        float_num += 0.01f;                         /* ������ֵ */
//        printf("float_num: %0.4f\r\n", float_num);  /* ��ӡ��ֵ */
//        vTaskDelay(1000);                           /* ��ʱ1000ticks */
//    }
//}

//void task_sdio(void *pvParameters){
//	
//    /* ��ӡSD�������Ϣ */
//		uint8_t key;
//    uint8_t t = 0;
//	
//		while (sd_init())   /* ��ⲻ��SD�� */
//    {
//				//lcd_show_string(30, 130, 200, 16, 16, "SD Card Error!", RED);
//        delay_ms(500);
//        //lcd_show_string(30, 130, 200, 16, 16, "Please Check! ", RED);
//        delay_ms(500);
//        //LED0_TOGGLE();  /* �����˸ */
//    }
//    show_sdcard_info(); 
//    
//    /* ���SD���ɹ� */
//    //lcd_show_string(30, 130, 200, 16, 16, "SD Card OK    ", BLUE);
//    //lcd_show_string(30, 150, 200, 16, 16, "SD Card Size:     MB", BLUE);
//    //lcd_show_num(30 + 13 * 8, 150, g_sd_card_info.CardCapacity >> 20, 5, 16, BLUE); /* ��ʾSD������ */

//    while (1)
//    {
//        key = key_scan(0);

//        if (key == KEY0_PRES)       /* KEY0������ */
//        {
//            sd_test_read(0,1);      /* ��0������ȡ1*512�ֽڵ����� */
//        }

//        t++;
//        delay_ms(10);

//        if (t == 20)
//        {
//            //LED0_TOGGLE();          /* �����˸ */
//            t = 0;
//        }
//    }
//}

//USBD_HandleTypeDef USBD_Device;             /* USB Device����ṹ�� */
//extern volatile uint8_t g_usb_state_reg;    /* USB״̬ */
//extern volatile uint8_t g_device_state;     /* USB���� ��� */

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
//		USBD_Init(&USBD_Device, &MSC_Desc, 0);                              /* ��ʼ��USB */
//    USBD_RegisterClass(&USBD_Device, USBD_MSC_CLASS);                   /* ����� */
//    USBD_MSC_RegisterStorage(&USBD_Device, &USBD_DISK_fops);            /* ΪMSC����ӻص����� */
//    USBD_Start(&USBD_Device);                                           /* ����USB */
//    delay_ms(1800);

//    while (1)
//    {
//        delay_ms(1);

//        if (usb_sta != g_usb_state_reg)   /* ״̬�ı��� */
//        {
//            //lcd_fill(30, 210, 240, 210 + 16, WHITE); /* �����ʾ */

//            if (g_usb_state_reg & 0x01)   /* ����д */
//            {
//                LED1(0);
//                //lcd_show_string(30, 210, 200, 16, 16, "USB Writing...", RED); /* ��ʾUSB����д������ */
//            }

//            if (g_usb_state_reg & 0x02)   /* ���ڶ� */
//            {
//                LED1(0);
//                //lcd_show_string(30, 210, 200, 16, 16, "USB Reading...", RED); /* ��ʾUSB���ڶ������� */
//            }

//            if (g_usb_state_reg & 0x04)
//            {
//                //lcd_show_string(30, 230, 200, 16, 16, "USB Write Err ", RED); /* ��ʾд����� */
//            }
//            else
//            {
//                //lcd_fill(30, 230, 240, 230 + 16, WHITE); /* �����ʾ */
//            }
//            
//            if (g_usb_state_reg & 0x08)
//            {
//                //lcd_show_string(30, 250, 200, 16, 16, "USB Read  Err ", RED); /* ��ʾ�������� */
//										printf("USBD_ReadErr\r\n");
//            }
//            else
//            {
//                //lcd_fill(30, 250, 240, 250 + 16, WHITE); /* �����ʾ */
//            }
//            
//            usb_sta = g_usb_state_reg; /* ��¼����״̬ */
//        }

//        if (device_sta != g_device_state)
//        {
//            if (g_device_state == 1)
//            {
//                //lcd_show_string(30, 190, 200, 16, 16, "USB Connected    ", RED);    /* ��ʾUSB�����Ѿ����� */
//								printf("USBD_BOTH_DIR Connected\r\n");
//            }
//            else
//            {
//                //lcd_show_string(30, 190, 200, 16, 16, "USB DisConnected ", RED);    /* ��ʾUSB���γ��� */
//															printf("USBD_BOTH_DIR DisConnected\r\n");

//            }
//            
//            device_sta = g_device_state;
//        }

//        tct++;

//        if (tct == 200)
//        {
//            tct = 0;
//            LED1(1);        /* �ر� LED1 */
//            LED0_TOGGLE();  /* LED0 ��˸ */

//            if (g_usb_state_reg & 0x10)
//            {
//                offline_cnt = 0;    /* USB������,�����offline������ */
//															printf("offline_cnt\r\n");

//                g_device_state = 1;
//            }
//            else    /* û�еõ���ѯ */
//            {
//                offline_cnt++;

//                if (offline_cnt > 10)
//                {
//                    g_device_state = 0;/* 2s��û�յ����߱��,����USB���γ��� */
//																	printf("no offcnt\r\n");

//                }
//            }

//            g_usb_state_reg = 0;
//        }
//    }
//}