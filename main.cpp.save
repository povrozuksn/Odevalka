#include "TXLib.h"
#include "buttom.cpp"
#include "picture.cpp"

int main()
{
    txCreateWindow (1200, 700);
    txDisableAutoPause();
    txTextCursor (false);
    int count_btn = 4;
    int count_pic = 9;
    int nCentralPic = 0;
    char str[100];

    //Инициализация кнопок
    Button btn[count_btn];
    btn[0] = {50, "Персонаж", "Персонаж"};
    btn[1] = {200, "Одежда", "Одежда"};
    btn[2] = {350, "Голов. уборы", "Уборы"};
    btn[3] = {500, "Трусы"};

    //Инициализация картинки меню
    Picture menuPic[count_pic];
    menuPic[0] = {20, 100, txLoadImage("Pictures/Персонаж/Girl.bmp"),       80,  165, 240, 500, false, "Персонаж"};
    menuPic[1] = {20, 300, txLoadImage("Pictures/Персонаж/Boy.bmp"),        80,  165, 240, 500, false, "Персонаж"};
    menuPic[2] = {20, 100, txLoadImage("Pictures/Одежда/Комбенезон.bmp"),   80,  140, 240, 420, false, "Одежда"};
    menuPic[3] = {20, 250, txLoadImage("Pictures/Одежда/Платье.bmp"),       80,  140, 240, 420, false, "Одежда"};
    menuPic[4] = {20, 400, txLoadImage("Pictures/Одежда/Пиджак.bmp"),       80,  140, 240, 420, false, "Одежда"};
    menuPic[5] = {20, 550, txLoadImage("Pictures/Одежда/Рубаха.bmp"),       80,   80, 240, 240, false, "Одежда"};
    menuPic[6] = {120, 100, txLoadImage("Pictures/Одежда/Джемпер.bmp"),     80,   80, 240, 240, false, "Одежда"};
    menuPic[7] = {20, 100, txLoadImage("Pictures/Уборы/Шлем.bmp"),         100,  105, 100, 105, false, "Уборы"};
    menuPic[8] = {20, 300, txLoadImage("Pictures/Уборы/Диадема.bmp"),      100,   59, 100,  59, false, "Уборы"};



    //Инициализация картинки в центре
    Picture centrPic[100];

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
        for(int i=0; i<nCentralPic; i++)
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
                while(txMouseButtons() == 1)
                {
                    txSleep(10);
                }

                centrPic[nCentralPic] = {200, 100, menuPic[npic].pic,
                                            menuPic[npic].w,
                                            menuPic[npic].h,
                                            menuPic[npic].w,
                                            menuPic[npic].h,
                                            menuPic[npic].visible,
                                            menuPic[npic].category};
                nCentralPic ++;
            }

        }

        //Выбор центральной картинки
        for(int i=0; i<nCentralPic; i++)
        {
            if(centrPic[i].click() && centrPic[i].visible)
                {
                    vybor = i;
                    mouse_click = false;
                }
        }

        /*
        sprintf(str, "Индекс выбранной картинки = %d", vybor);
        txTextOut(50, 600, str);
        sprintf(str, "Колическтво центральных = %d", nCentralPic);
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

        if(vybor>=0)
        {
            if(txMouseButtons() == 1 && !mouse_click)
            {
                centrPic[vybor].x = txMouseX() - centrPic[vybor].w_scr/2;
                centrPic[vybor].y = txMouseY() - centrPic[vybor].h_scr/2;
            }
            else
            {
                if(txMouseButtons() != 1)
                {
                    mouse_click = true;
                }
            }
        }

        if(vybor>=0 && GetAsyncKeyState (VK_DELETE))
        {
            centrPic[vybor] = centrPic[nCentralPic-1];
            nCentralPic--;
            vybor = -1;
            mouse_click = true;
        }



        txEnd();
        txSleep(50);
    }

    for(int i=0; i<count_pic; i++)
    {
        txDeleteDC (menuPic[i].pic);
    }

    for(int i=0; i<nCentralPic; i++)
    {
        txDeleteDC (centrPic[i].pic);
    }


return 0;
}

