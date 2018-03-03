#include "function.h"


int Key0_Flag=0;
static int Key1_Count=0;
static int Key2_Count=0;
static int lineCount=0;

extern  u8  ECGDateHandleOverFlag;


/***********************************************
**�������ƣ��缫����OLED�����缫����
**�����������
**����ֵ����
**����˵������
**���ߣ�WFY
************************************************/
void ElectrodeOff()
{
	OLED_ShowCHinese(24,3,38);//��
	OLED_ShowCHinese(42,3,39);//��
	OLED_ShowCHinese(60,3,40);//��
	OLED_ShowCHinese(78,3,41);//��
	OLED_ShowCHinese(96,3,42);//��
	
	Two_Long_Two_Short();
}



/***********************************************
**�������ƣ�OLED��ʾ����Ŀ��
**�����������
**����ֵ����
**����˵������
**���ߣ�WFY
************************************************/
void OLED_Show_Frame()
{
		OLED_ShowCHinese(0,0,4);//��
		OLED_ShowCHinese(21,0,5);//��
		OLED_ShowCHinese(42,0,6);//��
		OLED_ShowCHinese(63,0,7);//��
		OLED_ShowCHinese(84,0,8);//ϵ
		OLED_ShowCHinese(105,0,9);//ͳ
		OLED_ShowCHinese(0,6,10);//֣
		OLED_ShowCHinese(16,6,12);//��
		OLED_ShowCHinese(32,6,14);//��
		OLED_ShowCHinese(48,6,15);//��
		OLED_ShowCHinese(64,6,16);//��
		OLED_ShowCHinese(80,6,17);//��
		OLED_ShowCHinese(96,6,18);//ѧ
		OLED_ShowCHinese(112,6,19);//Ժ
}

/***********************************************
**�������ƣ�OLED��ʾ��ǰ��ʱ��
**�����������
**����ֵ����
**����˵������
**���ߣ�WFY
************************************************/
void OLED_ShowDate()
{
	
	while(RTC_Init())		//RTC��ʼ��	��һ��Ҫ��ʼ���ɹ�
	{ 
		delay_ms(800);
		OLED_Clear();
		OLED_ShowString(16,2,"RTC Error!!!",16);
		One_Long_One_Short();
	}	

	OLED_Show_Frame();
	OLED_ShowString(0,2,"Date:",16);
	OLED_ShowNum(48,2,calendar.w_year,4,12);
	OLED_ShowChar(72,2,'-',12);
	OLED_ShowNum(76,2,calendar.w_month,2,12);
	OLED_ShowChar(88,2,'-',12);
	OLED_ShowNum(92,2,calendar.w_date,2,12);
	
	OLED_ShowNum(48,3,calendar.hour,2,12);
	OLED_ShowChar(60,3,':',12);
	OLED_ShowNum(64,3,calendar.min,2,12);
	OLED_ShowChar(76,3,':',12);
	OLED_ShowNum(80,3,calendar.sec,2,12);
	
}

/***********************************************
**�������ƣ�OLED��ʾ��ǰ��ʱ��
**�����������
**����ֵ����
**����˵������
**���ߣ�WFY
************************************************/
void OLED_ShowDate1()
{
	
	while(RTC_Init())		//RTC��ʼ��	��һ��Ҫ��ʼ���ɹ�
	{ 
		delay_ms(800);
		OLED_Clear();
		OLED_ShowString(0,2,"RTC Error!!!",16);
		One_Long_One_Short();
	}	

	OLED_ShowString(0,2,"Date:",16);
	OLED_ShowNum(48,2,calendar.w_year,4,12);
	OLED_ShowChar(72,2,'-',12);
	OLED_ShowNum(76,2,calendar.w_month,2,12);
	OLED_ShowChar(88,2,'-',12);
	OLED_ShowNum(92,2,calendar.w_date,2,12);
	
	OLED_ShowNum(48,3,calendar.hour,2,12);
	OLED_ShowChar(60,3,':',12);
	OLED_ShowNum(64,3,calendar.min,2,12);
	OLED_ShowChar(76,3,':',12);
	OLED_ShowNum(80,3,calendar.sec,2,12);
	
}
/***********************************************
**�������ƣ�OLED��ʾ��ǰ���¶�
**�����������
**����ֵ����
**����˵������
**���ߣ�WFY
************************************************/
void OLED_Show_Temp()
{
	static int num=0;
	char Date[30];
	double t;
	while(DS18B20_Init())	//DS18B20��ʼ��	
	{
		num++;
		OLED_Clear();
		OLED_ShowString(0,2,"DS18B20 Error!!!",16);
		One_Long_Two_Short();
		if(num==3)
		{
			num=0;
			break;
		}
	}
	
	temperature=DS18B20_Get_Temp();
	t=temperature/10+(temperature%10)*0.1;
	sprintf(Date,"%7.1lf",t);
	u2_printf("T  :");
	u2_printf("\r\n");
	u2_printf(Date);
	u2_printf("\r\n");
	
	
	
	OLED_Show_Frame();
	OLED_ShowString(0,2,"Temp:",16);
	OLED_ShowNum(48,2,temperature/10,2,16);
	OLED_ShowChar(64,2,'.',16);
	OLED_ShowNum(72,2,temperature%10,1,16);
	OLED_ShowCHinese(90,2,20);
	OLED_ShowChar(100,2,'C',16);		
}

