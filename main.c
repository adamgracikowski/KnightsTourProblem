#include "KnightsTourProblem.c"

int main(void)
{
#if 0  // default Puzzle solution using backtracking
        solveKnightsTourProblem(HEIGHT, WIDTH);
#endif // default Puzzle solution using backtracking

#if 1 // interactive
    int height, width;
    printf("Enter height: ");
    if (scanf("%d", &height) != 1)
    {
        printf("Invalid Input.\n");
        return -1;
    }
    printf("Enter width: ");
    if (scanf("%d", &width) != 1)
    {
        printf("Invalid Input.\n");
        return -1;
    }

#if 0  // using backtracing algorithm
	solveKnightsTourProblem(height, width);
#endif // using backtracing algorithm

#if 1 // using Warnsdorff's Rule and starting from an upper left posiiton
    solveUsingWarnsdorffsRule((Position){0, 0}, height, width);
#endif // using Warnsdorff's Rule and starting from an upper left posiiton

#endif // intereactive

    system("pause");
    return 0;
}