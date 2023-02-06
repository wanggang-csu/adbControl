/*
 * ADBControl.h
 * adb控制指令映射，同时定义一些常用的操作
 * Written by: wanggang
 * update: 20230201
 */

#include "../../include/adb/ADBControl.h"

ADBControl::ADBControl()
{
    //PhoneInit(param);
    /*other init*/
}

ADBControl::~ADBControl()
{
    updatePhoneParametersThread.join();//阻塞式
}

/*辅助坐标点打印*/
string ADBControl::positionPrint(Position& position)
{
    string position_str = "(" + to_string(position.x) + ", " + to_string(position.y) + ")";
    return position_str;
}

/*
 * 手机参数初始化
 * 主要是横屏和竖屏时参数不一样
 * 
 */
int ADBControl::PhoneInit(PhoneParameters param)
{
    //屏幕参数和手机姿态有关，这影响到后续滑动和点击操作的坐标计算
    if (!isHorizontal)
    {

        mPhoneParams.Size.length = param.Size.length;
        mPhoneParams.Size.width = param.Size.width;

        mDisplayCenter.x = param.Size.width/2;
        mDisplayCenter.y = param.Size.length/2;

        mPhoneParams.Horizontal = false; //默认初始化为竖
    } else {
        //如果是横屏，参数需要改动一下
        mPhoneParams.Size.length = param.Size.width;
        mPhoneParams.Size.width = param.Size.length;

        mDisplayCenter.x = param.Size.length/2;
        mDisplayCenter.y = param.Size.width/2;

        mPhoneParams.Horizontal = true;

    }

    mPhoneParams.PhoneName = param.PhoneName;
    mPhoneParams.RefreshRate = param.RefreshRate;

    mStatus = Normal;
    return mStatus;
}

/*
 * 获取手机屏幕姿态
 * 读取SurfaceOrientation的数值
 * 1、3: 横
 * 0、2: 竖
 */
void ADBControl::getisHorizontal()
{
    //string command = "adb shell \"dumpsys input | grep SurfaceOrientation\"";
    string command = "adb shell \"dumpsys input | grep SurfaceOrientation\" > isHorizontal.txt";
    int state = system(command.c_str());

    string file_name = "isHorizontal.txt";
    ifstream in_file;
    in_file.open(file_name);
    string out_file; 
    getline(in_file, out_file, ';');
    while(in_file) 
    { 
        cout <<out_file<<endl; //输出获取的字符串
        getline(in_file, out_file,';');
    } 
    in_file.close(); //输出完毕 关闭文件

    //字符串匹配
    string child = "SurfaceOrientation";
    int childAddr = out_file.find(child);
    char res_char = out_file[childAddr+child.size()+2];
    int res_int = res_char - '0';
    cout<<getCurrentTime()<<
    "getisHorizontal(): display state = "<<res_int<<endl;

    if (res_int == 0 || res_int == 2) isHorizontal = false; //竖屏
    else isHorizontal = true; //横屏

    if (isHorizontal != mPhoneParams.Horizontal) needUpdate = true;  //如果获取的姿态与手机参数不同，需要更新
    else needUpdate = false;
}

/*
 * 这里需要一直循环运行，以更新手机基本参数
 * 目前主要是屏幕姿态
 * 
 */
void ADBControl::updatePhoneParameters(PhoneParameters param)
{
    int i = 0;
    while(true)
    {   
        //std::this_thread::sleep_for(std::chrono::seconds(1));
        std::this_thread::sleep_for(std::chrono::milliseconds(500)); //线程休眠500ms
        getisHorizontal();
        cout<<"needUpdate = "<< needUpdate <<endl;
        if (needUpdate) PhoneInit(param);
    }
}

/*
 * updatePhoneParameters以单独的线程去执行
 * 
 */
void ADBControl::createThread()
{
    if (mStatus == Normal)
    {
        //std::thread updatePhoneParametersThread(&ADBControl::updatePhoneParameters, this, mPhoneParams);
        updatePhoneParametersThread = std::thread(&ADBControl::updatePhoneParameters, this, mPhoneParams);
        //updatePhoneParametersThread.detach();//分离式[非阻塞]
    }    
}



/*
 * 生成点击指令
 * 
 */
