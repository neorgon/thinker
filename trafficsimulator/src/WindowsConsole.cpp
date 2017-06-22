#include "../include/WindowsConsole.h"

void WindowsConsole::ClearScreen() const
{
    HANDLE                     hStdOut;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD                      count;
    DWORD                      cellCount;
    COORD                      homeCoords = { 0, 0 };

    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hStdOut == INVALID_HANDLE_VALUE) return;

    /* Get the number of cells in the current buffer */
    if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
    cellCount = csbi.dwSize.X *csbi.dwSize.Y;

    /* Fill the entire buffer with spaces */
    if (!FillConsoleOutputCharacter(hStdOut, (TCHAR) ' ', cellCount, homeCoords, &count)) return;

    /* Fill the entire buffer with the current colors and attributes */
    if (!FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, cellCount, homeCoords, &count)) return;

    /* Move the cursor home */
    SetConsoleCursorPosition( hStdOut, homeCoords );
}

void WindowsConsole::GotoXY(short int x, short int y)
{
	COORD coord = {x, y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

	return;
}

void WindowsConsole::GetXY(short int &x, short int &y)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
    {
		x = csbi.dwCursorPosition.X;
		y = csbi.dwCursorPosition.Y;
	}
}

void WindowsConsole::SetColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), color);
}

void WindowsConsole::PrintCity() const
{
    /*const char city[] =
    "\n\
                             *                *                   *     \n\
                 *                                     *                \n\
         *              |           *             *        *         *  \n\
              *        -+-                 *                            \n\
           __           |      *             *          *        *      \n\
       ___|  |   *     _|_              *    ____    ____               \n\
       [_]|``|__      _| |_        *    |   |....|  |....|    *     *   \n\
          |     |   _|[] []|_    ___    |   |....|  | ___|__            \n\
       [_]|  `` |__|_  ______|  |   |  |_|  |....|  || -- - |   *     * \n\
          |________  |__     |  |# #|  |_|  |....|  || - -- |  _____    \n\
       [_]| _____ |     |__[]|  |   |  |_|  |....|__|| -- - | |* * *|   \n\
          | [___] |        |__  |# #|  |_|  |....|__|| -- -_|_|* * *|   \n\
       [_]|       | ``        | |   |__| |__|....|  || ___|* *|* * *|   \n\
          | _____ |           |__  #|_______|....|  | |* *|* *|* * *|   \n\
       [_]| [___] |       ``     |__|_______|__  |  | |* *|* *|* * *|   \n\
          |       |            __|_____________|__    |* *|* *|* * *|   \n\
       [_]| _____ |  ``      _|___________________|_  |* *|* *|* * *|   \n\
          | [___] |         |_______________________|  ______________   \n\
        __|_______|_________|_______________________| _________________ \n\
       |_______________________________________________________________|\n\
       |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n\
       ||||||||||||||||||||||  Traffic Simulator  ||||||||||||||||||||||\n\
       |||||||||||||||    ...:: FUNDACION JALA ::...    ||||||||||||||||\n\
       ||||||||||||||||||||||||||||DEV INT 22|||||||||||||||||||||||||||\n\
       |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n\
       |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n\
       |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n\
    ";

    for (int i = 0; i < 18; i ++) printf("\n");
    printf("%s", city);
    int j = 300000;
    for (int i = 0; i < 18; i ++) {
        usleep(j);
        j = (int)(j * 0.9);
        printf("\n");
    }
    printf("Press any key to continue\n");
    getchar();*/
}

void WindowsConsole::PrintMap(const map<int, vector<shared_ptr<TrafficLight>>> &tls, size_t mapSize)
{
    size_t x = 1, y = 1;
    int cx, cy;

    for (auto &t : tls)
    {
        SetColor(7);
        GotoXY(x * dx, y * dy);
        cout << ":";
        DrawDirection
            (
                cx = x * dx,
                cy = y * dy,
                t.second[0]->GetDirection(),
                t.second[0]->GetLight(),
                t.second[0]->CountVehicles()
            );
        t.second[0]->SetCoord(cx, cy);
        DrawDirection
            (
                cx = x * dx,
                cy = y * dy,
                t.second[1]->GetDirection(),
                t.second[1]->GetLight(),
                t.second[1]->CountVehicles()
            );
        t.second[1]->SetCoord(cx, cy);
        if (x % mapSize == 0)
        {
            x = 1;
            y++;
        }
        else
        {
            x++;
        }
    }
}

