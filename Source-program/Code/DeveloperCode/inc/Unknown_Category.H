#ifndef	_UNKNOWN_CATEGORY_H__
#define	_UNKNOWN_CATEGORY_H__

#include "INCLUDES.H"

sbit PIN_ConRelay = P3^6;
sbit PIN_ConBuzzer = P3^7;
sbit PIN_S1 = P1^0;
sbit PIN_S2 = P1^1;

#define Relay_On();     PIN_ConRelay=0;
#define Relay_Off();    PIN_ConRelay=1;
#define Buzzer_On();    PIN_ConBuzzer=0;
#define Buzzer_Off();   PIN_ConBuzzer=1;

#define H_MAX_to_AD 127     //���ʵ����ڴ�ֵ��
#define H_MIN_to_AD 0

#define HUMIDLIMIT_MAX  30  //ʪ�ȵ�����ֵ���趨���ֵ��
#define DEFAULT_HUMIDLIMIT 17//ʪ�ȵ�����ֵ�趨Ĭ��ֵ��
#define HUMIDLIMIT_MIN  14  //ʪ�ȵ�����ֵ���趨��Сֵ��

extern u8 Humidity;         //ʪ�ȣ�
extern u8 HumidLimit;       //ʪ�ȵ�����ֵ��

extern void STC_ISP();
extern void AD_to_Humidity();

#endif