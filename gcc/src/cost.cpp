#include "../include/cost.h"
#include <string.h>
#include <algorithm>

integer memoryChunk1[64 * 4] __attribute__((aligned(64)));
integer memoryChunk2[64 * 4] __attribute__((aligned(64)));

integer new_job[64 * 4] __attribute__((aligned(64)));

integer processing_time3[64 * 4] __attribute__((aligned(64)));

integer classic_cost(integer permutation[SIZE],
                     integer processing_times0[SIZE][SIZE]) {

  integer time[M] = {0};

  for (integer j = 0; j < J; j++) {
    integer job = permutation[j];
    for (integer m = 0; m < M; m++) {
      time[m] = std::max(time[m], time[m - 1]) + processing_times0[m][job];
    }
  }
  return time[M - 1];
}

integer new_cost(integer permutation[SIZE],
                 integer processing_time1[SIZE][SIZE]) {

  integer *oldTime = memoryChunk1;
  integer *newTime = memoryChunk2;

  for (integer m = 0; m < M1; m++) {
    int job = permutation[0 + M - m];
    oldTime[m] = processing_time1[m][job];
  }

  for (integer j = 1; j < J1; j++) {

    const integer *permutation_start = permutation + j;
    // std::reverse_copy(permutation_start, permutation_start + M1, new_job);

    #pragma simd
        for (integer m = 0; m < M1; m++) {
      new_job[m] = permutation_start[M - m];
    }

        
     for (int m = 1; m < M1; m++)
      processing_time3[m] = processing_time1[m][new_job[m]];

#pragma ivdep
    for (integer m = 1; m < M1; m++) {
      newTime[m] = std::max(oldTime[m], oldTime[m - 1]) + processing_time3[m];
      //
    }
    std::swap(oldTime, newTime);
  }

  return oldTime[M1 - 1];
}
