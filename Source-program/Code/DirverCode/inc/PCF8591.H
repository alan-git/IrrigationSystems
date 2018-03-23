#ifndef	_PCF8591_H__
#define	_PCF8591_H__

#include "INCLUDES.H"
/* *******************************************************************************************
/* 1.读出的第一组值似乎为0，初始化过程丢弃第一组；
/* N.OVER；
/* ******************************************************************************************* */

#define WRITE_PCF8591	0x90    //写指令；
#define READ_PCF8591	0x91    //读数据；
#define CON0			0
#define CON1			1
#define CON2			2
#define CON3			3       //传感器所在端口；
#define DASET_PCF8591	0x40    //四路单数入00通道无增益DA输出；

extern void PCF8591_Con_Init(u8);
extern u8 Read_PCF8591();
extern void DAout_PCF8591(u8, u8);

#endif