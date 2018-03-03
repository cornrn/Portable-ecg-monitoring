#include "key.h"
#include "delay.h"

/***********************************************
**�������ƣ�KEY��������
**�����������
**����ֵ����
**����˵����KEY0--PC5 KEY1--PB0  KEY2--PB1
**���ߣ�WFY
************************************************/
void KEY_Init(void)
{
	
	GPIO_InitTypeDef GPIO_InitStructure;

 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC,ENABLE);//ʹ��PORTA,PORTCʱ��

	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//�ر�jtag��ʹ��SWD��������SWDģʽ����
//KEY0	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_5;//PC5
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
 	GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��GPIOC5
//KEY1	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;//PC5
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
 	GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIOC5
//KEY2	 
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1;//PC5
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
 	GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIOC5
	
} 


/***********************************************
**�������ƣ�����������
**���������mode:0,��֧��������;1,֧��������;
**����ֵ�����ذ���ֵ
**����˵���� 0��û���κΰ�������
			KEY0_PRES��KEY0����
			KEY1_PRES��KEY1����
			WKUP_PRES��WK_UP���� 
			ע��˺�������Ӧ���ȼ�,KEY0>KEY1>WK_UP!!
**���ߣ�WFY
************************************************/
u8 KEY_Scan(void)
{
	if((KEY0==0)||(KEY1==0)||(KEY2==0))
	{
		delay_ms(10);
		if(KEY0==0)
		{
			while(!KEY0);
			return KEY0_PRES;
		}
		else if(KEY1==0)
		{
			while(!KEY1);
			return KEY1_PRES;
		}
		else if(KEY2==0)
		{
			while(!KEY2);
			return KEY2_PRES;
		}
		else
		{
			return 0;
		}
	}
}
//{	 
//	static u8 key_up=1;//�������ɿ���־
//	if(mode)key_up=1;  //֧������		  
//	if(key_up&&(KEY0==0||KEY1==0||KEY2==1))
//	{
//		delay_ms(10);//ȥ���� 
//		key_up=0;
//		if(KEY0==0)
//			return KEY0_PRES;
//		else if(KEY1==0)
//			return KEY1_PRES;
//		else if(KEY2==0)
//			return KEY2_PRES; 
//	}
//	else if(KEY0==1&&KEY1==1&&KEY2==1)
//		key_up=1; 	     
//	return 0;// �ް��������
//}
