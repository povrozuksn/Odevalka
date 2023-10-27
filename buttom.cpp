#include "TXLib.h"

struct Button
{
   int x;
   const char* name;
   string category;

   void draw()
    {
        txSetColor(TX_TRANSPARENT);
        txSetFillColor(TX_GRAY);
        Win32::RoundRect (txDC(), x+5, 35, x+145, 65, 30, 30);
        txSetColor(TX_BLACK, 2);
        txSetFillColor(TX_WHITE);
        if (click()) txSetFillColor(RGB(250, 180, 180));
        Win32::RoundRect (txDC(), x, 30, x+140, 60, 30, 30);
        txSetColor(TX_BLACK);
        txSelectFont("Times New Roman", 24);
        txDrawText (x, 30, x+140, 60, name);
    }

    bool click()
    {
        return( txMouseButtons() == 1 &&
                txMouseX() >= x && txMouseX() <= x+140 &&
                txMouseY() >= 35 && txMouseY() <= 65);
    }

};
