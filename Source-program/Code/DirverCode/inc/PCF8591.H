#ifndef	_PCF8591_H__
#define	_PCF8591_H__

#include "INCLUDES.H"
/* *******************************************************************************************
/* 1.�����ĵ�һ��ֵ�ƺ�Ϊ0����ʼ�����̶�����һ�飻
/* N.OVER��
/* ******************************************************************************************* */

#define WRITE_PCF8591	0x90    //дָ�
#define READ_PCF8591	0x91    //�����ݣ�
#define CON0			0
#define CON1			1
#define CON2			2
#define CON3			3       //���������ڶ˿ڣ�
#define DASET_PCF8591	0x40    //��·������00ͨ��������DA�����

extern void PCF8591_Con_Init(u8);
extern u8 Read_PCF8591();
extern void DAout_PCF8591(u8, u8);

#endif