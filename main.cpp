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




int level = 1;
bool exxit = false;
int currMenu = 0;
int ch = 0;
int diff = 4;
int easy_r=0, hard_r= 0, insane_r=0;

HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

string selectMap = "1 map";

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

string Logo = {
"\n\n\t ZZZZZZZZZZZ    ZZZZ    ZZZZ         ZZ         ZZZZ    ZZZZ    ZZZZZZZZZZZZ\n"
"\tZZZZZZZZZZZZ    ZZZZZ   ZZZZ        ZZZZ        ZZZZ   ZZZZ     ZZZZZZZZZZZZ\n"
"\tZZZZ            ZZZZZ   ZZZZ       ZZZZZZ       ZZZZ  ZZZZ      ZZZZ        \n"
"\tZZZZ            ZZZZ Z  ZZZZ      ZZZ  ZZZ      ZZZZ ZZZZ       ZZZZ        \n"
"\tZZZZZZZZZZZ     ZZZZ Z  ZZZZ     ZZZ    ZZZ     ZZZZZZZZ        ZZZZZZZZZZZZ\n"
"\t ZZZZZZZZZZZ    ZZZZ  Z ZZZZ    ZZZ      ZZZ    ZZZZZZZZ        ZZZZZZZZZZZZ\n"
"\t        ZZZZ    ZZZZ  Z ZZZZ    ZZZ      ZZZ    ZZZZ ZZZZ       ZZZZ        \n"
"\t        ZZZZ    ZZZZ   ZZZZZ    ZZZZZZZZZZZZ    ZZZZ  ZZZZ      ZZZZ        \n"
"\tZZZZZZZZZZZZ    ZZZZ   ZZZZZ    ZZ        ZZ    ZZZZ   ZZZZ     ZZZZZZZZZZZZ\n"
"\tZZZZZZZZZZZ     ZZZZ    ZZZZ    ZZ        ZZ    ZZZZ    ZZZZ    ZZZZZZZZZZZZ\n\n\n",
};

string MenuText[] = {
    "New game\n",
    "Choose difficulty\n",
    "Choose map\n",
    "Records\n",
    "Exit\n"
};

string LevelsText[] = {
    "easy\n",
    "hard\n",
    "insane\n"
};

string MapsText[] = {
    "1 map\n",
    "2 map\n",
    "3 map\n"
};


void loadRecords(){
    fin.open("records.txt");
    string str;
    getline(fin, str);
    easy_r =  stoi(str);
    getline(fin, str);
    hard_r =  stoi(str);
    getline(fin, str);
    insane_r =  stoi(str);
    fin.close();
}

class Food{
public:
     int x = 1 + (rand()%(WIDTH-3));
     int y = 1 + (rand()%(HEIGHT-2));
     char sign = 'F';
};


class Snake{
public:
    int dir = UP;
    char sign = 'o';
    int x[MAX_LEN_SNAKE] = {0};
    int y[MAX_LEN_SNAKE] = {0};
    int len = 2;

};


Snake checkKeys(Snake snake){
    if (GetKeyState('W') & 0x8000){
            if(snake.dir != DOWN) snake.dir = UP;
        }
        if (GetKeyState('S') & 0x8000){
            if(snake.dir != UP) snake.dir = DOWN;
        }
        if (GetKeyState('A') & 0x8000){
            if(snake.dir != RIGHT) snake.dir = LEFT;
        }
        if (GetKeyState('D') & 0x8000){
            if(snake.dir != LEFT) snake.dir = RIGHT;
        }
    return snake;
}



class Game{
public:
    Snake snake;

    void gotoxy(short x, short y){SetConsoleCursorPosition(hStdOut, {x, y});}


