## 智能灌溉系统
##### 开发环境：
    Source program：*Keil uVision4 V9.02*
    Simulation：*Proteus 8 Professional V8.6 SP2*
    *Microsoft Visio 2016 MSO*

### 文件链接
---

- 查看版本更新记录[版本历史](./Source-program/Documents/版本历史.md)
- 了解文件变量函数等的命名方式[命名方式](./Source-program/Documents/命名方式.md)
- 需要了解工程文件各自的功能定义，请参阅[工程说明](./Source-program/Documents/工程说明.md)

### 功能概述
---

#### 基本功能介绍：

#### 特色功能：
###### 1.软件复位：
在REG51.H的基础上，定义STC89C5xRC系列特有的特殊功能寄存器ISP_CONTR，检测到下载信号芯片自动重启，避免了调试过程中需要不断冷启动的不便。  
![软件复位的实现](./Pic/软件复位的实现.PNG "STC89-Datasheet软件复位的实现")   
###### 代码段：
    >    / ********************************
    >    // 下载检测
    >    / ******************************* /
    >    sfr ISP_CONTR = 0xE7;
    >    // ISP区复位：
    >    void STC_ISP()
    >    {
    >        P30 = 1;
    >        DelayUS(1);    // 等待电平稳定；
    >        if (!P30)
    >            ISP_CONTR = 0x60;
    >    }
###### 2.系统自测与进度条：
在程序上电初始化前加入系统自测，便于及时发现电路异常；加入进度显示，便于追踪程序运行位置，减少调试难度。  
###### 3.组合按键检测：
（组合按键不影响普通按键检测，选用）


