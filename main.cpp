#include <iostream>
#include <windows.h>
#include <string>
#include <conio.h>
#include <stdlib.h>
#include <fstream>
using namespace std;



ifstream fin;
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

char snake = 'o';
int snake_x[MAX_LEN_SNAKE] = {0};
int snake_y[MAX_LEN_SNAKE] = {0};
int snake_len = 2;

int level = 1;
bool exxit = false;
int currMenu = 0;
int ch = 0;
HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
string Map[] = {
"######################\n",
"|                    |\n",
"|                    |\n",
"|                    |\n",
"|                    |\n",
"|                    |\n",
"|                    |\n",
"|                    |\n",
"|                    |\n",
"|                    |\n",
"|                    |\n",
"|                    |\n",
"|                    |\n",
"|                    |\n",
"|                    |\n",
"|                    |\n",
"|                    |\n",
"|                    |\n",
"|                    |\n",
"|                    |\n",
"|                    |\n",
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

void loadMap(){
    string str;
    for(int i = 0; i < HEIGHT; i++){
        getline(fin, str);
        Map[i] = str + '\n';
    }
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
                    fin.close();
                    fin.open("map1.txt");
                }
                else if (currMenu == 1){
                    level = 2;
                    fin.close();
                    fin.open("map2.txt");
                }
                else if (currMenu == 2){
                    level = 3;
                    fin.close();
                    fin.open("map3.txt");
                }
            break;
        }
        if (currMenu < 0) currMenu = 0;
        if (currMenu > 3) currMenu = 3;
    }
}

void checkKeys(){
    if (GetKeyState('W') & 0x8000){
            if(snake_dir != DOWN) snake_dir = UP;
        }
        if (GetKeyState('S') & 0x8000){
            if(snake_dir != UP) snake_dir = DOWN;
        }
        if (GetKeyState('A') & 0x8000){
            if(snake_dir != RIGHT) snake_dir = LEFT;
        }
        if (GetKeyState('D') & 0x8000){
            if(snake_dir != LEFT) snake_dir = RIGHT;
        }
}

void game(){
    loadMap();
    snake_x[0] = WIDTH/2;
    snake_y[0] = HEIGHT/2;
    srand((unsigned int)time(NULL));
    int time = clock();
    int food_x = 1 + (rand()%(WIDTH-3));
    int food_y = 1 + (rand()%(HEIGHT-2));
    char food = '*';

    while(isRunning){
        gotoxy(0, 0);
        checkKeys();
        if(snake_x[0] == food_x && snake_y[0] == food_y){
            food_x = 1 + (rand()%(WIDTH-3));
            food_y = 1 + (rand()%(HEIGHT-2));
            snake_len++;
        }
        if(Map[snake_y[0]][snake_x[0]] != ' '){isRunning = false;cout<<1;}
        if((clock() - time)* 4 / CLOCKS_PER_SEC >= 1){
            time = clock();
            if(snake_dir == UP) --snake_y[0];
            if(snake_dir == DOWN) ++snake_y[0];
            if(snake_dir == LEFT) --snake_x[0];
            if(snake_dir == RIGHT) ++snake_x[0];
            if(snake_x[0] == 0 || snake_x[0] == WIDTH-2 || snake_y[0] == 0 || snake_y[0] == HEIGHT-1) isRunning = false;

            Map[food_y][food_x] = food;

            for(int i = snake_len-2; i>= 0; i--){
                snake_x[i+1] = snake_x[i];
                snake_y[i+1] = snake_y[i];
            }

            for(int i = 0; i < snake_len; i++) Map[snake_y[i]][snake_x[i]] = snake;
            Map[snake_y[0]][snake_x[0]] = '0';

            for(int i = 0; i < HEIGHT; i++) cout<<Map[i];
            cout<<"Lenght: "<<snake_len -1 ;

            for(int i = 0; i < snake_len; i++) Map[snake_y[i]][snake_x[i]] = ' ';

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
    GetConsoleTitle(Title, 1024);
    hwnd=FindWindow(NULL, Title);
    MoveWindow(hwnd,0,0,500,500,TRUE);
    HANDLE console_color;

    console_color = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console_color, 6);
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    fin.open("map1.txt");



    showMenu();
    return 0;
}
