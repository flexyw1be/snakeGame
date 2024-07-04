#include"menu.h"
using namespace std;
bool exxit = false;
int currMenu = 0;
int ch = 0;
HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
string a = "New Game";
string b = "Choice level";
string c = "Records";
string d = "Exit";
void gotoxy(short x, short y)
{
    SetConsoleCursorPosition(hStdOut, {x, y});
}

void showMenu()
{
    while (!exxit)
    {
        system("cls");
        cout << a << endl;
        cout << b << endl;
        cout << c << endl;
        cout << d << endl;

        gotoxy(0, currMenu);

        ch = _getch();
        if (ch == 224){
            ch = _getch();
        }
        switch(ch)
        {
            case 27: exxit = true;   break;
            case 72: currMenu--;    break;
            case 80: currMenu++;    break;
            case 13:
                if (currMenu == 0){
                    system("cls");
                    cout << "idet igra" << endl;
                }
                else if (currMenu == 1){
                    system("cls");
                    cout << "gg" << endl;
                }
                else if (currMenu == 2){
                    system("cls");
                    exxit = true;
                    cout << "plaki-plaki" << endl;
                }
            break;
        }
        if (currMenu < 0) currMenu = 0;
        if (currMenu > 3) currMenu = 3;

    }
}

