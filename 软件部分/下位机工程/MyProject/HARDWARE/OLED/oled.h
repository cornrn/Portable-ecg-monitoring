#ifndef __OLED_H
#define __OLED_H			  	 

#include "sys.h"
#include "stdlib.h"
#include "hc05.h"
#include "beep.h"


#define OLED_MODE 0
#define SIZE 8
#define XLevelL		0x00
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64	    

//-----------------OLED IIC�˿ڶ���----------------  					   

#define OLED_SCLK_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_10)//CLK
#define OLED_SCLK_Set() GPIO_SetBits(GPIOB,GPIO_Pin_10)

#define OLED_SDIN_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_11)//DIN
#define OLED_SDIN_Set() GPIO_SetBits(GPIOB,GPIO_Pin_11)



#define OLED_CMD  0	//д����
#define OLED_DATA 1	//д����


//OLED�����ú���
void OLED_WR_Byte(unsigned dat,unsigned cmd);  //OLEDд��һ���ֽں���������������ݣ�
void OLED_Display_On(void);//����oled��ʾ
void OLED_Display_Off(void);//�ر�OLED��ʾ							   		    
void OLED_Init(void);//��ʼ��OLED
void OLED_Clear(void);//�������� 
void OLED_Refresh_Gram(void);
void OLED_DrawPoint(u8 x,u8 y,u8 t);
void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot);
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 Char_Size);//��ָ��λ����ʾһ���ַ�,���������ַ�
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size);//��ʾ2������
void OLED_ShowString(u8 x,u8 y, u8 *p,u8 Char_Size);//��ʾ�ַ��� 
void OLED_Set_Pos(unsigned char x, unsigned char y);//�������ú���
void OLED_ShowCHinese(u8 x,u8 y,u8 no);//��ʾ����
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);//��ʾ��ʾBMPͼƬ128��64
void Delay_50ms(unsigned int Del_50ms);
void Delay_1ms(unsigned int Del_1ms);
void fill_picture(unsigned char fill_Data);//OLED��ʾͼƬ
void OLED_DrawLine(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot);
u8 OLED_Show_HC05Status(void);



void IIC_Stop(void);
void IIC_Start(void);
void Write_IIC_Command(unsigned char IIC_Command);
void Write_IIC_Data(unsigned char IIC_Data);
void Write_IIC_Byte(unsigned char IIC_Byte);

void IIC_Wait_Ack(void);
#endif  



