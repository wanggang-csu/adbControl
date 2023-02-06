#include <thread>
#include "../include/adb/ADBControl.h"

void testThread()
{
    int i = 0;
    while(i<100)
    {   
        //std::this_thread::sleep_for(std::chrono::microseconds(10000)); //线程休眠500ms
        sleep(1);
        cout<<"i = "<<i<<endl;
        ++i;
    }    
}

int main(int argc, char *argv[]) {

    PhoneParameters Phone;
    Phone.PhoneName = "Redmi";
    Phone.RefreshRate = 120;
    Phone.Size.length = 2400;
    Phone.Size.width = 1080;

    ADBControl test;
    test.PhoneInit(Phone);
    test.createThread();
    test.doCommand(SlideUp, 100, 4);
    //test.doCommand(SlideDown1_2);
    while (true)
    {
        sleep(1);
        cout<<"888888888888"<<endl;
    }
    
}