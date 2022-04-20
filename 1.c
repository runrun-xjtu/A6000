#include <reg51.h>
#include <intrins.h>
#include "DS1302_drv.h"
#include "digitron_drv.h"
#define uchar unsigned char
#define uint  unsigned int
#define DOT   0x7f
#define LCD12864_DATA P0 

sbit key1=P1^0;		// left key              
sbit key2=P1^1;	    // up key
sbit key3=P1^2;		// down key
sbit key4=P1^3;		// right key
sbit led5=P1^4;	    //	 �˲�����led�ƴ���ģ�麯��
sbit led6=P1^5;		//	 �˲�����led�ƴ���ģ�麯��
sbit led7=P1^6;		//	 �˲�����led�ƴ���ģ�麯��
sbit led8=P1^7;		//   �˲�����led�ƴ���ģ�麯��
sbit DQ = P1^4;
sbit LCD12864_RS = P2^7;        //����/����ѡ��
sbit LCD12864_RW = P2^6;        //��/дѡ��
sbit LCD12864_EN = P2^5;        //ʹ���ź�
sbit LCD12864_PSB = P2^4;       //��/���ӿ�ѡ��, H��,L��
sbit LCD12864_RST = P2^2;
sbit beep =  P3^5;
bit n=0;
bit m=0;
uint8 gSetTime[]={0x13,0x01,0x25,0x11,0x14,0x00};	//��ʼʱ������13��01��02��11��14��00��
idata unsigned int a[7]={0,0,0,0,0,0,0};
unsigned int option=0; 
code unsigned char number[]=
{
   0xc0,0xf9,0xa4,0xb0,0x99,
   0x92,0x82,0xf8,0x80,0x90,0xff
   };

unsigned char DigBuf[4];    //�����������ʾ������
	uchar m1,n1,i=1;
struct
{
    uint8 Seconds;  // ��
    uint8 Minutes;  // ��
    uint8 Hour;     // ʱ
    uint8 Date;     // ��
    uint8 Month;    // ��
    uint8 Year;     // ��
}gsTimeCalendar;
// ���ֶ��룬Segment[0]~Segment[9]�ֱ��Ӧ����0~9�Ķ���
code unsigned char Select1[] = {0xff,0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};       // λѡ��Select[0]Ϊȫѡ��Select[1]~Select[8]�ֱ��Ӧ��1λ�����Ҳࣩ~��8λ������ࣩ

uchar TH0system[]={0xfc,0xfc,0xfc,0xfc,0xfd,0xfd,0xfd,0xfd,0xfd,0xfd,0xfd,0xfe};
uchar TL0system[]={0x43,0x78,0xab,0xdb,0x08,0x33,0x5b,0x81,0xa5,0xc7,0xe7,0x05};
numtable[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e};
code unsigned char xjtu[]={
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X01,0X80,0X0E,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X18,0X00,0X00,0XC0,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X40,0X00,0X02,0X18,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X01,0X00,0X00,0X05,0X04,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X04,0X0C,0X00,0X08,0X81,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X08,0X20,0X80,0X17,0XC0,0XC0,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X10,0X10,0X00,0X00,0X40,0X20,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X40,0X00,0X23,0X10,0X80,0X10,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X63,0X38,0X00,0X08,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X80,0X06,0X7F,0XF9,0X80,0X04,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X01,0X60,0X07,0X80,0X0F,0X80,0X02,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X02,0X00,0X66,0X00,0X01,0X90,0X12,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X40,0X78,0X00,0X00,0XF8,0XA9,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X04,0X08,0X30,0X01,0X40,0X30,0X28,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X1B,0X60,0X25,0X60,0X12,0X20,0X80,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X08,0X03,0XC0,0X1D,0X70,0X0F,0X20,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X01,0X80,0X79,0X58,0X0C,0X00,0X40,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X10,0X01,0X00,0X7D,0X48,0X04,0X00,0X40,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X10,0X0F,0X00,0X7D,0X44,0X07,0X80,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X10,0X07,0X00,0X00,0X44,0X03,0X80,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X10,0X02,0X03,0XBF,0XF7,0XC2,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X02,0X03,0XFF,0XF7,0X02,0X00,0X20,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X0E,0X00,0XBF,0XF0,0X03,0XC0,0X20,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X02,0X00,0X1F,0XC0,0X03,0X80,0X20,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X02,0X00,0X0F,0XC0,0X02,0X00,0X20,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X10,0X07,0X01,0X0F,0XC0,0X03,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X10,0X0F,0X00,0X1F,0XE0,0X07,0X80,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X10,0X01,0X02,0X3F,0XF0,0X06,0X00,0X40,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X01,0X80,0X41,0X48,0X0C,0X00,0X40,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X08,0X03,0XC4,0XE8,0X0E,0X0E,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X08,0X03,0X5F,0XE8,0X4E,0X1E,0X00,0X80,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X04,0X00,0X22,0X16,0XB0,0X30,0X00,0X80,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X04,0X00,0X7C,0X00,0X00,0XF0,0X01,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X02,0X00,0X6C,0X00,0X01,0XB0,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X01,0X00,0X07,0X80,0X07,0X00,0X02,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X01,0X00,0X0E,0XFC,0XFB,0X80,0X04,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X80,0X00,0X67,0X31,0X00,0X08,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X40,0X00,0X67,0X30,0X00,0X10,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X20,0X00,0X00,0X00,0X00,0X20,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X18,0X00,0X00,0X00,0X88,0X40,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X04,0X00,0X00,0X00,0X01,0X80,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X03,0X00,0X80,0X00,0X02,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0XC0,0X00,0X20,0X08,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X10,0X00,0X00,0X60,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X03,0X00,0X03,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X1F,0XE0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
};
void delay(unsigned int t)	  
{ 
    unsigned int i,j;
    for(i=t;i>0;i--)
	for(j=110;j>0;j--);
}

