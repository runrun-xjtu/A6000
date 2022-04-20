/*=======================================================
<<<<<<<<<<<<<<<<<<< 爱普雷德技术团队 >>>>>>>>>>>>>>>>>>>>
<<<<<<<<<<<<<<<<<<< 我们一起追求卓越 >>>>>>>>>>>>>>>>>>>>
---------------------------------------------------------
旗舰网店: http://aplid.taobao.com/
官方邮箱: njaplid@163.com
 技术QQ1: 535676091
 技术QQ2: 1915624375
 技术QQ3: 154211813
---------------------------------------------------------
               All right reserved.2013.01
---------------------------------------------------------
 文件名: DS1302_drv.h
 描述: 时钟万年历模块驱动头文件
 作者:
=========================================================
-----------------------------------------------------------------------------------------------------------*/
#ifndef __DS1302_DRV_H__
#define __DS1302_DRV_H__

#include <intrins.h>
#include "type.h"
#include "IO_def.h"

/* 定义DS1302串行接口对应的端口 */
#define DS1302_RST  P37     //RST引脚，在新版本的芯片手册中定义为CE
#define DS1302_CLK  P36     //CLK引脚，作为串行接口的时钟引脚
#define DS1302_IO   P21     //数据引脚，输入输出

/* 定义DS1302串行接口对应的端口 */
#define DS1302_RST  P37     //RST引脚，在新版本的芯片手册中定义为CE
#define DS1302_CLK  P36     //CLK引脚，作为串行接口的时钟引脚
#define DS1302_IO   P21     //数据引脚，输入输出

/* 定义控制指令集寄存器地址 */
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


/* 定义寄存器写保护开关指令 */
#define WP_ON		    0x80
#define WP_OFF          0x00

/* 接口函数定义 */
void WriteDS1302(uint8 Adr, uint8 WByte);
uint8 ReadDS1302(uint8 Adr);

#endif