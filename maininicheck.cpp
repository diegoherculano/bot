#include <windows.h>
#include <iostream>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\opencv.hpp>
#include <string>

using namespace std;
using namespace cv;

Mat hwnd2mat(HWND hwnd){

    HDC hwindowDC,hwindowCompatibleDC;

    int height,width,srcheight,srcwidth;
    HBITMAP hbwindow;
    Mat src;
    BITMAPINFOHEADER  bi;

    hwindowDC=GetDC(hwnd);
    hwindowCompatibleDC=CreateCompatibleDC(hwindowDC);
    SetStretchBltMode(hwindowCompatibleDC,COLORONCOLOR);

    RECT windowsize;    // get the height and width of the screen
    GetClientRect(hwnd, &windowsize);

    srcheight = windowsize.bottom;
    srcwidth = windowsize.right;
    height = windowsize.bottom;  //change this to whatever size you want to resize to
    width = windowsize.right;

    src.create(height,width,CV_8UC4);

    // create a bitmap
    hbwindow = CreateCompatibleBitmap( hwindowDC, width, height);
    bi.biSize = sizeof(BITMAPINFOHEADER);    //http://msdn.microsoft.com/en-us/library/windows/window/dd183402%28v=vs.85%29.aspx
    bi.biWidth = width;
    bi.biHeight = -height;  //this is the line that makes it draw upside down or not
    bi.biPlanes = 1;
    bi.biBitCount = 32;
    bi.biCompression = BI_RGB;
    bi.biSizeImage = 0;
    bi.biXPelsPerMeter = 0;
    bi.biYPelsPerMeter = 0;
    bi.biClrUsed = 0;
    bi.biClrImportant = 0;

    // use the previously created device context with the bitmap
    SelectObject(hwindowCompatibleDC, hbwindow);
    // copy from the window device context to the bitmap device context
    StretchBlt( hwindowCompatibleDC, 0,0, width, height, hwindowDC, 0, 0,srcwidth,srcheight, SRCCOPY); //change SRCCOPY to NOTSRCCOPY for wacky colors !
    GetDIBits(hwindowCompatibleDC,hbwindow,0,height,src.data,(BITMAPINFO *)&bi,DIB_RGB_COLORS);  //copy from hwindowCompatibleDC to hbwindow

    // avoid memory leak
    DeleteObject (hbwindow); DeleteDC(hwindowCompatibleDC); ReleaseDC(hwnd, hwindowDC);

    return src;
}

int* imagesearch(string image, float prec=0.9)
{
    Mat mTemplate_Bgr,mTemplate;
    mTemplate_Bgr= imread(image,1);

    HWND hDesktopWnd;
    hDesktopWnd=GetDesktopWindow();
    Mat mScreenShot = hwnd2mat(hDesktopWnd);
    Mat mInput,mResult_Bgr= mScreenShot.clone();

    float Threshold= prec;

    cvtColor(mScreenShot, mInput,COLOR_BGR2GRAY);
    cvtColor(mTemplate_Bgr,mTemplate,COLOR_BGR2GRAY);

    Mat mResult;
    matchTemplate(mInput, mTemplate, mResult, TM_CCOEFF_NORMED);

    double minval, maxval ;
    Point minloc, maxloc;
    minMaxLoc(mResult, &minval, &maxval, &minloc, &maxloc);
    //cout << maxval << endl;
    int a = maxloc.x;
    int b = maxloc.y;
    static int r[2];
    if (maxval < Threshold)
    {
        r[0] = -1;
        r[1] = -1;
        return r;
    }
    else
    {
        r[0] = a;
        r[1] = b;
    }
    return r;
}

int* imagesearchcheck(Mat image)
{
    HWND hDesktopWnd;
    hDesktopWnd=GetDesktopWindow();
    Mat mScreenShot = hwnd2mat(hDesktopWnd);
    Mat mInput,mResult_Bgr= mScreenShot.clone();

    float Threshold= 0.98;

    cvtColor(mScreenShot, mInput,COLOR_BGR2GRAY);

    Mat mResult;
    matchTemplate(mInput, image, mResult, TM_CCOEFF_NORMED);

    double minval, maxval ;
    Point minloc, maxloc;
    minMaxLoc(mResult, &minval, &maxval, &minloc, &maxloc);
    int a = maxloc.x;
    int b = maxloc.y;
    static int r[2];
    if (maxval < Threshold)
    {
        r[0] = -1;
        r[1] = -1;
        return r;
    }
    else
    {
        r[0] = a;
        r[1] = b;
    }
    return r;
}