///////////////////////////////////////////////               time
void outnumber(unsigned char wei, unsigned char duan)
{
    unsigned int i;
    for(i=0;i<8;i++)
	{
	    shcp=0;
	  	if(duan & 0x80)
		{
		   Data=1;
		}
		else
		{
		   Data=0;
		}
		shcp=1;
		duan <<=1;
	}
	for(i=0;i<8;i++)
	{
	    shcp=0;
	  	if(wei & 0x80)
		{
		   Data=1;
		}
		else
		{
		   Data=0;
		}
		shcp=1;
		wei <<=1;
	}
	stcp=0;
	stcp=1;
}
void shanshuo(unsigned int x)
{
	unsigned int ti=0;
    while(ti<200)
   {outnumber(0x80,number[a[1]]);
	outnumber(0x40,number[a[2]]);
	outnumber(0x40,0x7f);
	outnumber(0x20,number[a[3]]);
	outnumber(0x10,number[a[4]]);
	outnumber(0x10,0x7f);
	outnumber(0x08,number[a[5]]);
	outnumber(0x04,number[a[6]]);
	ti++;
	}
	switch(x)
	{
	   case 0: while(ti<400)
   {outnumber(0x80,number[a[1]]);
	outnumber(0x40,number[a[2]]);
	outnumber(0x40,0x7f);
	outnumber(0x20,number[a[3]]);
	outnumber(0x10,number[a[4]]);
	outnumber(0x10,0x7f);
	outnumber(0x08,number[a[5]]);
	outnumber(0x04,number[a[6]]);
	ti++;
	}
	   case 1: while(ti<400)
   {outnumber(0x80,number[10]);
	outnumber(0x40,number[a[2]]);
	outnumber(0x40,0x7f);
	outnumber(0x20,number[a[3]]);
	outnumber(0x10,number[a[4]]);
	outnumber(0x10,0x7f);
	outnumber(0x08,number[a[5]]);
	outnumber(0x04,number[a[6]]);
	ti++;
	}
	break;
	  	case 2: while(ti<400)
   {outnumber(0x80,number[a[1]]);
	outnumber(0x40,number[10]);
	outnumber(0x40,0x7f);
	outnumber(0x20,number[a[3]]);
	outnumber(0x10,number[a[4]]);
	outnumber(0x10,0x7f);
	outnumber(0x08,number[a[5]]);
	outnumber(0x04,number[a[6]]);
	ti++;
	}
	break;
	   case 3: while(ti<400)
   {outnumber(0x80,number[a[1]]);
	outnumber(0x40,number[a[2]]);
	outnumber(0x40,0x7f);
	outnumber(0x20,number[10]);
	outnumber(0x10,number[a[4]]);
	outnumber(0x10,0x7f);
	outnumber(0x08,number[a[5]]);
	outnumber(0x04,number[a[6]]);
	ti++;
	}
	break;
	case 4: while(ti<400)
   {outnumber(0x80,number[a[1]]);
	outnumber(0x40,number[a[2]]);
	outnumber(0x40,0x7f);
	outnumber(0x20,number[a[3]]);
	outnumber(0x10,number[10]);
	outnumber(0x10,0x7f);
	outnumber(0x08,number[a[5]]);
	outnumber(0x04,number[a[6]]);
	ti++;
	}
	break;
	case 5: while(ti<400)
   {outnumber(0x80,number[a[1]]);
	outnumber(0x40,number[a[2]]);
	outnumber(0x40,0x7f);
	outnumber(0x20,number[a[3]]);
	outnumber(0x10,number[a[4]]);
	outnumber(0x10,0x7f);
	outnumber(0x08,number[10]);
	outnumber(0x04,number[a[6]]);
	ti++;
	}
	break;
	case 6: while(ti<400)
   {outnumber(0x80,number[a[1]]);
	outnumber(0x40,number[a[2]]);
	outnumber(0x40,0x7f);
	outnumber(0x20,number[a[3]]);
	outnumber(0x10,number[a[4]]);
	outnumber(0x08,number[a[5]]);
	outnumber(0x04,number[10]);
	ti++;
	}
	break;
	}
}

