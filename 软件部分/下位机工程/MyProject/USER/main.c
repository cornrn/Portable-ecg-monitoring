#include "delay.h"
#include "sys.h"
#include "bmp.h"
#include "function.h"
#include "usart.h"
#include "exti.h"
#include "led.h"
#include "hc05.h"
#include "usart2.h"
#include "malloc.h"	 
#include "mmc_sd.h"	

int main(void)
{		
	
	BspInit();//Ӳ����ʼ��
	
	while(OLED_Show_HC05Status());//��������Ƿ����ӳɹ�
	
	while(1) 
	{	
		Display_Function();//�ĵ�������ʾ
	}

}
