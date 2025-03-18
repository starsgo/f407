/**
 ****************************************************************************************************
 * @file        sdio_sdcard.c
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2021-11-05
 * @brief       SD�� ��������
 * @license     Copyright (c) 2020-2032, ������������ӿƼ����޹�˾
 ****************************************************************************************************
 * @attention
 *
 * ʵ��ƽ̨:����ԭ�� ̽���� F407������
 * ������Ƶ:www.yuanzige.com
 * ������̳:www.openedv.com
 * ��˾��ַ:www.alientek.com
 * �����ַ:openedv.taobao.com
 *
 * �޸�˵��
 * V1.0 20211105
 * ��һ�η���
 *
 ****************************************************************************************************
 */

#include "string.h"
#include "./SYSTEM/usart/usart.h"
#include "./BSP/KEY/key.h"
#include "./MALLOC/malloc.h"
#include "./BSP/SDIO/sdio_sdcard.h"


SD_HandleTypeDef g_sdcard_handler;            /* SD����� */
HAL_SD_CardInfoTypeDef g_sd_card_info_handle; /* SD����Ϣ�ṹ�� */

/**
 * @brief       ��ʼ��SD��
 * @param       ��
 * @retval      ����ֵ:0 ��ʼ����ȷ������ֵ����ʼ������
 */
uint8_t sd_init(void)
{
    uint8_t SD_Error;

    /* ��ʼ��ʱ��ʱ�Ӳ��ܴ���400KHZ */
    g_sdcard_handler.Instance = SDIO;
    g_sdcard_handler.Init.ClockEdge = SDIO_CLOCK_EDGE_RISING;                       /* ������ */
    g_sdcard_handler.Init.ClockBypass = SDIO_CLOCK_BYPASS_DISABLE;                  /* ��ʹ��bypassģʽ��ֱ����HCLK���з�Ƶ�õ�SDIO_CK */
    g_sdcard_handler.Init.ClockPowerSave = SDIO_CLOCK_POWER_SAVE_DISABLE;           /* ����ʱ���ر�ʱ�ӵ�Դ */
    g_sdcard_handler.Init.BusWide = SDIO_BUS_WIDE_1B;                               /* 1λ������ */
    g_sdcard_handler.Init.HardwareFlowControl = SDIO_HARDWARE_FLOW_CONTROL_DISABLE; /* �ر�Ӳ������ */
    g_sdcard_handler.Init.ClockDiv = SDIO_TRANSF_CLK_DIV;                           /* SD����ʱ��Ƶ�����25MHZ */

    SD_Error = HAL_SD_Init(&g_sdcard_handler);
    if (SD_Error != HAL_OK)
    {
        return 1;
    }
    
    HAL_SD_GetCardInfo(&g_sdcard_handler, &g_sd_card_info_handle);                  /* ��ȡSD����Ϣ */

    SD_Error = HAL_SD_ConfigWideBusOperation(&g_sdcard_handler, SDIO_BUS_WIDE_4B);  /* ʹ��4bit������ģʽ */
    if (SD_Error != HAL_OK)
    {
        return 2;
    }
    
    return 0;
}

/**
 * @brief       SDIO�ײ�������ʱ��ʹ�ܣ���������
                �˺����ᱻHAL_SD_Init()����
 * @param       hsd:SD�����
 * @retval      ��
 */
