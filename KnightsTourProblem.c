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

bool isWithinBoard(const Position p, const Board *board)
{
    return (p.row >= 0 && p.row < board->rows &&
            p.column >= 0 && p.column < board->columns);
}

bool isAccessible(const Position p, const Board *board)
{
    return (isWithinBoard(p, board) &&
            board->fields[p.row][p.column].whenVisited == NOT_VISITED);
}

bool solveKnightsTourProblem(const int r, const int c)
{
    Board board;
    initBoard(&board, r, c);
    if (!board.fields)
    {
        perror("Not enough memory.\n");
        return false;
    }
    Knight knight = {.cMove = {1, 2, 2, 1, -1, -2, -2, -1},
                     .rMove = {2, 1, -1, -2, -2, -1, 1, 2}};
    board.fields[0][0].whenVisited = 0;
    bool result;
    if ((result = backtracing((Position){0, 0}, 1, &board, &knight)) == false)
    {
        printf("Solution not found.");
    }
    else
    {
        printBoard(&board);
        printf("Solution found.\n\n");
    }
    freeBoard(&board);
    return result;
}

bool backtracing(Position p, int moveNumber, Board *board, Knight *knight)
{
    if (moveNumber == board->rows * board->columns)
        return true;

    int rNext, cNext;
    for (int k = 0; k < KNIGHT_MOVES; ++k)
    {
        rNext = p.row + knight->rMove[k];
        cNext = p.column + knight->cMove[k];
        if (isAccessible((Position){rNext, cNext}, board))
        {
            board->fields[rNext][cNext].whenVisited = moveNumber;
            if (backtracing((Position){rNext, cNext}, moveNumber + 1, board, knight))
                return true;
            else
                board->fields[rNext][cNext].whenVisited = NOT_VISITED;
        }
    }
    return false;
}
