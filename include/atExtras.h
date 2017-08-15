#ifndef ATEXTRAS_H
#define ATEXTRAS_H

#include "atScreen.h"

/**
    @file atExtras.c
    @author Frank Rodriguez
    @date 11 August 2017

    @brief A collection of functions that may be needed on certain operating systems
*/

#ifdef __unix__
    /**
        @brief Linux does not have getch() built-in, and it is very useful indeed.
    */
    int getch(void);
#endif // __unix__

#ifdef __WIN32
    /**
        @brief Draws the supplied AtScreen to the console using double-buffering.

        Iterates over the contents of @c atScreen->buffer, comparing it to the contents
        of @c atScreen->drawBuffer. For any coordinates in which they differ, the contents of
        @c atScreen->buffer[y][x] are printed at those coordinates, and the contents of
        @c atScreen->drawBuffer[y][x] are replaces with the buffer's.

        @note The cursor is placed to the bottom right of @p atScreen's draw area.
    */
    void windowsDrawScreen(AtScreen *atScreen);
#endif // __WIN32

#endif // ATEXTRAS_H
