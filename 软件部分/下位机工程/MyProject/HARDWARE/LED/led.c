#include "led.h"

/***********************************************
**�������ƣ�led��������
**�����������
**����ֵ����
**����˵����LED1--PA8 LED2--PA11  LED3--PA12
**���ߣ�WFY
************************************************/

void led_Init(void)
{
	GPIO_InitTypeDef  GPIO_Initstructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); //GPIOA��ʱ��ʹ��

	
//LED1--PA8	
	GPIO_Initstructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Initstructure.GPIO_Pin=GPIO_Pin_8;
	GPIO_Initstructure.GPIO_Speed=GPIO_Speed_50MHz;	
	GPIO_Init(GPIOA,&GPIO_Initstructure);//��GPIOA8����50M���������
	GPIO_SetBits(GPIOA,GPIO_Pin_8);//��GPIOA8λ��1����Ĭ��LED1����
	
//LED2--PA11
	GPIO_Initstructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Initstructure.GPIO_Pin=GPIO_Pin_11;
	GPIO_Initstructure.GPIO_Speed=GPIO_Speed_50MHz;	
	GPIO_Init(GPIOA,&GPIO_Initstructure);//��GPIOA11����50M���������
	GPIO_SetBits(GPIOA,GPIO_Pin_11);//��GPIOA11λ��1����Ĭ��LED2����
	
//LED2--PA12
	GPIO_Initstructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Initstructure.GPIO_Pin=GPIO_Pin_12;
	GPIO_Initstructure.GPIO_Speed=GPIO_Speed_50MHz;	
	GPIO_Init(GPIOA,&GPIO_Initstructure);//��GPIOA12����50M���������
	GPIO_SetBits(GPIOA,GPIO_Pin_12);//��GPIOA12λ��1����Ĭ��LED3����	

}

void Set_LED_Status(u8 led1_status,u8 led2_status,u8 led3_status,
	int count1,int count2,int count3,
		int time1,int time2,int time3)
{
	int i=0;
	if(led1_status==0)
	{
		LED1=led1_status;
		LED2=led2_status;
		LED3=led3_status;
		for(i=0;i<count1;i++)
		{
			delay_ms(time1);
		}
		LED1=~led1_status;
		for(i=0;i<count1;i++)
		{
			delay_ms(time1);
		}
	}
	if(led2_status==0)
	{
		LED1=led1_status;
		LED2=led2_status;
		LED3=led3_status;
		for(i=0;i<count2;i++)
		{
			delay_ms(time2);
		}
		LED2=~led2_status;
		for(i=0;i<count2;i++)
		{
			delay_ms(time2);
		}
	}
	if(led3_status==0)
	{
		LED1=led1_status;
		LED2=led2_status;
		LED3=led3_status;
		for(i=0;i<count3;i++)
		{
			delay_ms(time3);
		}
		LED3=~led3_status;
		for(i=0;i<count3;i++)
		{
			delay_ms(time3);
		}
	}
}

void WaterLights(void)
{
	LED1=0;delay_ms(100);LED1=1;delay_ms(100);
	LED2=0;delay_ms(100);LED2=1;delay_ms(100);
	LED3=0;delay_ms(100);LED3=1;delay_ms(100);
}

