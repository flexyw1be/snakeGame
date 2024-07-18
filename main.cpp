#include <iostream> //подключение библиотек
#include <windows.h>
#include <string>
#include <conio.h>
#include <stdlib.h>
#include <fstream>
using namespace std;

ifstream fin; //подключаем модуль для работы с файлами

//БЛОК ОБЪЯВЛЕНИЯ ГЛОБАЛЬНЫХ ПЕРЕМЕННЫХ

//Объявление констант
const int WIDTH = 23; //ширина игрового поля
const int HEIGHT = 22; //высота игрового поля
const int MENUPOINTS = 5; //кол-во пунктов в меню
const int MAX_LEN_SNAKE = (WIDTH - 3) * (HEIGHT -2); //максимальная длина змейки
//переменные, отвечающие за направление движения
const int UP = 0;
const int DOWN = 1;
const int LEFT = 2;
const int RIGHT = 3;


bool isRunning = true; //переменная для работы игрового цикла
bool exxit = false; //переменная для работы цикла меню

// целочисленные переменные
int coef; //коэффицент для увеличения скорости змейки
int currMenu = 0; //переменная для выбора пункта меню
int ch = 0; //переменная дла запоминания нажатия клавиатуры
int diff = 4; //сложность игры
int easy_r = 0; //рекорд в легком режиме
int hard_r= 0; //рекорд в среднем режиме
int insane_r=0; //рекорд в сложнос режиме
int bestScore; //лучший результат в выбранном режиме

HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE); //номер потока для буфера консоли в системе,

string selectMap = "1 map"; //текущая карта

