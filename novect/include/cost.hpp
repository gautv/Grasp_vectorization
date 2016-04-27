#ifndef COST_H
#define COST_H

#include <algorithm>
#include <cstdlib>
#include <iostream>

//=============Definitions==========================//

typedef int16_t integer;

static const integer J = 50;
static const integer M = 20;

static const integer J1 = J + 2 * (M - 1);
static const integer M1 = M + 1;

//================Functions==========================//

integer classic_cost(integer processing_times0[64 * 5][64 * 5]);
integer new_cost(integer processing_time1[64 * 5][64 * 5]);


#endif /* COST_H */
