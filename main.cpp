#include "Pro.hpp"

int main()
{
    // Początkowe wyczyszczenie ekranu
    io::Cls();

    // Deklaracja i przygotowanie zmiennych
    char code;
    int scale;
    COORD consoleSize = io::GetConsoleSize();
    COORD pos = { static_cast<short>(consoleSize.X / 2), static_cast<short>(consoleSize.Y / 2) };

    // Instrukcja
    pro::PrintInfo();

    // Wprowadzenie znaku ASCII do rysowania figury
    pro::InputCode(code);

    // Wprowadzenie początkowego rozmiaru figury
    pro::InputScale(scale, pos, consoleSize);

    // Schowanie kursora
    io::SetCursorVisibility(false);

    // Ustawianie pozycji startowej
    io::GotoXY(pos.X, pos.Y);

    // Początkowe narysowanie figury
    pro::DrawShape(code, scale, pos.X, pos.Y);

    // Pętla główna
    pro::MainLoop(code, scale, pos, consoleSize);

    return 0;
}