    void showMenu(){
        exxit = false;
        while (!exxit){
            system("cls");
            cout<<Logo;
            for(int i=0; i<MENUPOINTS; i++){
                if(currMenu == i)cout<<"\t\t\t\t>>>\t"<<MenuText[i];
                else cout<<"\t\t\t\t\t"<<MenuText[i];
            }
            cout<<"\n\t\t____________________________________________________________\n\t\t\t\t\tYour map: "<<selectMap<<endl;
            cout<<"\t\t\t\t\t\Your Difficulty: "<<LevelsText[diff/2 - 2];

            gotoxy(0, 13+currMenu);
            ch = _getch();
            if (ch == 224) ch = _getch();

            switch(ch){
                case 27: exxit = true;  system("cls");   break;
                case 72: currMenu--;    break;
                case 80: currMenu++;    break;
                case 13:
                    system("cls");
                    if (currMenu == 0){
                        run();
                    }
                    if (currMenu == 1){
                            setDifficulty();
                    }
                    if (currMenu == 2){
                        setMap();
                    }
                    if (currMenu == 3){
                        getRecords();
                    }
                break;
            }
        if (currMenu < 0) currMenu = 0;
        if (currMenu > 4) currMenu = 4;
        }
    }

    void endGame(){
        ofstream out;
        exxit = false;
        if(diff == 4 && easy_r < snake.len) easy_r = snake.len;
        if(diff == 6 && hard_r < snake.len) hard_r = snake.len;
        if(diff == 8 && insane_r < snake.len) insane_r = snake.len;
        out.open("records.txt");
        out << easy_r<<endl<<hard_r<<endl<<insane_r;


        while (!exxit){
            system("cls");
            cout<<Logo;
            cout<<"\n\n\n\n\t\t\t\t\tYou Lose";
            cout<<"\n\t\t\t\t\tYour score: "<<snake.len;
            ch = _getch();
            if (ch == 224)ch = _getch();
             switch(ch){
                case 13:
                    exxit = true;
            }
        }
        exxit = false;
    }

    void setMap(){
        exxit = false;
        currMenu = 0;
        while (!exxit){
            system("cls");
            cout<<Logo;
            cout<<"\t\t\t\t\tChoose Your Map\n";
            for(int i=0; i<size(MapsText); i++){
                if(currMenu == i)cout<<"\t\t\t\t>>>\t"<<MapsText[i];
                else cout<<"\t\t\t\t\t"<<MapsText[i];
            }
            cout<<"\t\t\t\t\tYour map: "<<selectMap;
            gotoxy(0, currMenu);
            ch = _getch();
            if (ch == 224)ch = _getch();

            switch(ch){
                case 27: exxit = true;   break;
                case 72: currMenu--;    break;
                case 80: currMenu++;    break;
                case 13:
                    exxit = true;
                    system("cls");
                    if (currMenu == 0){
                        selectMap = "1 map";
                        fin.close();
                        fin.open("map1.txt");
                    }
                    if (currMenu == 1){
                        selectMap = "2 map";
                        fin.close();
                        fin.open("map2.txt");
                    }
                    if (currMenu == 2){
                        selectMap = "3 map";
                        fin.close();
                        fin.open("map3.txt");
                    }
                break;
            }
            if (currMenu < 0) currMenu = 0;
            if (currMenu > size(MapsText)-1) currMenu = size(MapsText)-1;
        }
                exxit = false;
                currMenu = 0;

    }

    void setDifficulty(){
        exxit = false;
        currMenu = 0;
        while (!exxit){
            system("cls");
            cout<<Logo;
            cout<<"\t\t\t\t\tChoose Your Difficulty\n";
            for(int i=0; i<size(LevelsText); i++){
                if(currMenu == i)cout<<"\t\t\t\t>>>\t"<<LevelsText[i];
                else cout<<"\t\t\t\t\t"<<LevelsText[i];
            }
            cout<<"\t\t\t\t\tYour Difficulty: "<<LevelsText[diff/2 - 2];

            gotoxy(0, currMenu);
            ch = _getch();
            if (ch == 224)ch = _getch();

            switch(ch){
                case 27: exxit = true;   break;
                case 72: currMenu--;    break;
                case 80: currMenu++;    break;
                case 13:
                    exxit = true;
                    system("cls");
                    if (currMenu == 0){
                        diff = 4;
                    }
                    if (currMenu == 1){
                        diff = 6;
                    }
                    if (currMenu == 2){
                        diff = 8;
                    }
                break;
            }
            if (currMenu < 0) currMenu = 0;
            if (currMenu > 3) currMenu = 3;
        }
                exxit = false;
                currMenu = 0;

    }

