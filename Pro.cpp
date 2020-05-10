#include "Pro.hpp"

namespace io
{
    bool IsKeyPressed(Key key)
    {
        return (GetAsyncKeyState(key) & 0x8000) != 0;
    }

    void SetCursorVisibility(bool flag)
    {
        HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO info;
        GetConsoleCursorInfo(handle, &info);
        info.bVisible = flag;
        SetConsoleCursorInfo(handle, &info);
    }

    COORD GetConsoleSize()
    {
        CONSOLE_SCREEN_BUFFER_INFO info;
        COORD size;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
        size.X = info.srWindow.Right - info.srWindow.Left + 1;
        size.Y = info.srWindow.Bottom - info.srWindow.Top + 1;
        return size;
    }

    void GotoXY(short x, short y)
    {
        COORD pos;
        pos.X = x;
        pos.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    }

    void Cls()
    {
        std::system("cls");
    }
}

namespace pro
{
    void InputCode(char& code)
    {
        std::cout << "\nPodaj znak do rysowania figury: ";
        std::cin >> code;
    }

    void InputScale(int& scale, COORD pos, COORD consoleSize)
    {
        std::cout << "\nPodaj startowy rozmiar figury: ";

        while (std::cin >> scale)
        {
            if (IsValidAction(scale, pos.X, pos.Y, consoleSize)) break;

            std::cout << "Podano nieodpowiedni rozmiar startowy, podaj ponownie: ";
        }
    }

    void DrawShape(char code, int scale, int posX, int posY)
    {
        int copyX = posX;
        int copyY = posY;
        scale *= 2;

        io::Cls();

        // Rysowanie lewego ramienia
        io::GotoXY(copyX, copyY);
        std::cout.put(code);
        for (int i = 0; i < scale; ++i)
        {
            io::GotoXY(--copyX, ++copyY);
            std::cout.put(code);
        }
        io::GotoXY(--copyX, ++copyY);
        std::cout.put(code);
        for (int i = 0; i < scale; ++i)
        {
            io::GotoXY(--copyX, ++copyY);
            std::cout.put(code);
        }

        copyX = posX;
        copyY = posY;

        // Rysowanie prawego ramienia
        io::GotoXY(copyX, copyY);
        for (int i = 0; i < scale; ++i)
        {
            io::GotoXY(++copyX, ++copyY);
            std::cout.put(code);
        }
        io::GotoXY(++copyX, ++copyY);
        std::cout.put(code);
        for (int i = 0; i < scale; ++i)
        {
            io::GotoXY(++copyX, ++copyY);
            std::cout.put(code);
        }

        // Rysowanie "poprzeczki" figury
        copyX = posX - scale;
        copyY = posY + scale + 1;

        io::GotoXY(copyX, copyY);
        for (int i = 0; i < scale * 2 + 1; ++i)
        {
            std::cout.put(code);
        }
    }

    bool IsValidAction(int scale, short x, short y, COORD consoleSize)
    {
        // Sprawdzenie czy figura nie wyjdzie poza granice ekranu
        if (scale < 0) return false;

        if (y >= 0 && y + (scale * 4 + 1) < consoleSize.Y && x - (scale * 4) > 0 && x + (scale * 4 + 1) < consoleSize.X) return true;

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

    void MainLoop(char code, int scale, COORD pos, COORD consoleSize)
    {
        while (true)
        {
            // Wyjście
            if (io::IsKeyPressed(io::Escape)) break;

            // Ruch
            if (io::IsKeyPressed(io::Up))
            {
                if (IsValidAction(scale, pos.X, pos.Y - 1, consoleSize))
                {
                    DrawShape(code, scale, pos.X, --pos.Y);
                }
            }
            else if (io::IsKeyPressed(io::Down))
            {
                if (IsValidAction(scale, pos.X, pos.Y + 1, consoleSize))
                {
                    DrawShape(code, scale, pos.X, ++pos.Y);
                }
            }
            if (io::IsKeyPressed(io::Left))
            {
                if (IsValidAction(scale, pos.X - 1, pos.Y, consoleSize))
                {
                    DrawShape(code, scale, --pos.X, pos.Y);
                }
            }
            else if (io::IsKeyPressed(io::Right))
            {
                if (IsValidAction(scale, pos.X + 1, pos.Y, consoleSize))
                {
                    DrawShape(code, scale, ++pos.X, pos.Y);
                }
            }

            // Skalowanie
            if (io::IsKeyPressed(io::Minus))
            {
                if (scale > 1)
                {
                    if (IsValidAction(scale - 1, pos.X, pos.Y, consoleSize))
                    {
                        DrawShape(code, --scale, pos.X, pos.Y);
                    }
                }
            }
            else if (io::IsKeyPressed(io::Plus))
            {
                if (IsValidAction(scale + 1, pos.X, pos.Y, consoleSize))
                {
                    DrawShape(code, ++scale, pos.X, pos.Y);
                }
            }

            // Lekkie spowolnienie pętli żeby ograniczyć wykorzystanie procesora
            Sleep(10);
        }
    }
}
