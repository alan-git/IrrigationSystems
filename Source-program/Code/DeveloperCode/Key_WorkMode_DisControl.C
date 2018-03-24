
#include "Key_WorkMode_DisControl.H"

bit sS1 = 0, sS2 = 0;   //按键是否有过按下动作；
enum {
    noKey,              //无按键事件；
    combS1,             //以S1主按键的按键组合事件；（主按键即保持按下的按键）
    combS2,             //以S2主按键的按键组合事件；
    disCombS1,          //非组合S1按下事件；
    disCombS2,          //非组合S2按下事件；
}combHappened = noKey;  //按键组合事件发生处理后置noKey；

enum {
    autoControl,        //自动模式；
    manualControl,      //手动模式；
    adjustSec,          //调节秒；
    adjustMin,          //调节分；
    adjustHour,         //调节时；
    adjustHumidLimit,   //调节湿度阈值；
}workMode = autoControl;//工作模式默认为自动；

extern void checkPressKey();   //按键按下检测;
extern void checkCombKey();    //按键组合检测，在checkPressKey()后调用；
extern void checkOrdinaryKey();//普通按键检测，在checkCombKey()后调用；
extern void keyCheckOver();    //按键检测完毕响应，在checkOrdinaryKey()后调用；

/* *******************************************************************************************
// 自动模式下湿度过低自动开启Relay：
/* ******************************************************************************************* */
void AutoRelayControl()
{
    if (workMode == autoControl)
    {
        if (Humidity <= HumidLimit)     //当前湿度小于湿度阈值；
        {
            PIN_ConRelay = RELAY_ON;
        }
        else 
        {
            PIN_ConRelay = RELAY_OFF;
        }
    }                                   //Relay打开状态切换模式Relay自动关闭的语句在按键响应部分；  
}

/* *******************************************************************************************
// 非自动模式下湿度过低发出警报：
/* ******************************************************************************************* */
void BuzzerControl()
{
    if (workMode != autoControl)        //前提：非自动模式；
    {
//        TestCode();
        if (Humidity < HumidLimit)      //当前湿度小于湿度阈值；
        {
//            TestCode();
            if (PIN_ConRelay == RELAY_OFF)  //水泵未开启；
            {
                Buzzer_On();
            }
            else
            {
                Buzzer_Off();
            }
        }
        else 
        {
            Buzzer_Off();
        }
    }
    else
    {
        Buzzer_Off();
    } 
}
/* *******************************************************************************************
// 显示控制
/* ******************************************************************************************* */
void DisControl()
{
    switch (workMode)
    {
        case autoControl:   Dis_Auto_not_ManualMode(TRUE);
            break;
        case manualControl: Dis_Auto_not_ManualMode(FALSE);//TestCode(); 
            break;
        case adjustSec:     AdjustmentDataDis(SEC, Sec);
            break;
        case adjustMin:     AdjustmentDataDis(MIN, Min);
            break;
        case adjustHour:    AdjustmentDataDis(HOUR, Hour);
            break;
        case adjustHumidLimit:AdjustmentDataDis(HUMIDLIMIT, HumidLimit);
            break;
        default:
            break;
    }
}

/* *******************************************************************************************
// 按键响应
/* ******************************************************************************************* */
void KeyResponse()
{
    checkPressKey();    //按键按下检测;
    checkCombKey();     //按键组合检测，在checkPressKey()后调用；
    checkOrdinaryKey(); //普通按键检测，在checkCombKey()后调用；
    keyCheckOver();     //按键检测完毕响应，在checkOrdinaryKey()后调用；
}

/* *******************************************************************************************
// 按键按下检测
/* ******************************************************************************************* */
static void checkPressKey()
{
    if (!PIN_S1 && !sS1)    //按键S1不是持续按下（按键按下的一瞬间执行，持续按下不会再执行消抖）；
    {
        DelayMS(10);
        if (!PIN_S1)
        {
            sS1 = 1;        //确认按键按下；
        }
    }
    if (!PIN_S2 && !sS2)
    {
        DelayMS(10);
        if (!PIN_S2)
        {
            sS2 = 1;        //确认按键按下；  
        }
    }
}

/* *******************************************************************************************
// 按键组合检测，在checkPressKey()后调用；
/* ******************************************************************************************* */
/* ******************************************************************************************* 
/* 按键状态穷举：
/*  一、基础：
        1. S1按下后抬起，S2无动作；
        2. S2按下后抬起，S1无动作；
    二、组合：
        1. S1按下保持，S2反复按下；
        2. S2按下保持，S1反复按下；
上方四种是我们需要的，识别后调用功能函数
下方四种(很多种)不需要，识别后滤去；
        3. S1按下，S2按下，S1抬起，S2抬起；
        4. S2按下，S1按下，S2抬起，S1抬起；
        5. S1按下，S2按下保持，S1反复抬起按下；
        6. S2按下，S1按下保持，S2反复抬起按下；
/* ******************************************************************************************* */
static void checkCombKey()
{
    if (!PIN_S1)            //即目前S1处于按下状态；
    {
        if (sS2 && PIN_S2)  //S2按下过，并且目前处于抬起状态；
        {
//            sS2 = 0;//复位位置错误，已修改；
            combHappened = combS1;
        }
    }
    if (!PIN_S2)            //即目前S2处于按下状态；
    {
        if (sS1 && PIN_S1)  //S1按下过，并且目前处于抬起状态；
        {
//            sS1 = 0;//复位位置错误，已修改；
            combHappened = combS2;
        }
    }
// 下方函数不能与上方函数位置对调；
    if (PIN_S1 && combHappened == combS1 && sS1)    //S1抬起，有过以S1为主键的组合键操作，sS1未被复位；
    {
        combHappened = noKey;                       //仅复位，无其他操作；
        sS1 = 0;     
    }
    else if (PIN_S2 && combHappened == combS2 && sS2)//S2抬起，有过以S2为主键的组合键操作，sS2未被复位；
    {
        combHappened = noKey;                       //仅复位，无其他操作；
        sS2 = 0;     
    }
}

