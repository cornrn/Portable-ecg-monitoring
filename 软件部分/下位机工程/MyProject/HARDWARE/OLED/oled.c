#include "oled.h"
#include "stdlib.h" 	 
#include "delay.h"
#include "oledfont.h" 

//OLED���Դ�
//��Ÿ�ʽ����.
//[0]0 1 2 3 ... 127	
//[1]0 1 2 3 ... 127	
//[2]0 1 2 3 ... 127	
//[3]0 1 2 3 ... 127	
//[4]0 1 2 3 ... 127	
//[5]0 1 2 3 ... 127	
//[6]0 1 2 3 ... 127	
//[7]0 1 2 3 ... 127 			   
u8 OLED_GRAM[128][8];	
/***********************************************
**�������ƣ�IIC��������
**�����������
**����ֵ����
**����˵������
**���ߣ�WFY
************************************************/
void IIC_Start(void)
{

	OLED_SCLK_Set() ;
	OLED_SDIN_Set();
	OLED_SDIN_Clr();
	OLED_SCLK_Clr();
	
}


/***********************************************
**�������ƣ�IICֹͣ����
**�����������
**����ֵ����
**����˵������
**���ߣ�WFY
************************************************/
void IIC_Stop(void)
{
	
	OLED_SCLK_Set() ;
//	OLED_SCLK_Clr();
	OLED_SDIN_Clr();
	OLED_SDIN_Set();
	
}

/***********************************************
**�������ƣ�IIC�ȴ�����ź�
**�����������
**����ֵ����
**����˵������
**���ߣ�WFY
************************************************/
void IIC_Wait_Ack(void)
{

	OLED_SCLK_Set();
	OLED_SCLK_Clr();
	
}

/***********************************************
**�������ƣ�IIC Write byte
**���������IIC_Byte����д����ֽ�
**����ֵ����
**����˵������
**���ߣ�WFY
************************************************/
void Write_IIC_Byte(unsigned char IIC_Byte)
{
	unsigned char i;
	unsigned char m,da;
	da=IIC_Byte;
	OLED_SCLK_Clr();
	for(i=0;i<8;i++)		
	{
			m=da;
		//	OLED_SCLK_Clr();
		m=m&0x80;
		if(m==0x80)
		{OLED_SDIN_Set();}
		else OLED_SDIN_Clr();
			da=da<<1;
		OLED_SCLK_Set();
		OLED_SCLK_Clr();
		}


}

/***********************************************
**�������ƣ�IIC Write Command
**���������IIC_Command����д�������
**����ֵ����
**����˵������
**���ߣ�WFY
************************************************/
void Write_IIC_Command(unsigned char IIC_Command)
{
   IIC_Start();
   Write_IIC_Byte(0x78);            //Slave address,SA0=0
	IIC_Wait_Ack();	
   Write_IIC_Byte(0x00);			//write command
	IIC_Wait_Ack();	
   Write_IIC_Byte(IIC_Command); 
	IIC_Wait_Ack();	
   IIC_Stop();
}

/***********************************************
**�������ƣ�IIC Write Data
**���������IIC_Data����д�������
**����ֵ����
**����˵������
**���ߣ�WFY
************************************************/
void Write_IIC_Data(unsigned char IIC_Data)
{
   IIC_Start();
   Write_IIC_Byte(0x78);			//D/C#=0; R/W#=0
	IIC_Wait_Ack();	
   Write_IIC_Byte(0x40);			//write data
	IIC_Wait_Ack();	
   Write_IIC_Byte(IIC_Data);
	IIC_Wait_Ack();	
   IIC_Stop();
}

/***********************************************
**�������ƣ�OLEDд�����ݻ��������
**���������dat����д�������   cmd����д�������
**����ֵ����
**����˵������
**���ߣ�WFY
************************************************/
void OLED_WR_Byte(unsigned dat,unsigned cmd)
{
	if(cmd)
			{

			Write_IIC_Data(dat);
   
		}
	else {
   Write_IIC_Command(dat);
		
	}


}



/***********************************************
**�������ƣ�OLED��ʾͼƬ
**���������fill_Data��ͼƬ����
**����ֵ����
**����˵������
**���ߣ�WFY
************************************************/
void fill_picture(unsigned char fill_Data)
{
	unsigned char m,n;
	for(m=0;m<8;m++)
	{
		OLED_WR_Byte(0xb0+m,0);		//page0-page1
		OLED_WR_Byte(0x00,0);		//low column start address
		OLED_WR_Byte(0x10,0);		//high column start address
		for(n=0;n<128;n++)
			{
				OLED_WR_Byte(fill_Data,1);
			}
	}
}



