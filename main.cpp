#include <iostream>
#include <windows.h>
#include <string>
#include <conio.h>
#include <stdlib.h>
using namespace std;



//INITIALIZING VARIABLES
bool isRunning = true;
const int WIDTH = 23;
const int HEIGHT = 22;
const int MENUPOINTS = 5;
const int MAX_LEN_SNAKE = (WIDTH - 3) * (HEIGHT -2);

const int UP = 0;
const int DOWN = 1;
const int LEFT = 2;
const int RIGHT = 3;

int snake_dir = UP;

char snake = '0';
int snake_x[MAX_LEN_SNAKE] = {0};
int snake_y[MAX_LEN_SNAKE] = {0};
int snake_len = 1;

int level = 1;
bool exxit = false;
int currMenu = 0;
int ch = 0;
HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

string Map[] = {
"######################\n",
"#                    #\n",
"#                    #\n",
"#                    #\n",
"#                    #\n",
"#                    #\n",
"#                    #\n",
"#                    #\n",
"#                    #\n",
"#                    #\n",
"#                    #\n",
"#                    #\n",
"#                    #\n",
"#                    #\n",
"#                    #\n",
"#                    #\n",
"#                    #\n",
"#                    #\n",
"#                    #\n",
"#                    #\n",
"#                    #\n",
"######################\n"
};

string MenuText[] = {
    "New game\n",
    "Choice level\n",
    "Records\n",
    "Exit\n"
};

string LevelsText[] = {
    "1\n",
    "2\n",
    "3\n"
};



//BASIC FUNCTIONS
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


void gotoxy(short x, short y){
    SetConsoleCursorPosition(hStdOut, {x, y});
}


void getRecords(){
    exxit = false;
     while (!exxit){
        system("cls");
        cout<<"Your records could be here";
        ch = _getch();
        if (ch == 224){
            ch = _getch();
        }
        switch(ch){
            case 13: exxit = true;
            case 27: exxit = true;   break;
            }

        }
}


void setLevel(){
    exxit = false;
    currMenu = 0;
    while (!exxit){
        system("cls");
        for(int i=0; i<size(LevelsText); i++){
                cout<<LevelsText[i];
        }
        cout<<"Your level: "<<level;

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


void game(){
    snake_x[0] = WIDTH/2;
    snake_y[0] = HEIGHT/2;
    while(isRunning){
        gotoxy(0, 0);
        for(int i = 0; i < snake_len; i++){
            Map[snake_y[i]][snake_x[i]] = snake;
        }
        for(int i = 0; i < HEIGHT; i++){
            cout<<Map[i];
        }
    }
}


void showMenu(){
    while (!exxit){
        system("cls");
         for(int i=0; i<MENUPOINTS-1; i++){
                cout<<MenuText[i];
        }
        cout<<"Your level: "<<level;

        gotoxy(0, currMenu);
        ch = _getch();
        if (ch == 224){
            ch = _getch();
        }
        switch(ch){
            case 27: exxit = true;  system("cls");   break;
            case 72: currMenu--;    break;
            case 80: currMenu++;    break;
            case 13:
                system("cls");
                if (currMenu == 0){
                    cout << "idet igra" << endl;
                    game();
                }
                else if (currMenu == 1){
                    cout << "gg" << endl;
                    setLevel();
                    exxit = false;
                }
                else if (currMenu == 2){
                    getRecords();
                    exxit = false;
                }
                else if (currMenu == 3){
                    exxit = true;
                }
            break;
        }
        if (currMenu < 0) currMenu = 0;
        if (currMenu > 3) currMenu = 3;
    }
}




int main(){
    HWND hwnd;
    char Title[1024];
    GetConsoleTitle(Title, 1024); // Узнаем имя окна
    hwnd=FindWindow(NULL, Title); // Узнаем hwnd окна
    MoveWindow(hwnd,0,0,500,500,TRUE);//xnew,ynew,wnew,hnew -новые положение x,y, ширина и высота
    HANDLE console_color;
    console_color = GetStdHandle(
        STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(
            console_color, 6);
    int n;
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int time = clock();
    int choice;
    showMenu();
    return 0;
}
