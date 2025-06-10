# Sudoku Solver using Genetic Algorithm

## Project Description
The project implements a genetic algorithm to solve Sudoku puzzles in C. The algorithm generates a population of random boards that evolve through crossover and mutation until a correct solution is found (fitness = 0).

## Main Components
- **Tournament Selection**: Parent selection based on comparing the fitness of 3 randomly chosen individuals.
- **Crossover**: Creating new boards by combining fragments of two parents.
- **Mutation**: Random swapping of numbers in 3x3 subgrids to resolve conflicts.
- **Fitness**: Board evaluation based on the number of duplicates in rows, columns, and 3x3 subgrids.
- Support for fixed cells (cells that are already filled and can't be changed) in the Sudoku board.

## Configuration

The algorithm supports tuning several parameters:
- **POPULATION_SIZE:** number of individuals in each generation
- **MAX_GENERATIONS:** maximum number of generations before stopping
- **MUTATION_RATE:** probability that a mutation will occur for each individual.
- **CROSSOVER_RATE:** probability that crossover will occur between two selected parents when creating offspring. If crossover does not occur, the offspring is a direct copy of one of the parents.
  
To evaluate the impact of different configurations on Sudoku solving, you can modify the values of above-mentioned parameters declared in geneticalalgorithm.h.

## Possible Extensions
1. _**Elitism**_

The current version of the algorithm does not include elitism, meaning the best individual in a generation can be lost in the next one. Adding elitism (preserving the best individual unchanged) could improve the stability and performance of the evolutionary process.

2. _**User interface**_

3. _**Mutation extention**_

The mutation operation is now limited to swapping conflicting cells within 3x3 blocks. It may also be beneficial to perform swaps in rows or columns, which could help reduce conflicts in those units more efficiently.

4. _**Multi-point / uniform crossover**_

Only single-point crossover is used, with no implementation of multi-point or uniform crossover.

5. _**Roulette wheel selection / Ranking selection**_

The algorithm currently uses only tournament selection, without implementing other selection methods such as roulette wheel selection.

## Limitations:
1.	_**Performance on Hard Puzzles**_

The solver may struggle with very hard or sparse Sudoku boards, potentially requiring many generations or getting stuck in local optima.

https://github.com/user-attachments/assets/4b87fef4-4595-4a59-9f62-b25a5087f06e

