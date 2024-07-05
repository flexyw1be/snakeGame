#include <iostream>
#include <Windows.h>
#include <string>
#include <conio.h>
using namespace std;


const int WIDTH = 10;
const int HEIGHT = 10;
const int MENUPOINTS = 5;
string Map[] = {
"############\n",
"#          #\n",
"#          #\n",
"#          #\n",
"#          #\n",
"#          #\n",
"#          #\n",
"#          #\n",
"#          #\n",
"############\n"};
int level = 1;


bool exxit = false;
int currMenu = 0;
int ch = 0;
HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

string MenuText[] = {
    "New game\n",
    "Choice level\n",
    "Records\n",
    "Exit\n"};


string LevelsText[] = {
    "1\n",
    "2\n",
    "3\n"};


void ClearScreen(){
    DWORD n;
    DWORD size;
    COORD coord = {0};
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    HANDLE h = GetStdHandle ( STD_OUTPUT_HANDLE );
    GetConsoleScreenBufferInfo ( h, &csbi );
    size = csbi.dwSize.X * csbi.dwSize.Y;
    FillConsoleOutputCharacter ( h, TEXT ( ' ' ), size, coord, &n );
    GetConsoleScreenBufferInfo ( h, &csbi );
    FillConsoleOutputAttribute ( h, csbi.wAttributes, size, coord, &n );
    SetConsoleCursorPosition ( h, coord );
}



void gotoxy(short x, short y)
{
    SetConsoleCursorPosition(hStdOut, {x, y});
}


void setLevel(){
    exxit = false;
    while (!exxit){
        system("cls");
         for(int i=0; i<size(LevelsText); i++){
                cout<<LevelsText[i];
         }
        gotoxy(0, currMenu);
        ch = _getch();
        if (ch == 224){
            ch = _getch();
        }
        switch(ch){
            case 27: exxit = true;   break;
            case 72: currMenu--;    break;
            case 80: currMenu++;    break;
            case 13:
                exxit = true;
                system("cls");
                if (currMenu == 0){
                    level = 1;
                }
                else if (currMenu == 1){
                    level = 2;
                }
                else if (currMenu == 2){
                    level = 3;
                }
            break;
        }
        if (currMenu < 0) currMenu = 0;
        if (currMenu > 3) currMenu = 3;
    }
}
void showMenu(){
    while (!exxit){
        system("cls");
         for(int i=0; i<MENUPOINTS-1; i++){
                cout<<MenuText[i];
         }
        gotoxy(0, currMenu);
        ch = _getch();
        if (ch == 224){
            ch = _getch();
        }
        switch(ch){
            case 27: exxit = true;   break;
            case 72: currMenu--;    break;
            case 80: currMenu++;    break;
            case 13:
                system("cls");
                if (currMenu == 0){
                    cout << "idet igra" << endl;
                }
                else if (currMenu == 1){
                    cout << "gg" << endl;
                    setLevel();
                    exxit = false;
                }
                else if (currMenu == 2){
                    cout << "plaki-plaki" << endl;
                }
            break;
        }
        if (currMenu < 0) currMenu = 0;
        if (currMenu > 3) currMenu = 3;
    }
}




bool isRunning = true;
int main(){
    int n;
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int time = clock();
    int choice;
    showMenu();
    cin>>n;

    return 0;
}
