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

#endif // KNIGHTSTOURPROBLEM_H