void settime()
{
    while(1)	 //set time 
   {
	 shanshuo(option);

   if (key4==0)
   {     delay(20);
           if(key4==0)
	       {
		      nextwei:
			  option=option+1;
			  if( option==7) option=1;
			            while (1)
						{    shanshuo(option);
         	  
			        	   if (key2==0)	 //set time 2
                          {  delay(20);
                             if(key2==0)
							   {
							       a[option]=a[option]+1;
								   switch(option)
								   {
								      case 1:  if(a[option]>=3)  a[option]=0; break;
									  case 2:  if(a[option]>=10)  a[option]=0; break;
									  case 3:  if(a[option]>=6)  a[option]=0; break;
									  case 4:  if(a[option]>=10)  a[option]=0; break;
									  case 5:  if(a[option]>=6)  a[option]=0; break;
									  case 6:  if(a[option]>=10)  a[option]=0; break;
								   }
							   }
	                       }       
	                        while(1)
	                      {	  if (key2==1)
	                            break;}

					  
							
										 if (key3==0)
                             {  delay(20);
                                if(key3==0)
	                                 goto setover1;
	                                    }	  //check go out
                           if (key4==0)
                           {  delay(20);
                                if(key4==0)
	                               goto nextwei;
                                       	  }
	                    }
		   }
	     }
	     while(1)
	     {	  if (key4==1)
	     break;
	     }
		 //set over
	     
		
    }
	setover1:
	delay(20);
}

///////////////////////////////////////////////////////////////////////////////
void numchange(unsigned int x,unsigned int y,unsigned int z)
{
	unsigned char te1,te2; 
	switch(x)
	{
	   case 1: te1=0x10;break;
	   case 2: te1=0x20;break;
	   case 3: te1=0x30;break;
	   case 4: te1=0x40;break;
	   case 5: te1=0x50;break;
	   case 6: te1=0x60;break;
	   case 7: te1=0x70;break;
	   case 8: te1=0x80;break;
	   case 9: te1=0x90;break;
	   case 0: te1=0x00;break;
	}
	switch(y)
	{
	   case 1: te2=0x01;break;
	   case 2: te2=0x02;break;
	   case 3: te2=0x03;break;
	   case 4: te2=0x04;break;
	   case 5: te2=0x05;break;
	   case 6: te2=0x06;break;
	   case 7: te2=0x07;break;
	   case 8: te2=0x08;break;
	   case 9: te2=0x09;break;
	   case 0: te2=0x00;break;
	}
	gSetTime[z]=te1 | te2;
}


/**********************************************
���ܣ�
    ����ʱ�������
**********************************************/
void SetTimeCalendar(void)
{
	WriteDS1302(ADR_W_WP,WP_OFF);           //�ر�д�������ܣ�������Ը��Ĵ�������д����
    numchange(a[1],a[2],3);
	numchange(a[3],a[4],4);
	numchange(a[5],a[6],5);
	WriteDS1302(ADR_W_YEAR,gSetTime[0]);    //��
	WriteDS1302(ADR_W_MONTH,gSetTime[1]);   //��
	WriteDS1302(ADR_W_DATE,gSetTime[2]);    //��
	WriteDS1302(ADR_W_HOUR,gSetTime[3]);    //ʱ
	WriteDS1302(ADR_W_MINUTES,gSetTime[4]); //��
	WriteDS1302(ADR_W_SECONDS,gSetTime[5]); //��
    
	WriteDS1302(ADR_W_WP,WP_ON);            //����д�������ܣ�����ֹ�Ը��Ĵ�������д����
}

/**********************************************
���ܣ�
    ��ȡʱ��
���������
    ��
���������
    ��
����ֵ��
**********************************************/
void ReadTime(void)
{
    gsTimeCalendar.Seconds = ReadDS1302(ADR_R_SECONDS);		//��ȡ��
    gsTimeCalendar.Minutes = ReadDS1302(ADR_R_MINUTES);		//��ȡ��
    gsTimeCalendar.Hour    = ReadDS1302(ADR_R_HOUR);			//��ȡʱ
}

/**********************************************
    ����������ʾʱ�������
**********************************************/
bit BusyCheck(void)
{
    bit BusyBit;
    
    LCD12864_DATA = 0xFF;
    LCD12864_RS = 0;
    LCD12864_RW = 1;
    LCD12864_EN = 1;
    _nop_();
    BusyBit = (bit)(LCD12864_DATA>>7);
    LCD12864_EN = 0;
    return BusyBit;
}

/**********************************************
    д���LCD12864
**********************************************/
void CommandWrite12864(unsigned char CmdByte)
{
    while(BusyCheck());             //�ȴ�æ
    LCD12864_RS = 0;
    LCD12864_RW = 0;
    LCD12864_EN = 1;
    LCD12864_DATA = CmdByte;
    _nop_();
    LCD12864_EN = 0;
}

/**********************************************
    д���ݵ�LCD12864
**********************************************/
void DataWrite12864(unsigned char DataByte)
{
    while(BusyCheck());             //�ȴ�æ
    LCD12864_RS = 1;
    LCD12864_RW = 0;
    LCD12864_EN = 1;
    LCD12864_DATA = DataByte;
    _nop_();
    LCD12864_EN = 0;
}

