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
        Win32::RoundRect (txDC(), x+5, 35, x+145, 75, 30, 30);
        txSetColor(TX_BLACK, 2);
        txSetFillColor(TX_WHITE);
        Win32::RoundRect (txDC(), x, 30, x+140, 70, 30, 30);
        txSetColor(TX_BLACK);
        txSelectFont("Times New Roman", 24);
        txDrawText (x, 30, x+140, 70, name);
    }

    bool click()
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
    string category;

    void draw()
    {
        if(visible)
        {
            Win32::TransparentBlt (txDC(), x, y, w_scr, h_scr, pic, 0, 0, w, h, TX_WHITE);
        }
    }

    bool click()
    {
        return( txMouseButtons() == 1 &&
                txMouseX() >= 20 && txMouseX() <= 100 &&
                txMouseY() >= y && txMouseY() <= y+200);
    }
};




int main()
{
    txCreateWindow (1200, 700);
    txDisableAutoPause();
    txTextCursor (false);
    int count_btn = 4;
    int count_pic = 6;

    //Инициализация кнопок
    Button btn[count_btn];
    btn[0] = {50, "Персонаж", "Персонаж"};
    btn[1] = {200, "Одежда", "Одежда"};
    btn[2] = {350, "Аксесуары", "Аксесуары"};
    btn[3] = {500, "Трусы"};

    //Инициализация картинки меню
    Picture menuPic[count_pic];
    menuPic[0] = {20, 100, txLoadImage("Pictures/Персонаж/Girl.bmp"), 80, 200, 240, 600, false, "Персонаж"};
    menuPic[1] = {20, 300, txLoadImage("Pictures/Персонаж/Boy.bmp"), 80, 200, 240, 600, false, "Персонаж"};
    menuPic[2] = {20, 100, txLoadImage("Pictures/Одежда/Одежда1.bmp"), 80, 200, 240, 645, false, "Одежда"};
    menuPic[3] = {20, 300, txLoadImage("Pictures/Одежда/Одежда2.bmp"), 80, 200, 240, 423, false, "Одежда"};
    menuPic[4] = {20, 100, txLoadImage("Pictures/Аксесуары/Аксесуар1.bmp"), 100, 105, 100, 105, false, "Аксесуары"};
    menuPic[5] = {20, 300, txLoadImage("Pictures/Аксесуары/Аксесуар2.bmp"), 100, 59, 100, 59, false, "Аксесуары"};



    //Инициализация картинки в центре
    Picture centrPic[count_pic];
    centrPic[0] = {500, 100, menuPic[0].pic, 240, 600, menuPic[0].w, menuPic[0].h, false, "Персонаж"};
    centrPic[1] = {500, 100, menuPic[1].pic, 240, 600, menuPic[1].w, menuPic[1].h, false, "Персонаж"};
    centrPic[2] = {500, 200, menuPic[2].pic, 240, 645, menuPic[2].w, menuPic[2].h, false, "Одежда"};
    centrPic[3] = {500, 200, menuPic[3].pic, 240, 423, menuPic[3].w, menuPic[3].h, false, "Одежда"};
    centrPic[4] = {500, 100, menuPic[4].pic, 100, 105, menuPic[4].w, menuPic[4].h, false, "Аксесуары"};
    centrPic[5] = {500, 100, menuPic[5].pic, 100,  59, menuPic[5].w, menuPic[5].h, false, "Аксесуары"};

    int vybor = -1;
    bool mouse_click = false;

    while(!GetAsyncKeyState (VK_ESCAPE))
    {
        txBegin();
        txSetColor(TX_YELLOW);
        txSetFillColor(TX_YELLOW);
        txClear();

        //Рисование кнопок
        for(int i=0; i<count_btn; i++)
        {
            btn[i].draw();
        }
        //Рисование картинок
        //Меню
        for(int i=0; i<count_pic; i++)
        {
            menuPic[i].draw();
        }
        //Центральные
        for(int i=0; i<count_pic; i++)
        {
            centrPic[i].draw();
        }

        //Установка видимости картинок-меню по категории
        for(int ib=0; ib<count_btn; ib++)
        {
            if(btn[ib].click())
            {
                for(int ip=0; ip<count_pic; ip++)
                {
                    menuPic[ip].visible = false;
                    if(menuPic[ip].category == btn[ib].category)
                    {
                        menuPic[ip].visible = true;
                    }
                }
            }
        }

        /*
        //Видимость центральных картинок (проект типа ФОТОРОБОТ)
        for(int npic=0; npic<count_pic; npic++)
        {
            if(menuPic[npic].click() && menuPic[npic].visible)
            {
                for(int npic1=0; npic1<count_pic; npic1++)
                {
                    if(centrPic[npic1].category == centrPic[npic].category)
                    {
                        centrPic[npic1].visible = false;
                    }
                }
                centrPic[npic].visible = !centrPic[npic].visible;
                txSleep(100);
            }
        }
        */

        //Видимость центральных картинок (проект типа ПЛАНЕРОВКА)
        for(int npic=0; npic<count_pic; npic++)
        {
            if(menuPic[npic].click() && menuPic[npic].visible)
            {
                centrPic[npic].visible = true;
            }
        }


        //Выбор центральной картинки
        for(int i=0; i<count_pic; i++)
        {
            if(txMouseButtons() == 1 &&
                txMouseX() >= centrPic[i].x &&
                txMouseX() <= centrPic[i].x + centrPic[i].w_scr &&
                txMouseY() >= centrPic[i].y &&
                txMouseY() <= centrPic[i].y + centrPic[i].h_scr &&
                centrPic[i].visible)
                {
                    vybor = i;
                    mouse_click = true;
                }
        }
        /*
        char str[100];
        sprintf(str, "Индекс выбранной картинки = %d", vybor);
        txTextOut(50, 650, str);
        */

        if(vybor>=0)
        {
             if(GetAsyncKeyState (VK_LEFT))
             {
                centrPic[vybor].x -= 5;
             }
             if(GetAsyncKeyState (VK_RIGHT))
             {
                centrPic[vybor].x += 5;
             }
             if(GetAsyncKeyState (VK_UP))
             {
                centrPic[vybor].y -= 5;
             }
             if(GetAsyncKeyState (VK_DOWN))
             {
                centrPic[vybor].y += 5;
             }
             if(GetAsyncKeyState (VK_OEM_PLUS) || GetAsyncKeyState (VK_ADD))
             {
                centrPic[vybor].w_scr = centrPic[vybor].w_scr * 1.1;
                centrPic[vybor].h_scr = centrPic[vybor].h_scr * 1.1;
             }
             if(GetAsyncKeyState (VK_OEM_MINUS) || GetAsyncKeyState (VK_SUBTRACT))
             {
                centrPic[vybor].w_scr = centrPic[vybor].w_scr * 0.9;
                centrPic[vybor].h_scr = centrPic[vybor].h_scr * 0.9;
             }
        }


        txEnd();
        txSleep(50);
    }

    for(int i=0; i<count_pic; i++)
    {
        txDeleteDC (menuPic[i].pic);
    }

    for(int i=0; i<count_pic; i++)
    {
        txDeleteDC (centrPic[i].pic);
    }


return 0;
}

