#include "atPrint.h"
#include <string.h>

/**
    @file atPrint.c
    @author Frank Rodriguez
    @date 6 August 2017

    @brief The implementation of all functions declared in atPrint.h
*/

bool isWithinBounds(AtScreen *atScreen, int x, int y, int xMargin, int yMargin)
{
    if ((x + xMargin) > atScreen->width || (y + yMargin) > atScreen->height || x < 0 || y < 0)
        return false;
    return true;
}

bool placeChar(AtScreen *atScreen, char c, int x, int y)
{
    if (isWithinBounds(atScreen, x, y, 0, 0))
    {
        atScreen->buffer[y][x] = c;
        return true;
    }

    printf("ERROR: Could not place %c at (%i, %i) because it is out of bounds (%i x %i)\n",
                c, x, y, atScreen->width, atScreen->height);
    return false;
}

bool placeDouble(AtScreen *atScreen, double d, int precision, int x, int y)
{
    char *s = calloc(1, 50);
    sprintf(s, "%.*lf", precision, s);

    bool results = placeString(atScreen, s, x, y);
    free(s);

    return results;
}

bool placeInt(AtScreen *atScreen, int i, int x, int y)
{
    char *s = calloc(1, 11); // 11 = maximum digits in an int + 1
    sprintf(s, "%i", i);

    bool results = placeString(atScreen, s, x, y);
    free(s);

    return results;
}

bool placeString(AtScreen *atScreen, char *s, int x, int y)
{
    int length = strlen(s);

    if (isWithinBounds(atScreen, x, y, length, 0))
    {
        int tmpX;
        for (tmpX = 0; tmpX < length; tmpX++)
            atScreen->buffer[y][x + tmpX] = s[tmpX];

        return true;
    }

    return false;
}
