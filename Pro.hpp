#ifndef _PRO_HEADER
#define _PRO_HEADER

#include <iostream>
#include <Windows.h>

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
    bool IsKeyPressed(Key key);

    // Funkcja do chowania kursora
    void SetCursorVisibility(bool flag);

    // Pozyskiwanie rozmiaru bufera konsoli
    COORD GetConsoleSize();

    // Zmiana pozycji kursora
    void GotoXY(short x, short y);

    // Czyszczenie konsoli
    void Cls();
}

// Pomocna przestrzeń nazw dla projektu
namespace pro
{
    // Wprowadzenie znaku ASCII do rysowania figury
    void InputCode(char& code);

    // Wprowadzenie początkowego rozmiaru figury
    void InputScale(int& scale, COORD pos, COORD consoleSize);

    // Funkcja rysująca figurę w konsoli
    void DrawShape(char code, int scale, int posX, int posY);

    // Funckja sprawdzająca czy da się przesunąć lub powiększyć figurę
    bool IsValidAction(int scale, short x, short y, COORD consoleSize);

    // Wyświetlenie instrukcji
    void PrintInfo();

    // Główna pętla programu
    void MainLoop(char code, int scale, COORD pos, COORD consoleSize);
}

#endif
