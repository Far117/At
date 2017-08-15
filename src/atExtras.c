#include "atExtras.h"
#include "atScreen.h"

#ifdef __unix__
    int getch(void)
    {
        struct termios oldattr, newattr;
        int ch;
        tcgetattr( STDIN_FILENO, &oldattr );
        newattr = oldattr;
        newattr.c_lflag &= ~( ICANON | ECHO );
        tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
        ch = getchar();
        tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
        return ch;
    }
#endif // __unix__

#ifdef __WIN32

    #include <windows.h>
    void windowsDrawScreen(AtScreen *atScreen)
    {
        DWORD n;                         /* Number of characters written */
        DWORD size;                      /* number of visible characters */
        COORD coord = {0};               /* Top left screen position */
        CONSOLE_SCREEN_BUFFER_INFO csbi;

        /* Get a handle to the console */
        HANDLE h = GetStdHandle ( STD_OUTPUT_HANDLE );

        GetConsoleScreenBufferInfo ( h, &csbi );

        /* Find the number of characters to overwrite */
        size = csbi.dwSize.X * csbi.dwSize.Y;

        /* Overwrite the screen buffer with whitespace */
        /*
        FillConsoleOutputCharacter ( h, TEXT ( ' ' ), size, coord, &n );
        GetConsoleScreenBufferInfo ( h, &csbi );
        FillConsoleOutputAttribute ( h, csbi.wAttributes, size, coord, &n );
        */

        /* Reset the cursor to the top left position */


        int x, y;

        for (y = 0; y < atScreen->height; y++)
        {
            for (x = 0; x < atScreen->width; x++)
            {
                if (atScreen->drawBuffer[y][x] != atScreen->buffer[y][x])
                {
                    coord.X = x;
                    coord.Y = y;
                    SetConsoleCursorPosition(h, coord);

                    putchar(atScreen->buffer[y][x]);
                    atScreen->drawBuffer[y][x] = atScreen->buffer[y][x];
                }
            }
        }

        coord.X = atScreen->width - 1;
        coord.Y = atScreen->height - 1;
        SetConsoleCursorPosition ( h, coord );
    }

#endif // __WIN32
