#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <limits.h>
#include <time.h>

#include "Simulations.h"

int main()
{
    srand((unsigned)time(NULL));

    DoMixedSimulations();
    DoMatrixSimulations();
    DoStrongHeterogenousSimulations();

    return 1;
}
