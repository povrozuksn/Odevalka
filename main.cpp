#include "TXLib.h"

struct Button
{
   int x;
   const char* name;

   void drawButton()
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

    bool clickButton()
    {
        return( txMouseButtons() == 1 &&
                txMouseX() >= x && txMouseX() <= x+140 &&
                txMouseY() >= 35 && txMouseY() <= 75);
    }

};

struct Picture
{
    int x;
    int y;
    HDC pic;
    int w_scr;
    int h_scr;
    int w;
    int h;
    bool visible;

    void drawPictures()
    {
        Win32::TransparentBlt (txDC(), x, y, w_scr, h_scr, pic, 0, 0, w, h, TX_WHITE);
    }

};


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
    int count_btn = 4;

    //Инициализация кнопок
    Button btn[count_btn];
    btn[0] = {60, "Персонаж"};
    btn[1] = {250, "Одежда"};
    btn[2] = {440, "Аксесуары"};
    btn[3] = {630, "Трусы"};

    //Инициализация картинки меню
    Picture menuPic1 = {20, 100, txLoadImage("Pictures/Персонаж/Girl.bmp"), 80, 200, 240, 600, false};
    Picture menuPic2 = {20, 300, txLoadImage("Pictures/Персонаж/Boy.bmp"), 80, 200, 240, 600, false};


    //Инициализация картинки в центре
    Picture centrPic1 = {500, 100, txLoadImage("Pictures/Персонаж/Girl.bmp"), 240, 600, 240, 600, false};
    Picture centrPic2 = {500, 100, txLoadImage("Pictures/Персонаж/Boy.bmp"), 240, 600, 240, 600, false};



    while(!GetAsyncKeyState (VK_ESCAPE))
    {
        txBegin();
        txSetColor(TX_YELLOW);
        txSetFillColor(TX_YELLOW);
        txClear();

        //Рисование кнопок
        for(int i=0; i<count_btn; i++)
        {
            btn[i].drawButton();
        }

        if(btn[0].clickButton())
        {
            menuPic1.visible = true;
            menuPic2.visible = true;
        }

        if(menuPic1.visible)
        {
            menuPic1.drawPictures();
        }

        if(menuPic2.visible)
        {
            menuPic2.drawPictures();
        }

        if(clickPictures(100))
        {
            centrPic1.visible = true;
        }

        if(centrPic1.visible)
        {
            centrPic1.drawPictures();
        }

        if(clickPictures(300))
        {
            centrPic2.visible = true;
        }

        if(centrPic2.visible)
        {
            centrPic2.drawPictures();
        }

        txEnd();
        txSleep(50);
    }

    txDeleteDC (centrPic1.pic);
    txDeleteDC (centrPic2.pic);

return 0;
}

