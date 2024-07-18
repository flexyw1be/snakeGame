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
const int MENUPOINTS = 6; //кол-во пунктов в меню
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
    "Authors\n",
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

    void showMenu(){ //метод отрисовки меню
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
                        authors();
                    }
                    if (currMenu == 5){
                        exxit = true;
                    }
                break;
            } //обработка границ меню, чтобы курсор не вышел за границы
            if (currMenu < 0) {
                currMenu = 0;
            }
            if (currMenu > 5) {
                currMenu = 5;
            }
        }
    }

    void endGame(){ //метод обработки конца игры
        ofstream out; //подключаем модуль для записи в файл
        exxit = false; //изменяем переменну окончания игры
        if (diff == 4 && easy_r < snake.len) { //проверяем, не побил ли игрок рекорд
            easy_r = snake.len;
        }
        if (diff == 6 && hard_r < snake.len) {
            hard_r = snake.len;
        }
        if (diff == 8 && insane_r < snake.len) {
            insane_r = snake.len;
        }
        out.open("records.txt"); //открываем файл records.txt
        out<<easy_r<<endl<<hard_r<<endl<<insane_r<<endl; //записываем рекорды в файл

        while (!exxit){ //цикл для вывода информации
            system("cls"); //очистка консоли
            cout<<Logo; //вывод лого и основной информации
            cout<<"\n\n\n\n\t\t\t\t\t  GAME OVER";
            cout<<"\n\n\n\t\t\t\t\tYour score: "<<snake.len;
            cout<<"\n\t\t\t\t\tBest score: "<<bestScore;
            ch = _getch(); //считываем нажатия с клаивтуры
            if (ch == 224) {
                ch = _getch();
            }
             switch(ch){ //закрываем окно, если нажаты Space или Escape
                case 27: exxit = true;
                case 13: exxit = true;
            }
        }
        exxit = false;
    }

    void setMap(){ //метод выбора игровой карты
        exxit = false; //изменяем переменну окончания игры
        currMenu = 0; //по умолчанию выбираем 1 карту
        while (!exxit){  //цикл для вывода информации
            system("cls"); //очистка консоли
            cout<<Logo; //вывод основной информации
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
            gotoxy(0, currMenu); //перемещаем курсор к выбранному пункту
            ch = _getch(); //считываем нажатия с клаивтуры
            if (ch == 224) {
                ch = _getch();
            }
            switch (ch){ //обработка нажатий клавиш и выбора соответствующей карты
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
            } //обработка границ меню, курсор не должен выходить за эти границы
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

    void setDifficulty(){ //метод выбора сложности
        exxit = false; //изменяем переменну окончания игры
        currMenu = 0; //по умолчанию выбираем легкую сложность
        while (!exxit){ //цикл для вывода информации
            system("cls"); //очистка консоли
            cout<<Logo; //вывод информации
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

            gotoxy(0, currMenu); //перемещаем курсор в нужную позицию
            ch = _getch(); //считываем нажатия с клаивтуры
            if (ch == 224) {
                ch = _getch();
            }
            switch (ch){ //обработка нажатий клавиш клавиатуры, выбираем нужную сложность
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
            } //обработка границ меню, курсор не должен выходить за эти границы
            if (currMenu < 0) {
                currMenu = 0;
            }
            if (currMenu > 2) {
                currMenu = 2;
            }
        }
        exxit = false; //изменяем переменну окончания игры
        currMenu = 0; //присваиваем переменной значение по умолчанию

    }

    void run(){ //основной игровой метод
        loadMap(); //загружаем игровую карту
        snake.x[0] = WIDTH/4; //прасваиваем голове змеи начальное занчение
        snake.y[0] = HEIGHT/4;
        int time = clock(); //создаем переменную, чтобы отрисовывать картинку с каким-то периодом
        coef = (snake.len - 2) /5; // переменная, для увеличивания скорости змеи
        Food food; // создаем экзмепляр класса Food

        while (isRunning){ //основной игровой цикл
            gotoxy(0, 0); //переносим курсор в точку (0,0)
            snake = checkKeys(snake); //проверяем нажатия для управления змейкой
            if (snake.x[0] == food.x && snake.y[0] == food.y){ //проверяем, съела ли змея еду
                food.x = 1 + (rand()%(WIDTH-3));
                food.y = 1 + (rand()%(HEIGHT-2));
                snake.len++;
            }
            if ((snake.len - 2) /5 > coef){ //проверяем, нужно ли увеличивать скорость
                diff += 1;
                coef += 1;
            }

            if (Map[snake.y[0]][snake.x[0]] != ' ') { //проверяем, не наткнулась ли змейка на препятствие
                isRunning = false;
            }
            if ((clock() - time)* diff / CLOCKS_PER_SEC >= 1){ //цикл отрисовки картинки
                time = clock();
                if (snake.dir == UP) { //двигаем змейку в соответствующем направлении
                    --snake.y[0];
                }
                if (snake.dir == DOWN) {
                    ++snake.y[0];
                }
                if (snake.dir == LEFT) {
                    --snake.x[0];
                }
                if (snake.dir == RIGHT) {
                    ++snake.x[0];
                }
                if (snake.x[0] == WIDTH-1) {//проверка выхода за края карты
                    snake.x[0] = 0;
                }
                if (snake.x[0] == -1) {
                    snake.x[0] = WIDTH-2;
                }
                if (snake.y[0] == HEIGHT) {
                    snake.y[0] = 0;
                }
                if (snake.y[0] == -1) {
                    snake.y[0] = HEIGHT-1;
                }

                for (int i = 2; i<snake.len; i++){ //проверка, не наткнулась ли змейка сама на себя
                    if(snake.x[0] == snake.x[i] && snake.y[0] == snake.y[i]) {
                        isRunning = false;
                    }
                }

                Map[food.y][food.x] = food.sign; //отрисовываем еду
                if (Map[snake.y[0]][snake.x[0]] != ' ' && Map[snake.y[0]][snake.x[0]] != food.sign) {  //проверяем, не наткнулась ли змейка на препятствие
                    isRunning = false;
                }

                for (int i = snake.len; i>= 0; i--){  //двигаем змею
                    snake.x[i+1] = snake.x[i];
                    snake.y[i+1] = snake.y[i];
                }
                cout<<Logo; //выводим логотип змеи
                for (int i = 0; i < snake.len; i++) {  //отрисовываем змейку
                    Map[snake.y[i]][snake.x[i]] = snake.sign;
                }

                Map[snake.y[0]][snake.x[0]] = '0'; //отрисовка карты
                for (int i = 0; i < HEIGHT; i++) {
                    cout<<"\t\t\t\t"<<Map[i];
                }

                                for (int i = 0; i < snake.len; i++) {
                    Map[snake.y[i]][snake.x[i]] = ' ';
                }
                cout<<"\t\t\t\t\tScore: "<<snake.len - 1<<endl; //отрисовка HUD
                cout<<"\t\t\t\t\tBestScore: "<<bestScore<<endl;

            }
        }
        endGame(); //выводим окно конца игры
        isRunning = true; //задаем начальное значение основным переменным
        fin.close();
        fin.open("map1.txt");
        snake.len = 2;
    }

    void getRecords(){ //метод для получения рекордов
        exxit = false; //изменяем переменну закртытия окна
        while (!exxit){ //цикл вывода информации
            system("cls"); //очистка консоли
            cout<<Logo; //вывод информации
            cout<<"\t\t\t\t\tRecords";
            cout<<"\n\t\t\t\t\tEasy mode: "<<easy_r;
            cout<<"\n\t\t\t\t\tHard mode: "<<hard_r;
            cout<<"\n\t\t\t\t\tInsane mode: "<<insane_r;
            ch = _getch(); //считываем нажатие клавиатуры
            if (ch == 224) {
                ch = _getch();
            }
            switch (ch){ //закрываем окно, если нажаты Space или Escape
                case 27: exxit = true;
                case 13: exxit = true;
            }
        }
        exxit = false; //изменяем переменную закрытия окна
    }

    void loadMap(){ //метод загрузки карты
        string str; //строковая переменная для текущей строчки карты
        for (int i = 0; i < HEIGHT; i++){ //цикл для закгрузки карты
            getline(fin, str); //считываем i-ую строку карты в переменную str
            Map[i] = str + '\n'; //записываем строку в массив Map
        }
    }

    void authors(){ //метод для отображения авторов игры
        exxit = false; //изменяем переменну закртытия окна
        while (!exxit){ //цикл вывода информации
            system("cls"); //очистка консоли
            cout<<Logo; //вывод информации
            cout<<"\t\t\t\t\tGame Crated By\n\n";
            cout<<"\t\t\t\t\t  @flexyw1be\n\t\t\t\t\t  @vladbily";
            cout<<"\n\n\n\t\t\t\t\t    2024";
            ch = _getch(); //считываем нажатие клавиатуры
            if (ch == 224) {
                ch = _getch();
            }
            switch (ch){ //закрываем окно, если нажаты Space или Escape
                case 27: exxit = true;
                case 13: exxit = true;
            }
        }
        exxit = false; //изменяем переменную закрытия окна
    }


};


int main(){ //основная функция программы
    HWND hwnd;
    char Title[1024];
    GetConsoleTitle(Title, 1024);
    hwnd = FindWindow(NULL, Title); //задаем размеры окна консоли
    SetConsoleTextAttribute(hwnd,FOREGROUND_GREEN | FOREGROUND_INTENSITY );
    MoveWindow(hwnd,0,0,800,700,TRUE);
    HANDLE console_color;
    srand((unsigned int)time(NULL)); //инициализируем rand()
    console_color = GetStdHandle(STD_OUTPUT_HANDLE); //меняем цвет консоли и цвет текста
    SetConsoleTextAttribute(console_color, 6);
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    system("color 8E");

    loadRecords(); //загружаем рекорды
    fin.open("map1.txt"); //открываем карту по умолчанию
    bestScore = easy_r; //получаем рекорд в соответствующем режиме
    Game game; //создаем экземпляр класса Game
    game.showMenu(); //используем метод showMenu
    return 0;
}
