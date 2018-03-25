#ifndef	_UNKNOWN_CATEGORY_H__
#define	_UNKNOWN_CATEGORY_H__

#include "INCLUDES.H"

sbit PIN_ConRelay = P3^6;
sbit PIN_ConBuzzer = P3^7;
sbit PIN_S1 = P1^0;
sbit PIN_S2 = P1^1;

#define RELAY_OFF 1
#define RELAY_ON  0
#define Relay_On();    PIN_ConRelay=RELAY_ON;
#define Relay_Off();   PIN_ConRelay=RELAY_OFF;
#define Buzzer_On();    PIN_ConBuzzer=0;
#define Buzzer_Off();   PIN_ConBuzzer=1;

#define MULTIPLE_DETECTION 10   //一次有效检测所需的检测次数<256；

#define HUMIDLIMIT_MAX  30      //湿度调节阈值可设定最大值<100；
#define DEFAULT_HUMIDLIMIT 20   //湿度调节阈值设定默认值<100；
#define HUMIDLIMIT_MIN  14      //湿度调节阈值可设定最小值<100；

extern u8 Humidity;             //湿度；
extern u8 HumidLimit;           //湿度调节阈值；

extern void STC_ISP();
extern void AD_to_Humidity();

#endif
