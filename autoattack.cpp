#include <iostream>
#include <graphics.h>
#include <string>

using namespace std;

int main()
{
    HDC hDC;
    hDC = GetDC(NULL);
    char takenstring1[100];char takenstring2[100];char takenstring3[100];char takenstring4[100];
    char takenstring5[100];char takenstring6[100];
    GetPrivateProfileString(TEXT("AttackBar"),TEXT("vermelhox"),TEXT("ERROR: AutoAttack"),takenstring1,100,TEXT(".\\cfg.ini"));
    GetPrivateProfileString(TEXT("AttackBar"),TEXT("vermelhoy"),TEXT("ERROR: AutoAttack"),takenstring2,100,TEXT(".\\cfg.ini"));
    GetPrivateProfileString(TEXT("AttackBar"),TEXT("preto2x"),TEXT("ERROR: AutoAttack"),takenstring3,100,TEXT(".\\cfg.ini"));
    GetPrivateProfileString(TEXT("AttackBar"),TEXT("preto2y"),TEXT("ERROR: AutoAttack"),takenstring4,100,TEXT(".\\cfg.ini"));
    GetPrivateProfileString(TEXT("Delays"),TEXT("delayspell1"),TEXT("ERROR: Delay"),takenstring5,100,TEXT(".\\cfg.ini"));
    GetPrivateProfileString(TEXT("Delays"),TEXT("delayspell2"),TEXT("ERROR: Delay"),takenstring6,100,TEXT(".\\cfg.ini"));

    int vermelhox = stoi(takenstring1);
    int vermelhoy = stoi(takenstring2);
    int preto2x = stoi(takenstring3);
    int preto2y = stoi(takenstring4);
    int delay1 = stoi(takenstring5);
    int delay2 = stoi(takenstring6);
    int delay = delay1/2;

    printf("\n AutoAttack %d %d %d %d DELAY %d %d", vermelhox, vermelhoy, preto2x, preto2y, delay1);
    printf("\n Carregado!\n");

while(1)
{
    COLORREF pre1 = GetPixel(hDC, vermelhox, vermelhoy);
    COLORREF pre2 = GetPixel(hDC, preto2x, preto2y);
    if(pre2 == 0)
    {
        Sleep(delay2/2);
        keybd_event(VK_F1, 0, 0, 0); //Press down the Key
        keybd_event(VK_F1, 0, KEYEVENTF_KEYUP, 0); //Release the Key
        printf("Spell2\n");
        Sleep(delay2/2);
    }
    else if(pre1 == 255){
        Sleep(delay1/2);
        keybd_event('4', 0, 0, 0); //Press down the Key
        keybd_event('4', 0, KEYEVENTF_KEYUP, 0); //Release the Key
        printf("Spell1\n");
        Sleep(delay1/2);
    }
}
}