/***********************************************
**�������ƣ���ʱ50���뺯��
**���������Del_50ms
**����ֵ����
**����˵������
**���ߣ�WFY
************************************************/
void Delay_50ms(unsigned int Del_50ms)
{
	unsigned int m;
	for(;Del_50ms>0;Del_50ms--)
		for(m=6245;m>0;m--);
}

/***********************************************
**�������ƣ���ʱ1���뺯��
**���������Del_1ms
**����ֵ����
**����˵������
**���ߣ�WFY
************************************************/
void Delay_1ms(unsigned int Del_1ms)
{
	unsigned char j;
	while(Del_1ms--)
	{	
		for(j=0;j<123;j++);
	}
}


/***********************************************
**�������ƣ��������ú���
**���������x,y����
**����ֵ����
**����˵������
**���ߣ�WFY
************************************************/
void OLED_Set_Pos(unsigned char x, unsigned char y) 
{ 	
	OLED_WR_Byte(0xb0+y,OLED_CMD);
	OLED_WR_Byte(((x&0xf0)>>4)|0x10,OLED_CMD);
	OLED_WR_Byte((x&0x0f),OLED_CMD); 
}   	  

/***********************************************
**�������ƣ�����OLED��ʾ
**�����������
**����ֵ����
**����˵������
**���ߣ�WFY
************************************************/
void OLED_Display_On(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC����
	OLED_WR_Byte(0X14,OLED_CMD);  //DCDC ON
	OLED_WR_Byte(0XAF,OLED_CMD);  //DISPLAY ON
}

/***********************************************
**�������ƣ��ر�OLED��ʾ 
**�����������
**����ֵ����
**����˵������
**���ߣ�WFY
************************************************/
void OLED_Display_Off(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC����
	OLED_WR_Byte(0X10,OLED_CMD);  //DCDC OFF
	OLED_WR_Byte(0XAE,OLED_CMD);  //DISPLAY OFF
}		   			 

/***********************************************
**�������ƣ��������� 
**�����������
**����ֵ����
**����˵����������,������Ļ�Ǻ�ɫ��!��û����һ��!!!
**���ߣ�WFY
************************************************/
void OLED_Clear(void)  
{  
	u8 i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_WR_Byte (0xb0+i,OLED_CMD);    //����ҳ��ַ��0~7��
		OLED_WR_Byte (0x00,OLED_CMD);      //������ʾλ�á��е͵�ַ
		OLED_WR_Byte (0x10,OLED_CMD);      //������ʾλ�á��иߵ�ַ   
		for(n=0;n<128;n++)OLED_WR_Byte(0,OLED_DATA); 
	} //������ʾ
}

/***********************************************
**�������ƣ�����OLED
**�����������
**����ֵ����
**����˵������
**���ߣ�WFY
************************************************/
void OLED_On(void)  
{  
	u8 i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_WR_Byte (0xb0+i,OLED_CMD);    //����ҳ��ַ��0~7��
		OLED_WR_Byte (0x00,OLED_CMD);      //������ʾλ�á��е͵�ַ
		OLED_WR_Byte (0x10,OLED_CMD);      //������ʾλ�á��иߵ�ַ   
		for(n=0;n<128;n++)OLED_WR_Byte(1,OLED_DATA); 
	} //������ʾ
}

/***********************************************
**�������ƣ���ָ��λ����ʾһ���ַ�,���������ַ�
**������������꣺x:0~127  y:0~63  �ַ���chr����ʾ�ַ�  Char_Size���ַ���С
**����ֵ����
**����˵����mode:0,������ʾ;1,������ʾ	size:ѡ������ 16/12 
**���ߣ�WFY
************************************************/
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 Char_Size)
{      	
	unsigned char c=0,i=0;	
		c=chr-' ';//�õ�ƫ�ƺ��ֵ			
		if(x>Max_Column-1){x=0;y=y+2;}
		if(Char_Size ==16)
			{
			OLED_Set_Pos(x,y);	
			for(i=0;i<8;i++)
			OLED_WR_Byte(F8X16[c*16+i],OLED_DATA);
			OLED_Set_Pos(x,y+1);
			for(i=0;i<8;i++)
			OLED_WR_Byte(F8X16[c*16+i+8],OLED_DATA);
			}
			else {	
				OLED_Set_Pos(x,y);
				for(i=0;i<6;i++)
				OLED_WR_Byte(F6x8[c][i],OLED_DATA);
				
			}
}

