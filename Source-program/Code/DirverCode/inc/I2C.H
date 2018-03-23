#ifndef	_I2C_H__
#define	_I2C_H__

#include "INCLUDES.H"
/* *******************************************************************************************
/* 1.
/* N.OVER£»
/* ******************************************************************************************* */

extern void I2C_Start();
extern void I2C_Stop();
extern void I2C_Send_Byte(u8);
extern u8   I2C_Recv_Byte();

#endif