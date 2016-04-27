#include "../include/cost.h"
#include "../include/instance.h"

integer J, M;
integer J1, M1;
integer M2;

clock_t cost_time;

void swap(integer permutation[SIZE], integer i, integer j) {
  auto tmp = permutation[i];
  permutation[i] = permutation[j];
  permutation[j] = tmp;
}

void swap_columns(integer instance[SIZE][SIZE], integer i, integer j) {
  for (integer m = 0; m < M2; m++) {
    auto tmp = instance[m][i];
    instance[m][i] = instance[m][j];
    instance[m][j] = tmp;
  }
}

integer classical_local_search(integer permutation[SIZE],
                               integer processingTime0[SIZE][SIZE],
                               integer &min_j1, integer &min_j2) {
  int min_cost = 999999999; // minimum cost = + infinity (at first)
  bool has_found_better_minimum = true;

  while (has_found_better_minimum) {

    integer before_cost = min_cost;

    // Iteration through each elements (Permutation in O(N^2))
    for (integer j1 = 0; j1 < J; j1++)
      for (integer j2 = 0; j2 < J; j2++) // OPTIMIZATION : i2 < i1 ????
      {
        // Generation Neighbour
        swap(permutation, j1, j2);

        // Computation of the cost
        auto start_cost = clock();
        integer current_cost = classic_cost(permutation, processingTime0);
        auto end_cost = clock();
        cost_time += (end_cost - start_cost);

        // Go back to the Original Permutation
        swap(permutation, j1, j2);

        if (current_cost < min_cost) {
          min_cost = current_cost;
          min_j1 = j1;
          min_j2 = j2;
        }
      }
    has_found_better_minimum = (min_cost < before_cost);
  }
  return min_cost;
}

integer new_local_search(integer processingTime1[SIZE][SIZE], integer &min_j1,
                         integer &min_j2) {
  int min_cost = 999999999; // minimum cost = + infinity (at first)
  bool has_found_better_minimum = true;

  while (has_found_better_minimum) {

    integer before_cost = min_cost;

    // Iteration through each elements (Permutation in O(N^2))
    for (integer j1 = M - 1; j1 < J + (M - 1); j1++)
      for (integer j2 = M - 1; j2 < J + (M - 1);
           j2++) // OPTIMIZATION : i2 < i1 ????
      {
        // Generation Neighbour
        swap_columns(processingTime1, j1, j2);

        // Computation of the cost
        auto start_cost = clock();
        integer current_cost = new_cost(processingTime1);
        auto end_cost = clock();
        cost_time += (end_cost - start_cost);

        // Go back to the Original Permutation
        swap_columns(processingTime1, j1, j2);

        if (current_cost < min_cost) {
          min_cost = current_cost;
          min_j1 = j1;
          min_j2 = j2;
        }
      }
    has_found_better_minimum = (min_cost < before_cost);
  }

  return min_cost;
}

int main(int argc, char **argv) {

  auto start_main = clock();

  // Getting arguments ...
  J = atoi(argv[1]);
  M = atoi(argv[2]);
  int instance_ID = atoi(argv[3]);

  int isVectorized = atoi(argv[4]);
  int numberIterations = atoi(argv[5]);

  int aaaa = instance_ID == (-1) ? 20 : instance_ID;

  instance _instance(aaaa);

  if (instance_ID != -1) {
    *(_instance.data) >> J;
    *(_instance.data) >> M;
  } else {
    int trash;
    *(_instance.data) >> trash;
    *(_instance.data) >> trash;
  }

  J1 = J + 2 * (M - 1);
  M1 = M + 1;
  M2 = M1 + 1;

  //--- GENERATE INITIAL SOLUTION + PERMUTATION FROM OTHER INSTANCE ---

  integer permutation0[SIZE] __attribute__((aligned(64)));
  integer permutation1[SIZE] __attribute__((aligned(64)));

  for (integer j = 0; j < J; j++)
    permutation0[j] = j;

  for (integer j = 0; j < J1; ++j) {
    if (j < (M - 1) || j >= J + (M - 1))
      permutation1[j] = 0;
    else
      permutation1[j] = permutation0[j - M + 1] + (M - 1);
  }

  // Initialisation Processing Times

  integer processingTime0[SIZE][SIZE] __attribute__((aligned(64)));
  integer processingTime1[SIZE][SIZE] __attribute__((aligned(64))) = {0};

  if (instance_ID == -1) {
    for (integer j = 0; j < J; j++)
      for (integer m = 0; m < M; m++)
        processingTime0[m][j] = rand() % 64;
  }

  if (instance_ID != 1) {
    for (int j = 0; j < M; j++)
      for (int i = 0; i < J; i++)
        *(_instance.data) >> processingTime0[j][i];
  }

  for (integer j = M - 1; j < J + (M - 1); j++) {
    for (integer m = 1; m < M1; m++) {
      processingTime1[m][j] = processingTime0[m - 1][j - (M - 1)];
    }
  }

  for (integer j = 0; j < J1; j++) {
    processingTime1[M1][j] = permutation1[j];
  }

  //--- LOCAL SEARCH ---
  integer min_j1;
  integer min_j2;

  if (isVectorized == 1) {
    for (int i = 0; i < numberIterations; i++) {
      min_j1 = -1;
      min_j2 = -1;
      auto cost = new_local_search(processingTime1, min_j1, min_j2);
      /*printf("cost = %d j1 = %d j2=%d\n", cost, min_j1 - (M - 1),
        min_j2 - (M - 1));*/
    }
  } else if (isVectorized == 0) {
    for (int i = 0; i < numberIterations; i++) {
      min_j1 = -1;
      min_j2 = -1;
      auto cost =
          classical_local_search(permutation0, processingTime0, min_j1, min_j2);
      // printf("cost = %d j1 = %d j2=%d\n", cost, min_j1, min_j2);
    }
  }

  auto end_main = clock();
  auto elapsed_main = end_main - start_main;

  printf("%d %d %d %ld %ld\n",J,M,instance_ID ,cost_time, elapsed_main);

  return 0;
}
