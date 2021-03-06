/* *******************************************************************************************
// Author:      biu~
// Last Date:   2018/03/22
// 蓝桥杯国赛驱动，添加注释及DA转换驱动；
/* ******************************************************************************************* */

#include "PCF8591.H"

/* *******************************************************************************************
// 初始化一个端口，后续调用Read函数进行读取：
/* ******************************************************************************************* */
void PCF8591_Con_Init(u8 con)
{
    I2C_Start();
    I2C_Send_Byte(WRITE_PCF8591);
    I2C_Send_Byte(con);
    I2C_Stop();
}

/* *******************************************************************************************
// 将Init函数定义的端口AD读出：
/* ******************************************************************************************* */
u8 Read_PCF8591()
{
    u8 recv_data;
    I2C_Start();
    I2C_Send_Byte(READ_PCF8591);
    DelayUS(3);
    recv_data = I2C_Recv_Byte();
    I2C_Stop();
    return recv_data;
}

/* *******************************************************************************************
// DA输出
/* ******************************************************************************************* */
//void DAout_PCF8591(u8 con, u8 dat)  //DA转换
//{
//    I2C_Start();
//    I2C_Send_Byte(WRITE_PCF8591);
//    I2C_Send_Byte(con);
//    I2C_Send_Byte(dat);
//    I2C_Stop();
//}
