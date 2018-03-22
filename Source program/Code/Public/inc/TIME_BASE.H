#ifndef _TIME_BASE_H__
#define _TIME_BASE_H__

#include "INCLUDES.H"

/* *******************************************************************************************
/* 1.利用STC-ISP软件导出函数 Timer0Init/Timer1Init/...；
/* 2.#define T_0/T_1/...;
/* 3.修改定时器0/1/...溢出时长；
/* 4.选取一个基准时间(TIME_BASE)；
/* N.OVER；
/* ******************************************************************************************* */
#define T_0
//#define T_1
//#define T_2

#ifdef T_0
	#define SET_T0_TIME				(2000L)			//定时器0溢出时长；
	#define TIMING_DELAY_USE_TIMER	SET_T0_TIME
#else
	#ifdef T_1
		#define SET_T1_TIME			(2000L)			//定时器1溢出时长；
		#define TIMING_DELAY_USE_TIMER	SET_T1_TIME	
	#else
		#ifdef T_2
			#define SET_T2_TIME		(2000L)			//定时器2溢出时长；
			#define TIMING_DELAY_USE_TIMER	SET_T2_TIME	
		#endif
	#endif
#endif

//#define _16MS		(16000L)	  					//自定义基准时长(溢出时长的整数倍)；
#define TIME_BASE	_20MS							//基准时间定义；

#define OVERFLOW_TIMES (TIME_BASE/TIMING_DELAY_USE_TIMER)//计满所选基准时间，定时器的溢出次数；
#define _60S		(60000000L)
#define _20S		(20000000L)
#define _10S		(10000000L)
#define _5S			(5000000L)
#define _2S			(2000000L)
#define _1S			(1000000L)
#define _500MS		(500000L)
#define _200MS		(200000L)
#define _100MS		(100000L)
#define _50MS		(50000L)
#define _20MS		(20000L)		//50HZ
#define _10MS		(10000L)
#define _5MS		(5000L)
#define _2MS		(2000L)

extern void InitInterrupt();

#endif			  	 
