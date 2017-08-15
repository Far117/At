#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "atScreen.h"
#include "atPrint.h"

/**
    @file demo.c
    @author Frank Rodriguez
    @date 5 August 2017

    @brief Displays basic functionality of the @ library.
*/

void pong();
void rpg();

int main()
{
    //pong();
    rpg();
    return 0;
}

void pong()
{
    typedef struct Paddle
    {
        int x, y;
    } Paddle;

    typedef struct Ball
    {
        int x, y;
        int xSpeed, ySpeed;
    } Ball;

    int width = 70, height = 24;
    Paddle left, right;
    Ball ball;
    AtScreen *screen = newAtScreen(width, height);

    left.x = 5;
    left.y = height / 2;
    right.x = width - 5;
    right.y = width / 2;

    ball.x = width / 2;
    ball.y = height / 2;
    ball.xSpeed = rand() % 2;
    ball.ySpeed = rand() % 2;

    #define BALLSPEED 2
    #define PADDLESPEED 4


    bool newGame = true;
    while (true)
    {
        clearAtScreen(screen, ' ');
        if (newGame)
        {
            !ball.xSpeed ? (ball.xSpeed = -BALLSPEED) : (ball.xSpeed = BALLSPEED);
            !ball.ySpeed ? (ball.ySpeed = -BALLSPEED) : (ball.ySpeed = BALLSPEED);
            ball.x = width / 2;
            ball.y = height / 2;

            left.x = 5;
            left.y = height / 2;
            right.x = width - 5;
            right.y = height / 2;

            newGame = false;
        }

        // Paddle AI
        if (ball.xSpeed < 0) // Going left
        {
            if (ball.y > left.y && isWithinBounds(screen, left.x, left.y, 0, 1))
                left.y += PADDLESPEED;
            else if (ball.y < left.y && isWithinBounds(screen, left.x, left.y - PADDLESPEED, 0, 2))
                left.y -= PADDLESPEED;
        }
        else // Going right
        {
            if (ball.y > right.y && isWithinBounds(screen, right.x, right.y + PADDLESPEED, 0, 1))
                right.y += PADDLESPEED;
            else if (ball.y < right.y && isWithinBounds(screen, right.x, right.y - PADDLESPEED, 0, 2))
                right.y -= PADDLESPEED;
        }

        // Ball logic

        // Hits walls
        if (!isWithinBounds(screen, ball.x, ball.y + ball.ySpeed, 0, 0))
            ball.ySpeed = -ball.ySpeed;
        if (!isWithinBounds(screen, ball.x + ball.xSpeed, ball.y, 0, 0))
            ball.xSpeed = -ball.xSpeed;

        if (ball.x <= 0 || ball.x >= width - 1)
            newGame = true;



        int tmp;
        for (tmp = left.y - 1; tmp < left.y + 2; tmp++)
            placeChar(screen, '#', left.x, tmp);
        for (tmp = right.y - 1; tmp < right.y + 2; tmp++)
            placeChar(screen, '#', right.x, tmp);

        // Hits Paddles
        if (getScreenPosition(screen, ball.x + ball.xSpeed, ball.y) == '#')
            ball.xSpeed = -ball.xSpeed;

        ball.x += ball.xSpeed;
        ball.y += ball.ySpeed;

        placeChar(screen, 'O', ball.x, ball.y);

        drawAtScreen(screen);
    }
}

void rpg()
{
    typedef struct Object
    {
        int x, y;
        char symbol;
    } Object;

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

        drawAtScreen(screen);

        switch (getch())
        {
            case 'w': player.y--; break;
            case 'a': player.x--; break;
            case 's': player.y++; break;
            case 'd': player.x++; break;
            case 'b': goto END;
        }
    }

    END:
        freeAtScreen(screen);
        return;
}
