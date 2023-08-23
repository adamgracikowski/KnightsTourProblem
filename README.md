# The Knight's Tour Problem

## Table of Contents:

- [What is the Knight's Tour Problem?](#what-is-the-knight's-tour-problem?)
- [Existence](#existence)
- [About the implementation](#about-the-implementation)
- [Author](#author)
- [Contributing](#contributing)
- [Show your support](#show-your-support)

## [What is the Knight's Tour Problem?](https://en.wikipedia.org/wiki/Knight%27s_tour)

A knight's tour is a sequence of moves of a knight on a chessboard such that the knight visits every square exactly once. 
If the knight ends on a square that is one knight's move from the beginning square the tour is called a **closed tour**. Otherwise, it is called an **open tour**.

The knight's tour problem is the mathematical problem of finding a knight's tour. The knight's tour problem is an instance of the more general 
[Hamiltonian path problem](https://en.wikipedia.org/wiki/Hamiltonian_path_problem) in graph theory.
<p align="center">
  <img src="https://upload.wikimedia.org/wikipedia/commons/c/ca/Knights-Tour-Animation.gif" alt="Knight's Tour gif" />
</p>
Variations of the knight's tour problem involve chessboards of different sizes than the usual 8 × 8, as well as different starting positions of a knight on the chessboard.

## Existence:

It is mathematically proved that for any m × n board with m ≤ n, a closed knight's tour is always possible unless one or more of these three conditions are met:
1. m and n are both odd
2. m = 1, 2, or 4
3. m = 3 and n = 4, 6, or 8.

For a more detailed analysis with a partial explanation see the following [article](https://web.archive.org/web/20190526154119/https://pdfs.semanticscholar.org/c3f5/e69e771771de1be50a8a8bf2561804026d69.pdf).

## About the implementation:

In order to solve the knight's tour problem two different solutions were implemented. 

|Function:|Explanation:|
|---|---|
|`bool solveKnightsTourProblem(const int r, const int c)`| It accepts the number of rows `r` and the number columns `c` of the chessboard and finds a solution of the problem using **backtracing algorithm**. In this case the knight is initially positioned in the corner of the chessboard. Once the solution is found, it is printed to the standard output. If the solution was not found, the following message is displayed: "`Solution not found.`"|
|`bool solveUsingWarnsdorffsRule(Position start, const int rows, const int columns)`| A more general function which apart from accepting chessboard dimensions allows to specify a starting position `start` of the knight. Warnsdorff's rule is a heuristic in which the knight always proceeds to the square from which it will have the fewest onward moves. Apart from printing the solution to the standard output (if it exists), the function informs if the path was a **closed path** or an **open path** by displaying appropriate messeges: "`Closed Tour found.`" or "`Open Tour found.`".|

Both functions use a self-implemented rectangular array `Board` (with **dynamic memory allocation**) to represent the chessboard. 

```cpp
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
```

Such structure allows to solve the knight's tour problem for different dimensions of the chessboard.

Helper functions of the `Board` structures include:

|Function:|Explanation:|
|---|---|
|`bool initBoard(Board *board, const int rows, const int columns)`|Allocates memory for the `board` insance of `Board`. If failure occurs, it sets `board->fields` to `NULL`.|
|`void freeBoard(Board *board)`|Dealocates memory alocated for the `board` object. It successfully prevents from any memory leaks.|
|`void resetBoard(Board *board)`|Sets all fields to `NOT_VISITED`.|
|`void printBoard(Board *board)`|Displays the contents of the `board` to the standard output.|

To make the usage of the programme more entertaining the `solveUsingWarnsdorffsRule` function supports an **animaton**, which can be disabled by setting `INTERACTIVE_PRINT`
to `0` in `KnightsTourProblem.h` header file.

The following **macro** is responsible for the animation effect:

```cpp
#define ANIMATION_DELAY 500
#define ANIMATION(instruction, delay) \
    if (INTERACTIVE_PRINT)            \
    {                                 \
        Sleep(delay);                 \
        if (system("cls"))            \
            system("clear");          \
        instruction;                  \
    }
```
The usage of the macro inside `solveUsingWarnsdorffsRule` is as follows:

```cpp
ANIMATION(printBoard(&board), ANIMATION_DELAY);
```
An exemplary solution of the knight's tour generated by the programme is shown in the picture below.

<p align="center">
  <img src="https://github.com/adamgracikowski/KnightsTourProblem/blob/main/KnightsTourScreenshot.png" alt="Exemplary Solution screenshot" />
</p>

Numbers in each field of the chessboard indicate order in which the knight made his tour across the board.

## Author:

My GitHub: [@adamgracikowski](https://github.com/adamgracikowski)

## Contributing:

All contributions, issues, and feature requests are welcome! 🤝

## Show your support:

Give a ⭐️ if you like this project and its documentation!
