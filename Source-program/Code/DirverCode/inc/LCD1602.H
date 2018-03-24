#ifndef	_LCD1602_H__
#define	_LCD1602_H__

#include "INCLUDES.H"
/* *******************************************************************************************
/* 1.
/* N.OVER��
/* ******************************************************************************************* */

#define BLACK_BLOCK 0xFF

extern void LCD1602_Init();                 //��ʼ��LCD1602��
extern void LCD1602_Clear();                //LCD1602������
extern void WriteOneData(u8 dat);           //��LCD1602дһ�ֽڣ�
extern void LCD1602_DisString(u8 *chr);     //��LCD1602д�ַ�����
extern void LCD1602_GoTo_yx(u8 y, u8 x);    //����LCD1602���ꣻ
extern void LCD1602_DisNum(u8 two_digits_num);//��LCD1602д������(��λ)��


#endif