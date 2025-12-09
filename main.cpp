 #include <windows.h>
#include <iostream>
#include "televisor.h"

using namespace std;

HDC hdc;

bool CheckCollision(TVBase* tv, Figure* figure);

int main() 
{
	setlocale(LC_ALL, "RU");

	int x0 = 300;
	int y0 = 300;

	HWND hwnd = GetConsoleWindow();
	if (hwnd == NULL) 
	{
		cout << "Console Window Descriptor NOT FOUND!\n";
		return 1;
	}//end if

	hdc = GetWindowDC(hwnd);
	if (hdc == 0) 
	{
		cout << "Handle Device Context NOT FOUND!\n";
		return 2;
	}//end if

	Television tv(x0, y0);
	TelevisionWithAntenna tvAnt(x0, y0);
	BrokenTelevision tvGrid(x0, y0);
	Molotok mk(800, 400);
	Aquarium aqua(550, 500, 250, 180);
	TelevisionWithoutLegs tvwlg(x0, y0);
	TelevisionWithoutButtons tvWB(x0, y0);
    TelevisionWithSpeakers tvSpeakers(x0, y0);
    SimpleCircle circle(500, 130, 30);

    TVBase* CurrentTV = &tv;

    TVBase* bufTv[6];
    bufTv[0] = &tv;
    bufTv[1] = &tvAnt;
    bufTv[2] = &tvGrid;
    bufTv[3] = &tvwlg;
    bufTv[4] = &tvWB;
    bufTv[5] = &tvSpeakers;

    Figure* bufFigure[3];
    bufFigure[0] = &mk;
    bufFigure[1] = &aqua;
    bufFigure[2] = &circle;

	for (int i = 0; i < 3; i++) 
	{
		bufFigure[i]->Show();
	}//end for
	CurrentTV->Show();

	cout << "Управление телевизором стрелками. ESC — выход.\n";

    bool canCollide = true;

    while (true)
    {
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) break;

        if (GetAsyncKeyState('1') & 0x8000)
        {
            CurrentTV->Hide();
            CurrentTV = &tv;
            CurrentTV->MoveTo(x0, y0);
            Sleep(200);
        }//end if

        int newX = x0;
        int newY = y0;

        if (GetAsyncKeyState(VK_UP) & 0x8000) newY -= 5;
        if (GetAsyncKeyState(VK_DOWN) & 0x8000) newY += 5;
        if (GetAsyncKeyState(VK_LEFT) & 0x8000) newX -= 5;
        if (GetAsyncKeyState(VK_RIGHT) & 0x8000) newX += 5;

        CurrentTV->MoveTo(newX, newY);

        // Проверяем столкновение
        bool isCollidingNow = false;
        for (int i = 0; i < 3; i++)
        {
            if (CheckCollision(CurrentTV, bufFigure[i]))
            {
                isCollidingNow = true;
                break;
            }//end if
        }//end for

        if (isCollidingNow && canCollide)
        {
            //Не меняем телевизор
            canCollide = false; 

            CurrentTV->Hide();
            int currentIndex = CurrentTV->GetId();
            int nextIndex = (currentIndex + 1) % 6;

            CurrentTV = bufTv[nextIndex];
            CurrentTV->MoveTo(newX, newY);

            Sleep(120);
        }//end if

        // Если вышли из объекта, то при следующем столкновении 
        // меняем телевизор на следующий
        if (!isCollidingNow)
        {
            canCollide = true;
        }//end if

        x0 = newX;
        y0 = newY;

        Sleep(30);
    }//end while

	return 0;
}//end main
