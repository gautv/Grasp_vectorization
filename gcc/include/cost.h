#ifndef COST_H
#define COST_H

#include <algorithm>
#include <cstdlib>
#include <iostream>

//=============Definitions==========================//

using integer = uint16_t;

static const integer J = 100;
static const integer M = 20;

static const integer J1 = J + 2*(M - 1);
static const integer M1 = M + 1;

static const integer SIZE = 64 * 4;

//================Functions==========================//
integer classic_cost(integer permutation[SIZE],integer processing_time0[SIZE][SIZE]);
integer new_cost(integer permutation[SIZE],integer processing_time1[SIZE][SIZE]);


#endif /* COST_H */