/**********************************************
���ܣ�
    ��ʼ��LCD12864
**********************************************/
void Reset12864(void)
{
	LCD12864_PSB = 1;               //ѡ�񲢿ڴ���
	CommandWrite12864(0x30);        //ѡ�����ָ�
	CommandWrite12864(0x0c);        //����ʾ(���αꡢ������)
	CommandWrite12864(0x01);        //�����ʾ�������趨��ַָ��Ϊ00H
	CommandWrite12864(0x06);        //ָ�������ϵĶ�ȡ��д��ʱ���趨�α���ƶ�����ָ����ʾ����λ
}

/**********************************************
���ܣ�
    ����
**********************************************/
void ScreenClear12864(void)
{
    CommandWrite12864(0x01);
}

/**********************************************
���ܣ�
    ��ָ��������ʾ�ַ���
���������
    x: ������(0����15)
    y: ������(0����1)
    String: �ַ���
**********************************************/
void StringDisplay12864(unsigned char x, unsigned char y, unsigned char *String)
{
    if((x<8)&&(y<4))
    {
        //ָ�����ݵ�ַ
        switch(y)
        {
            case 0:
                CommandWrite12864(0x80|0x00|x);
                break;
            case 1:
                CommandWrite12864(0x80|0x10|x);
                break;
            case 2:
                CommandWrite12864(0x80|0x08|x);
                break;
            case 3:
                CommandWrite12864(0x80|0x18|x);
                break;
        }
        //��ʾ�ַ���
        while(*String != '\0')
        {
            DataWrite12864(*String);
            delay(50);
            String++;
        }
    }
}
void PictureDisplay12864(unsigned char code *Picture)
{
    unsigned char i,j,k;
    
	CommandWrite12864(0x34);
	CommandWrite12864(0x34);
    for(i=0; i<2; i++)                      //GDRAM��������ҳ
    {
        for(j=0; j<32; j++)
        {
            /* д������y�ͺ�����x */
            CommandWrite12864(0x80+j);      //дGDRAM������y������y��
            if(i==0)
            {
                CommandWrite12864(0x80);    //дGDRAM������x����ҳ��
            }
            else
            {
                CommandWrite12864(0x88);    //дGDRAM������x����ҳ��
            }
            /* ��16���ֽ�д��GDRAM */
            for(k=0; k<16; k++)
            {
                DataWrite12864(*Picture++);
            }
        }
    }
    /* �򿪻�ͼ��ʾ����ѡ�����ָ� */
    CommandWrite12864(0x36);
    CommandWrite12864(0x30);
}
void delay50us(uint t)
{
	char i;
	for(;t>0;t--)
		for(i=19;i>0;i--);
}

void delay50ms(uint t)
{
	uint i;
	for(;t>0;t--)
		for(i=6245;i>0;i--);
}

void changex(unsigned char x1, unsigned char y1,unsigned char x)
{  unsigned char str[1];
   switch(x)
   {
	  case 0: str[0]='0';break;
	   case 1: str[0]='1';break;
	    case 2: str[0]='2';break;
		 case 3: str[0]='3';break;
		  case 4: str[0]='4';break;
		   case 5: str[0]='5';break;
		    case 6: str[0]='6';break;
			 case 7: str[0]='7';break;
			  case 8: str[0]='8';break;
			   case 9: str[0]='9';break;	   
   }
StringDisplay12864(x1,y1,str);
}
//////////////////////////////////////////////////////////////////////
void jisuanqi()
{
 uchar i=0,keyl=0x00,keyh=0x00,key=0x00,a=0,b=0,c,g=0,s=0,f;
 int output=0;
 n=0; m=0;
 f=0;
 c=99;
  Reset12864();                           //Һ��12864��ʼ��
    delay(20); 
	 ScreenClear12864();
	delay(1000);
	StringDisplay12864(7,0,"��");
	StringDisplay12864(7,1,"��");
	StringDisplay12864(7,2,"��");
	StringDisplay12864(6,3,"����");
 while(1)
 {
  P1=0xf0;
  keyl=P1;
  keyl=keyl&0xf0;
  if(keyl!=0xf0)
  {
   P1=0x0f;
   keyh=P1;
   keyh=keyh&0x0f;
   key=keyl+keyh;
  }
  switch (key)
  {
			case 0xee:	i=7;		break;
			case 0xde:	i=8;		break;
			case 0xbe:	i=9;		break;
			case 0x7e:	i=10;		break;
			case 0xed:	i=4;		break;
			case 0xdd:	i=5;		break;
			case 0xbd:	i=6;		break;
			case 0x7d:	i=11;		break;	
			case 0xeb:	i=1;		break;
			case 0xdb:	i=2;		break;
			case 0xbb:	i=3;		break;
			case 0x7b:	i=12;		break;	
			case 0xe7:	i=0;		break;
			case 0xd7:	i=13;		break;
			case 0xb7:	i=14;		break;
			case 0x77:	i=15;		break;
  }
  if(i>=0&&i<=9)
  {
   if(c==99)
   {
    a=i;
	changex(0,0,a);
   }
   if(c!=99)
   {
    b=i;
	changex(0,2,b);
   }
  }
  if(i>9&&i!=13&&i!=14)
  {
   c=i;
   switch(i)
   {  case 15:
            StringDisplay12864(0,1,"+ "); break;
	  case 10:
            StringDisplay12864(0,1,"/ "); break;
	  case 11:
            StringDisplay12864(0,1,"* ");  break;
	  case 12:
            StringDisplay12864(0,1,"- ");  break;
  }
  }
  if(n==0)
  {
   if(i==14)
   {
    if(c==10)
	{
	 m=1;
	 output=a*10/b;
	}
    if(c==11)output=a*b;
    if(c==12)
	{
	 if(a>=b)
	 {
	 output=a-b;
	 }
	 else if(a<b)
	 {
	  output=b-a;
	  f=1;
	 }
	}
    if(c==15)output=a+b;
    n=1;
   }
  }
  if(i==14)
  {
   if(m==1)
   {
   	 g=output%10;
		 s=output/10;
		 StringDisplay12864(0,3,"= ");
         changex(2,3,s); 
		 StringDisplay12864(3,3,"."); 
		 changex(4,3,g); 

   }
   else if(f==1)
   {
    if(output/10==0)
		{	
		 StringDisplay12864(0,3,"= ");
		 StringDisplay12864(2,3,"-");
		 changex(3,3,output); 
		}
		else if(output/100==0)
		{
		 g=output%10;
		 s=output/10;
		 StringDisplay12864(0,3,"= ");
		 StringDisplay12864(2,3,"-"); 
		 changex(3,3,s);
		 changex(4,3,g);
		}
   }	  
   else if(output/10==0)
		{	
		 StringDisplay12864(0,3,"= ");
 		 changex(2,3,output); 
		}
		else if(output/100==0)
		{
		 g=output%10;
		 s=output/10;
		 StringDisplay12864(0,3,"= ");
		 changex(2,3,s);
		 changex(3,3,g); 
		}
				delay(5000);
	   ScreenClear12864();
	    delay(1000);
		break;
  }
  if(i==13)
  {
   output==0;
   n=0;
   m=0;
   f=0;
   c=99;
  }	
}
}

