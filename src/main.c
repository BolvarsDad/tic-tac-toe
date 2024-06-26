#include <stdio.h>

#include "minimax.h"

#define MIN(num1, num2) \
    ( (num1) < (num2) ? (num1) : (num2) )

static const int winstates[8][3] = {
    {0,1,2}, {3,4,5}, {6,7,8},  // horizontal
    {0,3,6}, {1,4,7}, {2,5,8},  // vertical
    {0,4,8}, {2,4,6}            // diagonal
};

static const char *gameres_str[3] = {
    "Game was a draw",
    "Player won",
    "Player lost"
};

void
print_board(char *board)
{
    static char *player_chr = ".xo?";

    for (int y = 0; y < 3; ++y){
        for (int x = 0; x < 3; ++x){
            int player = MIN(3, board[y * 3 + x]);

            if (player < 0)
                player = 3;

            printf("%c ", player_chr[player]);
        }

        putchar('\n');
    }
}

// Since the return value here will be either 0, 1, or 2, this works fine.
// Since there's no overlap of ones, any mismatch will result in a 0.
int
is_winstate(char *board, int const *winstate)
{
    return board[winstate[0]] & board[winstate[1]] & board[winstate[2]];
}

int
board_full(char *board)
{
    for (size_t i = 0; i < 8; ++i)
        if (board[i] == 0)
            return 0;

    return 1;
}

int
check_win(char *board)
{
    for (size_t i = 0; i < 8; ++i)
        if (is_winstate(board, winstates[i]))
        {
            return board[winstates[i][0]];
        }

    return 0;
}

int
get_digit()
{
    int c = getchar() - '0';
    int flush;

    while ((flush = getchar()) != '\n' && flush != EOF);

    return c;
}

int
game_step(char *board, char player)
{
    while (check_win(board) == 0)
    {
        if (board_full(board))
            break;

        print_board(board);
        printf("Select a square (0-8): ");

        int idx = get_digit();
        if (idx < 0 || idx > 8 || board[idx] != 0)
        {
            puts("Invalid input");
        }
        else {
            board[idx] = player;
        }
    }

    print_board(board);
    printf("%s\n", gameres_str[check_win(board)]);
    return 0;
}

int
main(void)
{
    char board[9] = {0,0,0,0,0,0,0,0,0};
    char player = 1; // 1 = x
    char opponent = 2; // 2 = o

    while (game_step(board, player))
        ;

    return 0;
}