string ADBControl::generateClickCommand(Position& position)
{
    if ((position.x < 0 || position.y < 0) || 
        (position.x > mPhoneParams.Size.width || position.y > mPhoneParams.Size.length)) 
    {
        cout<<getCurrentTime()<<
        "generateClickCommand(): Warning: position"<<positionPrint(position)<<" is wrong"<<endl;
        //to do :回到桌面
    }

    string clickCMD = "adb shell input tap ";
    string positionCMD = to_string(position.x) + " " + to_string(position.y);
    clickCMD = clickCMD + positionCMD;
    cout<<getCurrentTime()<<
    "generateClickCommand(): Click: position"<<positionPrint(position)<<endl;

    return clickCMD;    
}

/*
 * 生成滑动指令
 * 
 */
string ADBControl::generateSlideCommand(Position& from_position, Position& to_position)
{
    if ((from_position.x < 0 || from_position.y < 0 || to_position.x < 0 || to_position.y < 0) || 
        (from_position.x > mPhoneParams.Size.width || from_position.x > mPhoneParams.Size.length || 
         to_position.x > mPhoneParams.Size.width || to_position.y > mPhoneParams.Size.length)) 
    {
        cout<<getCurrentTime()<<
        "generateSlideCommand(): Warning: position"<<
        positionPrint(from_position)<<
        positionPrint(to_position)<<
        "is wrong"<<endl;
        //to do :回到桌面
    }

    string slideCMD = "adb shell input swipe ";
    string positionCMD = to_string(from_position.x) + " " + to_string(from_position.y) + " " + 
                         to_string(to_position.x) + " " + to_string(to_position.y);
    slideCMD = slideCMD + positionCMD;

    cout<<getCurrentTime()<<
    "generateSlideCommand(): Slide: position"<<positionPrint(from_position)<<
    "==to=="<<positionPrint(to_position)<<endl;
    
    return slideCMD;    
}

/*
 * 生成事件指令
 * 
 */
string ADBControl::generateEventCommand(int& key_event)
{
    if (key_event >= KEYCODE_ERROR )
    {
        cout<<getCurrentTime()<<
        "generateEventCommand(): Warning: keyevent"<<
        key_event<<
        "is wrong"<<endl;
    }
    string keyEventCMD = "adb shell input keyevent ";
    keyEventCMD += to_string(key_event);

    cout<<getCurrentTime()<<
    "generateEventCommand(): keyEvent: "<<key_event<<endl;

    return keyEventCMD;

}


void ADBControl::doCommand(int commandType, Position position, int distance)
{

    int state = 0;
    Position from_position = {0,0};
    //区分是点击/滑动
    switch (commandType)
    {
    case Click:
        state = system(generateClickCommand(position).c_str());
        break;

    case SlideUp:
        from_position.x = position.x;
        from_position.y = position.y - distance;
        state = system(generateSlideCommand(position, from_position).c_str());
        break;

    case SlideDown:
        from_position.x = position.x;
        from_position.y = position.y + distance;
        state = system(generateSlideCommand(position, from_position).c_str());
        break;

    case SlideLeft:
        from_position.x = position.x - distance;
        from_position.y = position.y;
        state = system(generateSlideCommand(position, from_position).c_str());
        break;

    case SlideRight:
        from_position.x = position.x + distance;
        from_position.y = position.y;
        state = system(generateSlideCommand(position, from_position).c_str());
        break;   

    default:
        break;
    }

    sleep(waitCommand);    
}


/*
void ADBControl::doCommand(int commandType)
{
    
    int state = 0;
    Position from_position = {0, 0}, to_position = {0, 0};
    from_position.x = mDisplayCenter.x;
    from_position.y = mDisplayCenter.y;

    int temp_enum = 0;
    //区分是点击/滑动
    switch (commandType)
    {
    case SlideUp1:
        to_position.x = from_position.x;
        to_position.y = 0;
        state = system(generateSlideCommand(from_position, to_position).c_str());
        break;

    case SlideDown1:
        to_position.x = from_position.x;
        to_position.y = mPhoneParams.Size.length;
        state = system(generateSlideCommand(from_position, to_position).c_str());
        break;

    case SlideLeft1:
        to_position.x = 0;
        to_position.y = from_position.y;
        state = system(generateSlideCommand(from_position, to_position).c_str());
        break;

    case SlideRight1:
        to_position.x = mPhoneParams.Size.width;
        to_position.y = from_position.y;
        state = system(generateSlideCommand(from_position, to_position).c_str());
        break;

    case SlideUp1_2:
        to_position.x = from_position.x;
        to_position.y = (mPhoneParams.Size.width/4)*1;
        state = system(generateSlideCommand(from_position, to_position).c_str());
        break;

    case SlideDown1_2:
        to_position.x = from_position.x;
        to_position.y = (mPhoneParams.Size.width/4)*3;
        state = system(generateSlideCommand(from_position, to_position).c_str());
        break;

    case SlideLeft1_2:
        to_position.x = (mPhoneParams.Size.width/4)*1;
        to_position.y = from_position.y;
        state = system(generateSlideCommand(from_position, to_position).c_str());
        break;

    case SlideRight1_2:
        to_position.x = (mPhoneParams.Size.width/4)*3;
        to_position.y = from_position.y;
        state = system(generateSlideCommand(from_position, to_position).c_str());
        break;

    case Home:
        temp_enum = KEYCODE_HOME;
        state = system(generateEventCommand(temp_enum).c_str());
    
    case Back:
        temp_enum = KEYCODE_BACK;
        state = system(generateEventCommand(temp_enum).c_str());

    default:
        break;
    }
    sleep(waitCommand);

}
*/

