#include "../include/cost.h"


integer processingTime0[SIZE][SIZE] __attribute__((aligned(64))) ;
integer processingTime1[SIZE][SIZE] __attribute__((aligned(64))) = {0};


int main(int argc, char **argv) {

  //Getting arguments ...
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

  
  std::cout << classic_cost(processingTime0) << std::endl;
  std::cout << new_cost(processingTime1) << std::endl;

  return 0;
}
