/* *******************************************************************************************
// Author: biu~
// System self-test and initialization;系统自检与初始化；
/* ******************************************************************************************* */

#include "SysSelf-test_And_SysInit.H"

/* *******************************************************************************************
// 系统自检与初始化整合函数：
/* ******************************************************************************************* */
extern void sysSelftest();
extern void sysInit();
extern void initOver();
void SysSelftest_And_SysInit()
{
    // 系统自检：
    sysSelftest();
    // 系统初始化：
    sysInit();
    // 初始化完成提示：
    initOver();
}
/* *******************************************************************************************
// 系统自检：
/* ******************************************************************************************* */
static void sysSelftest()
{
    u8 temp_ad;
    // 初始化LCD1602：
	LCD1602_Init(); 
	// 设置PCF8591检测亮度：
    PCF8591_Con_Init(CON1);
    Read_PCF8591();                 //第一组值丢弃；
#ifndef DeveloperMode               //调试模式下不再执行，耗时较长；
//    TestCode();
    // 检测1602显示：
    Dis_SysSelftest();
    Dis_ProgressBar(2);
    // 系统状态提示灯常亮0.8S：
    SysLED_On();
    DelayMS(800);
    SysLED_Off();
    Dis_ProgressBar(4);
    // 继电器打开0.5S：
    Relay_On();
    DelayMS(500);
    Relay_Off();
    Dis_ProgressBar(4);
    // 蜂鸣器打开0.3S：
    Buzzer_On();
    DelayMS(300);
    Buzzer_Off();
    Dis_ProgressBar(4);
#endif
    // 检测光线强度：
    temp_ad = Read_PCF8591(); 
    if (temp_ad > LIGHT_INTENSITY_THRESHOLD)
    {
        Dis_Its_Daytime_Not_Night(temp_ad, FALSE);
//        TestCode();
    }
    else
    {
        Dis_Its_Daytime_Not_Night(temp_ad, TRUE);
    }
    DelayMS(1500);
}
/* *******************************************************************************************
// 系统初始化
/* ******************************************************************************************* */
extern void initIO();
static void sysInit()
{
    Dis_init_();
    // IO电平初始化：
    initIO();
    Dis_ProgressBar(4);
	// 时间时钟初始化：
	Timer_Clock_Init();
    Dis_ProgressBar(4);
	// 设定PCF8591读取端口为传感器端：
	PCF8591_Con_Init(CON3);
    Read_PCF8591();                         //第一组值丢弃；
    Dis_ProgressBar(4);
    DelayMS(450);                           //阻塞感，让人有“正在加载”的感觉；
    // 时基定时器初始化并开启中断总开关：
    InitInterrupt();
    Dis_ProgressBar(4);
    initOver();
    LCD1602_Clear();                        //清除显示信息；
}

/* *******************************************************************************************
// IO电平初始化
/* ******************************************************************************************* */
static void initIO()
{
    P0 = 0xFF;
    P1 = 0xFF;	
    P2 = 0xFF;	
    P3 = 0xFF;	
//    P4 = 0xFF;	
//    P5 = 0xFF;	
//    P6 = 0xFF;	
//    P7 = 0xFF;	
//    P0M0 = 0x00;	
//    P0M1 = 0x00;	
//    P1M0 = 0x00;	
//    P1M1 = 0x00;	
//    P2M0 = 0x00;	
//    P2M1 = 0x00;	
//    P3M0 = 0x00;	
//    P3M1 = 0x00;	
//    P4M0 = 0x00;	
//    P4M1 = 0x00;	
//    P5M0 = 0x00;	
//    P5M1 = 0x00;	
//    P6M0 = 0x00;	
//    P6M1 = 0x00;	
//    P7M0 = 0x00;	
//    P7M1 = 0x00;	
}

/* *******************************************************************************************
// 初始化完成提示
/* ******************************************************************************************* */
static void initOver()
{
    SysLED_Flash(50, 2);
}
