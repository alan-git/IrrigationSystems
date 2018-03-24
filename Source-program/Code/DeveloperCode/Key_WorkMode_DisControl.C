
#include "Key_WorkMode_DisControl.H"

bit sS1 = 0, sS2 = 0;   //�����Ƿ��й����¶�����
enum {
    noKey,              //�ް����¼���
    combS1,             //��S1�������İ�������¼����������������ְ��µİ�����
    combS2,             //��S2�������İ�������¼���
    disCombS1,          //�����S1�����¼���
    disCombS2,          //�����S2�����¼���
}combHappened = noKey;  //��������¼�������������noKey��

enum {
    autoControl,        //�Զ�ģʽ��
    manualControl,      //�ֶ�ģʽ��
    adjustSec,          //�����룻
    adjustMin,          //���ڷ֣�
    adjustHour,         //����ʱ��
    adjustHumidLimit,   //����ʪ����ֵ��
}workMode = autoControl;//����ģʽĬ��Ϊ�Զ���

extern void checkPressKey();   //�������¼��;
extern void checkCombKey();    //������ϼ�⣬��checkPressKey()����ã�
extern void checkOrdinaryKey();//��ͨ������⣬��checkCombKey()����ã�
extern void keyCheckOver();    //������������Ӧ����checkOrdinaryKey()����ã�

