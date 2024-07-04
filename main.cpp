#include <iostream>
#include <Windows.h>
#include <string>



using namespace std;


void ClearScreen()
  {
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

// void gotoxy(int x, int y) { 
//     COORD pos = {x, y};
//     HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
//     SetConsoleCursorPosition(output, pos);
// }

const int WIDTH = 10;
const int HEIGHT = 10;
const int MENUPOINTS = 5;
const int SIZE = 12;

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


void menu(){
    ClearScreen();
    for(int i=0; i<MENUPOINTS-1; i++){
        cout<<MenuText[i];
    }
    cout<<MenuText[MENUPOINTS-1]<<level<<"\n";
}

void choiceLevel(){
    int lev;
    cin>>lev;
    level = lev;
}



bool isRunning = true;
int main(){
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int time = clock();
    int choice;
    // menu();
    while(isRunning){
        menu();
        cin>>choice;
    }
    //     cout<<"1";}
    //     for(int x =0; x < WIDTH; x++){
    //         cout<<Map[x];
    //     }
    // }
    return 0;
}