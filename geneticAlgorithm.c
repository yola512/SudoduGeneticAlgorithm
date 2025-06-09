#include "geneticAlgorithm.h"

static int fixed[9][9]; // which cells are fixed in the original board

int calculateFitness(int **board) {
  int fitness = 0;
  // count duplicates in rows
  for (int i = 0; i < 9; i++) {
    int count[10] = {0};
    for (int j = 0; j < 9; j++) {
      count[board[i][j]]++;
    }
    for (int k = 1; k <= 9; k++) {
      if (count[k] > 1) fitness += (count[k] - 1); // every duplicate is a conflict
    }
  }
  // count duplicates in columns
  for (int j = 0; j < 9; j++) {
    int count[10] = {0};
    for (int i = 0; i < 9; i++) {
      count[board[i][j]]++;
    }
    for (int k = 1; k <= 9; k++) {
      if (count[k] > 1) fitness += (count[k] - 1);
    }
  }
  // count duplicates in 3x3 boxes
  for (int boxRow = 0; boxRow < 3; boxRow++) {
    for (int boxCol = 0; boxCol < 3; boxCol++) {
      int count[10] = {0};
      for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
          count[board[boxRow * 3 + i][boxCol * 3 + j]]++;
        }
      }
      for (int k = 1; k <= 9; k++) {
        if (count[k] > 1) fitness += (count[k] - 1);
      }
    }
  }
  return fitness; // the lower the better
}


void initializeIndividual(Individual *ind, int **initial) {
  ind -> board = allocateBoard();
  copyBoard(initial, ind->board);

  fill_board_with_nums(ind->board); // random board filling

  ind -> fitness = calculateFitness(ind->board);
}

void copyIndividual(Individual *src, Individual *dest) {
    if (!dest->board)
        dest->board = allocateBoard();

    copyBoard(src->board, dest->board);
    dest->fitness = src->fitness;
}

void mutate(Individual *ind) {
  for (int boxRow = 0; boxRow < 3; boxRow++) {
    for (int boxCol = 0; boxCol < 3; boxCol++) {
      int startRow = boxRow * 3;
      int startCol = boxCol * 3;
      // find cells with conflicts in subgrid
      int conflicts[9] = {0};
      int index = 0;
      for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
          int r = startRow + i, c = startCol + j;
          if (!fixed[r][c] && !finalCheck(ind->board, r, c, ind->board[r][c])) {
            conflicts[index++] = r * 9 + c; // store conflicts' indexes
          }
        }
      }
      if (index > 1) {
        // swap two random cells with conflicts
        int c1 = conflicts[rand() % index];
        int c2 = conflicts[rand() % index];
        if (c1 != c2) {
          int r1 = c1 / 9, c1_col = c1 % 9;
          int r2 = c2 / 9, c2_col = c2 % 9;
          swap(&ind->board[r1][c1_col], &ind->board[r2][c2_col]);
        }
      }
    }
  }
  ind->fitness = calculateFitness(ind->board);
}

void crossover(Individual *parent1, Individual *parent2, Individual *child) {
  child->board = allocateBoard();
  int crossover_point = rand() % 9;
  for (int box = 0; box < 9; box++) {
    int boxRow = (box / 3) * 3;
    int boxCol = (box % 3) * 3;
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        int r = boxRow + i;
        int c = boxCol + j;
        if (fixed[r][c]) {
          child->board[r][c] = parent1->board[r][c];
        }
        else {
          if (box < crossover_point) {
            child->board[r][c] = parent1->board[r][c];
          }
          else {
            child->board[r][c] = parent2->board[r][c];
          }
        }
      }
    }
  }
  child->fitness = calculateFitness(child->board);
}

int selectParent(Individual *population) {
  int best_index = rand() % POPULATION_SIZE;
  for (int i = 1; i < 3; i++) {
    int index = rand() % POPULATION_SIZE;
    if (population[index].fitness < population[best_index].fitness) {
      best_index = index;
    }
  }
  return best_index;
}

void solveWithGeneticAlgorithm(Game *game) {
  srand(time(NULL));
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      fixed[i][j] = (game->board[i][j] != 0);
    }
  }
  Individual population[POPULATION_SIZE];
  for (int i = 0; i < POPULATION_SIZE; i++) {
    initializeIndividual(&population[i], game->board);
  }
  Individual best;
  best.board = NULL;
  best.fitness = 9999;
  for (int generation = 0; generation < MAX_GENERATIONS; generation++) {
    for (int i = 0; i < POPULATION_SIZE; i++) {
      if (population[i].fitness < best.fitness) {
        copyIndividual(&population[i], &best);
      }
    }
    if (best.fitness == 0) {
      break;
    }
    Individual new_population[POPULATION_SIZE];
    for (int i = 0; i < POPULATION_SIZE; i++) {
      int index1 = selectParent(population);
      int index2 = selectParent(population);
      crossover(&population[index1], &population[index2], &new_population[i]);
      if ((rand() / (double)RAND_MAX) < MUTATION_RATE) {
        mutate(&new_population[i]);
      }
    }
    for (int i = 0; i < POPULATION_SIZE; i++) {
      copyIndividual(&new_population[i], &population[i]);
    }
    if (generation % 100 == 0) {
      printf("Generation %d, best fitness: %d\n", generation, best.fitness);
    }
  }
  printf("Final fitness: %d\n", best.fitness);
  copyBoard(best.board, game->board);

  // freeing memory
  for (int i = 0; i < POPULATION_SIZE; i++) {
    for (int j = 0; j < 9; j++) {
      free(population[i].board[j]);
    }
    free(population[i].board);
  }
  if (best.board) {
    for (int j = 0; j < 9; j++) {
      free(best.board[j]);
    }
    free(best.board);
  }
}