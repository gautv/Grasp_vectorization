#include "../include/cost.h"

integer processingTime0[SIZE][SIZE] __attribute__((aligned(64)));
integer processingTime1[SIZE][SIZE] __attribute__((aligned(64))) = {0};

int main(int argc, char **argv) {

  // Getting arguments ...
  int isVectorized = atoi(argv[1]);
  int numberIterations = atoi(argv[2]);

  // Initialisation Processing Times
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
      classic_cost(processingTime0);
  } else {
    for (int iteration = 0; iteration < numberIterations; iteration++)
      new_cost(processingTime1);
  }

  //--- GENERATE INITIAL SOLUTION ---
  integer permutation[J];

  for (int j = 0, j < J; j++)
    permutation[j] = j;

  //--- LOCAL SEARCH ---
  {
    integer min_cost = 99999;
    integer min_j1 = 1;
    integer min_j2 = -1;
    bool has_found_better_minimum = true;

    while (has_found_better_minimum) {

      integer before_cost = min_cost;

      // Iteration through each elements (Permutation in O(N^2))
      for (integer i1 = 0; i1 < J; i1++)
        for (integer i2 = 0; i2 < J; i2++) // OPTIMIZATION : i2 < i1 ????
        {
          // Generation Neighbour
          std::swap(permutation[i1], permutation[i2]);

          // Computation of the cost
          integer current_cost = classic_cost(processingTime0);

          // Go back to the Original Permutation
          std::swap(permutation[i1], permutation[i2]);

          if (current_cost < min_cost) {
            min_cost = currrent_cost;
            min_i1 = i1;
            min_i2 = i2;
          }
        }

      has_found_better_minimum = (min_cost < before_cost)
    }
  }
}

return 0;
}