void WindowsConsole::DrawDirection(int &cx, int &cy, size_t dir, bool tlGreen, size_t vehicles)
{
    int i;

    switch (dir)
    {
        case 0:
            for (i = cx + 1; i < cx + (dx - 1); i++)
            {
                SetColor(7);
                GotoXY(i, cy);
                cout << char(196);
            }
            SetColor(15);
            GotoXY(i - 3, cy);
            cout << vehicles;
            tlGreen ?  SetColor(10): SetColor(12);
            GotoXY(i, cy);
            cout << "*";
            cx = i;
        break;
        case 90:
            for (i = cy - 1; i > cy - (dy - 1); i--)
            {
                SetColor(7);
                GotoXY(cx, i);
                cout << char(179);
            }
            SetColor(15);
            GotoXY(cx, i + 1);
            cout << vehicles;
            tlGreen ?  SetColor(10): SetColor(12);
            GotoXY(cx, i);
            cout << "*";
            cy = i;
        break;
        case 180:
            for (i = cx - 1; i > cx - (dx - 1); i--)
            {
                SetColor(7);
                GotoXY(i, cy);
                cout << char(196);
            }
            SetColor(15);
            GotoXY(i + 3, cy);
            cout << vehicles;
            tlGreen ?  SetColor(10): SetColor(12);
            GotoXY(i, cy);
            cout << "*";
            cx = i;
        break;
        case 270:
            for (i = cy + 1; i < cy + (dy - 1); i++)
            {
                SetColor(7);
                GotoXY(cx, i);
                cout << char(179);
            }
            SetColor(15);
            GotoXY(cx, i - 1);
            cout << vehicles;
            tlGreen ?  SetColor(10): SetColor(12);
            GotoXY(cx, i);
            cout << "*";
            cy = i;
        break;
    }
}

void WindowsConsole::UpdateMap(const map<int, vector<shared_ptr<TrafficLight>>> &tls)
{
    for (auto &t : tls)
    {
        t.second[0]->GetLight() ? SetColor(10) : SetColor(12);
        GotoXY(t.second[0]->GetCoord().x, t.second[0]->GetCoord().y);
        cout << "*";
        switch (t.second[0]->GetDirection())
        {
            case 0:
                SetColor(15);
                GotoXY(t.second[0]->GetCoord().x - 3, t.second[0]->GetCoord().y);
                cout << t.second[0]->CountVehicles();
            break;
            case 90:
                SetColor(15);
                GotoXY(t.second[0]->GetCoord().x, t.second[0]->GetCoord().y + 1);
                cout << t.second[0]->CountVehicles();
            break;
            case 180:
                SetColor(15);
                GotoXY(t.second[0]->GetCoord().x + 3, t.second[0]->GetCoord().y);
                cout << t.second[0]->CountVehicles();
            break;
            case 270:
                SetColor(15);
                GotoXY(t.second[0]->GetCoord().x, t.second[0]->GetCoord().y - 1);
                cout << t.second[0]->CountVehicles();
            break;
        }
        t.second[1]->GetLight() ? SetColor(10) : SetColor(12);
        GotoXY(t.second[1]->GetCoord().x, t.second[1]->GetCoord().y);
        cout << "*";
        switch (t.second[1]->GetDirection())
        {
            case 0:
                SetColor(15);
                GotoXY(t.second[1]->GetCoord().x - 3, t.second[1]->GetCoord().y);
                cout << t.second[1]->CountVehicles();
            break;
            case 90:
                SetColor(15);
                GotoXY(t.second[1]->GetCoord().x, t.second[1]->GetCoord().y + 1);
                cout << t.second[1]->CountVehicles();
            break;
            case 180:
                SetColor(15);
                GotoXY(t.second[1]->GetCoord().x + 3, t.second[1]->GetCoord().y);
                cout << t.second[1]->CountVehicles();
            break;
            case 270:
                SetColor(15);
                GotoXY(t.second[1]->GetCoord().x, t.second[1]->GetCoord().y - 1);
                cout << t.second[1]->CountVehicles();
            break;
        }
    }
}