/***********************************************
**�������ƣ�m^n����
**���������u8 m,u8 n
**����ֵ�������ó���ֵ
**����˵������
**���ߣ�WFY
************************************************/
u32 oled_pow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}				  
 
/***********************************************
**�������ƣ���ʾ2������
**���������x,y :������� len :���ֵ�λ��  size2:�����С	  num:��ֵ(0~4294967295);
**����ֵ�������ó���ֵ
**����˵������
**���ߣ�WFY
************************************************/
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size2)
{         	
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/oled_pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				OLED_ShowChar(x+(size2/2)*t,y,' ',size2);
				continue;
			}else enshow=1; 
		 	 
		}
	 	OLED_ShowChar(x+(size2/2)*t,y,temp+'0',size2); 
	}
} 


void OLED_ShowString(u8 x,u8 y,u8 *chr,u8 Char_Size)
{
	unsigned char j=0;
	while (chr[j]!='\0')
	{		OLED_ShowChar(x,y,chr[j],Char_Size);
			x+=8;
		if(x>120){x=0;y+=2;}
			j++;
	}
}

/***********************************************
**�������ƣ���ʾ����
**���������x,y :������� len :���ֵ�λ��  size2:�����С	  num:��ֵ(0~4294967295);
**����ֵ�������ó���ֵ
**����˵������
**���ߣ�WFY
************************************************/
void OLED_ShowCHinese(u8 x,u8 y,u8 no)
{      			    
	u8 t,adder=0;
	OLED_Set_Pos(x,y);	
  for(t=0;t<16;t++)
	{
		OLED_WR_Byte(Hzk[2*no][t],OLED_DATA);
		adder+=1;
    }	
	OLED_Set_Pos(x,y+1);	
    for(t=0;t<16;t++)
	{	
		OLED_WR_Byte(Hzk[2*no+1][t],OLED_DATA);
		adder+=1;
    }					
}

/***********************************************
**�������ƣ���ʾ��ʾBMPͼƬ128��64
**�����������ʼ������(x,y),x�ķ�Χ0��127 yΪҳ�ķ�Χ0��7
**����ֵ����
**����˵������
**���ߣ�WFY
************************************************/
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[])
{ 	
 unsigned int j=0;
 unsigned char x,y;
  
  if(y1%8==0) y=y1/8;      
  else y=y1/8+1;
	for(y=y0;y<y1;y++)
	{
		OLED_Set_Pos(x0,y);
    for(x=x0;x<x1;x++)
	    {      
	    	OLED_WR_Byte(BMP[j++],OLED_DATA);	    	
	    }
	}
} 

//�����Դ浽LCD		 
void OLED_Refresh_Gram(void)
{
	u8 i,n;		    
	for(i=2;i<8;i++)  
	{  
		OLED_WR_Byte (0xb0+i,OLED_CMD);    //����ҳ��ַ��0~7��
		OLED_WR_Byte (0x00,OLED_CMD);      //������ʾλ�á��е͵�ַ
		OLED_WR_Byte (0x10,OLED_CMD);      //������ʾλ�á��иߵ�ַ   
		for(n=0;n<128;n++)OLED_WR_Byte(OLED_GRAM[n][i],OLED_DATA); 
	}   
}


//x1,y1,x2,y2 �������ĶԽ�����
//ȷ��x1<=x2;y1<=y2 0<=x1<=127 0<=y1<=63	 	 
//dot:0,���;1,���	  
void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot)  
{  
	u8 x,y;  
	for(x=x1;x<=x2;x++)
	{
		for(y=y1;y<=y2;y++)OLED_DrawPoint(x,y,dot);
	}													    
	OLED_Refresh_Gram();//������ʾ
}


