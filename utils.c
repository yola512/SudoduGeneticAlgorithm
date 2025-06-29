#include "utils.h"

// creating new game
Game *createNewGame(Difficulty difficulty) {
    Game *game = malloc(sizeof(Game));
    if (!game) {
        printf("Memory allocation failed for Game.\n");
        return NULL;
    }
    game->board = NULL;  // will be set by generateSudoku
    return game;
}

// allocating memory for the board
int **allocateBoard() {
  int **board = malloc(9 * sizeof(int *));
  if (board == NULL) {
    perror("Error allocating memory for board\n");
    return NULL;
  }
  for (int i = 0; i < 9; i++) {
    board[i] = (int *)malloc(9 * sizeof(int));
    if (board[i] == NULL) {
      perror("Error allocating memory for board\n");
      // free previously allocated memory
      for (int j = 0; j < i; j++) {
          free(board[j]);
      }
      free(board);
      return NULL;
    }
  }
    return board;
}

void freeGame(Game *game) {
    if (game == NULL) {
        return;
    }

    // free memory for the board
    for (int i = 0; i < 9; i++) {
        free(game->board[i]);
    }
    free(game->board);
    // free 'game' struct itself
    free(game);
}

// printing board
void printBoard(Game *game) {
   if (!game || !game->board) return;

   int boardSize = 9;
   int boxSize = sqrt(boardSize);
   // numerating columns (easier for user)
    printf("     \n");
    printf("     ");
    for (int i = 0; i < boardSize; i++) {
        // +1 for 1-based indexing
        printf("%2d ", i+1);  // <-- tutaj %2d daje dwucyfrową szerokość
        if ((i + 1) % boxSize == 0 && i != boardSize - 1) {
            printf("| ");
        }
    }
    printf("|\n");

    // top border
    printf("    ");
    for (int i = 0; i < boardSize + boxSize - 1; i++) {
        printf("----");
    }
    printf("-\n");

    // rows
    for (int i = 0; i < boardSize; i++) {
        // +1 for 1-based indexing
        printf("%2d | ", i+1);  // row num
        for (int j = 0; j < boardSize; j++) {
            if (game->board[i][j] == 0)
                printf(" . ");
            else
                printf(" %d ", game->board[i][j]);

            if ((j + 1) % boxSize == 0 && j != boardSize - 1)
                printf("| ");
        }
        printf("|\n");

        // horizontal line between boxes
        if ((i + 1) % 3 == 0 && i != boardSize - 1) {
            printf("    ");
            for (int k = 0; k < boardSize + boxSize - 1; k++) {
                printf("----");
            }
            printf("-\n");
        }
    }
}

// auxiliary function to copy boards
void copyBoard(int **source, int **destination) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            destination[i][j] = source[i][j];
        }
    }
}

// auxiliary function for swapping two values
void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

void fill_board_with_nums(int **board)
{
    int box = 3;

    // iterating through each box
    for (int boxRow = 0; boxRow < box; boxRow++)
    {
        for (int boxCol = 0; boxCol < box; boxCol++)
        {
            int start_row = boxRow * box;
            int start_col = boxCol * box;

            bool used[10] = {false}; // numbers 1-9
            int missing_nums[100];
            int missing_count = 0;

            // mark numbers that have been used in current box
            for (int i = 0; i < box; i++)
            {
                for (int j = 0; j < box; j++)
                {
                    int val = board[start_row + i][start_col + j];
                    if (val >= 1 && val <= 9)
                        used[val] = true;
                }
            }

            // collect missing numbers
            for (int num = 1; num <= 9; num++)
            {
                if (!used[num])
                    missing_nums[missing_count++] = num;
            }

            // swap numbers (randomize order)
            for (int i = 0; i < missing_count; i++) {
                int j = rand() % missing_count; // random index
                swap(&missing_nums[i], &missing_nums[j]); // swap with random element
            }

            // fill empty cells (value 0) with shuffled missing numbers
            int index = 0;
            for (int i = 0; i < box; i++) {
                for (int j = 0; j < box; j++) {
                    int r = start_row + i;
                    int c = start_col + j;
                    if (board[r][c] == 0 && index < missing_count) {
                        board[r][c] = missing_nums[index++];
                    }
                }
            }
        }
    }
}