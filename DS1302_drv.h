/*=======================================================
<<<<<<<<<<<<<<<<<<< �����׵¼����Ŷ� >>>>>>>>>>>>>>>>>>>>
<<<<<<<<<<<<<<<<<<< ����һ��׷��׿Խ >>>>>>>>>>>>>>>>>>>>
---------------------------------------------------------
�콢����: http://aplid.taobao.com/
�ٷ�����: njaplid@163.com
 ����QQ1: 535676091
 ����QQ2: 1915624375
 ����QQ3: 154211813
---------------------------------------------------------
               All right reserved.2013.01
---------------------------------------------------------
 �ļ���: DS1302_drv.h
 ����: ʱ��������ģ������ͷ�ļ�
 ����:
=========================================================
-----------------------------------------------------------------------------------------------------------*/
#ifndef __DS1302_DRV_H__
#define __DS1302_DRV_H__

#include <intrins.h>
#include "type.h"
#include "IO_def.h"

/* ����DS1302���нӿڶ�Ӧ�Ķ˿� */
#define DS1302_RST  P37     //RST���ţ����°汾��оƬ�ֲ��ж���ΪCE
#define DS1302_CLK  P36     //CLK���ţ���Ϊ���нӿڵ�ʱ������
#define DS1302_IO   P21     //�������ţ��������

/* ����DS1302���нӿڶ�Ӧ�Ķ˿� */
#define DS1302_RST  P37     //RST���ţ����°汾��оƬ�ֲ��ж���ΪCE
#define DS1302_CLK  P36     //CLK���ţ���Ϊ���нӿڵ�ʱ������
#define DS1302_IO   P21     //�������ţ��������

/* �������ָ��Ĵ�����ַ */
#define ADR_R_SECONDS   0x81
#define ADR_R_MINUTES	0x83
#define ADR_R_HOUR    	0x85
#define ADR_R_DATE		0x87
#define ADR_R_MONTH	    0x89
#define ADR_R_DAY		0x8B
#define ADR_R_YEAR		0x8D
#define ADR_R_WP		0x8F

#define ADR_W_SECONDS   0x80
#define ADR_W_MINUTES	0x82
#define ADR_W_HOUR    	0x84
#define ADR_W_DATE		0x86
#define ADR_W_MONTH	    0x88
#define ADR_W_DAY		0x8A
#define ADR_W_YEAR		0x8C
#define ADR_W_WP		0x8E


/* ����Ĵ���д��������ָ�� */
#define WP_ON		    0x80
#define WP_OFF          0x00

/* �ӿں������� */
void WriteDS1302(uint8 Adr, uint8 WByte);
uint8 ReadDS1302(uint8 Adr);

#endif