//���� 
//x:0~127
//y:0~63
//t:1 ��� 0,���				   
void OLED_DrawPoint(u8 x,u8 y,u8 t)
{
	u8 pos,bx,temp=0;
	if(x>127||y>63)return;//������Χ��.
	pos=7-y/8;
	bx=y%8;
	temp=1<<(7-bx);
	if(t)OLED_GRAM[x][pos]|=temp;
	else OLED_GRAM[x][pos]&=~temp;
	OLED_Refresh_Gram();//������ʾ
		
}

	
/***********************************************
**�������ƣ���ʼ��OLED
**�����������
**����ֵ����
**����˵������
**���ߣ�WFY
************************************************/
void OLED_Init(void)
{ 	 	 
 	GPIO_InitTypeDef  GPIO_InitStructure;
 	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //ʹ��A�˿�ʱ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11;	 
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//�ٶ�50MHz
 	GPIO_Init(GPIOB, &GPIO_InitStructure);	  //��ʼ��GPIOD3,6
 	GPIO_SetBits(GPIOB,GPIO_Pin_10|GPIO_Pin_11);	


	delay_ms(200);

	OLED_WR_Byte(0xAE,OLED_CMD);//--display off
	OLED_WR_Byte(0x00,OLED_CMD);//---set low column address
	OLED_WR_Byte(0x10,OLED_CMD);//---set high column address
	OLED_WR_Byte(0x40,OLED_CMD);//--set start line address  
	OLED_WR_Byte(0xB0,OLED_CMD);//--set page address
	OLED_WR_Byte(0x81,OLED_CMD); // contract control
	OLED_WR_Byte(0xFF,OLED_CMD);//--128   
	OLED_WR_Byte(0xA1,OLED_CMD);//set segment remap 
	OLED_WR_Byte(0xA6,OLED_CMD);//--normal / reverse
	OLED_WR_Byte(0xA8,OLED_CMD);//--set multiplex ratio(1 to 64)
	OLED_WR_Byte(0x3F,OLED_CMD);//--1/32 duty
	OLED_WR_Byte(0xC8,OLED_CMD);//Com scan direction
	OLED_WR_Byte(0xD3,OLED_CMD);//-set display offset
	OLED_WR_Byte(0x00,OLED_CMD);//
	
	OLED_WR_Byte(0xD5,OLED_CMD);//set osc division
	OLED_WR_Byte(0x80,OLED_CMD);//
	
	OLED_WR_Byte(0xD8,OLED_CMD);//set area color mode off
	OLED_WR_Byte(0x05,OLED_CMD);//
	
	OLED_WR_Byte(0xD9,OLED_CMD);//Set Pre-Charge Period
	OLED_WR_Byte(0xF1,OLED_CMD);//
	
	OLED_WR_Byte(0xDA,OLED_CMD);//set com pin configuartion
	OLED_WR_Byte(0x12,OLED_CMD);//
	
	OLED_WR_Byte(0xDB,OLED_CMD);//set Vcomh
	OLED_WR_Byte(0x30,OLED_CMD);//
	
	OLED_WR_Byte(0x8D,OLED_CMD);//set charge pump enable
	OLED_WR_Byte(0x14,OLED_CMD);//
	
	OLED_WR_Byte(0xAF,OLED_CMD);//--turn on oled panel
	
	
	OLED_Clear();
}  
/***********************************************
**�������ƣ�OLED���ߺ���
**�����������
**����ֵ����
**����˵������
**���ߣ�WFY
************************************************/
void OLED_DrawLine(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot)
{
	double k,b;
	int i=0;
	double y;
	k=(y2-y1)*1.0/(x2-x1);
	b=y1-k*x1;
	for(i=x1;i<=x2;i++)
	{
		y=k*i+b;
		OLED_DrawPoint(i,y,dot);
	}	
}

/***********************************************
**�������ƣ�OLED��ʾ��������״̬
**�����������
**����ֵ����
**����˵������
**���ߣ�WFY
************************************************/
u8 OLED_Show_HC05Status(void)
{
	u8 t;
	t=HC05_Sta_Show();
	if(t==1)//�������ӳɹ�
	{
		OLED_ShowCHinese(8,3,29);//��
		OLED_ShowCHinese(26,3,30);//��
		OLED_ShowCHinese(44,3,31);//��
		OLED_ShowCHinese(62,3,32);//��
		OLED_ShowCHinese(80,3,33);//��
		OLED_ShowCHinese(98,3,34);//��
		OLED_ShowCHinese(116,3,35);//!
		return 0;
		
	}
	else//��������δ�ɹ�
	{
		
		OLED_ShowCHinese(8,3,29);//��
		OLED_ShowCHinese(26,3,30);//��
		OLED_ShowCHinese(44,3,31);//��
		OLED_ShowCHinese(62,3,32);//��
		OLED_ShowCHinese(80,3,36);//ʧ
		OLED_ShowCHinese(98,3,37);//��
		OLED_ShowCHinese(116,3,35);//!
		One_Long_Three_Short();
		return 1;
	}
}


