/* *******************************************************************************************
// 普通按键检测，在checkCombKey()后调用；
/* ******************************************************************************************* */
static void checkOrdinaryKey()
{
    if (combHappened == noKey)      //前提：在之前未检测到组合按键；
    {
        if (sS1 && PIN_S1)      //按键S1已经抬起并有按下记录；
        {
//            TestCode();  
            sS1 = 0;
            combHappened = disCombS1;      
        }
        else if (sS2 && PIN_S2) //按键S2已经抬起并有按下记录；
        {
            sS2 = 0;
            combHappened = disCombS2;    
        }
    }
}

/* *******************************************************************************************
// 按键检测完毕响应，在checkOrdinaryKey()后调用；
/* ******************************************************************************************* */
extern void combS1_Work();      //对应功能函数；
extern void combS2_Work();
extern void disCombS1_Work();
extern void disCombS2_Work();

static void keyCheckOver()
{
    switch (combHappened)
    {
        case noKey:         //无处理；
            break;
        case combS1:    combS1_Work();
            break;
        case combS2:    combS2_Work();
            break;
        case disCombS1: disCombS1_Work();//TestCode();  
            break;
        case disCombS2: disCombS2_Work();
            break;
        default:
            break;
    }
}

/* *******************************************************************************************
// CombS1功能函数；
/* ******************************************************************************************* */
static void combS1_Work()
{
    if (sS2 && PIN_S2)  //S2按下过，并且目前处于抬起状态；
    {
        sS2 = 0;//修改后的复位位置；
        TestCode();  
        switch (workMode)
        {
            case autoControl:                               //自动模式下，组合键无效；
                break;
            case manualControl: workMode = adjustSec;       //按键每判定一次，工作模式下移一个；
                break;
            case adjustSec:     workMode = adjustMin;
                break;
            case adjustMin:     workMode = adjustHour;
                break;
            case adjustHour:    workMode = manualControl;  //恢复初始状态；
                break;
            default:
                break;
        }                   //不应有复位；
    }
}

/* *******************************************************************************************
// CombS2功能函数；
/* ******************************************************************************************* */
static void combS2_Work()
{
    if (sS1 && PIN_S1)  //S1按下过，并且目前处于抬起状态；
    {
        sS1 = 0;//修改后的复位位置；
        switch (workMode)
        {
            case autoControl:                               //自动模式下，组合键无效；
                break;
            case manualControl: workMode = adjustHumidLimit;//判定一次，调节模式；
                break;
            case adjustHumidLimit:workMode = manualControl; //判定两次，恢复原模式；
                break;
            default:
                break;
        }                   //不应有复位；
    }
}

/* *******************************************************************************************
// disCombS1功能函数；
/* ******************************************************************************************* */
static void disCombS1_Work()
{
    switch (workMode)
    {
        case autoControl:
        {
           workMode = manualControl;//TestCode();
            if (PIN_ConRelay == RELAY_ON)
            {
                PIN_ConRelay = RELAY_OFF;
            }
            break;
        }
        case manualControl: workMode = autoControl; //自动手动模式下，触发disCombS1，两个模式之间相互转换；
            break;
        case adjustSec:     Sec = 0;                    //秒归零；
            break;
        case adjustMin:                                 //其余自增；
        {
            if (Min < 59)
                Min ++;
            else
                Min = 0;
            break;
        }
        case adjustHour:
        {
            if (Hour < 23)
                Hour ++;
            else
                Hour = 0;
            break;
        }
        case adjustHumidLimit:
        {
            if (HumidLimit < HUMIDLIMIT_MAX)            //在不满足if时，不予执行；
                HumidLimit ++;
            break;
        }
        default:
            break;
    }
    combHappened = noKey;       //复位；
}

/* *******************************************************************************************
// disCombS2功能函数；
/* ******************************************************************************************* */
static void disCombS2_Work()
{
    switch (workMode)
    {
        case autoControl:                                //手动模式下，无效；
            break;
        case manualControl: PIN_ConRelay = !PIN_ConRelay;//自动模式下，更改继电器状态；
            break;
        case adjustSec:     Sec = 0;                    //秒归零；
            break;
        case adjustMin:                                 //其余自减；
        {
            if (Min > 0)
                Min --;
            else
                Min = 59;
            break;
        }
        case adjustHour:
        {
            if (Hour > 0)
                Hour --;
            else
                Hour = 23;
            break;
        }
        case adjustHumidLimit:
        {
            if (HumidLimit > HUMIDLIMIT_MIN)            //在不满足if时，不予执行；
                HumidLimit --;
            break;
        }
        default:
            break;
    }
    combHappened = noKey;       //复位；
}