void ADBControl::doCommand(int commandType, Position from_position, Position to_position)
{
    int state = 0;
    //区分是点击/滑动
    switch (commandType)
    {
    case Slide:
        state = system(generateSlideCommand(from_position, to_position).c_str());
        break;
    
    default:
        break;
    }
    sleep(waitCommand);
}

void ADBControl::doCommand(int commandType, int times)
{
    int state = 0;
    int i = 0;
    int temp_cmd = 0;

    Position from_position = {0, 0}, to_position = {0, 0};
    from_position.x = mDisplayCenter.x;
    from_position.y = mDisplayCenter.y;

    switch (commandType)
    {
    case Back:
        temp_cmd = KEYCODE_BACK;
        while (i < times) 
        {
            state = system(generateEventCommand(temp_cmd).c_str());
            ++i;
        }
        break;

    case Home:
        temp_cmd = KEYCODE_HOME;
        state = system(generateEventCommand(temp_cmd).c_str());

    case SlideUp1:
        to_position.x = from_position.x;
        to_position.y = 0;
        state = system(generateSlideCommand(from_position, to_position).c_str());
        break;

    case SlideDown1:
        to_position.x = from_position.x;
        to_position.y = mPhoneParams.Size.length;
        state = system(generateSlideCommand(from_position, to_position).c_str());
        break;

    case SlideLeft1:
        to_position.x = 0;
        to_position.y = from_position.y;
        state = system(generateSlideCommand(from_position, to_position).c_str());
        break;

    case SlideRight1:
        to_position.x = mPhoneParams.Size.width;
        to_position.y = from_position.y;
        state = system(generateSlideCommand(from_position, to_position).c_str());
        break;

    case SlideUp1_2:
        to_position.x = from_position.x;
        to_position.y = (mPhoneParams.Size.width/4)*1;
        state = system(generateSlideCommand(from_position, to_position).c_str());
        break;

    case SlideDown1_2:
        to_position.x = from_position.x;
        to_position.y = (mPhoneParams.Size.width/4)*3;
        state = system(generateSlideCommand(from_position, to_position).c_str());
        break;

    case SlideLeft1_2:
        to_position.x = (mPhoneParams.Size.width/4)*1;
        to_position.y = from_position.y;
        state = system(generateSlideCommand(from_position, to_position).c_str());
        break;

    case SlideRight1_2:
        to_position.x = (mPhoneParams.Size.width/4)*3;
        to_position.y = from_position.y;
        state = system(generateSlideCommand(from_position, to_position).c_str());
        break;

    default:
        break;
    }
    sleep(waitCommand);

}

void ADBControl::doCommand(int commandType, int distance, int times)
{
    int state = 0;
    int i = 0;
    Position from_position = {0, 0}, to_position = {0, 0};
    from_position.x = mDisplayCenter.x;
    from_position.y = mDisplayCenter.y;
    //区分是点击/滑动
    switch (commandType)
    {
    case SlideUp:
        to_position.x = from_position.x;
        to_position.y = from_position.y - distance;
        while (i < times) 
        {
            state = system(generateSlideCommand(from_position, to_position).c_str());
            ++i;
            sleep(1);
        }
        break;
    
    default:
        break;
    }
    sleep(waitCommand);

}

void ADBControl::openApp(Position& app)
{
    int state = 0;
    state = system(generateClickCommand(app).c_str());
    sleep(10);
}