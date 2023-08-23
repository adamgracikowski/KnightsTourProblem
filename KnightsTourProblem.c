#include "KnightsTourProblem.h"

bool initBoard(Board *board, const int rows, const int columns)
{
    if (board)
    {
        board->rows = rows;
        board->columns = columns;
        board->fields = malloc(board->rows * sizeof(Field *));
        if (!board->fields)
        {
            board->rows = board->columns = 0;
            return false;
        }
        for (int i = 0; i < board->rows; ++i)
        {
            board->fields[i] = malloc(board->columns * sizeof(Field));
            if (!board->fields[i])
            {
                for (int j = 0; j < i; ++j)
                {
                    free(board->fields[j]);
                }
                free(board->fields);
                board->rows = board->columns = 0;
                board->fields = NULL;
                return false;
            }
        }
        resetBoard(board);
        return true;
    }
    return false;
}

void freeBoard(Board *board)
{
    if (board)
    {
        for (int i = 0; i < board->rows; ++i)
        {
            if (board->fields[i])
                free(board->fields[i]);
        }
        free(board->fields);
    }
}

void resetBoard(Board *board)
{
    if (board)
    {
        for (int i = 0; i < board->rows; ++i)
        {
            for (int j = 0; j < board->columns; ++j)
            {
                board->fields[i][j].whenVisited = NOT_VISITED;
            }
        }
    }
}

void printBoard(Board *board)
{
    int fieldWidth = calculateFieldWidth(board);

    for (int i = 0; i < board->rows; ++i)
    {
        for (int j = 0; j < board->columns; ++j)
        {
            if (board->fields[i][j].whenVisited == NOT_VISITED)
                printf("[%*c]", fieldWidth, ' ');
            else
                printf("[%*d]", fieldWidth, board->fields[i][j].whenVisited);
        }
        printf("\n");
    }
}

int calculateFieldWidth(Board *board)
{
    int greatestNumber = board->rows * board->columns - 1;
    int counter;
    do
    {
        greatestNumber /= 10;
        ++counter;
    } while (greatestNumber != 0);
    return counter;
}
