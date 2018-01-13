#include "Pro.hpp"

int main()
{
    // Początkowe wyczyszczenie ekranu
    io::Cls();

    // Deklaracja i przygotowanie zmiennych
    char Code;
    int Scale;
    COORD ConsoleSize = io::GetConsoleSize();
    COORD Pos;
    Pos.X = ConsoleSize.X / 2;
    Pos.Y = ConsoleSize.Y / 2;

    // Instrukcja
    pro::PrintInfo();

    // Wprowadzenie znaku ASCII do rysowania figury
    pro::InputCode(Code);

    // Wprowadzenie początkowego rozmiaru figury
    pro::InputScale(Scale, Pos, ConsoleSize);

    // Schowanie kursora
    io::SetCursorVisibility(false);

    // Ustawianie pozycji startowej
    io::GotoXY(Pos.X, Pos.Y);

    // Początkowe narysowanie figury
    pro::DrawShape(Code, Scale, Pos.X, Pos.Y);

    // Pętla główna
    pro::MainLoop(Code, Scale, Pos, ConsoleSize);

    return 0;
}