/***********************************************
**�������ƣ�OLED��ʾ��ǰ���¶�
**�����������
**����ֵ����
**����˵������
**���ߣ�WFY
************************************************/
void OLED_Show_Temp1()
{
	static int num=0;
	char Date[30];
	double t;
	while(DS18B20_Init())	//DS18B20��ʼ��	
	{
		num++;
		OLED_Clear();
		OLED_ShowString(0,2,"DS18B20 Error!!!",16);
		One_Long_Two_Short();
		if(num==3)
		{
			num=0;
			break;
		}
	}
	
	temperature=DS18B20_Get_Temp();
	t=temperature/10+(temperature%10)*0.1;
	sprintf(Date,"%7.1lf",t);
	u2_printf("T  :");
	u2_printf("\r\n");
	u2_printf(Date);
	u2_printf("\r\n");
	
	OLED_ShowString(0,2,"Temp:",16);
	OLED_ShowNum(48,2,temperature/10,2,16);
	OLED_ShowChar(64,2,'.',16);
	OLED_ShowNum(72,2,temperature%10,1,16);
	OLED_ShowCHinese(90,2,20);
	OLED_ShowChar(100,2,'C',16);		
}



/***********************************************
**�������ƣ�OLED��ʾ��ǰ��ʱ����¶�
**���������time:��ʱʱ��
**����ֵ����
**����˵������
**���ߣ�WFY
************************************************/
void OLED_Show_Date_Temp(int time)
{
		OLED_Clear();	
		OLED_ShowDate();
		delay_ms(time);
		delay_ms(time);
		delay_ms(time);
		delay_ms(time);
		OLED_Clear();
		OLED_Show_Temp();
		delay_ms(time);
		delay_ms(time);
		OLED_Clear();
}
/***********************************************
**�������ƣ�OLED��ʾ����
**���������time:��ʱʱ��
**����ֵ����
**����˵������
**���ߣ�WFY
************************************************/
void OLED_ShowCoordinate(int num)
{
	OLED_ShowCHinese(10,0,21);//��
	OLED_ShowCHinese(34,0,22);//��
	OLED_ShowCHinese(58,0,23);//��
	OLED_ShowCHinese(82,0,24);//��
	OLED_ShowNum(116,0,num,1,16);
	OLED_Fill(0,0,127,0,1);//x��	
	OLED_Fill(0,0,0,47,1);//y��
}


/***********************************************
**�������ƣ�OLED��ʾ�ĵ粨��0
**���������time:��ʱʱ��
**����ֵ����
**����˵������
**���ߣ�WFY
************************************************/
void OLED_Plot_ECG()
{
	int x=0;
	int y=0;
	int i=0,j=0;
	u8 t=0;
	int tempArry[128];
	static int count=0;
	static int ECGcount=0;
	double max,min,offset;
	OLED_ShowCoordinate(1);
	Max_Min(ECGArry,&max,&min,1280);
	if(min<0)
	{
		offset=-min;
	}
	else
	{
		offset=0;
	}
	
	for(i=0;i<1280;i++)
	{
		x=i-count*128+2;
		y=((ECGArry[i]+offset)/(max-min))*45+8;
		tempArry[i-count*128]=y;
		OLED_DrawPoint(x,y,1);
		if((i+1)%128==0)
		{
			
			for(j=0;j<128;j++)
			{
				OLED_DrawPoint(j+2,tempArry[j],0);
			}
			count++;
			t=KEY_Scan();
			if(t==KEY1_PRES)
			{
				ECGcount++;
			}
			if(ECGcount%4==0)
			{
				;
			}
			else if(ECGcount%4==1)
			{
				OLED_Clear();
				OLED_Plot_ECG1();
				break;
			}
			else if(ECGcount%4==2)
			{
				OLED_Clear();
				OLED_Plot_ECG2();
				count=0;
				break;
			}
			else
			{
				OLED_Clear();
				count=0;
				break;
			}
			
		}
	}
	count=0;	
}