void StringDisplay(unsigned char x, unsigned char y, unsigned char *String)
{
    if((x<8)&&(y<4))
    {
        //ָ�����ݵ�ַ
        switch(y)
        {
            case 0:
                CommandWrite12864(0x80|0x00|x);
                break;
            case 1:
                CommandWrite12864(0x80|0x10|x);
                break;
            case 2:
                CommandWrite12864(0x80|0x08|x);
                break;
            case 3:
                CommandWrite12864(0x80|0x18|x);
                break;
        }
        //��ʾ�ַ���
        while(*String != '\0')
        {
            DataWrite12864(*String);
            delay(5);
            String++;
        }
    }
}
void begin()
{	
    unsigned int countnum;
    Reset12864();                           //Һ��12864��ʼ��
    delay(20); 
	for(countnum=0;countnum<2;countnum++)
	{                             //��ʱ,��֤��ʾ���ȶ�
	ScreenClear12864();
	delay(1000);
	PictureDisplay12864(xjtu);         //��ʾLogoͼ��
    delay(1000);
    ScreenClear12864();
	delay(1000);
	StringDisplay12864(0,0,"������ͨ��ѧ");
    StringDisplay12864(0,1,"Сѧ�ڼ������Ŀ");
    StringDisplay12864(0,2,"�ɹ�չʾ");
    StringDisplay12864(0,3,"................");
	delay(1000);
	ScreenClear12864();
	StringDisplay12864(0,0,"��ʮ����");
    StringDisplay12864(0,1,"�鳤�ŵ���");
    StringDisplay12864(0,2,"��Ա���񶫺��Ϻ�");
    StringDisplay12864(0,3,"���ݷ�  ���");
    delay(2000);
	ScreenClear12864();
	delay(1000);
	}
	while(1)
	{
	StringDisplay12864(1,1,"�밴�ҷ����");
    StringDisplay12864(2,2,"�������    ");
	ScreenClear12864();
	if(key4==0)
	   {	
         delay(20);
		 if(key4==0)
		 {
		  break;
		 }		   
	   }
	}
  
}

void choosefunction(unsigned int x)
{
   if(x==0)
   {
   StringDisplay(2,0,"����ѡ��");
   StringDisplay(1,1,"�¶ȼ�");
   StringDisplay(1,2,"ʵʱʱ��");
   StringDisplay(1,3,"������    ");
   }
   else if(x==1)
   {
   StringDisplay(2,0,"����ѡ��");
   StringDisplay(0,1,"--�¶ȼ�    ");
   StringDisplay(0,2,"  ʵʱʱ��      ");
   StringDisplay(0,3,"  ������    ");
   }
   else if (x==2)
   {
 //  ScreenClear12864();
   StringDisplay(2,0,"����ѡ��");
   StringDisplay(0,1,"  �¶ȼ�    ");
   StringDisplay(0,2,"--ʵʱʱ��      ");
   StringDisplay(0,3,"  ������    ");
   }
   else if(x==3)
   {
 //  ScreenClear12864();
   StringDisplay(2,0,"����ѡ��");
   StringDisplay(0,1,"  �¶ȼ�    ");
   StringDisplay(0,2,"  ʵʱʱ��      ");
   StringDisplay(0,3,"--������    ");
   }
   else if(x==4)
   {
   StringDisplay(2,0,"����ѡ��");
   StringDisplay(0,1,"--�ܱ�      ");
   StringDisplay(0,2,"  ������        ");
      StringDisplay(0,3,"          ");
   }
   else if(x==5)
   {
   StringDisplay(2,0,"����ѡ��");
   StringDisplay(0,1,"  �ܱ�      ");
   StringDisplay(0,2,"--������        ");
         StringDisplay(0,3,"          ");
   }
}