void HAL_SD_MspInit(SD_HandleTypeDef *hsd)
{
    GPIO_InitTypeDef gpio_init_struct;

    __HAL_RCC_SDIO_CLK_ENABLE();    /* ʹ��SDIOʱ�� */
    SD_D0_GPIO_CLK_ENABLE();        /* D0����IOʱ��ʹ�� */
    SD_D1_GPIO_CLK_ENABLE();        /* D1����IOʱ��ʹ�� */
    SD_D2_GPIO_CLK_ENABLE();        /* D2����IOʱ��ʹ�� */
    SD_D3_GPIO_CLK_ENABLE();        /* D3����IOʱ��ʹ�� */
    SD_CLK_GPIO_CLK_ENABLE();       /* CLK����IOʱ��ʹ�� */
    SD_CMD_GPIO_CLK_ENABLE();       /* CMD����IOʱ��ʹ�� */

    gpio_init_struct.Pin = SD_D0_GPIO_PIN;              /* SD_D0����ģʽ���� */
    gpio_init_struct.Mode = GPIO_MODE_AF_PP;            /* ���츴�� */
    gpio_init_struct.Pull = GPIO_PULLUP;                /* ���� */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;      /* ���� */
    gpio_init_struct.Alternate = GPIO_AF12_SDIO;        /* ����ΪSDIO */
    HAL_GPIO_Init(SD_D0_GPIO_PORT, &gpio_init_struct);  /* ��ʼ�� */

    gpio_init_struct.Pin = SD_D1_GPIO_PIN;              /* SD_D1����ģʽ���� */
    HAL_GPIO_Init(SD_D1_GPIO_PORT, &gpio_init_struct);  /* ��ʼ�� */

    gpio_init_struct.Pin = SD_D2_GPIO_PIN;              /* SD_D2����ģʽ���� */
    HAL_GPIO_Init(SD_D2_GPIO_PORT, &gpio_init_struct);  /* ��ʼ�� */

    gpio_init_struct.Pin = SD_D3_GPIO_PIN;              /* SD_D3����ģʽ���� */
    HAL_GPIO_Init(SD_D3_GPIO_PORT, &gpio_init_struct);  /* ��ʼ�� */

    gpio_init_struct.Pin = SD_CLK_GPIO_PIN;             /* SD_CLK����ģʽ���� */
    HAL_GPIO_Init(SD_CLK_GPIO_PORT, &gpio_init_struct); /* ��ʼ�� */

    gpio_init_struct.Pin = SD_CMD_GPIO_PIN;             /* SD_CMD����ģʽ���� */
    HAL_GPIO_Init(SD_CMD_GPIO_PORT, &gpio_init_struct); /* ��ʼ�� */
}

/**
 * @brief       ��ȡ����Ϣ����
 * @param       cardinfo:SD����Ϣ���
 * @retval      ����ֵ:��ȡ����Ϣ״ֵ̬
 */
uint8_t get_sd_card_info(HAL_SD_CardInfoTypeDef *cardinfo)
{
    uint8_t sta;
    
    sta = HAL_SD_GetCardInfo(&g_sdcard_handler, cardinfo);
    
    return sta;
}

/**
 * @brief       �ж�SD���Ƿ���Դ���(��д)����
 * @param       ��
 * @retval      ����ֵ:SD_TRANSFER_OK      ������ɣ����Լ�����һ�δ���
                       SD_TRANSFER_BUSY SD ����æ�������Խ�����һ�δ���
 */
uint8_t get_sd_card_state(void)
{
    return ((HAL_SD_GetCardState(&g_sdcard_handler) == HAL_SD_CARD_TRANSFER) ? SD_TRANSFER_OK : SD_TRANSFER_BUSY);
}

/**
 * @brief       ��SD��(fatfs/usb����)
 * @param       pbuf  : ���ݻ�����
 * @param       saddr : ������ַ
 * @param       cnt   : ��������
 * @retval      0, ����;  ����, �������(���SD_Error����);
 */
uint8_t sd_read_disk(uint8_t *pbuf, uint32_t saddr, uint32_t cnt)
{
    uint8_t sta = HAL_OK;
    uint32_t timeout = SD_TIMEOUT;
    long long lsector = saddr;
    
    __disable_irq();                                                                       /* �ر����ж�(POLLINGģʽ,�Ͻ��жϴ��SDIO��д����!!!) */
    sta = HAL_SD_ReadBlocks(&g_sdcard_handler, (uint8_t *)pbuf, lsector, cnt, SD_TIMEOUT); /* ���sector�Ķ����� */

    /* �ȴ�SD������ */
    while (get_sd_card_state() != SD_TRANSFER_OK)
    {
        if (timeout-- == 0)
        {
            sta = SD_TRANSFER_BUSY;
        }
    }
    __enable_irq(); /* �������ж� */
    
    return sta;
}

/**
 * @brief       дSD��(fatfs/usb����)
 * @param       pbuf  : ���ݻ�����
 * @param       saddr : ������ַ
 * @param       cnt   : ��������
 * @retval      0, ����;  ����, �������(���SD_Error����);
 */
uint8_t sd_write_disk(uint8_t *pbuf, uint32_t saddr, uint32_t cnt)
{
    uint8_t sta = HAL_OK;
    uint32_t timeout = SD_TIMEOUT;
    long long lsector = saddr;
    
    __disable_irq();                                                                        /* �ر����ж�(POLLINGģʽ,�Ͻ��жϴ��SDIO��д����!!!) */
    sta = HAL_SD_WriteBlocks(&g_sdcard_handler, (uint8_t *)pbuf, lsector, cnt, SD_TIMEOUT); /* ���sector��д���� */

    /* �ȴ�SD��д�� */
    while (get_sd_card_state() != SD_TRANSFER_OK)
    {
        if (timeout-- == 0)
        {
            sta = SD_TRANSFER_BUSY;
        }
    }
    __enable_irq();     /* �������ж� */
    
    return sta;
}

