#ifndef ATSCREEN_H
#define ATSCREEN_H

#ifdef _WIN32
    #define CURRENT_OS "Windows"
    #define CLEAR system("cls")

#elif defined __unix__
    #define CURRENT_OS "Unix"
    #define CLEAR system("clear")

#else
    #define CLEAR system("clear")
    #define CURRENT_OS "Unknown"

#endif

/**
    @file atScreen.h
    @author Frank Rodriguez
    @date 27 July 2017
    @brief A collection of functions which perform work on the AtScreen struct.

    When requiring an AtScreen struct, all functions will take a pointer to one for
    efficiency's sake.
*/

/**
    @brief The backbone of the @ library.

    Allows information to be drawn to the console based on x/y coordinates, rather than
    line-by-line. It is double-buffered to facilitate quick draw times.

    @warning By necessity, an AtScreen is internally referenced as [y][x] instead of [x][y].
    Since the latter is more natural, all functions that require x/y coordinates will switch
    their inputs (x->y, y->x) to account for this quirk. When creating a user-defined function,
    care must be taken to reference the AtScreen in a similar way.
*/
typedef struct AtScreen
{
    char **buffer; /**< Where all characters to be drawn are stored*/
    char **drawBuffer;/**< The last drawn frame */
    char *printBuffer; /**< Used as a temporary container when concatenating data to print to console*/
    int width,  /**< The width of the drawn window (should be <= console width)*/
        height; /**< The height of the drawn window (should be <= console height)*/
} AtScreen;

/**
    @brief Creates and returns a pointer to a new AtScreen.

    Allocates @p width to AtScreen->buffer, and @p height to AtScreen->buffer[]. Sets
    AtScreen->width/height accordingly.
*/
AtScreen *newAtScreen(int width, int height);

/**
    @brief Frees all pointers contained by @p *atScreen, then frees @p *atScreen itself.
*/
void freeAtScreen(AtScreen *atScreen);

/**
    @brief Deletes all characters from @p atScreen, replacing them with @p clearChar.
*/
void clearAtScreen(AtScreen *atScreen, char clearChar);

/**
    @brief Returns the @c char at (@p x,@p y) in @p atScreen's buffer.
*/
char getScreenPosition(AtScreen *atScreen, int x, int y);

/**
    @brief A wrapper which sends the command to the function most-optimized for the system.
*/
void drawAtScreen(AtScreen *atScreen);

/**
    @brief Displays the contents of @p atScreen's buffer to the console.

    Concatenates all characters of the supplied atScreen's buffer into one cstring,
    then clears the console and prints the cstring to it.
*/
void slowDrawAtScreen(AtScreen *atScreen);


#endif // ASCREEN_H
