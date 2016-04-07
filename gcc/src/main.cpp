#include "../include/cost.h"
#include <cstdio>
int main(int argc, char **argv) {

  // Getting arguments ...
  int isVectorized = atoi(argv[1]);
  int numberIterations = atoi(argv[2]);

  // Intialisation permutation

  integer permutation0[SIZE] __attribute__((aligned(64)));
  integer permutation1[SIZE] __attribute__((aligned(64)));

  for (int j = 0; j < J; j++)
    permutation0[j] = j;

  for (int j = 0; j < J1; ++j) {
    if (j < (M - 1) || j >= J + (M - 1))
      permutation1[j] = 0;
    else
      permutation1[j] = permutation0[j - M + 1] + (M - 1);
  }

   // Initialisation Processing Times

  integer processingTime0[SIZE][SIZE] __attribute__((aligned(64)));
  integer processingTime1[SIZE][SIZE] __attribute__((aligned(64))) = {0};

  for (integer j = 0; j < J; j++)
    for (integer m = 0; m < M; m++)
      processingTime0[m][j] = m + j;

  for (integer j = M - 1; j < J + (M - 1); j++) {
    for (integer m = 1; m < M1; m++) {
      processingTime1[m][j] = processingTime0[m - 1][j - (M - 1)];
    }
  }

  if (isVectorized == 0) {
    for (int iteration = 0; iteration < numberIterations; iteration++)
      classic_cost(permutation0, processingTime0);
  } else {
    for (int iteration = 0; iteration < numberIterations; iteration++)
      new_cost(permutation1, processingTime1);
  }

  printf("\n\n --- Results ---\n");

  std::cout << classic_cost(permutation0, processingTime0) << std::endl;
  std::cout << new_cost(permutation1, processingTime1) << std::endl;

  return 0;
}
