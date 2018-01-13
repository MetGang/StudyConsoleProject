#include "Pro.hpp"

namespace io
{

bool IsKeyPressed(Key _Key)
{
    return (GetAsyncKeyState(_Key) & 0x8000) != 0;
}

void SetCursorVisibility(bool _Flag)
{
    HANDLE Hnd = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO Info;
    GetConsoleCursorInfo(Hnd, &Info);
    Info.bVisible = _Flag;
    SetConsoleCursorInfo(Hnd, &Info);
}

COORD GetConsoleSize()
{
    CONSOLE_SCREEN_BUFFER_INFO Info;
    COORD Size;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
    Size.X = Info.srWindow.Right - Info.srWindow.Left + 1;
    Size.Y = Info.srWindow.Bottom - Info.srWindow.Top + 1;
    return Size;
}

void GotoXY(short _X, short _Y)
{
    COORD Pos;
    Pos.X = _X;
    Pos.Y = _Y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void Cls()
{
    std::system("cls");
}

}

namespace pro
{

void InputCode(char& _Code)
{
    std::cout << "\nPodaj znak do rysowania figury: ";
    std::cin >> _Code;
}

void InputScale(int& _Scale, COORD _Pos, COORD _ConsoleSize)
{
    std::cout << "\nPodaj startowy rozmiar figury: ";

    while(std::cin >> _Scale)
    {
        if(IsValidAction(_Scale, _Pos.X, _Pos.Y, _ConsoleSize)) break;

        std::cout << "Podano nieodpowiedni rozmiar startowy, podaj ponownie: ";
    }
}

void DrawShape(char _Code, int _Scale, int _PosX, int _PosY)
{
    int CopyX = _PosX;
    int CopyY = _PosY;
    _Scale *= 2;

    io::Cls();

    // Rysowanie lewego ramienia
    io::GotoXY(CopyX, CopyY);
    std::cout.put(_Code);
    for(int i = 0; i < _Scale; ++i)
    {
        io::GotoXY(--CopyX, ++CopyY);
        std::cout.put(_Code);
    }
    io::GotoXY(--CopyX, ++CopyY);
    std::cout.put(_Code);
    for(int i = 0; i < _Scale; ++i)
    {
        io::GotoXY(--CopyX, ++CopyY);
        std::cout.put(_Code);
    }

    CopyX = _PosX;
    CopyY = _PosY;

    // Rysowanie prawego ramienia
    io::GotoXY(CopyX, CopyY);
    for(int i = 0; i < _Scale; ++i)
    {
        io::GotoXY(++CopyX, ++CopyY);
        std::cout.put(_Code);
    }
    io::GotoXY(++CopyX, ++CopyY);
    std::cout.put(_Code);
    for(int i = 0; i < _Scale; ++i)
    {
        io::GotoXY(++CopyX, ++CopyY);
        std::cout.put(_Code);
    }

    // Rysowanie "poprzeczki" figury
    CopyX = _PosX - _Scale;
    CopyY = _PosY + _Scale + 1;

    io::GotoXY(CopyX, CopyY);
    for(int i = 0; i < _Scale * 2 + 1; ++i)
    {
        std::cout.put(_Code);
    }
}

bool IsValidAction(int _Scale, short _X, short _Y, COORD _ConsoleSize)
{
    // Sprawdzenie czy figura nie wyjdzie poza granice ekranu
    if(_Scale < 0) return false;

    if(_Y >= 0 &&
       _Y + (_Scale * 4 + 1) < _ConsoleSize.Y &&
       _X - (_Scale * 4) > 0 &&
       _X + (_Scale * 4 + 1) < _ConsoleSize.X) return true;

    return false;
}

void PrintInfo()
{
    std::cout
    << "Klawiszologia\n\n"
    << "Strzalki : Poruszanie figury\n"
    << "+        : Zwiekszenie rozmiaru figury\n"
    << "-        : Zmniejszenie rozmiaru figury\n"
    << "Escape   : Koniec programu\n";
}

void MainLoop(char _Code, int _Scale, COORD _Pos, COORD _ConsoleSize)
{
    while(true)
    {
        // Wyjście
        if(io::IsKeyPressed(io::Escape)) break;

        // Ruch
        if(io::IsKeyPressed(io::Up))
        {
            if(IsValidAction(_Scale, _Pos.X, _Pos.Y - 1, _ConsoleSize))
            {
                DrawShape(_Code, _Scale, _Pos.X, --_Pos.Y);
            }
        }
        else if(io::IsKeyPressed(io::Down))
        {
            if(IsValidAction(_Scale, _Pos.X, _Pos.Y + 1, _ConsoleSize))
            {
                DrawShape(_Code, _Scale, _Pos.X, ++_Pos.Y);
            }
        }
        if(io::IsKeyPressed(io::Left))
        {
            if(IsValidAction(_Scale, _Pos.X - 1, _Pos.Y, _ConsoleSize))
            {
                DrawShape(_Code, _Scale, --_Pos.X, _Pos.Y);
            }
        }
        else if(io::IsKeyPressed(io::Right))
        {
            if(IsValidAction(_Scale, _Pos.X + 1, _Pos.Y, _ConsoleSize))
            {
                DrawShape(_Code, _Scale, ++_Pos.X, _Pos.Y);
            }
        }

        // Skalowanie
        if(io::IsKeyPressed(io::Minus))
        {
            if(_Scale > 1)
            {
                if(IsValidAction(_Scale - 1, _Pos.X, _Pos.Y, _ConsoleSize))
                {
                    DrawShape(_Code, --_Scale, _Pos.X, _Pos.Y);
                }
            }
        }
        else if(io::IsKeyPressed(io::Plus))
        {
            if(IsValidAction(_Scale + 1, _Pos.X, _Pos.Y, _ConsoleSize))
            {
                DrawShape(_Code, ++_Scale, _Pos.X, _Pos.Y);
            }
        }

        // Lekkie spowolnienie pętli żeby ograniczyć wykorzystanie procesora
        Sleep(10);
    }
}

}
