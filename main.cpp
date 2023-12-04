#include "TXLib.h"
#include "buttom.cpp"
#include "picture.cpp"
#include <fstream>
#include <stdio.h>
#include <dirent.h>

using namespace std;

int get_w(string adress)
{
    FILE *f1 = fopen(adress.c_str(), "rb");
    unsigned char headerinfo[54];
    fread(headerinfo, sizeof(unsigned char), 54, f1);
    int w = *(int *)&headerinfo[18];

    return w;
}

int get_h(string adress)
{
    FILE *f1 = fopen(adress.c_str(), "rb");
    unsigned char headerinfo[54];
    fread(headerinfo, sizeof(unsigned char), 54, f1);
    int h = *(int *)&headerinfo[22];

    return h;
}

int readFromDir(string adress, Picture menuPic[], int count_pic)
{
    DIR *dir;
    struct dirent *ent;
    int X = 20;
    int Y = 100;
    if ((dir = opendir (adress.c_str())) != NULL)
    {
      while ((ent = readdir (dir)) != NULL)
      {
        if((string)ent->d_name != "." && (string)ent->d_name != "..")
        {
            if(Y<=550 && X == 20)
            {
                X = 20;
            }
            else if (Y>550)
            {
                X = 120;
                Y = 100;
            }
            menuPic[count_pic].x = X;
            menuPic[count_pic].y = Y;
            menuPic[count_pic].adress = adress + (string)ent->d_name;
            count_pic++;
            Y += 150;
        }
      }
      closedir (dir);
    }

    return count_pic;
}

string runFileDialog(bool isSave)
{
    string FileName = "";

    OPENFILENAME ofn;
    TCHAR szFile[260] = {0};

    // Initialize OPENFILENAME
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = txWindow();
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = ("Text\0*.TXT\0");
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    // Display the Open dialog box.
    if(isSave)
    {
        if (GetSaveFileName(&ofn)==TRUE)
        {
           FileName = ofn.lpstrFile;
           FileName = FileName + ".txt";

        }
    }
    else
    {
        if (GetOpenFileName(&ofn)==TRUE)
        {
           FileName = ofn.lpstrFile;
        }
    }
    return FileName;
}


const int count_btn = 11;
//Кнопка сохранения
const int btn_save = count_btn-4;
//Кнопка загрузки
const int btn_load = count_btn-3;
//Кнопка справки
const int btn_help = count_btn-2;
//Кнопка меню
const int btn_menu = count_btn-1;

//Режим меню
const int page_menu = 0;
//Режим редактора
const int page_redactor = 1;
//Режим справки
const int page_help = 2;


