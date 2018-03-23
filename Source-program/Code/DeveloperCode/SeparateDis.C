
#include "SeparateDis.H"

/* *******************************************************************************************
// 显示系统自检：
/* ******************************************************************************************* */
void Dis_SysSelftest()
{
    LCD1602_Clear();
    LCD1602_DisString("System Self-test:");   
    LCD1602_GoTo_yx(2,0);
}

/* *******************************************************************************************
// 显示加载进度条：
// Input：读取到的AD值，Day/Night选择；
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
    temp_ad ++;       //防止出现定义了参数却未使用的警告；
    temp_ad --;
#endif
    LCD1602_GoTo_yx(2,9);
    LCD1602_DisString("Right?"); 
}

/* *******************************************************************************************
// 显示加载进度条：
// Input：要显示的黑块数量
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
// 显示初始化过程：
// Input：要显示的黑块数量
/* ******************************************************************************************* */
void Dis_init_()
{
    LCD1602_Clear();
    LCD1602_DisString("System Init:");   
    LCD1602_GoTo_yx(2,0);
}

/* *******************************************************************************************
// 自动或手动模式的显示内容：
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
// 调节数据时的显示内容：
// 参数1：宏定义，时，分，秒，或湿度阈值；
// 参数2：当前值；
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