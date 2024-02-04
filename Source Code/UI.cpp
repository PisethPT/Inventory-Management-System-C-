#include <iostream>
#include <windows.h>
using namespace std;

// Set coord on screen console
class UI
{
protected:
    // Set Position
    void setUI(int x, int y)
    {
        COORD coord = {0, 0};
        coord.X = x;
        coord.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    }
    // Set Color
    void setColorsAttribute(int color)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    }

    // Set Border
    void setBorder(int x, int y, int length, int color, string title, int symbols)
    {
        setColorsAttribute(color);
        setUI(x, y);

        for (size_t i = 0; i < length; i++) // 29
        {
            cout << (char)symbols; // 224
        }

        cout << title;
        for (size_t i = 0; i < length; i++) // 29
        {
            cout << (char)symbols; // 224
        }
    }

    // Set Frame
    void setFrame(int x, int y, int width, int hieght, string tittle, int color1, int color2, int symbols)
    {
        setColorsAttribute(color1); // 4
        setUI(x, y);
        cout << tittle << endl;

        setColorsAttribute(color2); // 8

        for (int borx = 1; borx <= width; borx++) // start: 1->3
        {
            for (int bory = 1; bory <= hieght; bory++) // start: 1->140
            {
                if (borx == 1 || borx == width || bory == 1 || bory == hieght) // 140
                {
                    cout << (char)symbols; // 220
                }
                else
                    cout << " ";
            }
            cout << endl;
        }
    }
};