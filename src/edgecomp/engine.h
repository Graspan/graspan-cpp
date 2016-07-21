#ifndef ENGINE_H
#define ENGINE_H

#include <ctime>

#include "compute.h"

#include "../datastructures/context.h"
#include "../datastructures/vertex.h"
#include "../datastructures/loadedvertexinterval.h"
#include "../datastructures/computationset.h"
#include "../loader/loader.h"
#include "../../test/timer.h"

int run_computation(Context &context);

#endif
