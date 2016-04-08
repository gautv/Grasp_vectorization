#include "../include/cost.h"

int main(int argc, char **argv) {

  // Getting arguments ...
  int isVectorized = atoi(argv[1]);
  int numberIterations = atoi(argv[2]);

  //--- GENERATE INITIAL SOLUTION + PERMUTATION FROM OTHER INSTANCE ---

  integer permutation0[SIZE] __attribute__((aligned(64)));
  integer permutation1[SIZE] __attribute__((aligned(64)));

  // for (integer j = 0; j < J; j++)
  //  permutation0[j] = j;

  permutation0[0] = 0;
  permutation0[1] = 1;
  permutation0[2] = 2;

  for (integer j = 0; j < J1; ++j) {
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

  //--- LOCAL SEARCH ---
  {
    int min_cost = 999999999; // minimum cost = + infinity (at first)
    integer min_j1 = -1;
    integer min_j2 = -1;
    bool has_found_better_minimum = true;

    while (has_found_better_minimum) {

      integer before_cost = min_cost;

      // Iteration through each elements (Permutation in O(N^2))
      for (integer j1 = 0; j1 < J; j1++)
        for (integer j2 = 0; j2 < J; j2++) // OPTIMIZATION : i2 < i1 ????
        {
          // Generation Neighbour
          std::swap(permutation0[j1], permutation0[j2]);

          // Computation of the cost
          integer current_cost = classic_cost(permutation0,processingTime0);

          // Go back to the Original Permutation
          std::swap(permutation0[j1], permutation0[j2]);

          if (current_cost < min_cost) {
            min_cost = current_cost;
            min_j1 = j1;
            min_j2 = j2;
          }
        }
      has_found_better_minimum = (min_cost < before_cost);
    }
    printf("min j1 = %d\tmin j2=%d\tmin cost = %d\n",min_j1,min_j2,min_cost);
  }


  return 0;
}

