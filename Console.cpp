#include "Console.h"





Console::Console()
{
    this->pos_Usr.x = 0;
    this->pos_Usr.y = 24;
    this->pos_Info.x = 0;
    this->pos_Info.y = 0;
    this->width = 50;
    this->height = 10;
}

Console::~Console()
{
}

void Console::LoginShow(int width,int height)
{
    this->Set_WinSize(width, height);
    std::cout << "    欢迎来到多人聊天室    " << std::endl;
}

void Console::ChatShow(int width, int height)
{
    this->Set_WinSize(width, height);
    this->SetXY(pos_Usr.x, pos_Usr.y-1);
    std::cout << std::string(70, '-') << std::endl;
    std::cout << " >> ";
    pos_Usr.x += 4;
}

void Console::Set_WinSize(int width, int height)
{
    std::string cmd = "mode con cols=" + std::to_string(width) + " lines=" + std::to_string(height);
    system(cmd.c_str());
}
// 设置光标位置
void Console::SetXY(int x, int y)
{
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
// 获取当前光标位置
void Console::GetCurXY(POINT& pos)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    pos.x = csbi.dwCursorPosition.X;
    pos.y = csbi.dwCursorPosition.Y;
    return;
}
