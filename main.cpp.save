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

bool clickPictures(int y)
{
    return( txMouseButtons() == 1 &&
            txMouseX() >= 20 && txMouseX() <= 100 &&
            txMouseY() >= y && txMouseY() <= y+200);
}


int main()
{
    txCreateWindow (1200, 700);
    txDisableAutoPause();
    txTextCursor (false);

    HDC  pic1 = txLoadImage ("Pictures/Girl.bmp");
    HDC  pic2 = txLoadImage ("Pictures/Boy.bmp");
    bool pic1_menu_visible = false;
    bool pic2_menu_visible = false;
    bool pic1_central_visible = false;
    bool pic2_central_visible = false;


    while(!GetAsyncKeyState (VK_ESCAPE))
    {
        txBegin();
        txSetColor(TX_YELLOW);
        txSetFillColor(TX_YELLOW);
        txClear();


        drawButton(60, "Персонаж");
        drawButton(250, "Button2");


        if(clickButton(60))
        {
            pic1_menu_visible = true;
            pic2_menu_visible = true;
        }

        if(pic1_menu_visible)
        {
            Win32::TransparentBlt (txDC(), 20, 100, 80, 200, pic1, 0, 0, 240, 600, TX_WHITE);
        }

        if(pic2_menu_visible)
        {
            Win32::TransparentBlt (txDC(), 20, 300, 80, 200, pic2, 0, 0, 240, 600, TX_WHITE);
        }

        if(clickPictures(100))
        {
            pic1_central_visible = true;
        }

        if(pic1_central_visible)
        {
            Win32::TransparentBlt (txDC(), 500, 100, 240, 600, pic1, 0, 0, 240, 600, TX_WHITE);
        }

        if(clickPictures(300))
        {
            pic2_central_visible = true;
        }

        if(pic2_central_visible)
        {
            Win32::TransparentBlt (txDC(), 500, 100, 240, 600, pic2, 0, 0, 240, 600, TX_WHITE);
        }





        if(clickButton(250))
        {
        }


        txEnd();
        txSleep(50);
    }

    txDeleteDC (pic1);
    txDeleteDC (pic2);


return 0;
}

