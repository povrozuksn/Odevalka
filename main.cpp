#include "TXLib.h"

void drawButton(int x, const char* name)
{
    txSetColor(TX_TRANSPARENT);
    txSetFillColor(TX_GRAY);
    Win32::RoundRect (txDC(), x+5, 35, x+145, 75, 30, 30);
    txSetColor(TX_BLACK, 2);
    txSetFillColor(TX_WHITE);
    Win32::RoundRect (txDC(), x, 30, x+140, 70, 30, 30);
    txSetColor(TX_BLACK);
    txSelectFont("Times New Roman", 24);
    txDrawText (x, 30, x+140, 70, name);
}

bool clickButton(int x)
{
    return( txMouseButtons() == 1 &&
            txMouseX() >= x && txMouseX() <= x+140 &&
            txMouseY() >= 35 && txMouseY() <= 75);
}

int main()
{
    txCreateWindow (1200, 700);
    txDisableAutoPause();
    txTextCursor (false);

    HDC  pic1 = txLoadImage ("Pictures/Girl.bmp");
    HDC  pic2 = txLoadImage ("Pictures/Boy.bmp");


    while(!GetAsyncKeyState (VK_ESCAPE))
    {
        txBegin();
        txSetColor(TX_YELLOW);
        txSetFillColor(TX_YELLOW);
        txClear();


        drawButton(60, "Button1");
        drawButton(250, "Button2");


        if(clickButton(60))
        {
            txTransparentBlt (txDC(), 100, 200, 300, 700, pic1, 0, 0, TX_WHITE);
        }

        if(clickButton(250))
        {
            txTransparentBlt (txDC(), 100, 200, 300, 900, pic2, 0, 0, TX_WHITE);
        }


        txEnd();
        txSleep(50);
    }

    txDeleteDC (pic1);
    txDeleteDC (pic2);


return 0;
}

