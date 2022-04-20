
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
void WriteDS1302(uint8 Adr, uint8 WByte)   //��Adr��ַ��д������WByte
{
	DS1302_RST = 0;  //��ʱ��RST��ʼΪ�͵�ƽ
	DS1302_CLK = 0;  //CLK��ʼҲΪ�͵�ƽ
	DS1302_RST = 1;   //RST�ڸߵ�ƽ���ſ��Խ���ͨѶ��
 	TransmitByte(Adr);  //��д��ַ
	TransmitByte(WByte);  //���ոյĵ�ַ��д������
	DS1302_RST = 0;    //д��һ�����ݣ�RST���͡�
}


/**********************************************
���ܣ�
    ��DS1302ĳ��ַ��һ�ֽ�����

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
