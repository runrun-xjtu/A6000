
#include "DS1302_drv.h"

static void TransmitByte(uint8 TByte)
{
    uint8 i;
    for(i = 0;i < 8;i++)
    {
		DS1302_CLK = 0;
        if(TByte&0x01)
        {
            DS1302_IO = 1;
        }
        else
        {
            DS1302_IO = 0;
        }
        DS1302_CLK = 1;
        TByte >>= 1;
    }
}

/**********************************************

**********************************************/
static uint8 ReceiveByte(void)
{
    uint8 i,RecByte;
    for(i = 0;i < 8;i++)
    {
		DS1302_CLK = 0;
        RecByte >>= 1;
        if(DS1302_IO)
        {
            RecByte |= 0x80;
        }
        else
        {
            RecByte &= ~0x80;
        }
        DS1302_CLK = 1;
    }
    return(RecByte);
}

/**********************************************

**********************************************/
void WriteDS1302(uint8 Adr, uint8 WByte)   //往Adr地址中写入数据WByte
{
	DS1302_RST = 0;  //看时序，RST开始为低电平
	DS1302_CLK = 0;  //CLK开始也为低电平
	DS1302_RST = 1;   //RST在高电平，才可以进行通讯。
 	TransmitByte(Adr);  //先写地址
	TransmitByte(WByte);  //往刚刚的地址中写入数据
	DS1302_RST = 0;    //写完一次数据，RST拉低。
}


/**********************************************
功能：
    从DS1302某地址读一字节数据

**********************************************/
uint8 ReadDS1302(uint8 Adr)
{
	unsigned char RByte;
	DS1302_RST = 0;
	DS1302_CLK = 0;
	DS1302_RST = 1;
	TransmitByte(Adr);
	RByte = ReceiveByte();
	DS1302_RST = 0;
	return(RByte);
}
