/*
 * ADBControl.h
 * adb控制指令映射，同时定义一些常用的操作
 * Written by: wanggang
 * update: 20230201
 */

#ifndef ADBCONTROL_H
#define ADBCONTROL_H

#include <iostream>
#include <string>
#include <unistd.h>
#include <fstream>
#include <thread>
#include "LogPlugin.hpp"
#include "KeyEvent.h"

using namespace std;

//命令的类型
//枚举避免全大写，否则容易和宏冲突
//必要可以单独加上class
enum commandType {
    Home,
    Back,
    Click, /*需要填充坐标*/
    Slide, /*需要填充坐标*/
    SlideUp, SlideDown, SlideLeft, SlideRight, /*需要填充坐标*/
    SlideUp1, SlideDown1, SlideLeft1, SlideRight1, /*滑动1页*/
    SlideUp1_2, SlideDown1_2, SlideLeft1_2, SlideRight1_2 /*滑动1/2页*/
};

enum mStatus {
    Normal = 0,
    Error = -1
};

//分辨率
struct ScreenResolution {
    /*
    ***w***
    *     *
    l     *
    *     *
    *******
    */
    int length;
    int width;
};

//手机基本参数
struct PhoneParameters {
    string PhoneName; //手机型号
    int RefreshRate; //刷新率
    ScreenResolution Size; //屏幕尺寸
    bool Horizontal; //手机姿态
};

//坐标点
struct Position
{
    int x;
    int y;
    Position(): x(0), y(0) {};
    Position(int x_, int y_) : x(x_), y(y_) {}
};


class ADBControl {
public:

    PhoneParameters mPhoneParams;
    Position mDisplayCenter;
    int mStatus = 0; //类的状态

    ADBControl();
    ~ ADBControl();

    int PhoneInit(PhoneParameters param);

    //获取手机实时姿态
    bool isHorizontal = false; //默认为竖屏
    void getisHorizontal();

    //更新参数
    void updatePhoneParameters(PhoneParameters param);
    bool needUpdate = false;
    void createThread();
    std::thread updatePhoneParametersThread;

public:
    //填充点击坐标，生成点击操作
    string generateClickCommand(Position& position);
    //填充滑动坐标，生产滑动操作
    string generateSlideCommand(Position& from_position, Position& to_position);
    //keyevent
    string generateEventCommand(int& key_event);

    /*执行命令*/
    /*(1)点击：坐标
     *(2)滑动：初始坐标&滑动距离
    */
    void doCommand(int commandType, Position position, int distance=0);

    /*(1)点击：坐标&点击次数
     *(2)事件：back事件&back次数
    */
    void doCommand(int commandType, int times=1);

    /*(1)滑动：滑动距离&滑动次数
     *
    */
    void doCommand(int commandType, int distance, int times=1);

    /*这种操作意义不大，不同app滑动的情况不相同*/
    /*(1)滑动：预设的滑动坐标&距离，例如上滑1/2页. 
     *(2)事件：back
     *(3)事件：home
    */
    //void doCommand(int commandType);

    /*(1)滑动：初始坐标&终点坐标
    */
    void doCommand(int commandType, Position from_position, Position to_position);

    int waitCommand = 3;

public:
    /*基本操作*/
    //打开app
    void openApp(Position& app);

public:   
    //辅助
    string positionPrint(Position& position);


public:

};
#endif