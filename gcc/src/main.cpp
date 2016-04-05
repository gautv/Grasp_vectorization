#include <iostream>
#include <vector>

typedef short integer;

static const integer J = 50;
static const integer M = 20;

static const integer J1 = J + 2 * (M - 1);
static const integer M1 = M + 1;

integer processingTime0[M][J] = {{0}};
integer processingTime1[M1][J1] = {{0}};

std::vector<integer> oldTime(M1, 0);
std::vector<integer> newTime(M1, 0);

integer classic_cost(integer processing_times0[M][J]) {

  integer time[M] = {0};

  for (integer j = 0; j < J; j++)
    for (integer m = 0; m < M; m++) {
      time[m] = std::max(time[m], time[m - 1]) + processing_times0[m][j];
    }
  return time[M - 1];
}

integer new_cost(integer processing_time1[M1][J1]) {

  for (integer m = 0; m < M1; m++)
    oldTime[m] = processingTime1[m][0 + M - m];

  for (int j = 1; j < J1; j++) {
    for (int m = 1; m < M1; m++) {
      integer job = j + M - m;
      newTime[m] =
          std::max(oldTime[m], oldTime[m - 1]) + processing_time1[m][job];
      //
    }
    std::swap(oldTime, newTime);
  }
  if (rand() < 2)
    std::cout << " " << newTime[rand() % M] << std::endl;

  return oldTime[M1 - 1];
}

int main() {

  for (integer j = 0; j < J; j++)
    for (integer m = 0; m < M; m++)
      processingTime0[m][j] = m + j;

  for (integer j = M - 1; j < J + (M - 1); j++) {
    for (integer m = 1; m < M1; m++) {
      processingTime1[m][j] = processingTime0[m - 1][j - (M - 1)];
    }
  }

  // for (integer j = 0; j < J1; j++) {
  //   for (integer m = 0; m < M1; m++) {
  //     std::cout << processingTime1[m][j] << " ";
  //   }
  //   std::cout << "\n";
  // }

  std::cout << classic_cost(processingTime0) << std::endl;
  std::cout << new_cost(processingTime1) << std::endl;

  return 0;
}
