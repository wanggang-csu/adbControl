#include <iostream>
#include <time.h>

using namespace std;

string getCurrentTime()
{
    time_t timep;
    time(&timep);
    char currentTime[256];
    strftime(currentTime, sizeof(currentTime), "%Y-%m-%d %H:%M:%S", localtime(&timep));
    string returnTime = "[" + string(currentTime) + "] ";
    return returnTime;
}