#ifndef _PRO_HEADER
#define _PRO_HEADER

#include <iostream>
#include <windows.h>

// Pomocna przestrzeń nazw dla obsługi konsoli
namespace io
{

// Alias dla define'ów Windowsa
enum Key
{
    Up = VK_UP,
    Right = VK_RIGHT,
    Left = VK_LEFT,
    Down = VK_DOWN,
    Plus = VK_ADD,
    Minus = VK_SUBTRACT,
    Escape = VK_ESCAPE
};

// Odczyt stanu danego klawisza z klawiatury
bool IsKeyPressed(Key _Key);

// Funkcja do chowania kursora
void SetCursorVisibility(bool _Flag);

// Pozyskiwanie rozmiaru bufera konsoli
COORD GetConsoleSize();

// Zmiana pozycji kursora
void GotoXY(short _X, short _Y);

// Czyszczenie konsoli
void Cls();

}

// Pomocna przestrzeń nazw dla projektu
namespace pro
{

// Wprowadzenie znaku ASCII do rysowania figury
void InputCode(char& _Code);

// Wprowadzenie początkowego rozmiaru figury
void InputScale(int& _Scale, COORD _Pos, COORD _ConsoleSize);

// Funkcja rysująca figurę w konsoli
void DrawShape(char _Code, int _Scale, int _PosX, int _PosY);

// Funckja sprawdzająca czy da się przesunąć lub powiększyć figurę
bool IsValidAction(int _Scale, short _X, short _Y, COORD _ConsoleSize);

// Wyświetlenie instrukcji
void PrintInfo();

// Główna pętla programu
void MainLoop(char _Code, int _Scale, COORD _Pos, COORD _ConsoleSize);

}

#endif