///time function

void shijian(void)
{
	  unsigned int mm=0;
	   
		    ReadTime();             //��ȡʱ��

	StringDisplay(2,1,"ʵʱʱ��");
	StringDisplay(2,2,"��");
	StringDisplay(5,2,"��");
	changex(0,2,gsTimeCalendar.Hour>>4);
	changex(1,2,gsTimeCalendar.Hour&0x0f);
	changex(3,2,gsTimeCalendar.Minutes>>4);
	changex(4,2,gsTimeCalendar.Minutes&0x0f);
	changex(6,2,gsTimeCalendar.Seconds>>4);
	changex(7,2,gsTimeCalendar.Seconds&0x0f);
	StringDisplay(0,3,"        ");
	StringDisplay(0,0,"        ");
}

/*---------------------------------------------------------------------------------------------------------*/
/* �¶�ģ��DS18B20��غ��� */
/**********************************************
    ��ʱ����
**********************************************/
void DelayXus(unsigned char n)
{
    while(n--);
}
unsigned char DS18B20Init(void)
{
    unsigned char Prence;
    DQ = 0;
    DelayXus(180);//540us = 180*3us (��׼��3us)
    DQ = 1;
    DelayXus(20);//60us = 20*3us
    if (!DQ)//˵������
    {
        Prence = 1;   
    }
    else//˵��������
    {
        Prence = 0;
    }
    DelayXus(160);//480 = 160*3us
    return Prence;
}
void DS18B20WriteOneByte(unsigned char dat)
{
    unsigned char i;
    for (i=0;i<8;i++)/*д8��λ*/
    {
        if (dat & 0x01)//�ж������д0 ����д1 ,��д���ֽ�
        {
             /*���͵�ƽ*/
             DQ = 0;
             /*������15us֮���ͷ����ߣ��������͵�ƽ��ʱ���ֱ������1us���������ǵ���ʱ1us���ϣ�����ʱ��3us��*/
             DelayXus(1);//3 = 1*3us ��׼��3us
             /*�ͷ�����*/
             DQ = 1;
             /*�ͷź����ٵõ�45us�����Ǿ������ȸ�60us*/
             DelayXus(20);//60 = 20*3us
        }
        else
        {
             /*���͵�ƽ*/
             DQ = 0;
             /*��DS18B20ʱ�䷴Ӧ����Ҫ60us<T<120us������ȡ���м�ֵ��84us*/
             DelayXus(28);//84 = 28*3us 
             /*�ͷ�����*/
             DQ = 1;
             /*�ȴ�����1us*/
             DelayXus(1);
        }
        dat >>= 1;//�ֽ�����������1λ
    }
}
/**********************************************
���ܣ�
    ��DS18B20��ȡһ���ֽ�
**********************************************/
unsigned char DS18B20ReadOneByte(void)
{
    unsigned char i;
    unsigned char TempDat = 0;
    for (i=0;i<8;i++)/*д8��λ*/
    {
        TempDat >>= 1;
        DQ  = 0;
        DelayXus(1);
        DQ = 1;
        _nop_();      
        if (DQ)
        {
            TempDat |= 0X80;
        }
        else
        {
        }
     
        DelayXus(25);
    }
    return TempDat;
}
/**********************************************
���ܣ�
    ��ʼ�¶�ת��

**********************************************/
void DS18B20TConvertStart(void)
{
    DS18B20Init();              //DS18B20��ʼ��
    delay(1);                   //��ʱ
    
    DS18B20WriteOneByte(0xCC);     //��������ROMָ��
    DS18B20WriteOneByte(0x44);     //���������¶�ת��ָ��
}

/**********************************************
���ܣ�
    ��ȡ�¶�ֵ

**********************************************/
unsigned int DS18B20TGet(void)
{
    unsigned int Temperature;
    
    DS18B20Init();              //DS18B20��ʼ��
    delay(1);                   //��ʱ
    
    DS18B20WriteOneByte(0xCC);     //��������ROMָ��
    DS18B20WriteOneByte(0xBE);     //���Ͷ�ȡ��ǩָ��
    
    Temperature = DS18B20ReadOneByte();    //��ȡ��ǩ�ĵ��ֽڣ�8λ��
    Temperature |= DS18B20ReadOneByte()<<8;//��ȡ��ǩ�ĸ��ֽڣ�8λ��
    
    return(Temperature);        //���ض�ȡ�ı�ǩֵ��16λ��
}

/*---------------------------------------------------------------------------------------------------------*/
/* �������ʾ��غ��� */