    void run(){
        loadMap();
        snake.x[0] = WIDTH/2;
        snake.y[0] = HEIGHT/2;
        int time = clock();
        Food food;

        while(isRunning){
            gotoxy(0, 0);
            snake = checkKeys(snake);
            if(snake.x[0] == food.x && snake.y[0] == food.y){
                food.x = 1 + (rand()%(WIDTH-3));
                food.y = 1 + (rand()%(HEIGHT-2));
                snake.len++;
            }
            if(snake.x[0] == WIDTH-1) snake.x[0] = 0;
            if(snake.x[0] == 0) snake.x[0] = WIDTH-2;
            if(Map[snake.y[0]][snake.x[0]] != ' '){isRunning = false;cout<<1;}
            if((clock() - time)* diff / CLOCKS_PER_SEC >= 1){
                time = clock();
                if(snake.dir == UP) --snake.y[0];
                if(snake.dir == DOWN) ++snake.y[0];
                if(snake.dir == LEFT) --snake.x[0];
                if(snake.dir == RIGHT) ++snake.x[0];
                if(Map[snake.y[0]][snake.x[0]] != ' ' && Map[snake.y[0]][snake.x[0]] != food.sign) isRunning = false;

                Map[food.y][food.x] = food.sign;

                for(int i = snake.len-2; i>= 0; i--){
                    snake.x[i+1] = snake.x[i];
                    snake.y[i+1] = snake.y[i];
                }

                for(int i = 0; i < snake.len; i++) Map[snake.y[i]][snake.x[i]] = snake.sign;
                Map[snake.y[0]][snake.x[0]] = '0';

                for(int i = 0; i < HEIGHT; i++) cout<<"\t\t\t\t"<<Map[i];
                cout<<"\t\t\t\t\tScore: "<<snake.len -1 ;

                for(int i = 0; i < snake.len; i++) Map[snake.y[i]][snake.x[i]] = ' ';

            }
        }
        endGame();
        isRunning = true;
        fin.close();
        fin.open("map1.txt");
        snake.len = 2;
    }

    void getRecords(){
        exxit = false;
        while (!exxit){
            system("cls");
            cout<<Logo;
            cout<<"\t\t\t\t\tRecords";
            cout<<"\n\t\t\t\t\tEasy mode: "<<easy_r;
            cout<<"\n\t\t\t\t\tHard mode: "<<hard_r;
            cout<<"\n\t\t\t\t\tInsane mode: "<<insane_r;
            ch = _getch();
            if (ch == 224)ch = _getch();
             switch(ch){
                case 13:
                    exxit = true;
            }
        }
        exxit = false;
    }

    void loadMap(){
        string str;
        for(int i = 0; i < HEIGHT; i++){
            getline(fin, str);
            Map[i] = str + '\n';
        }
    }


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


int main(){
    HWND hwnd;
    char Title[1024];
    GetConsoleTitle(Title, 1024);
    hwnd=FindWindow(NULL, Title);
    SetConsoleTextAttribute(hwnd,FOREGROUND_GREEN | FOREGROUND_INTENSITY );
    MoveWindow(hwnd,0,0,1920,1080,TRUE);
    HANDLE console_color;
    srand((unsigned int)time(NULL));
    console_color = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console_color, 6);
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    loadRecords();
    system("color 8E");
    fin.open("map1.txt");
    Game game;
    game.showMenu();

    return 0;
}
