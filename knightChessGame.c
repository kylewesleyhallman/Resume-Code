#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
 * Display the board.
 */
void print_board(char b[][8])
{
    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            printf("%c ", b[row][col]);
        }
        printf("\n");
    }
}

/*
 * Initialize the board to be all underscores.
 */
void init_board(char b[][8])
{
    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            b[row][col] = '_';
        }
    }
}

/*
 * Get a move from the user.
 *
 *   2   3
 * q       e
 *     K
 * a       d
 *   z   x
 *
 */
char get_move()
{
    char m;
    int valid = 0;
    do
    {
        printf("What's your move? ");
        scanf(" %c", &m);
        if (m != '2' && m != '3' && m != 'e' && m != 'd' &&
            m != 'x' && m != 'z' && m != 'a' && m != 'q')
        {
            printf("Moves are 2, 3, e, d, x, z, a, q\n");
        }
        else
        {
            valid = 1;
        }
    } while (! valid);
    
    return m;
}

/*
 * The function is passed the knight's x and y location,
 * plus the user's move (from get_move()).
 * The move will be one of 2, 3, e, d, x, z, a, q.
 * The function should change the x and y location based
 * on the direction the user selected.
 * The function returns 1 (true) if the move was valid.
 * Returns 0 if the move would cause the knight to move
 * off the board. If the move is invalid, the knight's
 * position does not change.
 *
 * 
 */
int move_knight(int *ky, int *kx, char m)
{
    if (m =='2') //move up 2 and left 1. ' ' around 2 
    {
        *ky = *ky - 1;
        *kx = *kx - 2;
        if (*ky < 0 || *kx < 0 || *ky > 7 || *kx > 7)
        {
            return 0;
        }

    }
    
    if (m =='3') //move up 2 and left 1. ' ' around 2 
    {
        *ky = *ky + 1;
        *kx = *kx - 2;
        if (*ky < 0 || *kx < 0 || *ky > 7 || *kx > 7)
        {
            return 0;
        }

    }
    
    if (m =='e') //move up 2 and left 1. ' ' around 2 
    {
        *ky = *ky + 2;
        *kx = *kx - 1;
        if (*ky < 0 || *kx < 0 || *ky > 7 || *kx > 7)
        {
            return 0;
        }

    }
    
    if (m =='d') //move up 2 and left 1. ' ' around 2 
    {
        *ky = *ky + 2;
        *kx = *kx + 1;
        if (*ky < 0 || *kx < 0 || *ky > 7 || *kx > 7)
        {
            return 0;
        }

    }
    
    if (m =='x') //move up 2 and left 1. ' ' around 2 
    {
        *ky = *ky + 1;
        *kx = *kx + 2;
        if (*ky < 0 || *kx < 0 || *ky > 7 || *kx > 7)
        {
            return 0;
        }

    }
    
    if (m =='z') //move up 2 and left 1. ' ' around 2 
    {
        *ky = *ky - 1;
        *kx = *kx + 2;
        if (*ky < 0 || *kx < 0 || *ky > 7 || *kx > 7)
        {
            return 0;
        }

    }
    
    if (m =='a') //move up 2 and left 1. ' ' around 2 
    {
        *ky = *ky - 2;
        *kx = *kx + 1;
        if (*ky < 0 || *kx < 0 || *ky > 7 || *kx > 7)
        {
            return 0;
        }

    }
    
    if (m =='q') //move up 2 and left 1. ' ' around 2 
    {
        *ky = *ky - 2;
        *kx = *kx - 1;
        if (*ky < 0 || *kx < 0 || *ky > 7 || *kx > 7)
        {
            return 0;
        }

    }
    
    
    
return 1;
}


int main()
{
    char board[8][8];
    int kx = 1, ky = 7;   // Starting location for knight
    
    srand(time(NULL));    // Seed the random number generator
    
    int tx, ty;           // Target location
    
    do
    {
        tx = rand() % 8;  // Pick random target
        ty = rand() % 8;
    } while (tx == kx && ty == ky);
    
    init_board(board);
    board[ty][tx] = 'G';    // Place goal and knight
    board[ky][kx] = 'K';
    
    print_board(board);
    
    int moves = 0;
    
    while (tx != kx || ty != ky)
    
    {
        char move = get_move();
        board[ky][kx] = '_';
        int ret = move_knight(&kx, &ky, move);
        board[ky][kx] = 'K';
        if (!ret)
        {
            printf("Invalid move.\n");
        }
        else
        {
            print_board(board);
            moves++;
        }
    }
    printf("You won in %d moves!\n", moves);
}