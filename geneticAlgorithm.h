#ifndef GENETICALGORITHM_H
#define GENETICALGORITHM_H

#include "sudoku.h"

#define POPULATION_SIZE 200
#define MAX_GENERATIONS 10000
#define MUTATION_RATE 0.10

typedef struct {
    int **board;
    int fitness;
} Individual;

int calculateFitness(int **board);
void initializeIndividual(Individual *ind, int **initial);
void copyIndividual(Individual *src, Individual *dest);
void mutate(Individual *ind);
void crossover(Individual *parent1, Individual *parent2, Individual *child);
int selectParent(Individual *population);
void solveWithGeneticAlgorithm(Game *game);

#endif //GENETICALGORITHM_H
