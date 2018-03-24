/* *******************************************************************************************
// Author: biu~
// �޷���ȷ������û����ܺ�����Ŵ���
/* ******************************************************************************************* */

#include "Unknown_Category.H"

u8 Humidity = 0;                    //ʪ�ȣ�
u8 HumidLimit = DEFAULT_HUMIDLIMIT; //ʪ�ȵ�����ֵ��
/* *******************************************************************************************
// ���ؼ��
/* ******************************************************************************************* */
// ISP����λ��
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
// ��ADֵת��Ϊʪ�Ȱٷֱȣ����ж��е��ã�
// �޷��õ����������Ĭ�ϴ�����Ϊ���ԡ�
/* ******************************************************************************************* */
void AD_to_Humidity()
{
    u8 temp_ad;
    float min_accuracy;
    temp_ad = Read_PCF8591();
    if(temp_ad >= H_MAX_to_AD)
    {
        Humidity = 99;
    }
    else if (temp_ad <= H_MIN_to_AD)
    {
        Humidity = 0;
    }
    else
    {
        min_accuracy = (H_MAX_to_AD - H_MIN_to_AD) / 100;
        Humidity = (H_MAX_to_AD - temp_ad) / min_accuracy;      //����ʵ�����ѡ����㹫ʽ��
    }
}