void wendu()
{
    unsigned int i=0;   //����ѭ���ļ���ֵ������ʼֵ
	double x1,x2;
    float TGet;         //�����DS18B20��ȡ����
    signed int TShow;   //����ת������Ҫ��ʾ����
	ScreenClear12864();
       	delay(1000);
		StringDisplay12864(2,0,"ʵʱ�¶�");
		changex(5,1,DigBuf[3]);
        StringDisplay12864(4,1,". ");
	    changex(3,1,DigBuf[2]);
	    changex(2,1,DigBuf[1]);
			StringDisplay12864(2,2,"�����¶�");
		changex(5,3,a[3]);
        StringDisplay12864(4,3,". ");
	    changex(3,3,a[2]);
	    changex(2,3,a[1]);
		x1=DigBuf[1]*10+DigBuf[2]+DigBuf[3]*0.1;
		x2=a[1]*10+a[2]+a[3]*0.1;
		if(x1>x2)
		{
		Buzz=1;
		}
		else
		{ Buzz=0;   }
   	while(i<2000)
	{
        /* ����1���������ж���䣬�������¶�ת�� */
        if(i==0)
        {
            DS18B20TConvertStart();     //�����¶�ת��
        }
        /* ����2���������ж���䣬��ȡ�¶�ֵ��ת���洢����ʾ���� */
        if(i==100)
        {
            TGet = DS18B20TGet()*0.0625;//�õ���ʵʮ�����¶�ֵ����ΪDS18B20
        			                    //���Ծ�ȷ��0.0625�ȣ����Զ������ݵ����λ�������0.0625�ȡ�
            TShow = TGet*10+0.5;        //�Ŵ�ʮ������������Ŀ�Ľ�С������һλҲת��Ϊ����ʾ���֣�ͬʱ����һ���������������

            if(TShow<0)                 //�ж��¶�ֵ�Ƿ�Ϊ����
            {
                DigBuf[0] = 0xbf;
                TShow = 0-TShow;
            }
            else
            {
                DigBuf[0] = TShow/1000; //�����¶Ȱ�λֵ
            }
            TShow = TShow%1000;
            DigBuf[1] = TShow/100;      //�����¶�ʮλֵ
            TShow = TShow%100;
            DigBuf[2] = TShow/10;       //�����¶ȸ�λֵ
            DigBuf[3] = TShow%10;       //����С�����һλֵ
        }
        /* ����3����i���м�1����� */
        if(++i>3000)                    //��i��ֵ��1�����ж�i�Ƿ����3000
        {
            i = 0;                      //��������3000�������
        }
        /* ����4����������ܵĶ�̬��ʾ */
	 
        if(DigBuf[0]==0xbf)             //�ж�DigBuf[0]��ֵ�Ƿ�Ϊ0xbf�����ж��¶��Ƿ�Ϊ����
        {
            DigShowCustom(4,0xbf);      //���Ǹ�������4λ��ʾ����
        }
        else if(DigBuf[0]>0)            //��DigBuf[0]��Ϊ0xbf�����ж�DigBuf[0]�Ƿ����0
        {
            DigShowNumber(4,DigBuf[0],0);//��DigBuf[0]����0����4λ��ʾ����ֵ
        }
        else                            //����
        {
            DigShowCustom(4,0xff);      //��4λ�����ȫ��
        }
    }
}

void setwendu()
{
    a[1]=0;a[2]=0;a[3]=0;a[4]=10;a[5]=10;a[6]=10;
	option=0;
    while(1)	 //set time 
   {
	 shanshuo(option);
   if (key4==0)
   {     delay(20);
           if(key4==0)
	       {
		      nextwei:
			  option=option+1;
			  if( option==4) option=1;
			            while (1)
						{    shanshuo(option);
         	  
			        	   if (key2==0)	 //set time 2
                          {  delay(20);
                             if(key2==0)
							   {
							       a[option]=a[option]+1;
								   switch(option)
								   {
								      case 1:  if(a[option]>=10)  a[option]=0; break;
									  case 2:  if(a[option]>=10)  a[option]=0; break;
									  case 3:  if(a[option]>=10)  a[option]=0; break;
								   }
							   }
	                       }       
	                        while(1)
	                      {	  if (key2==1)
	                            break;}

					  
							
										 if (key3==0)
                             {  delay(20);
                                if(key3==0)
	                                 goto setover1;
	                                    }	  //check go out
                           if (key4==0)
                           {  delay(20);
                                if(key4==0)
	                               goto nextwei;
                                       	  }
	                    }
		   }
	     }
	     while(1)
	     {	  if (key4==1)
	     break;
	     }
		 //set over
	     
		
    }
	setover1:
	delay(20);

}

void paobiao()
{
 uchar i,a,b,c;
  unsigned long int j;
 bit k,m,n;
 m=1;
 n=0;
 k=1;
 i=0;
 a=0;
 b=0;
 c=0;
 while(1)
 {
  n=0;
  j=25; 
  while(j--)
  {
  outnumber(0x80,number[a]);
  outnumber(0x40,number[b]);
  outnumber(0x20,number[c]);
  }
  if(!key2)
  {
   k=1;
  }
  if(!key3)
  {
   k=0;
  }
  if(!key4)n=1;
  if(k==1)
  {
   if(c==9){b++;c=-1;}
   if(b==10&&c==-1)
   {a++;b=0;c=-1;}
   if(a==10&&b==10&&c==-1)
   {a=0;b=0;c=-1;} 
   c++;
  }
  if(n==1)
  {
   a=0;
   b=0;
   c=0;
  } 
  if(!key1)
  break;
 }
}
//////////////////////////////////////
void delay25us(uint t)
{
	uchar i;
	for(;t>0;t--)
	{
		for(i=19;i>0;i--);
	}
}

