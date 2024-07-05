#include <iostream>
#include <Windows.h>
#include <string>
#include <conio.h>
using namespace std;


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

bool exxit = false;
int currMenu = 0;
int ch = 0;
HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
string a = "New Game ";
string b = "Choice level ";
string c = "Records ";
string d = "Exit ";


void gotoxy(short x, short y)
{
    SetConsoleCursorPosition(hStdOut, {x, y});
}

void showMenu(){
    while (!exxit){
        cout << a << endl;
        cout << b << endl;
        cout << c << endl;
        cout << d << endl;

        gotoxy(0, currMenu-1);

        ch = _getch();
        if (ch == 224){
            ch = _getch();
        }
        switch(ch){
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
string MenuText[] = {
    "1> New game\n",
    "2> Choice level\n",
    "3> Records\n",
    "4> Exit\n",
    "Your level: "};
int level = 1;


// void menu(){
//     ClearScreen();
//     for(int i=0; i<MENUPOINTS-1; i++){
//         cout<<MenuText[i];
//     }
//     cout<<MenuText[MENUPOINTS-1]<<level<<"\n";
// }

// void choiceLevel(){
//     int lev;
//     cin>>lev;
//     level = lev;
// }



bool isRunning = true;
int main(){
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int time = clock();
    int choice;
    showMenu();
    // menu();
    // while(isRunning){
    //     showMenu();
    // }
    //     cout<<"1";}
    //     for(int x =0; x < WIDTH; x++){
    //         cout<<Map[x];
    //     }
    // }
    return 0;
}