int main()
{
    txCreateWindow (1200, 700);
    txDisableAutoPause();
    txTextCursor (false);
    int count_pic = 0;
    int nCentralPic = 0;
    char str[100];

    int page = page_menu;

    //Инициализация кнопок
    Button btn[count_btn];
    btn[0] = {50, 30, "Персонаж", "Персонаж"};
    btn[1] = {200,30, "Одежда", "Одежда"};
    btn[2] = {350,30, "Голов. уборы", "Уборы"};
    btn[3] = {500,30, "Обувь", "Обувь"};
    btn[4] = {650,30, "Аксесуары", "Аксесуары"};
    btn[5] = {800,30, "Сумки", "Сумки"};
    btn[6] = {950,30, "Животные", "Животные"};
    btn[7] = {1000,550, "Сохранить", ""};
    btn[8] = {1000,600, "Загрузить", ""};
    btn[9] = {1000,650, "Справка", ""};
    btn[10] = {530,350, "Начать", ""};


    //Инициализация картинки меню
    Picture menuPic[100];

    count_pic = readFromDir("Pictures/Персонаж/", menuPic, count_pic);
    count_pic = readFromDir("Pictures/Одежда/", menuPic, count_pic);
    count_pic = readFromDir("Pictures/Уборы/", menuPic, count_pic);
    count_pic = readFromDir("Pictures/Обувь/", menuPic, count_pic);
    count_pic = readFromDir("Pictures/Аксесуары/", menuPic, count_pic);
    count_pic = readFromDir("Pictures/Сумки/", menuPic, count_pic);
    count_pic = readFromDir("Pictures/Животные/", menuPic, count_pic);

    for(int i=0; i<count_pic; i++)
    {
        menuPic[i].pic = txLoadImage(menuPic[i].adress.c_str());

        menuPic[i].w = get_w(menuPic[i].adress);
        menuPic[i].h = get_h(menuPic[i].adress);

        menuPic[i].visible = false;

        string str = menuPic[i].adress;
        int pos1 = str.find("/");
        int pos2 = str.find("/", pos1+1);
        menuPic[i].category = str.substr(pos1+1, pos2-pos1-1);

        if(menuPic[i].category == "Уборы" || menuPic[i].category == "Аксесуары")
        {
            menuPic[i].w_scr = menuPic[i].w/2;
            menuPic[i].h_scr = menuPic[i].h/2;
        }
        else
        {
            menuPic[i].w_scr = menuPic[i].w/3;
            menuPic[i].h_scr = menuPic[i].h/3;
        }
    }

    //Инициализация картинки в центре
    Picture centrPic[100];

    int vybor = -1;
    bool mouse_click = false;

    while(!GetAsyncKeyState (VK_ESCAPE))
    {
        txBegin();
        txSetColor(TX_BLACK);
        txSetFillColor(TX_YELLOW);
        txClear();

        //Режим меню
        if(page == page_menu)
        {
            btn[btn_menu].draw();
            btn[btn_help].draw();
            if(btn[btn_menu].click())
            {
               page = page_redactor;
               txSleep(100);
            }
        }

        //Режим редактора
        if(page == page_redactor)
        {

            //Рисование кнопок
            for(int i=0; i<count_btn-1; i++)
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

                    centrPic[nCentralPic] = {200, 100,
                                                menuPic[npic].adress,
                                                menuPic[npic].pic,
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

            //Сохранение результатов в файл
            if(btn[btn_save].click())
            {
                string FileName = runFileDialog(true);


                ofstream fileout;               // поток для записи
                fileout.open(FileName);      // открываем файл для записи
                if (fileout.is_open())
                {
                    for(int i=0; i<nCentralPic; i++)
                    {
                        if(centrPic[i].visible)
                        {
                            fileout << centrPic[i].x << endl;
                            fileout << centrPic[i].y << endl;
                            fileout << centrPic[i].adress << endl;
                            fileout << centrPic[i].w_scr << endl;
                            fileout << centrPic[i].h_scr << endl;
                        }
                    }
                }
                fileout.close();                // закрываем файл для записи
            }

            //Чтение из файла
            if(btn[btn_load].click())
            {

                string FileName = runFileDialog(false);

                for(int i = 0; i<count_pic; i++)
                {
                    centrPic[i].visible = false;
                }

                char buff[50];
                ifstream filein(FileName); // окрываем файл для чтения

                while (filein.good())
                {
                    filein.getline(buff, 50);
                    int x = atoi(buff);
                    filein.getline(buff, 50);
                    int y = atoi(buff);
                    filein.getline(buff, 50);
                    string adress = buff;
                    filein.getline(buff, 50);
                    int w_scr = atoi(buff);
                    filein.getline(buff, 50);
                    int h_scr = atoi(buff);

                    for(int i = 0; i<count_pic; i++)
                    {

                        if(menuPic[i].adress == adress)
                        {
                            centrPic[nCentralPic] = {x, y,
                                                    menuPic[i].adress,
                                                    menuPic[i].pic,
                                                    w_scr,
                                                    h_scr,
                                                    menuPic[i].w,
                                                    menuPic[i].h,
                                                    true,
                                                    menuPic[i].category};
                            nCentralPic ++;
                        }
                    }
                }
                filein.close();     // закрываем файл
            }

            if(btn[btn_help].click())
            {
               page = page_help;
               btn[btn_help].name = "Вернуться";
               txSleep(100);
            }

        }

        //Режим справки
        else if(page == page_help)
        {
            txSelectFont("Times New Roman", 42);
            txDrawText(0, 200, 1200, 600,
                        "Программа 'Гардероб'.\n\n"
                        "Выбирай персонажа, одежду, аксесуары.\n"
                        "Комбинируй по своему вкусу.\n"
                        "Картинки передвигаются стрелочками и мышкой\n"
                        "Увеличить '+', уменьшить '-'\n"
                        "Результат можно сохранять в txt-формате и загружать\n"
                        "Выход из программы - 'Escape'.\n");
            btn[btn_help].draw();
            if(btn[btn_help].click())
            {
               page = page_redactor;
               btn[btn_help].name = "Справка";
               txSleep(100);
            }
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

