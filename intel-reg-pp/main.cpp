#include "reg_print.h"
#include "reg_print_args.h"
#include <stdio.h>

int main(int argc, char * argv[])
{
    stREG_PRINT__DEF stReg = { 0, REG_PRINT__ID_UNKNOWN, 0, 0, 0};

    printf("\nIntel Register Pretty Print (intel-reg-pp) v1.0.0\n\n");

    // Determine which register to print
    REG_PRINT_ARGS__Parse(argc, argv, &stReg);

    // Now, perform the pretty-print
    REG_PRINT__DisplayDetails(&stReg);

    return 0;
}
