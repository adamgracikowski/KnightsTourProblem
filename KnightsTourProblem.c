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

Position generatePosition(const int rows, const int columns)
{
    return (Position){rand() % rows, rand() % columns};
}

bool solveUsingWarnsdorffsRule(Position start, const int rows, const int columns)
{
    Board board;
    initBoard(&board, rows, columns);
    if (!board.fields)
    {
        perror("Not enough memory.\n");
        return false;
    }
    Knight knight = {.cMove = {1, 2, 2, 1, -1, -2, -2, -1},
                     .rMove = {2, 1, -1, -2, -2, -1, 1, 2}};
    Position p = {start.row, start.column};
    board.fields[p.row][p.column].whenVisited = 0;

    int n = board.rows * board.columns;
    for (int i = 1; i < n; ++i)
    {
		ANIMATION(printBoard(&board), ANIMATION_DELAY);
        if (moveNext(&p, &board, &knight) == false)
        {
            printf("Solution not found.\n");
            freeBoard(&board);
            return false;
        }
    }
	ANIMATION(, ANIMATION_DELAY);
    printBoard(&board);
    if (isNeighbour(p, start, &knight))
        printf("Closed Tour found.\n");
    else
        printf("Open Tour found.\n");
    freeBoard(&board);
    return true;
}

bool moveNext(Position *p, Board *board, Knight *knight)
{
    int randIdx = rand() % KNIGHT_MOVES;
    int minAccess = KNIGHT_MOVES + 1, currentAccess, minAccessIdx = -1, rNext, cNext;
    for (int i = 0; i < KNIGHT_MOVES; ++i)
    {
        int j = (i + randIdx) % KNIGHT_MOVES;
        rNext = p->row + knight->rMove[j];
        cNext = p->column + knight->cMove[j];
        Position pNext = {rNext, cNext};
        if (isAccessible(pNext, board) && (currentAccess = countAccess(pNext, board, knight)) < minAccess)
        {
            minAccess = currentAccess;
            minAccessIdx = j;
        }
    }
    if (minAccessIdx == -1)
        return false;

    int moveNumber = board->fields[p->row][p->column].whenVisited;
    p->row = p->row + knight->rMove[minAccessIdx];
    p->column = p->column + knight->cMove[minAccessIdx];
    board->fields[p->row][p->column].whenVisited = moveNumber + 1;
    return true;
}

int countAccess(const Position p, Board *board, Knight *knight)
{
    int counter = 0;
    for (int i = 0; i < KNIGHT_MOVES; ++i)
    {
        if (isAccessible((Position){p.row + knight->rMove[i], p.column + knight->cMove[i]}, board))
        {
            counter++;
        }
    }
    return counter;
}

bool isNeighbour(const Position p1, const Position p2, Knight *knight)
{
    for (int i = 0; i < KNIGHT_MOVES; ++i)
    {
        if (p1.row + knight->rMove[i] == p2.row && p1.column + knight->cMove[i] == p2.column)
            return true;
    }
    return false;
}