/* *******************************************************************************************
// ���Զ�ģʽ��ʪ�ȹ��ͷ���������
/* ******************************************************************************************* */
void BuzzerControl()
{
    if (workMode != autoControl)        //ǰ�᣺���Զ�ģʽ��
    {
//        TestCode();
        if (Humidity < HumidLimit)      //��ǰʪ��С��ʪ����ֵ��
        {
//            TestCode();
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
/* *******************************************************************************************
// ��ʾ����
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
// ������Ӧ
/* ******************************************************************************************* */
void KeyResponse()
{
    checkPressKey();    //�������¼��;
    checkCombKey();     //������ϼ�⣬��checkPressKey()����ã�
    checkOrdinaryKey(); //��ͨ������⣬��checkCombKey()����ã�
    keyCheckOver();     //������������Ӧ����checkOrdinaryKey()����ã�
}

/* *******************************************************************************************
// �������¼��
/* ******************************************************************************************* */
static void checkPressKey()
{
    if (!PIN_S1 && !sS1)    //����S1���ǳ������£��������µ�һ˲��ִ�У��������²�����ִ����������
    {
        DelayMS(10);
        if (!PIN_S1)
        {
            sS1 = 1;        //ȷ�ϰ������£�
        }
    }
    if (!PIN_S2 && !sS2)
    {
        DelayMS(10);
        if (!PIN_S2)
        {
            sS2 = 1;        //ȷ�ϰ������£�  
        }
    }
}

/* *******************************************************************************************
// ������ϼ�⣬��checkPressKey()����ã�
/* ******************************************************************************************* */
/* ******************************************************************************************* 
/* ����״̬��٣�
/*  һ��������
        1. S1���º�̧��S2�޶�����
        2. S2���º�̧��S1�޶�����
    ������ϣ�
        1. S1���±��֣�S2�������£�
        2. S2���±��֣�S1�������£�
�Ϸ�������������Ҫ�ģ�ʶ�����ù��ܺ���
�·�����(�ܶ���)����Ҫ��ʶ�����ȥ��
        3. S1���£�S2���£�S1̧��S2̧��
        4. S2���£�S1���£�S2̧��S1̧��
        5. S1���£�S2���±��֣�S1����̧���£�
        6. S2���£�S1���±��֣�S2����̧���£�
/* ******************************************************************************************* */
static void checkCombKey()
{
    if (!PIN_S1)            //��ĿǰS1���ڰ���״̬��
    {
        if (sS2 && PIN_S2)  //S2���¹�������Ŀǰ����̧��״̬��
        {
//            sS2 = 0;//��λλ�ô������޸ģ�
            combHappened = combS1;
        }
    }
    if (!PIN_S2)            //��ĿǰS2���ڰ���״̬��
    {
        if (sS1 && PIN_S1)  //S1���¹�������Ŀǰ����̧��״̬��
        {
//            sS1 = 0;//��λλ�ô������޸ģ�
            combHappened = combS2;
        }
    }
// �·������������Ϸ�����λ�öԵ���
    if (PIN_S1 && combHappened == combS1 && sS1)    //S1̧���й���S1Ϊ��������ϼ�������sS1δ����λ��
    {
        combHappened = noKey;                       //����λ��������������
        sS1 = 0;     
    }
    else if (PIN_S2 && combHappened == combS2 && sS2)//S2̧���й���S2Ϊ��������ϼ�������sS2δ����λ��
    {
        combHappened = noKey;                       //����λ��������������
        sS2 = 0;     
    }
}

/* *******************************************************************************************
// ��ͨ������⣬��checkCombKey()����ã�
/* ******************************************************************************************* */
static void checkOrdinaryKey()
{
    if (combHappened == noKey)      //ǰ�᣺��֮ǰδ��⵽��ϰ�����
    {
        if (sS1 && PIN_S1)      //����S1�Ѿ�̧���а��¼�¼��
        {
//            TestCode();  
            sS1 = 0;
            combHappened = disCombS1;      
        }
        else if (sS2 && PIN_S2) //����S2�Ѿ�̧���а��¼�¼��
        {
            sS2 = 0;
            combHappened = disCombS2;    
        }
    }
}

/* *******************************************************************************************
// ������������Ӧ����checkOrdinaryKey()����ã�
/* ******************************************************************************************* */
extern void combS1_Work();      //��Ӧ���ܺ�����
extern void combS2_Work();
extern void disCombS1_Work();
extern void disCombS2_Work();

static void keyCheckOver()
{
    switch (combHappened)
    {
        case noKey:         //�޴�����
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
// CombS1���ܺ�����
/* ******************************************************************************************* */
static void combS1_Work()
{
    if (sS2 && PIN_S2)  //S2���¹�������Ŀǰ����̧��״̬��
    {
        sS2 = 0;//�޸ĺ�ĸ�λλ�ã�
        TestCode();  
        switch (workMode)
        {
            case autoControl:                               //�Զ�ģʽ�£���ϼ���Ч��
                break;
            case manualControl: workMode = adjustSec;       //����ÿ�ж�һ�Σ�����ģʽ����һ����
                break;
            case adjustSec:     workMode = adjustMin;
                break;
            case adjustMin:     workMode = adjustHour;
                break;
            case adjustHour:    workMode = manualControl;  //�ָ���ʼ״̬��
                break;
            default:
                break;
        }                   //��Ӧ�и�λ��
    }
}

/* *******************************************************************************************
// CombS2���ܺ�����
/* ******************************************************************************************* */
static void combS2_Work()
{
    if (sS1 && PIN_S1)  //S1���¹�������Ŀǰ����̧��״̬��
    {
        sS1 = 0;//�޸ĺ�ĸ�λλ�ã�
        switch (workMode)
        {
            case autoControl:                               //�Զ�ģʽ�£���ϼ���Ч��
                break;
            case manualControl: workMode = adjustHumidLimit;//�ж�һ�Σ�����ģʽ��
                break;
            case adjustHumidLimit:workMode = manualControl; //�ж����Σ��ָ�ԭģʽ��
                break;
            default:
                break;
        }                   //��Ӧ�и�λ��
    }
}

/* *******************************************************************************************
// disCombS1���ܺ�����
/* ******************************************************************************************* */
static void disCombS1_Work()
{
    switch (workMode)
    {
        case autoControl:   workMode = manualControl;//TestCode();
            break;
        case manualControl: workMode = autoControl; //�Զ��ֶ�ģʽ�£�����disCombS1������ģʽ֮���໥ת����
            break;
        case adjustSec:     Sec = 0;                    //����㣻
            break;
        case adjustMin:                                 //����������
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
            if (HumidLimit < HUMIDLIMIT_MAX)            //�ڲ�����ifʱ������ִ�У�
                HumidLimit ++;
            break;
        }
        default:
            break;
    }
    combHappened = noKey;       //��λ��
}

/* *******************************************************************************************
// disCombS2���ܺ�����
/* ******************************************************************************************* */
static void disCombS2_Work()
{
    switch (workMode)
    {
        case autoControl:                                //�ֶ�ģʽ�£���Ч��
            break;
        case manualControl: PIN_ConRelay = !PIN_ConRelay;//�Զ�ģʽ�£����ļ̵���״̬��
            break;
        case adjustSec:     Sec = 0;                    //����㣻
            break;
        case adjustMin:                                 //�����Լ���
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
            if (HumidLimit > HUMIDLIMIT_MIN)            //�ڲ�����ifʱ������ִ�У�
                HumidLimit --;
            break;
        }
        default:
            break;
    }
    combHappened = noKey;       //��λ��
}
