
#include "SeparateDis.H"

/* *******************************************************************************************
// ��ʾϵͳ�Լ죺
/* ******************************************************************************************* */
void Dis_SysSelftest()
{
    LCD1602_Clear();
    LCD1602_DisString("System Self-test:");   
    LCD1602_GoTo_yx(2,0);
}

/* *******************************************************************************************
// ��ʾ���ؽ�������
// Input����ȡ����ADֵ��Day/Nightѡ��
/* ******************************************************************************************* */
void Dis_Its_Daytime_Not_Night(u8 temp_ad, bit sw)
{
    LCD1602_Clear();
    if (sw == TRUE)
    {
        LCD1602_DisString("It's Daytime,"); 
    }
    else
    {
        LCD1602_DisString("It's Night,");  
    }
#ifdef DeveloperMode
    LCD1602_GoTo_yx(2,0);
    LCD1602_DisNum(temp_ad/100); 
    LCD1602_DisNum(temp_ad); 
#else
    temp_ad ++;       //��ֹ���ֶ����˲���ȴδʹ�õľ��棻
    temp_ad --;
#endif
    LCD1602_GoTo_yx(2,9);
    LCD1602_DisString("Right?"); 
}

/* *******************************************************************************************
// ��ʾ���ؽ�������
// Input��Ҫ��ʾ�ĺڿ�����
/* ******************************************************************************************* */
void Dis_ProgressBar(u8 num)
{
    u8 i;
    for (i=0; i<num; i++)
    {
        WriteOneData(BLACK_BLOCK);
        DelayMS(80);   
    }
}

/* *******************************************************************************************
// ��ʾ��ʼ�����̣�
// Input��Ҫ��ʾ�ĺڿ�����
/* ******************************************************************************************* */
void Dis_init_()
{
    LCD1602_Clear();
    LCD1602_DisString("System Init:");   
    LCD1602_GoTo_yx(2,0);
}

/* *******************************************************************************************
// �Զ����ֶ�ģʽ����ʾ���ݣ�
/* ******************************************************************************************* */
void Dis_Auto_not_ManualMode(bit a_not_m)
{
//    u8 i;
    LCD1602_Clear();
    LCD1602_DisString("H:");   
    LCD1602_DisNum(Humidity);
    WriteOneData('%');   
    if (a_not_m == TRUE)
    {
//        for (i=0; i<(16-5-sizeof("Auto")); i++)
//        {
//            WriteOneData(' ');   
//        }
//        LCD1602_DisString("Auto");
        LCD1602_DisString("       Auto");
    }
    else
    {
//        for (i=0; i<(16-5-sizeof("Manual")); i++)
//        {
//            WriteOneData(' ');   
//        }
//        LCD1602_DisString("Manual");
        LCD1602_DisString("     Manual");
    }
    LCD1602_GoTo_yx(2,0);
    LCD1602_DisString("Time: ");
    LCD1602_DisNum(Hour);   
    WriteOneData(':');
    LCD1602_DisNum(Min);   
    WriteOneData(':');
    LCD1602_DisNum(Sec);   
}
/* *******************************************************************************************
// ��������ʱ����ʾ���ݣ�
// ����1���궨�壬ʱ���֣��룬��ʪ����ֵ��
// ����2����ǰֵ��
/* ******************************************************************************************* */
void AdjustmentDataDis(u8 choose, num_data)
{
    LCD1602_Clear();
    LCD1602_DisString("Set:");
    switch (choose)
    {
        case HOUR:LCD1602_DisString("Hour = ");
            break;
        case MIN: LCD1602_DisString("Min = ");
            break;
        case SEC: LCD1602_DisString("Sec = ");
            break;
        case HUMIDLIMIT:LCD1602_DisString("H_Limit = ");
            break;
        default:
            break;
    }
    LCD1602_DisNum(num_data);
    LCD1602_GoTo_yx(2,0);
    switch (choose)
    {
        case SEC: LCD1602_DisString("S1,S2: Set zero");
            break;
        default: LCD1602_DisString("S1: Inc, S2: Dec");
            break;
    }    
}