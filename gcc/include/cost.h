#ifndef COST_H
#define COST_H

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <iostream>

//=============Definitions==========================//

using integer = unsigned short;

extern integer J;
extern integer M;

extern integer J1;
extern integer M1;

static const integer SIZE = 64 * 10;

//================Functions==========================//
integer classic_cost(integer permutation[SIZE],
                     integer processing_time0[SIZE][SIZE]);

integer new_cost(integer processing_time1[SIZE][SIZE]);

#endif /* COST_H */