int autoloot(int a, int b)
{
    keybd_event(VK_SHIFT, 0, 0, 0);
    Sleep(100);
    SetCursorPos(a, b);
    mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0 );
    mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0 );
    Sleep(100);
    SetCursorPos(a, b-50);
    mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0 );
    mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0 );
    Sleep(100);
    SetCursorPos(a, b+50);
    mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0 );
    mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0 );
    Sleep(100);
    SetCursorPos(a-50, b);
    mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0 );
    mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0 );
    Sleep(100);
    SetCursorPos(a-50, b-50);
    mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0 );
    mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0 );
    Sleep(100);
    SetCursorPos(a-50, b+50);
    mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0 );
    mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0 );
    Sleep(100);
    SetCursorPos(a+50, b);
    mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0 );
    mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0 );
    Sleep(100);
    SetCursorPos(a+50, b-50);
    mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0 );
    mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0 );
    Sleep(100);
    SetCursorPos(a+50, b+50);
    mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0 );
    mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0 );
    Sleep(100);
    SetCursorPos(a+150, b+150);
    mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0 );
    mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0 );
    Sleep(300);
    keybd_event(VK_SHIFT, 0, KEYEVENTF_KEYUP, 0);
}

int goldchanger()
{
    int* gold;
    goldw:
        gold = imagesearch("gold.png");
        if(gold[0] != -1)
        {
            SetCursorPos(gold[0], gold[1]);
            mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
            mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
            Sleep(200);
            goto goldw;
        }
}

