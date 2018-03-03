#include "delay.h" 			 
#include "usart.h" 			 
#include "usart2.h" 			 
#include "hc05.h" 
#include "led.h" 
#include "string.h"	 
#include "math.h"
 	   
/**************************
**�������ƣ�HC05_Init
**�������ܣ���ʼ��ATK-HC05ģ��
**������������
**�������أ�����ֵ:0,�ɹ�;1,ʧ��.
**�������ߣ�������
**�޸�ʱ�䣺2016.05.17
**�ر�˵����PA4-LED    PC4-KEY
****************************/
void HC05_Init(void)
{
	  		 
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC,ENABLE);	//ʹ��PORTA Cʱ��	
//LED 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;				 // �˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 //��������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);					 //�����趨������ʼ��A4
	 
//KEY
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;				 // �˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOC4

	USART2_Init(9600);	//��ʼ������2Ϊ:9600,������.
	HC05_KEY=1;					//KEY�ø�,����ATģʽ	 
}	 


/**************************
**�������ƣ�HC05_Get_Role
**�������ܣ���ȡATK-HC05ģ��Ľ�ɫ
**������������
**�������أ�����ֵ:0,�ӻ�;1,����;0XFF,��ȡʧ��.
**�������ߣ�������
**�޸�ʱ�䣺2016.05.17
**�ر�˵������
****************************/
u8 HC05_Get_Role(void)
{	 		    
	u8 retry=0X0F;
	u8 temp,t;
	while(retry--)
	{
		HC05_KEY=1;					//KEY�ø�,����ATģʽ
		delay_ms(10);
		u2_printf("AT+ROLE?\r\n");	//��ѯ��ɫ
		for(t=0;t<20;t++) 			//��ȴ�200ms,������HC05ģ��Ļ�Ӧ
		{
			delay_ms(10);
			if(USART2_RX_STA&0X8000)break;
		}		
		HC05_KEY=0;					//KEY����,�˳�ATģʽ
		if(USART2_RX_STA&0X8000)	//���յ�һ��������
		{
			temp=USART2_RX_STA&0X7FFF;	//�õ����ݳ���
			USART2_RX_STA=0;			 
			if(temp==13&&USART2_RX_BUF[0]=='+')//���յ���ȷ��Ӧ����
			{
				temp=USART2_RX_BUF[6]-'0';//�õ�����ģʽֵ
				break;
			}
		}		
	}
	if(retry==0)temp=0XFF;//��ѯʧ��.
	return temp;
} 							   

/**************************
**�������ƣ�HC05_Set_Cmd
**�������ܣ�ATK-HC05��������
**����������atstr:ATָ�.����:"AT+RESET"/"AT+UART=9600,0,0"/"AT+ROLE=0"���ַ���
**�������أ�����ֵ:0,���óɹ�;����,����ʧ��.
**�������ߣ�������
**�޸�ʱ�䣺2016.05.17
**�ر�˵�����˺�����������ATK-HC05,�����ڽ�����OKӦ���ATָ��
****************************/
u8 HC05_Set_Cmd(u8* atstr)
{	 		    
	u8 retry=0X0F;
	u8 temp,t;
	while(retry--)
	{
		HC05_KEY=1;					//KEY�ø�,����ATģʽ
		delay_ms(10);
		u2_printf("%s\r\n",atstr);	//����AT�ַ���
		HC05_KEY=0;					//KEY����,�˳�ATģʽ
		for(t=0;t<20;t++) 			//��ȴ�100ms,������HC05ģ��Ļ�Ӧ
		{
			if(USART2_RX_STA&0X8000)break;
			delay_ms(5);
		}		
		if(USART2_RX_STA&0X8000)	//���յ�һ��������
		{
			temp=USART2_RX_STA&0X7FFF;	//�õ����ݳ���
			USART2_RX_STA=0;			 
			if(temp==4&&USART2_RX_BUF[0]=='O')//���յ���ȷ��Ӧ����
			{			
				temp=0;
				break;			 
			}
		}		
	}
	if(retry==0)temp=0XFF;//����ʧ��.
	return temp;
} 
///////////////////////////////////////////////////////////////////////////////////////////////////
//ͨ���ú���,��������USMART,���Խ��ڴ���2�ϵ�ATK-HC05ģ��
//str:���.(����ע�ⲻ����Ҫ������س���)
void HC05_CFG_CMD(u8 *str)
{					  
	u8 temp;
	u8 t;		  
	HC05_KEY=1;						//KEY�ø�,����ATģʽ
	delay_ms(10);
	u2_printf("%s\r\n",(char*)str); //����ָ��
	for(t=0;t<50;t++) 				//��ȴ�500ms,������HC05ģ��Ļ�Ӧ
	{
		if(USART2_RX_STA&0X8000)break;
		delay_ms(10);
	}									    
	HC05_KEY=0;						//KEY����,�˳�ATģʽ
	if(USART2_RX_STA&0X8000)		//���յ�һ��������
	{
		temp=USART2_RX_STA&0X7FFF;	//�õ����ݳ���
		USART2_RX_STA=0;
		USART2_RX_BUF[temp]=0;		//�ӽ�����		 
		printf("\r\n%s",USART2_RX_BUF);//���ͻ�Ӧ���ݵ�����1
	} 				 
}

//��ʾATK-HC05ģ�������״̬
void HC05_Role_Show(void)
{
	if(HC05_Get_Role()==1)
		printf("ROLE:Master\n");//����
	else 
		printf("ROLE:Slave\n");//�ӻ�
}


//��ʾATK-HC05ģ�������״̬
u8 HC05_Sta_Show(void)
{												 
	if(HC05_LED)
		return 1;//���ӳɹ�
	else 
		return 0;//δ����
}	
//����λ�������ĵ�����
void HC05_SendDate(double *arry,int num,int len)
{
	int i=0;
	char DateTemp[30];
	for(i=num*128;i<len;i++)
		{
			if(arry[i]>=0)
			{
				sprintf(DateTemp,"%8.3lf",arry[i]);
				u2_printf(DateTemp);
				u2_printf("\r\n");	
			}
			else
			{
				sprintf(DateTemp,"%9.3lf",arry[i]);
				u2_printf(DateTemp);
				u2_printf("\r\n");
			}	
		}

}









