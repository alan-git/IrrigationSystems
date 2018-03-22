#ifndef _TIMER_CLOCK_H__
#define _TIMER_CLOCK_H__

#include "INCLUDES.H"
/* *******************************************************************************************
/* 1.检查基准时间(TIME_BASE)是否能将1S整除；
/* N.OVER；
/* ******************************************************************************************* */

extern u8 Hour, Min, Sec;		//时分秒；
extern void Timer_Clock_Init();	//时间时钟初始化；
extern void Timer_Clock();		//时间时钟计时函数；


#endif
