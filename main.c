#include <stdio.h>
#include "geneticAlgorithm.h"

int main(void) {
    Game *currentGame = NULL;
    int running = 1;
    char input[100];
    int option;


     while (running) {
         printf("\n********************************\n");
         printf("*       WELCOME TO SUDOKU!     *\n");
         printf("********************************\n");
         printf("\nMain Menu:\n");
         printf("--------------\n");
         printf("  1. New game.\n");
         printf("  2. Exit.\n");

         printf("Please enter an option from the main menu: ");
         if (fgets(input, sizeof(input), stdin) == NULL) {
             printf("Error reading input\n");
             continue;
         }

         if (sscanf(input, "%d", &option) != 1) {
             printf("Invalid input. Please enter a number: 1 or 2.\n");
             continue;
         }

         switch (option) {
             case 1: {
                 if (currentGame) {
                     freeGame(currentGame);
                 }

                 Difficulty difficulty;
                 char difficultyInput[10];

                 // difficulty selection
                 printf("\n*** Select Difficulty ***\n");
                 printf("[ Difficulty is based on the number of hints you get :) ]\n");
                 printf("  a. Easy\n");
                 printf("  b. Medium\n");
                 printf("  c. Hard\n");
                 printf("Difficulty choice:");

                 if (fgets(difficultyInput, sizeof(difficultyInput), stdin) == NULL) {
                     printf("Error reading input\n");
                     continue;
                 }
                 // remove newline
                 difficultyInput[strcspn(difficultyInput, "\n")] = '\0';
                 if (strlen(difficultyInput) != 1) {
                     printf("Please enter exactly one character (a/b/c).\n");
                     continue;
                 }
                 switch (difficultyInput[0]) {
                     case 'a': case 'A': difficulty = EASY; break;
                     case 'b': case 'B': difficulty = MEDIUM; break;
                     case 'c': case 'C': difficulty = HARD; break;
                     default:
                         printf("Invalid choice! Please enter a, b or c.\n");
                         continue;
                 }

                 currentGame = createNewGame(difficulty);
                 currentGame->board = generateSudoku(difficulty, currentGame);

                 printf("\n--------------------------------------------\n");
                 printf("- GENERATED SUDOKU BOARD (before solving) -\n");
                 printf("--------------------------------------------\n");
                 printBoard(currentGame);

                 solveWithGeneticAlgorithm(currentGame);

                 printf("\n---------------------------------\n");
                 printf("- SOLVED SUDOKU BOARD (after Genetic Algorithm) -\n");
                 printf("---------------------------------\n");
                 printBoard(currentGame);

                 if (currentGame) {
                     freeGame(currentGame);
                 }

                 break;
             }
             case 2: {
                 if (currentGame) {
                     freeGame(currentGame);
                 }
                 printf("See you next time! :)\n");
                 running = 0;
                 break;
             }
             default: {
                 printf("Invalid option!\n");
             }
         }
     }

    return 0;
}