/***********************************************
**�������ƣ�OLED��ʾ�ĵ粨��1
**���������time:��ʱʱ��
**����ֵ����
**����˵������
**���ߣ�WFY
************************************************/
void OLED_Plot_ECG1()
{
	int x=0;
	int y=0;
	int i=0,j=0;
	u8 t;
	int tempArry[128];
	static int count=0;
	static int ECGcount1=0;
	double max,min,offset;
	OLED_ShowCoordinate(2);
	Max_Min(ECGArry1,&max,&min,1280);
	if(min<0)
	{
		offset=-min;
	}
	else
	{
		offset=0;
	}
	for(i=0;i<1280;i++)
	{
		x=i-count*128+2;
		y=((ECGArry1[i]+offset)/(max-min))*45+8;
		tempArry[i-count*128]=y;
		OLED_DrawPoint(x,y,1);
		if((i+1)%128==0)
		{
			for(j=0;j<128;j++)
			{
				OLED_DrawPoint(j+2,tempArry[j],0);
			}
			count++;
			t=KEY_Scan();
			if(t==KEY1_PRES)
			{
				ECGcount1++;
			}
			if(ECGcount1%2==0)
			{
				;
			}
			else 
			{
				count=0;
				OLED_Clear();
				OLED_Plot_ECG2();
				break;
			}
		}
	}
	count=0;	
}

/***********************************************
**�������ƣ�OLED��ʾ�ĵ粨��2
**���������time:��ʱʱ��
**����ֵ����
**����˵������
**���ߣ�WFY
************************************************/
void OLED_Plot_ECG2()
{
	int x=0;
	int y=0;
	int i=0,j=0;
	u8 t;
	int tempArry[128];
	static int count=0;
	static int ECGcount2=0;
	double max,min,offset;
	OLED_ShowCoordinate(3);
	Max_Min(ECGArry2,&max,&min,1280);
	if(min<0)
	{
		offset=-min;
	}
	else
	{
		offset=0;
	}
	for(i=0;i<1280;i++)
	{
		x=i-count*128+2;
		y=((ECGArry2[i]+offset)/(max-min))*45+8;
		tempArry[i-count*128]=y;
		OLED_DrawPoint(x,y,1);
		if((i+1)%128==0)
		{
			for(j=0;j<128;j++)
			{
				OLED_DrawPoint(j+2,tempArry[j],0);
			}
			count++;
			t=KEY_Scan();
			if(t==KEY1_PRES)
			{
				ECGcount2++;
			}
			if(ECGcount2%2==0)
			{
				;
			}
			else 
			{
				count=0;
				OLED_Clear();
				OLED_Plot_ECG();
			}
		}
	}
	count=0;	
}
/***********************************************
**�������ƣ�OLED��ʾ����
**���������time:��ʱʱ��
**����ֵ����
**����˵������
**���ߣ�WFY
************************************************/
void OLED_Show_HeartRate()
{
	OLED_ShowCHinese(16,0,25);//��
	OLED_ShowCHinese(40,0,26);//��
	OLED_ShowCHinese(64,0,27);//��
	OLED_ShowCHinese(88,0,28);//ʾ
	
	OLED_ShowCHinese(8,4,25);//��
	OLED_ShowCHinese(32,4,26);//��
	
	OLED_ShowChar(50,4,':',16);
	
	OLED_ShowNum(68,4,75,2,16);
	
	OLED_ShowString(96,4,"bpm",16);
	
}
/***********************************************
**�������ƣ�OLED��ʾ���ʺ��ĵ粨��
**���������time:��ʱʱ��
**����ֵ����
**����˵������
**���ߣ�WFY
************************************************/
void OLED_Show_ECG_HeartRate(int time)
{
	int x=0;
	int y=0;
	int i=0,j=0;
	int tempArry[128];
	static int count=0;
	double max,min,offset;
	OLED_ShowCoordinate(1);
	Max_Min(ECGArry,&max,&min,1280);
	if(min<0)
	{
		offset=-min;
	}
	else
	{
		offset=0;
	}

	for(i=0;i<1280;i++)
	{
		
		x=i-count*128+2;
		y=((ECGArry[i]+offset)/(max-min))*45+8;
		tempArry[i-count*128]=y;
		OLED_DrawPoint(x,y,1);
		if((i+1)%128==0)
		{
			for(j=0;j<128;j++)
			{
				OLED_DrawPoint(j+2,tempArry[j],0);
			}
			OLED_Clear();
			OLED_Show_HeartRate();
			delay_ms(time);
			OLED_Clear();
			count++;
			if((Key0_Flag%4)!=1)
			{
				OLED_Clear();
				count=0;
				break;
			}
			OLED_ShowCoordinate(1);
		}
	}
	count=0;
}


