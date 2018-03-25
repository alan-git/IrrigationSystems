/* *******************************************************************************************
// Author: biu~
// 无法明确分类的用户功能函数存放处；
/* ******************************************************************************************* */

#include "Unknown_Category.H"

u8 Humidity = 0;                    //湿度；
u8 HumidLimit = DEFAULT_HUMIDLIMIT; //湿度调节阈值；
/* *******************************************************************************************
// 下载检测
/* ******************************************************************************************* */
// ISP区复位：
sfr ISP_CONTR = 0xE7;
void STC_ISP()
{
    P30 = 1;
    Delay1US();
    Delay1US();
    if (!P30)
        ISP_CONTR = 0x60;
}

/* *******************************************************************************************
// 将AD值转换为湿度百分比，在中断中调用；
// 无法得到具体参数，默认传感器为线性。
/* ******************************************************************************************* */
void AD_to_Humidity()
{
    auto u8 temp_ad[MULTIPLE_DETECTION];     //临时值寄存；
    auto u16 temp_ad_sum = 0;                //所有临时值的和；
    auto u8 i;                               //计次；
    for (i=0; i<MULTIPLE_DETECTION; i++)
    {
        temp_ad[i] = Read_PCF8591();
    }
    for (i=0; i<MULTIPLE_DETECTION; i++)
    {
        temp_ad_sum += temp_ad[i];
    }
    temp_ad[0] = temp_ad_sum / MULTIPLE_DETECTION;      //目前temp_ad[0]存储的是多次采样的均值；
    if (temp_ad[0] >= 253)                  //特殊样本值单独列举；
    {
        Humidity = 0;
    }
    else if (temp_ad[0] <= 2)               //特殊样本值单独列举；
    {
        Humidity = 99;
    }
    else
    {
        Humidity = (255 - temp_ad[0]) / 3;
    }

//    if(temp_ad >= H_MAX_to_AD)
//    {
//        Humidity = 0;
//    }
//    else if (temp_ad <= H_MIN_to_AD)
//    {
//        Humidity = 99;
//    }
//    else
//    {
//        min_accuracy = (H_MAX_to_AD - H_MIN_to_AD) / 100;
//        Humidity = (temp_ad - H_MIN_to_AD) / min_accuracy;      //根据实际情况选择计算公式；
//    }
}
