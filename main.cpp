#include <bits/stdc++.h>
#include <Windows.h>



using namespace std;


// void gotoxy(int x, int y) { 
//     COORD pos = {x, y};
//     HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
//     SetConsoleCursorPosition(output, pos);
// }

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
    "Новая игра\n",
    "Выбрать сложность\n",
    "Рекорды\n",
    "Выход\n",
    "Уровень: "
};


void menu(){
    for(int i=0; i<MENUPOINTS; i++){
        cout<<MenuText[i];
    }
}



bool isRunning = true;
int main(){
    setlocale(0, ""); 
    int time = clock();
    menu();
    // while(isRunning){
    //     cout<<"1";
    //     for(int x =0; x < WIDTH; x++){
    //         cout<<Map[x];
    //     }
    // }
    return 0;
}