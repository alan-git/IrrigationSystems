#ifndef	_LCD1602_H__
#define	_LCD1602_H__

#include "INCLUDES.H"
/* *******************************************************************************************
/* 1.
/* N.OVER；
/* ******************************************************************************************* */

extern void LCD1602_Init();                 //初始化LCD1602；
extern void LCD1602_Clear();                //LCD1602清屏；
extern void LCD1602_DisDtring(u8 *chr);     //向LCD1602写字符串；
extern void LCD1602_GoTo_xy(u8 y, u8 x);    //设置LCD1602坐标；
extern void LCD1602_DisNum(u8 two_digits_num);//向LCD1602写数字量(两位)；


#endif