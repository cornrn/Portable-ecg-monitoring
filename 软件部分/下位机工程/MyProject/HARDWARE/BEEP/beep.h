#ifndef __BEEP_H
#define __BEEP_H
#include "sys.h"

#define BEEP PCout(13)//PC13

void Beep_Init(void);//��������ʼ����������

void One_Long_One_Short(void);//һ��һ��

void One_Long_Two_Short(void);//һ������

void One_Long_Three_Short(void);//һ������

void One_Long_Four_Short(void);//һ���Ķ�

void Two_Long_Two_Short(void);//��������




#endif


