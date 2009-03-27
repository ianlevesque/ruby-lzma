// LzmaBench.h

#ifndef __LzmaBench_h
#define __LzmaBench_h

#include <stdio.h>
#include "Types.h"

int LzmaBenchmark(FILE *f, UInt32 numIterations, UInt32 dictionarySize, bool isBT4);

#endif