void show_sdcard_info(void)
{
    HAL_SD_CardCIDTypeDef sd_card_cid;

    HAL_SD_GetCardCID(&g_sdcard_handler, &sd_card_cid); /* ��ȡCID */
    get_sd_card_info(&g_sd_card_info_handle);           /* ��ȡSD����Ϣ */

    switch (g_sd_card_info_handle.CardType)
    {
    case CARD_SDSC:
    {
        if (g_sd_card_info_handle.CardVersion == CARD_V1_X)
        {
            printf("Card Type:SDSC V1\r\n");
        }
        else if (g_sd_card_info_handle.CardVersion == CARD_V2_X)
        {
            printf("Card Type:SDSC V2\r\n");
        }
    }
    break;

    case CARD_SDHC_SDXC:
        printf("Card Type:SDHC\r\n");
        break;
    default: break;
    }

    printf("Card ManufacturerID:%d\r\n", sd_card_cid.ManufacturerID);                   /* ������ID */
    printf("Card RCA:%d\r\n", g_sd_card_info_handle.RelCardAdd);                        /* ����Ե�ַ */
    printf("LogBlockNbr:%d \r\n", (uint32_t)(g_sd_card_info_handle.LogBlockNbr));       /* ��ʾ�߼������� */
    printf("LogBlockSize:%d \r\n", (uint32_t)(g_sd_card_info_handle.LogBlockSize));     /* ��ʾ�߼����С */
    printf("Card Capacity:%d MB\r\n", (uint32_t)SD_TOTAL_SIZE_MB(&g_sdcard_handler));   /* ��ʾ���� */
    printf("Card BlockSize:%d\r\n\r\n", g_sd_card_info_handle.BlockSize);               /* ��ʾ���С */
}

/**
 * @brief       ����SD���Ķ�ȡ
 *   @note      ��secaddr��ַ��ʼ,��ȡseccnt������������
 * @param       secaddr : ������ַ
 * @param       seccnt  : ������
 * @retval      ��
 */
void sd_test_read(uint32_t secaddr, uint32_t seccnt)
{
    uint32_t i;
    uint8_t *buf;
    uint8_t sta = 0;

    buf = mymalloc(SRAMIN, seccnt * 512);       /* �����ڴ�,��SRAM�����ڴ� */
    sta = sd_read_disk(buf, secaddr, seccnt);   /* ��ȡsecaddr������ʼ������ */

    if (sta == 0)
    {
        //lcd_show_string(30, 170, 200, 16, 16, "USART1 Sending Data...", BLUE);
        printf("SECTOR %d DATA:\r\n", secaddr);

        for (i = 0; i < seccnt * 512; i++)
        {
            printf("%x ", buf[i]);              /* ��ӡsecaddr��ʼ���������� */
        }

        printf("\r\nDATA ENDED\r\n");
        //lcd_show_string(30, 170, 200, 16, 16, "USART1 Send Data Over!", BLUE);
    }
    else
    {
        printf("err:%d\r\n", sta);
        //lcd_show_string(30, 170, 200, 16, 16, "SD read Failure!      ", BLUE);
    }

    myfree(SRAMIN, buf); /* �ͷ��ڴ� */
}

/**
 * @brief       ����SD����д��
 *   @note      ��secaddr��ַ��ʼ,д��seccnt������������
 *              ����!! ���дȫ��0XFF������,���������SD��.
 *
 * @param       secaddr : ������ַ
 * @param       seccnt  : ������
 * @retval      ��
 */
void sd_test_write(uint32_t secaddr, uint32_t seccnt)
{
    uint32_t i;
    uint8_t *buf;
    uint8_t sta = 0;

    buf = mymalloc(SRAMIN, seccnt * 512);       /* ��SRAM�����ڴ� */

    for (i = 0; i < seccnt * 512; i++)          /* ��ʼ��д�������,��3�ı���. */
    {
        buf[i] = i * 3;
    }

    sta = sd_write_disk(buf, secaddr, seccnt);  /* ��secaddr������ʼд��seccnt���������� */

    if (sta == 0)
    {
        printf("Write over!\r\n");
    }
    else
    {
        printf("err:%d\r\n", sta);
    }

    myfree(SRAMIN, buf); /* �ͷ��ڴ� */
}




