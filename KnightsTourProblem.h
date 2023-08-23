#ifndef KNIGHTSTOURPROBLEM_H
#define KNIGHTSTOURPROBLEM_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

#define KNIGHT_MOVES 8
#define NOT_VISITED -1
#define STD_ROWS 8
#define STD_COLUMNS 8

//--------------------------------------

#define INTERACTIVE_PRINT 1
// #define INTERACTIVE_PRINT 0 // uncomment this line and comment the line above to disable the animation
#define ANIMATION_DELAY 500
#define ANIMATION(instruction, delay) \
    if (INTERACTIVE_PRINT)            \
    {                                 \
        Sleep(delay);                 \
        if (system("cls"))            \
            system("clear");          \
        instruction;                  \
    }

//--------------------------------------

typedef struct Field
{
    int whenVisited;
} Field;

typedef struct Board
{
    int rows;
    int columns;
    Field **fields;
} Board;

typedef struct Knight
{
    int rMove[KNIGHT_MOVES];
    int cMove[KNIGHT_MOVES];
} Knight;

typedef struct Position
{
    int row;
    int column;
} Position;

//--------------------------------------

bool initBoard(Board *board, const int rows, const int columns);
void freeBoard(Board *board);
void resetBoard(Board *board);
void printBoard(Board *board);
int calculateFieldWidth(Board *board);
bool isWithinBoard(const Position position, const Board *board);
bool isAccessible(const Position position, const Board *board);
bool solveKnightsTourProblem(const int r, const int c);
bool backtracing(Position p, int m, Board *board, Knight *knight);

bool solveUsingWarnsdorffsRule(Position start, const int rows, const int columns);
bool moveNext(Position *p, Board *board, Knight *knight);
int countAccess(const Position p, Board *board, Knight *knight);
bool isNeighbour(const Position p1, const Position p2, Knight *knight);
Position generatePosition(const int rows, const int columns);

#endif // KNIGHTSTOURPROBLEM_H
