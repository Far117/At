#include <stdio.h>
#include <stdlib.h>

#include "atScreen.h"
#include "atPrint.h"

/**
    @file demo.c
    @author Frank Rodriguez
    @date 5 August 2017

    @brief Displays basic functionality of the @ library.
*/

typedef struct Object
{
    int x, y;
    char symbol;
} Object;

int main()
{
    int windowWidth = 70, windowHeight = 24;
    AtScreen *screen = newAtScreen(windowWidth, windowHeight);

    Object player;
    player.x = windowWidth / 2;
    player.y = windowHeight / 2;
    player.symbol = '@';

    while(true)
    {
        clearAtScreen(screen, '.');

        placeChar(screen, player.symbol, player.x, player.y);
        placeInt(screen, 100, 0, 0);
        placeDouble(screen, 1.1, 1, screen->width / 2, 0);
        placeString(screen, "Fire!", screen->width / 2, screen->height - 1);

        printAtScreen(screen);

        switch (getch())
        {
            case 'w': player.y--; break;
            case 'a': player.x--; break;
            case 's': player.y++; break;
            case 'd': player.x++; break;
        }
    }

    return 0;
}
