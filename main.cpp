#include <bits/stdc++.h>
#include <Windows.h>



using namespace std;


void gotoxy(int x, int y) { 
    COORD pos = {x, y};
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(output, pos);
}

const int WIDTH = 10;
const int HEIGHT = 10;


char map[] = "##########\n"
"#         #\n"
"#         #\n"
"#         #\n"
"#         #\n"
"#         #\n"
"#         #\n"
"#         #\n"
"#         #\n"
"###########\n";


bool isRunning = true;
int main(){
    int time = clock();

    // while(isRunning){
    //     cout<<"1";
    // }
    cout<<"1";
    return 0;
}