/***********************************************
**�������ƣ������������ֵ����Сֵ
**���������arry������  max�����ֵ min����Сֵ len�����鳤��
**����ֵ����
**����˵������
**���ߣ�WFY
************************************************/
void Max_Min(const double* arry,double* max,double* min,int len)
{
	int i=0;
	
	*max=arry[0];
	*min=arry[0];
	
	for(i=0;i<len;i++)
	{
		if(arry[i]>*max)
		{
			*max=arry[i];
		}
	}
	
	for(i=0;i<len;i++)
	{
		if(arry[i]<*min)
		{
			*min=arry[i];
		}
	}	
}
/***********************************************
**�������ƣ����ݰ�����ʾ��Ӧ�Ĵ���
**�����������
**����ֵ��
**����˵������
**���ߣ�WFY
************************************************/
void Display1_Function()
{
	u8 KeyValue=KEY_Scan();
	
	switch(KeyValue)
	{
		case KEY1_PRES:
		{
			Key1_Count++;
			if(Key1_Count%2==0)
			{
				OLED_Clear();
				OLED_ShowDate1();
				break;
			}
			else
			{
				OLED_Clear();
				OLED_Show_Temp1();
				break;
			}
		}
		case KEY2_PRES:
		{
			Key2_Count++;
			if(Key2_Count%2==0)
			{
				OLED_Clear();
				OLED_Plot_ECG();
				break;
			}
			else
			{
				OLED_Clear();
				OLED_Show_HeartRate();
				break;
			}
		}
	}
}

/***********************************************
**�������ƣ�ϵͳ��Ӳ����Դ��ʼ��
**�����������
**����ֵ��
**����˵������
**���ߣ�WFY
************************************************/
void BspInit()
{
	delay_init();	    	 //��ʱ������ʼ��	
	uart_init(9600);		//����1��ʼ��������Ϊ9600
	NVIC_Configuration(); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ� 	LED_Init();			     //LED�˿ڳ�ʼ��
	OLED_Init();			//��ʼ��OLED  
	Beep_Init();			//��ʼ��������
	led_Init();				//��ʼ��LED
	EXTIX_Init();			//��ʼ���ⲿ�ж�
	
	HC05_Init(); 			//��ʼ������
	
	SPI3_Init();			//��ʼ��SD����SPI�ӿ�
	SD_Initialize();	//��ʼ��SD��
	
	SPI_Configuration();//ADS1293  spi�ӿڳ�ʼ��
	TIMER_Configuration();//��ʼ����ʱ��
	ADS1293_ResetControl(ADS1293_Reset_Disable);		//Release reset pin, assert it as high
	ADS1293_Init();//ADS1293��ʼ��
	
	while(ElectrodeDetection(Leads));
	
	
	ADS1293_StartConversion();//��ʼADS1293���ݲɼ�
}

/***********************************************
**�������ƣ��ĵ����ݵĲɼ��뷢�ͺ�дSD��
**�����������
**����ֵ��
**����˵������
**���ߣ�WFY
************************************************/
void ECGDate_Handle()
{
	ADS1293_Handler();//�ĵ����ݴ���
//	if(ECGDateHandleOverFlag==1)//һ֡���ݴ������
	if(1)	
	{
			
//�����������ݲ���		
		ECGDateHandleOverFlag=0;
		u2_printf("\r\n");
		u2_printf("ECGCh1:");
		u2_printf("\r\n");
		HC05_SendDate(ECGArry,lineCount,128);//��������ͨ��1������
		u2_printf("\r\n");
		u2_printf("ECGCh2:");
		u2_printf("\r\n");
		HC05_SendDate(ECGArry1,lineCount,128);//��������ͨ��2������
		u2_printf("\r\n");
		u2_printf("ECGCh3:","\r\n");
		u2_printf("\r\n");
		HC05_SendDate(ECGArry2,lineCount,128);//��������ͨ��3������
		u2_printf("\r\n");
		lineCount++;
//SD��д���ݲ���
		SD_WriteDisk((u8*)ECGArry,lineCount,lineCount);
		SD_WriteDisk((u8*)ECGArry1,lineCount,lineCount);
		SD_WriteDisk((u8*)ECGArry2,lineCount,lineCount);
		if(lineCount==9)
		{
			lineCount=0;
		}
	}	
}
//�缫��⺯��
u8 ElectrodeDetection(unsigned int* leadarry)
{
	int i=0;
	for(i=0;i<5;i++)
	{
		if(leadarry[i]==0)
		{
			ElectrodeOff();
			return 1;
		}
	}
	return 0;
}


