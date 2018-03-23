#ifndef	_SEPARATEDIS_H__
#define	_SEPARATEDIS_H__

#include "INCLUDES.H"

#define HOUR 1        //AdjustmentDataDis()参数choose的值；
#define MIN 2
#define SEC 3
#define HUMIDLIMIT 4

extern void Dis_SysSelftest();
extern void Dis_Its_Daytime_Not_Night(u8 temp_ad, bit sw);
extern void Dis_ProgressBar(u8 num);
extern void Dis_init_();
extern void Dis_Auto_not_ManualMode(bit a_not_m);
extern void AdjustmentDataDis(u8 choose, num_data);

#endif