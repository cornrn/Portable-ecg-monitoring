#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"
	 

#define KEY0  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_5)//��ȡ����0
#define KEY1  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)//��ȡ����1
#define KEY2  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)//��ȡ����2 
 

#define KEY0_PRES	1		//KEY0  
#define KEY1_PRES	2		//KEY1 
#define KEY2_PRES	3		//KEY2  

void KEY_Init(void);//����������������
u8 KEY_Scan(void);  	//����ɨ�躯������


#endif