/*****************************
��ʱ����,��Լ��ʱt*25ms
ʹ����������24MHZ�ľ���Ƶ����
*****************************/
void delay25ms(uint t)
{
	uint i;
	for(;t>0;t--)
	{
		for(i=6245;i>0;i--);
	}
}
 void delay50us1(uint t)
{
	char i;
	for(;t>0;t--)
		for(i=19;i>0;i--);
}
void qin()
{		
	 uchar keyl,keyh,key;
	TMOD=0x01;
	EA=1;
	ET0=0;
	TR0=1;
	while(1)
	{
		P1=0xf0;
		keyl=P1;
		keyl=keyl&0xf0;
		if(keyl!=0xf0)
		{
			delay25us(400);
			if(keyl!=0xf0)
			{
			 	keyl=P1&0xf0;
				keyl=keyl|0x0f;
				P1=keyl;
				keyh=P1;
				keyh=keyh&0x0f;
				keyl=keyl&0xf0;
				key=keyh+keyl;
				switch (key)
				{
		 			case 0xee:	i=1;	break;
					case 0xde:	i=2;	break;
					case 0xbe:	i=3;	break;
					case 0x7e:	i=4;	break;
					case 0xed:	i=5;	break;
					case 0xdd:	i=6;	break;
					case 0xbd:	i=7;	break;
					case 0x7d:	i=8;	break;
		 			case 0xeb:	i=9;	break;
					case 0xdb:	i=10;	break;
					case 0xbb:	i=11;	break;
					case 0x7b:	i=12;	break;
		 			case 0xe7:	i=13;	break;
					case 0xd7:	i=14;	break;
					case 0xb7:	i=15;	break;
					case 0x77:	i=16;	break;
				}
				if(i>12)
				{
					ET0=0;
					break;
				}
				else
				{
					ET0=1;
				}
			}
		}
		else
		{
			ET0=0;	
		}
	

	}	
}

void time0() interrupt 1
{
	TH0=TH0system[i-1];
	TL0=TL0system[i-1];
	beep=~beep;
}


//����Ϊ������
void main(void)
{
   unsigned int option=0,ix;
   Buzz=0;
   begin();  
   delay(1000);	
   	ScreenClear12864();
	delay(1000);
	StringDisplay(2,0,"ʱ������");
	StringDisplay(0,1,"�Ҽ�����һλ");
	StringDisplay(0,2,"�ϼ�����ʱ��");
	StringDisplay(0,3,"�¼���ȷ��");
	delay(1000);
	settime();
	SetTimeCalendar();
	   	ScreenClear12864();
	delay(1000);
	StringDisplay(1,0,"�����¶�����");
	StringDisplay(0,1,"�Ҽ�����һλ");
	StringDisplay(0,2,"�ϼ������¶�");
	StringDisplay(0,3,"�¼���ȷ��");
	delay(1000);
	setwendu();
	ScreenClear12864();
	delay(1000);

zdr:   while(1)
   {
    choosefunction(option);	 //	   ����ѡ��������ʾ��������2��
      if(key3==0)			 //up key
	  {
		delay(20);
		if(key3==0)
		{
		   option++;
		   if(option==6) option=1;	  // 1=�¶� 2=ʱ�� 3=������
		   choosefunction(option);
		}
       }
	   	while(1)
		{ if(key3==1) break; }

	   if(key2==0)
	  {
		delay(20);
		if(key2==0)
		{
		   option--;
		   if(option==0) option=5;	  // 1=�¶� 2=ʱ�� 3=������
		   switch (option)
		   {
			  choosefunction(option);
		   }
		}
       }
	   	while(1)
		{ if(key2==1) break; }

	   if(key4==0)			 //right key
	  {
		delay(20);
		if(key4==0)
		{
			ix=0;
			while(1)
			{
		      switch (option)
             {
	           case 1: wendu(); //�¶���ʾ��������ʾ��������3��+����ܺ�����4����
	             break;
	           case 2: if(ix==0)
			           {
					      ScreenClear12864();
						  delay(1000);
						  ix=1;
					   }
			           shijian(); //ʱ�亯������ʾ��������5��+����ܺ�����6����
	                   break;  
	           case 3: jisuanqi(); //������������������������7��+��ʾ��������8������Ӧ�ý�����ϵʵ����һ������  ��
	             goto zdr;		   //ע���˼���������ֻ��Ҫִ��һ������

			   case 4:
			          paobiao();	//�ܱ�
					 break;	
			   case 5:
			          qin();  //������
					 goto zdr;	 
             }
			  if(key1==0)       //left key
	            {
		         delay(20);
		         if(key1==0)
		           {
				     break;
				   }
				}
			}
		    while(1)
		    { if(key1==1) break; }

		}
	  }
	  while(1)
		{ if(key4==1) break; }
    }	
}