string Map[] = { //массив строк - карта игрового поля
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

string Logo = { //лого игры
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

string MenuText[] = { //массив строк - пункты меня
    "New game\n",
    "Choose difficulty\n",
    "Choose map\n",
    "Records\n",
    "Exit\n"
};

string LevelsText[] = { //массив строк - меню выбора сложности
    "easy\n",
    "hard\n",
    "insane\n"
};

string MapsText[] = { //массив строк - меню выбора карты
    "1 map\n",
    "2 map\n",
    "3 map\n"
};

//БЛОК ОПИСАНИЯ ФУНКЦИЙ

void ClearScreen(){ //функция очищения консоли
    DWORD n;
    DWORD size;
    COORD coord = {0};
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(h, &csbi);
    size = csbi.dwSize.X * csbi.dwSize.Y;
    FillConsoleOutputCharacter(h, TEXT ( ' ' ), size, coord, &n);
    GetConsoleScreenBufferInfo(h, &csbi);
    FillConsoleOutputAttribute(h, csbi.wAttributes, size, coord, &n);
    SetConsoleCursorPosition(h, coord);
}

void loadRecords(){ //функция загрузки рекордов
    fin.open("records.txt"); //открываем текстовый файл с рекордами
    string str; //инициализируем переменную типа string
    getline(fin, str); //считываем строку с рекордом в легком режиме
    easy_r = stoi(str); //преобразуем в целочисленный вид
    getline(fin, str);//считываем строку с рекордом в среднем режиме
    hard_r = stoi(str);//преобразуем в целочисленный вид
    getline(fin, str);//считываем строку с рекордом в сложном режиме
    insane_r = stoi(str);//преобразуем в целочисленный вид
    fin.close(); //закрываем файл
}

//БЛОК ОПИСАНИЯ КЛАССОВ

class Food{ //класс для описания объекта еды
public:
     int x = 1 + (rand() % (WIDTH - 3)); //случайно задается координата x
     int y = 1 + (rand() % (HEIGHT - 2)); //случайно задается координата y
     char sign = '@'; //символ отрисовки еды на игровом поле
};


class Snake{//класс для описания объекта змеи
public:
    int dir = UP; //направление движения змеи
    char sign = 'o'; //символ отрисовки змеи на игровом поле
    int x[MAX_LEN_SNAKE] = {0}; //массив координат по оси x
    int y[MAX_LEN_SNAKE] = {0}; //массив координат по оси н
    int len = 2; //длина змеи

};


Snake checkKeys(Snake snake){ //функция для считывания нажатий клавиатуры и управления змейкой
    if (GetKeyState('W') & 0x8000){ //считываем нажатие клавиши W
            if(snake.dir != DOWN) { // если это вохможно, то изменяем дивжение
                snake.dir = UP;
            }
        }
        if (GetKeyState('S') & 0x8000){ //считываем нажатие клавиши S
            if(snake.dir != UP) { // если это вохможно, то изменяем дивжение
                snake.dir = DOWN;
            }
        }
        if (GetKeyState('A') & 0x8000){ //считываем нажатие клавиши A
            if(snake.dir != RIGHT) { // если это вохможно, то изменяем дивжение
                snake.dir = LEFT;
            }
        }
        if (GetKeyState('D') & 0x8000){ //считываем нажатие клавиши D
            if(snake.dir != LEFT) { // если это вохможно, то изменяем дивжение
                snake.dir = RIGHT;
            }
        }
    return snake;  // возвращаем объект змеи
}


class Game{ //класс для описания работы игры
public:
    Snake snake; //создание объекта змеи

    void gotoxy(short x, short y){ //функция для переноса курсорв в консоли в точку (x,y)
        SetConsoleCursorPosition(hStdOut, {x, y}); //переносим курсор стандартной функцией
    }

    void showMenu(){ //функция отрисовки меню
        exxit = false;
        while (!exxit){ //основной цикл
            system("cls"); //очистка консоли
            cout<<Logo; //вывод лого
            for (int i = 0; i < MENUPOINTS; i++){ //цикл для вывода пунктов меню
                if(currMenu == i){
                    cout<<"\t\t\t\t>>>\t"<<MenuText[i];
                }
                else {
                    cout<<"\t\t\t\t\t"<<MenuText[i];
                }
            }
            cout<<"\n\t\t____________________________________________________________\n\t\t\t\t\tYour map: "<<selectMap<<endl; //вывод текущих сложности и карты
            cout<<"\t\t\t\t\t\Your Difficulty: "<<LevelsText[diff/2 - 2];

            gotoxy(0, 13 + currMenu); //перемещение курсора в точку (0,13)
            ch = _getch(); // считываем нажатие клавишт
            if (ch == 224) {
                ch = _getch();
            }

            switch (ch){
                case 27: exxit = true;  system("cls");   break; //обработка нажатие клавиши Escape
                case 72: currMenu--;    break; //обработка нажатия стрелки вверх
                case 80: currMenu++;    break; //обработка нажатия стрелки вниз
                case 13:  //обработка нажатия клавиши Enter, вызов соответствующих функций
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
                    if (currMenu == 4){
                        exxit = true;
                    }
                break;
            } //реализация границ меню, чтобы курсор не вышел за граници
            if (currMenu < 0) {
                currMenu = 0;
            }
            if (currMenu > 4) {
                    currMenu = 4;
            }
        }
    }

    void endGame(){ //функция обработки о
        ofstream out;
        exxit = false;
        if (diff == 4 && easy_r < snake.len) {
            easy_r = snake.len;
        }
        if (diff == 6 && hard_r < snake.len) {
            hard_r = snake.len;
        }
        if (diff == 8 && insane_r < snake.len) {
            insane_r = snake.len;
        }
        out.open("records.txt");
        out<<easy_r<<endl<<hard_r<<endl<<insane_r<<endl;

        while (!exxit){
            system("cls");
            cout<<Logo;
            cout<<"\n\n\n\n\t\t\t\t\tYou Lose";
            cout<<"\n\t\t\t\t\tYour score: "<<snake.len;
            ch = _getch();
            if (ch == 224) {
                ch = _getch();
            }
             switch(ch){
                case 13: exxit = true;
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
            for (int i = 0; i < size(MapsText); i++){
                if(currMenu == i) {
                    cout<<"\t\t\t\t>>>\t"<<MapsText[i];
                }
                else {
                    cout<<"\t\t\t\t\t"<<MapsText[i];
                }
            }
            cout<<"\t\t\t\t\tYour map: "<<selectMap;
            gotoxy(0, currMenu);
            ch = _getch();
            if (ch == 224) {
                ch = _getch();
            }
            switch (ch){
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
            if (currMenu < 0) {
                currMenu = 0;
            }
            if (currMenu > size(MapsText) - 1) {
                currMenu = size(MapsText) - 1;
            }
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
            for (int i = 0; i < size(LevelsText); i++){
                if (currMenu == i) {
                    cout<<"\t\t\t\t>>>\t"<<LevelsText[i];
                }
                else {
                    cout<<"\t\t\t\t\t"<<LevelsText[i];
                }
            }
            cout<<"\t\t\t\t\tYour Difficulty: "<<LevelsText[diff/2 - 2];

            gotoxy(0, currMenu);
            ch = _getch();
            if (ch == 224) {
                ch = _getch();
            }
            switch (ch){
                case 27: exxit = true;   break;
                case 72: currMenu--;    break;
                case 80: currMenu++;    break;
                case 13:
                    exxit = true;
                    system("cls");
                    if (currMenu == 0){
                        diff = 4;
                        bestScore = easy_r;
                    }
                    if (currMenu == 1){
                        diff = 6;
                        bestScore = hard_r;
                    }
                    if (currMenu == 2){
                        diff = 8;
                        bestScore = insane_r;
                    }
                break;
            }
            if (currMenu < 0) {
                currMenu = 0;
            }
            if (currMenu > 2) {
                currMenu = 2;
            }
        }
        exxit = false;
        currMenu = 0;

    }

    void run(){
        loadMap();
        snake.x[0] = WIDTH/4;
        snake.y[0] = HEIGHT/4;
        int time = clock();
        coef = (snake.len - 2) /5;
        Food food;

        while(isRunning){
            gotoxy(0, 0);
            snake = checkKeys(snake);
            if (snake.x[0] == food.x && snake.y[0] == food.y){
                food.x = 1 + (rand()%(WIDTH-3));
                food.y = 1 + (rand()%(HEIGHT-2));
                snake.len++;
            }
            if ((snake.len - 2) /5 > coef){
                diff += 1;
                coef += 1;
            }

            if (Map[snake.y[0]][snake.x[0]] != ' ') {
                isRunning = false;
                cout<<1;
            }
            if ((clock() - time)* diff / CLOCKS_PER_SEC >= 1){
                time = clock();
                if (snake.dir == UP) --snake.y[0];
                if (snake.dir == DOWN) ++snake.y[0];
                if (snake.dir == LEFT) --snake.x[0];
                if (snake.dir == RIGHT) ++snake.x[0];
                if (snake.x[0] == WIDTH-1) snake.x[0] = 0;
                if (snake.x[0] == -1) snake.x[0] = WIDTH-2;
                if (snake.y[0] == HEIGHT) snake.y[0] = 0;
                if (snake.y[0] == -1) snake.y[0] = HEIGHT-1;

                for (int i = 2; i<snake.len; i++){
                    if(snake.x[0] == snake.x[i] && snake.y[0] == snake.y[i]) isRunning = false;
                }

                Map[food.y][food.x] = food.sign;
                if (Map[snake.y[0]][snake.x[0]] != ' ' && Map[snake.y[0]][snake.x[0]] != food.sign) {
                    isRunning = false;
                }

                for (int i = snake.len; i>= 0; i--){
                    snake.x[i+1] = snake.x[i];
                    snake.y[i+1] = snake.y[i];
                }
                cout<<Logo;
                for (int i = 0; i < snake.len; i++) {
                    Map[snake.y[i]][snake.x[i]] = snake.sign;
                }

                Map[snake.y[0]][snake.x[0]] = '0';
                for (int i = 0; i < HEIGHT; i++) {
                    cout<<"\t\t\t\t"<<Map[i];
                }
                cout<<"\t\t\t\t\tScore: "<<snake.len - 1<<endl;
                cout<<"\t\t\t\t\tBestScore: "<<bestScore<<endl;


                for (int i = 0; i < snake.len; i++) {
                    Map[snake.y[i]][snake.x[i]] = ' ';
                }

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
            if (ch == 224) {
                ch = _getch();
            }
            switch (ch){
                case 13: exxit = true;
            }
        }
        exxit = false;
    }

    void loadMap(){
        string str;
        for (int i = 0; i < HEIGHT; i++){
            getline(fin, str);
            Map[i] = str + '\n';
        }
    }


};


int main(){
    HWND hwnd;
    char Title[1024];
    GetConsoleTitle(Title, 1024);
    hwnd = FindWindow(NULL, Title);
    SetConsoleTextAttribute(hwnd,FOREGROUND_GREEN | FOREGROUND_INTENSITY );
    MoveWindow(hwnd,0,0,800,700,TRUE);
    HANDLE console_color;
    srand((unsigned int)time(NULL));
    console_color = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console_color, 6);
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    system("color 8E");

    loadRecords();
    fin.open("map1.txt");
    bestScore = easy_r;
    Game game;
    game.showMenu();

    return 0;
}
