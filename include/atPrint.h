#ifndef ATPRINT_H
#define ATPRINT_H

#include <stdbool.h>
#include "atScreen.h"

/**
    @file atPrint.h
    @author Frank Rodriguez
    @date 5 August 2017

    @brief A collection of functions which place data into AtScreens.
*/

/**
    @brief Checks if the supplied coordinates, plus any additional margins, are within bounds of @p atScreen's buffer.

    @return Returns @c true if the coordinates fit, @c false otherwise.
*/
bool isWithinBounds(AtScreen *atScreen, int x, int y, int xMargin, int yMargin);

/**
    @brief Places @p c at the @p x and @p y coordinates supplied.

    @return Returns @c true if there was no error, or @c false if the supplied coordinates were out of bounds.
*/
bool placeChar(AtScreen *atScreen, char c, int x, int y);

/**
    @brief Places @p d at the @p x and @p y coordinates supplied.

    Truncates @p d to the number of decimals dictated by @p precision.

    @return Returns @c true if there was no error, or @c false if the supplied coordinates were out of bounds.
*/
bool placeDouble(AtScreen *atScreen, double d, int precision, int x, int y);

/**
    @brief Places @p i at the @p x and @p y coordinates supplied.

    @return Returns @c true if there was no error, or @c false if the supplied coordinates were out of bounds.
*/
bool placeInt(AtScreen *atScreen, int i, int x, int y);

/**
    @brief Places @p s at the @p x and @p y coordinates supplied.

    @return Returns @c true if there was no error, or @c false if the supplied coordinates were out of bounds.
*/
bool placeString(AtScreen *atScreen, char *s, int x, int y);

#endif // ATPRINT_H
