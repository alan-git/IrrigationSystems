#ifndef _TIMER_CLOCK_H__
#define _TIMER_CLOCK_H__

#include "INCLUDES.H"
/* *******************************************************************************************
/* 1.����׼ʱ��(TIME_BASE)�Ƿ��ܽ�1S������
/* N.OVER��
/* ******************************************************************************************* */

extern char Hour, Min, Sec;     //ʱ���룻
extern void Timer_Clock_Init(); //ʱ��ʱ�ӳ�ʼ����
extern void Timer_Clock();      //ʱ��ʱ�Ӽ�ʱ������


#endif