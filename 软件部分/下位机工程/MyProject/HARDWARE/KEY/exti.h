#ifndef __EXTI_H
#define __EXIT_H	 
#include "sys.h"
#include "stm32f10x_exti.h"
#include "function.h"
#include "led.h"

#define DATE_TEMP_FLAG  0  //ʱ���¶��л���ʾ
#define ECG_HEARTRATE_FLAG 1	//�ĵ粨�κ������л���ʾ
#define OTHER_FLAG 2	//�ĵ粨�κ������л���ʾ
#define ECGDATEHANDLE 3  //���ݴ���

static int Key0_Count;
static int ECG_Count;
extern int Key0_Flag;
extern int ECG_Count_Flag;

void EXTIX_Init(void);//IO��ʼ��
u8 Key_Function(void);
void Display_Function(void);
		 					    
#endif

