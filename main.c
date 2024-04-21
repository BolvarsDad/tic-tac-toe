#include <stdio.h>

const int winstates[8][3] = {
    {0,1,2}, {3,4,5}, {6,7,8},  // horizontal
    {0,3,6}, {1,4,7}, {2,5,8},  // vertical
    {0,4,8}, {2,4,6}            // diagonal
};

void
print_board(char *board)
{
    for (int x = 0; x < 3; ++x) {
        for (int y = 0; y < 3; ++y)
            printf("%c ", board[x * 3 + y]);

        putchar('\n');
    }
}
    
// Applies the axiom that if A = B, and B = C, then A = C.
// Returns true if board[winstate[0]] == board[winstate[1]] == board[winstate[2]]
int
check_winstate(char *board, int const *winstate)
{
    if (board[winstate[0]] != board[winstate[1]])
        return 0;

    return board[winstate[0]] == board[winstate[2]];
}

int
check_win(char *board)
{
    for (size_t i = 0; i < 8; ++i)
        if (check_winstate(board, winstates[i]))
            return board[winstates[i][0]];

    return -1;
}

int
game_step(char *board, char player)
{   
    while (check_win(board) != -1)
    {
        print_board(board);

        printf("Select a square (0-9): ");
        int c = getchar() - '0';

        if (c < 0 || c > 9)
        {
            puts("Selection out of range");
            continue;
        }

        board[c] = player;
    }

    if (check_win(board) == player)
        goto exit_win;

    else if (check_win(board) == '\0')
        goto exit_draw;

    else
        goto exit_loss;

exit_win:
    printf("You win (%c)\n", player);
    return 0;

exit_loss:
    printf("You lose (%c)\n", player);
    return 0;

exit_draw:
    puts("Draw");
    return 0;
}

int
main(void)
{
    char board[9] = 
        "..."
        "..."
        "...";
    char player = 'x';

    while (game_step(board, player))
        ;

    return 0;
}