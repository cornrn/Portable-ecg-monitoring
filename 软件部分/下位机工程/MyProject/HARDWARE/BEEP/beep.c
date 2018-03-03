#include "sys.h"
#include "beep.h"
#include "delay.h"

/***********************************************
**�������ƣ���������������
**�����������
**����ֵ����
**����˵����BEEP--PC13
**���ߣ�WFY
************************************************/
void Beep_Init(void)
{
	GPIO_InitTypeDef  GPIO_Initstructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE); //GPIOC��ʱ��ʹ��
		
	GPIO_Initstructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Initstructure.GPIO_Pin=GPIO_Pin_13;
	GPIO_Initstructure.GPIO_Speed=GPIO_Speed_50MHz;	
	GPIO_Init(GPIOC,&GPIO_Initstructure);//��GPIOC8����50M���������
	
	GPIO_ResetBits(GPIOC,GPIO_Pin_13);//�ȹرշ�����
}

void One_Long_One_Short(void)
{
	
	BEEP=1;
	delay_ms(800);
	BEEP=0;
	delay_ms(800);//����������500ms
	
	BEEP=1;//�򿪷�����
	delay_ms(200);
	BEEP=0;
	delay_ms(800);//����������500ms
	
}

void One_Long_Two_Short(void)
{
	BEEP=1;
	delay_ms(800);
	BEEP=0;
	delay_ms(800);//����������500ms
	
	BEEP=1;//�򿪷�����
	delay_ms(200);
	BEEP=0;
	delay_ms(800);//����������500ms
	
	BEEP=1;//�򿪷�����
	delay_ms(200);
	BEEP=0;
	delay_ms(800);//����������500ms
}

void One_Long_Three_Short(void)
{
	One_Long_Two_Short();
	
	BEEP=1;//�򿪷�����
	delay_ms(200);
	BEEP=0;
	delay_ms(800);//����������500ms
}

void One_Long_Four_Short(void)
{
	One_Long_Three_Short();
	BEEP=1;//�򿪷�����
	delay_ms(200);
	BEEP=0;
	delay_ms(800);//����������500ms
}

void Two_Long_Two_Short(void)
{
	BEEP=1;
	delay_ms(800);
	BEEP=0;
	delay_ms(800);//����������500ms
	
	BEEP=1;
	delay_ms(800);
	BEEP=0;
	delay_ms(800);//����������500ms
	
	BEEP=1;//�򿪷�����
	delay_ms(200);
	BEEP=0;
	delay_ms(800);//����������500ms
	
	BEEP=1;//�򿪷�����
	delay_ms(200);
	BEEP=0;
	delay_ms(800);//����������500ms
}
