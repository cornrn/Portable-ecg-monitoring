#include "exti.h"
#include "led.h"
#include "key.h"
#include "delay.h"
#include "usart.h"




//static int Key1_Count;
//static int Key2_Count; 
 
//�ⲿ�жϳ�ʼ������
void EXTIX_Init(void)
{
 
 	  EXTI_InitTypeDef EXTI_InitStructure;
 	  NVIC_InitTypeDef NVIC_InitStructure;

	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//�ⲿ�жϣ���Ҫʹ��AFIOʱ��

	  KEY_Init();//��ʼ��������Ӧioģʽ
	
//key0
    //GPIOC.5 �ж����Լ��жϳ�ʼ������
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource5);

  	EXTI_InitStructure.EXTI_Line=EXTI_Line5;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//�½��ش���
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

////key1
//    //GPIOB.0	  �ж����Լ��жϳ�ʼ������
//  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource0);

//  	EXTI_InitStructure.EXTI_Line=EXTI_Line0;
//  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
//  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
//  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//  	EXTI_Init(&EXTI_InitStructure);	  	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���
////key2
//    //GPIOB.1	  �ж����Լ��жϳ�ʼ������
//  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource1);

//   	EXTI_InitStructure.EXTI_Line=EXTI_Line1;
//  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
//  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
//  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//  	EXTI_Init(&EXTI_InitStructure);		//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���


 
//  	NVIC_InitStructure.NVIC_IRQChannel = EXTI_Line0;			//ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
//  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2 
//  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//�����ȼ�1
//  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
//  	NVIC_Init(&NVIC_InitStructure);  	  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
		
		NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			//ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2�� 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//�����ȼ�1
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure); 
 
 
//   	NVIC_InitStructure.NVIC_IRQChannel = EXTI_Line1;			//ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
//  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2�� 
//  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//�����ȼ�1
//  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
//  	NVIC_Init(&NVIC_InitStructure); 
 
}

 
//void EXTI0_IRQHandler(void)
//{
//  printf("key1\r\n");
//	delay_ms(10);    //����
//	if(KEY1==0)
//	{
//		Key1_Count++;
//	}
//	while(!KEY1);
//	EXTI_ClearITPendingBit(EXTI_Line0);  //���EXTI0��·����λ
//}


 void EXTI9_5_IRQHandler(void)
{			
	printf("key0\r\n");
	delay_ms(10);   //����			 
	if(KEY0==0)	
	{
		Key0_Count++;
		Key0_Flag=Key0_Count;
	}
	while(!KEY0);
  EXTI_ClearITPendingBit(EXTI_Line5);    //���LINE5�ϵ��жϱ�־λ  
}

//void EXTI1_IRQHandler(void)
//{
//	printf("key2\r\n");
//	delay_ms(10);    //����
//	if(KEY2==0)
//	{
//		Key2_Count++;
//	}
//	while(!KEY2);
//	EXTI_ClearITPendingBit(EXTI_Line1);  //���EXTI1��·����λ
//}

/***********************************************
**�������ƣ����ݰ���ȷ����Ӧ�Ĺ���
**�����������
**����ֵ��
**����˵������
**���ߣ�WFY
************************************************/
u8 Key_Function(void)
{
	
	
	if(Key0_Count%4==0)
	{
		return DATE_TEMP_FLAG;
	}
	else if(Key0_Count%4==1)
	{
		
		return ECG_HEARTRATE_FLAG;
	}
	else if(Key0_Count%4==2)
	{
		return ECGDATEHANDLE;
	}
	else
	{
		return OTHER_FLAG;
	}	
}


/***********************************************
**�������ƣ����ݰ�����ʾ��Ӧ�Ĵ���
**�����������
**����ֵ��
**����˵������
**���ߣ�WFY
************************************************/
void Display_Function(void)
{
	u8 f=0;
	f=Key_Function();
	switch(f)
	{
		case DATE_TEMP_FLAG:  //ʱ���¶��л���ʾ
		{
			Set_LED_Status(0,1,1,1,0,0,100,0,0);
			OLED_Show_Date_Temp(8000);
			break;
		}
		case ECG_HEARTRATE_FLAG:  //�ĵ粨�κ������л���ʾ
		{
			Set_LED_Status(1,0,1,0,1,0,0,100,0);
			OLED_Show_ECG_HeartRate(1000);
			break;
		}
		case ECGDATEHANDLE:
		{
			WaterLights();
			ECGDate_Handle();//�ĵ����ݴ���
		}
		case OTHER_FLAG:
		{
			Set_LED_Status(1,1,0,0,0,1,0,0,100);
			Display1_Function();
			break;
		}
	}
}
	

