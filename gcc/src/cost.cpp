#include "../include/cost.h"

integer memoryChunk1[64*2] __attribute__((aligned(64))) ;
integer memoryChunk2[64*2] __attribute__((aligned(64)));

integer classic_cost(integer processing_times0[SIZE][SIZE]) {

  integer time[M] = {0};

  for (integer j = 0; j < J; j++)
    for (integer m = 0; m < M; m++) {
      time[m] = std::max(time[m], time[m - 1]) + processing_times0[m][j];
    }
  return time[M - 1];
}

integer new_cost(integer processing_time1[SIZE][SIZE]) {

  integer* oldTime = memoryChunk1;
  integer* newTime = memoryChunk2;

  for (integer m = 0; m < M1; m++)
    oldTime[m] = processing_time1[m][0 + M - m];

  for (int j = 1; j < J1; j++) {
      for (int m = 1; m < M1; m++) {
      integer job = j + M - m;
      newTime[m] =
          std::max(oldTime[m], oldTime[m - 1]) + processing_time1[m][job];
      //
    }
    std::swap(oldTime, newTime);
  }

  return oldTime[M1 - 1];
}
