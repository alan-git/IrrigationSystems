#ifndef _PBDATA_H__
#define _PBDATA_H__

#include <MATH.H>
#include <STDIO.H>
#include <STRING.H>
#include <INTRINS.H>
#include <REGX52.H>

sfr AUXR   = 0x8E;

sbit P00 = P0^0;
sbit P01 = P0^1;
sbit P02 = P0^2;
sbit P03 = P0^3;
sbit P04 = P0^4;
sbit P05 = P0^5;
sbit P06 = P0^6;
sbit P07 = P0^7;

sbit P10 = P1^0;
sbit P11 = P1^1;
sbit P12 = P1^2;
sbit P13 = P1^3;
sbit P14 = P1^4;
sbit P15 = P1^5;
sbit P16 = P1^6;
sbit P17 = P1^7;

sbit P20 = P2^0;
sbit P21 = P2^1;
sbit P22 = P2^2;
sbit P23 = P2^3;
sbit P24 = P2^4;
sbit P25 = P2^5;
sbit P26 = P2^6;
sbit P27 = P2^7;

sbit P30 = P3^0;
sbit P31 = P3^1;
sbit P32 = P3^2;
sbit P33 = P3^3;
sbit P34 = P3^4;
sbit P35 = P3^5;
sbit P36 = P3^6;
sbit P37 = P3^7;

/* *******************************************************************************************
/* 1.根据芯片选择include的芯片头文件(向下兼容，一边情况下不必修改);
/* 2.选择FOSC，并适当修改PARAMETER_US&MS，根据需求选择是否屏蔽.C中的微秒级延时函数;
/* 3.从STC-ISP中导出1US延时函数并在.C中替换;
/* 4.根据工作状态提示灯的位置定义LED及LED的ON/OFF(未设计择不必理会);
/* 5.根据需求选择是否屏蔽数码管字形，位选数组;
/* N.OVER；
/* ******************************************************************************************* */

#define PARAMETER_US	1//6		//软件延时时长；
#define PARAMETER_MS	125//680	//软件延时时长；

#define LED			P12				//工作状态提示灯；
#define LED_On(); 	LED=0;
#define LED_Off(); 	LED=1;

#define FOSC			FOSC_12		//系统频率；
#define FOSC_33_1176	(33117600L)
#define FOSC_22_1184	(22118400L)
#define FOSC_18_432		(18432000L)		
#define FOSC_11_0592	(11059200L)		
#define FOSC_5_5296		(5529600L)
#define FOSC_33			(33000000L)
#define FOSC_30			(30000000L)
#define FOSC_27			(27000000L)
#define FOSC_24			(24000000L)
#define FOSC_20			(20000000L)
#define FOSC_12			(12000000L)
#define FOSC_6			(6000000L)

#define TRUE	1
#define FALSE	0
#define u8 		unsigned char
#define u16 	unsigned int
#define uchar 	unsigned char			//兼容；
#define uint 	unsigned int
#define u32 	unsigned long
#define nop();	_nop_();

#define SEG_NEGATIVE_SIGN	0xBF		//负号显示；
#define SEG_POINT			0x7F		//小数点显示；

extern const u8 code W_Scan[8];
extern const u8 code Seg_7[11];			//数码管字形数组；

extern void 		Delay1US();
extern void 		DelayUS(u16 x);
extern void 		DelayMS(u16 x);
extern void			InitIO();
extern void			InitOver();
extern void			STC_ISP();

#endif

/*******************************************************************************
//data	固定指片内RAM：		0x00~0x7F
//bdata	固定指片内RAM：		0x20~0x2F
//idata	固定指片内RAM：		0x00~0xFF
//xdata	一般指扩展RAM：		0x0000~0xFFFF，也指STC内部扩展RAM：0x0000~0xFFFF
//code	指程序存储区ROM：	0x0000~0xFFFF
/*******************************************************************************/

/*
_crol_ 字符循环左移 　　
_cror_ 字符循环右移 　　
_irol_ 整数循环左移 　　
_iror_ 整数循环右移 　　
_lrol_ 长整数循环左移 　　
_lror_ 长整数循环右移 　　
_nop_ 空操作8051 NOP 指令
_testbit_ 测试并清零位8051 JBC 指令 

（_crol_，_irol_，_lrol_）以位形式将val 循环左移n 位，该函数与8051“RLA”指令相关，上面几个函数不同于参数类型。
（_cror_，_iror_，_lror_）以位形式将val 循环右移n 位，该函数与8051“RRA”指令相关，上面几个函数不同于参数类型。 
（_nop_）    产生一个NOP 指令,该函数可用作C 程序的时间比较。C51 编译器在_nop_函数工作期间不产生函数调用，即在程序中直接执行了NOP 指令。
（_testbit_）产生一个JBC 指令，该函数测试一个位，当置位时返回1，否则返回0。如果该位置为1，则将该位复位为0。
             8051 的JBC 指令即用作此目的。_testbit_只能用于可直接寻址的位；在表达式中使用是不允许的。
*/

/*****************************************************************************
Name        : SPIReadByte(void)
Description : 读SPI数据
Input       : None
Output      : None
Return      : None
*****************************************************************************/

