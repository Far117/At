#include "atScreen.h"

/**
    @file atScreen.c
    @author Frank Rodriguez
    @date 5 August 2017

    @brief The implementation of functions declared in atScreen.h
*/

AtScreen *newAtScreen(int width, int height)
{
    AtScreen *atScreen = malloc(sizeof(AtScreen));

    atScreen->width = width;
    atScreen->height = height;

    // +height to account for newlines, +1 to account for null-terminator
    atScreen->printBuffer = calloc(height * width + height + 1, 1);
    atScreen->buffer = malloc(height * sizeof(char*));

    int i;
    for (i = 0; i < width; i++)
        atScreen->buffer[i] = malloc(width);

    return atScreen;
}

void freeAtScreen(AtScreen *atScreen)
{
    int i;
    for (i = 0; i < atScreen->height; i++)
        free(atScreen->buffer[i]);

    free(atScreen->buffer);

    free(atScreen);

    return;
}

void clearAtScreen(AtScreen *atScreen, char clearChar)
{
    int y, x;

    for (y = 0; y < atScreen->height; y++)
        for (x = 0; x < atScreen->width; x++)
            atScreen->buffer[y][x] = clearChar;

    return;
}

void printAtScreen(AtScreen *atScreen)
{
    int x, y, pos = 0;
    for (y = 0; y < atScreen->height; y++)
    {
        for (x = 0; x < atScreen->width; x++)
            atScreen->printBuffer[pos++] = atScreen->buffer[y][x];

        atScreen->printBuffer[pos++] = '\n';
    }

    CLEAR;
    printf("%s", atScreen->printBuffer);

    return;
}
