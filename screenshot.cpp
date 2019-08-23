#include <windows.h>
#include <iostream>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\opencv.hpp>
#include <string>
#include <mmsystem.h>

using namespace std;
using namespace cv;

int main()
{
    PlaySound(TEXT("alarm.wav"), NULL, SND_SYNC);
    system("pause");
    return 0;
}