int main(void)
{
    string way[27] = {"ways\\way1.png", "ways\\way2.png", "ways\\way3.png", "ways\\way4.png", "ways\\way5.png", "ways\\way6.png", "ways\\way7.png", "ways\\way8.png", "ways\\way9.png", "ways\\way10.png",
    "ways\\way11.png", "ways\\way12.png", "ways\\way13.png", "ways\\way14.png", "ways\\way15.png", "ways\\way16.png", "ways\\way17.png", "ways\\way18.png", "ways\\way19.png", "ways\\way20.png", "ways\\way21.png",
    "ways\\way22.png", "ways\\way23.png", "ways\\way24.png", "ways\\way25.png", "ways\\way26.png", "ways\\way27.png"};
    int atual = 0;
    int clickin = 1;
    int w;
    int loot = 0;
    int confe = 1;
    HDC hDC;
    hDC = GetDC(NULL);
    Mat mTemplate;
    printf("F12 = Exit \nQuantos Waypoints: ");
    scanf("%d", &w);

    //READ POS .INI
    char takenstring[100];char takenstring2[100];
    GetPrivateProfileString(TEXT("PositionChar"),TEXT("x"),TEXT("ERROR: POSX"),takenstring,100,TEXT(".\\cfg.ini"));
    GetPrivateProfileString(TEXT("PositionChar"),TEXT("y"),TEXT("ERROR: POSY"),takenstring2,100,TEXT(".\\cfg.ini"));
    int posx = stoi(takenstring);
    int posy = stoi(takenstring2);
    printf("Carregando CFG..\n PosX: %d - PosY: %d", posx, posy);

    //READ ATTACK .INI
    char takenstring3[100];char takenstring4[100];char takenstring5[100];char takenstring6[100];
    GetPrivateProfileString(TEXT("AttackBar"),TEXT("vermelhox"),TEXT("ERROR: VERX"),takenstring3,100,TEXT(".\\cfg.ini"));
    GetPrivateProfileString(TEXT("AttackBar"),TEXT("vermelhoy"),TEXT("ERROR: VERY"),takenstring4,100,TEXT(".\\cfg.ini"));
    GetPrivateProfileString(TEXT("AttackBar"),TEXT("pretox"),TEXT("ERROR: PREX"),takenstring5,100,TEXT(".\\cfg.ini"));
    GetPrivateProfileString(TEXT("AttackBar"),TEXT("pretoy"),TEXT("ERROR: PREY"),takenstring6,100,TEXT(".\\cfg.ini"));
    int verx = stoi(takenstring3);
    int very = stoi(takenstring4);
    int prex = stoi(takenstring5);
    int prey = stoi(takenstring6);
    printf("\n ATTACK: \n VERX %d VERY %d PREX %d PREY %d", verx, very, prex, prey);
    printf("\n Carregado! Iniciando... \n\n");

start:
    while(1)
    {
        if(GetKeyState(VK_F12) & 0x8000)
        {
            cout << "QUIT!" << endl;
            return 0;
        }
        COLORREF ver = GetPixel(hDC, verx, very);//GetPixel Vermelho
        COLORREF preto = GetPixel(hDC, prex, prey);//GetPixel Preto
        if(ver == 255)
        {
            Sleep(500);
        }
        else if(preto == 0)
        {
            keybd_event(VK_SPACE, 0, 0, 0); //Atacar Monstro
            keybd_event(VK_SPACE, 0, KEYEVENTF_KEYUP, 0);
            clickin = 1;
            if(loot != 0){autoloot(posx, posy);}
            loot = 1;
            Sleep(500);
        }
        else
        {
            if(loot == 1){
                autoloot(posx, posy);
                loot = 0;
                goldchanger();
                keybd_event(VK_F4, 0, 0, 0); //Comer Food
                keybd_event(VK_F4, 0, KEYEVENTF_KEYUP, 0);
                Sleep(300);
            }
            int* img = imagesearch(way[atual], 0.5);
            COLORREF centro = GetPixel(hDC, img[0]+10, img[1]+10);//GetPixel Branco
            //cout << "COR: " << centro << endl;
            //cout << "Buscando Imagem: " << atual << " X: " << img[0] << endl;
            if(atual == w-1 && confe == 1 && centro == 16777215 || centro == 0)
            {
                atual = 0;
                confe = 0;
                goto click;
            }
            else if(confe == 1 && centro == 16777215 || centro == 0)
            {
                atual = atual+1;
                confe = 0;
                cout << "Atual: " << atual << " +1" << endl;
                goto click;
            }
        if(clickin == 1 && preto != 0){goto click;}
        }
    }
click:
    cout << "Buscando Click: " << way[atual] << endl;
    int* now = imagesearch(way[atual], 0.5);
    if(now[0] != -1)
    {
        keybd_event(VK_ESCAPE, 0, 0, 0); //Stop para Clicar
        keybd_event(VK_ESCAPE, 0, KEYEVENTF_KEYUP, 0);
        Sleep(500);
        SetCursorPos(now[0]+10, now[1]+10);//Clicando na img
        Sleep(500);
        mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0 );
        mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0 );
    }
    clickin = 0;
    confe = 1;
    goto check;
check:
    cout << "Conferindo se andou..." << endl;
    for(int z=0;z<10;z++)
    {
        Sleep(100);
        COLORREF preto = GetPixel(hDC, prex, prey);//GetPixel Preto
        if(preto == 0){goto start;}//Monstro = start
        if(z == 9)
        {
            HWND hDesktopWnd2;
            hDesktopWnd2=GetDesktopWindow();
            Mat mScreenShot2 = hwnd2mat(hDesktopWnd2);
            mTemplate = mScreenShot2.clone();//Tirando Print apos 2s
            cvtColor(mScreenShot2,mTemplate,COLOR_BGR2GRAY);
        }

    }
    for(int i=0;i<10;i++)
    {
        Sleep(100);
        COLORREF preto = GetPixel(hDC, prex, prey);//GetPixel Preto
        if(preto == 0){goto start;}//Monstro = start
        if(i == 9)
        {
            int* chk = imagesearchcheck(mTemplate); //Check print apos 2seg
            cout << "Andou? " << chk[0] << endl;
            if(chk[0] != -1 && preto != 0){goto click;}
        }
    }
    goto start;
}
