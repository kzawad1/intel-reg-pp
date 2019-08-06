#include "reg_print.h"

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

void REG_PRINT_ARGS__DisplayHelp(void);
void REG_PRINT_ARGS__Parse(int argc, char* argv[], stREG_PRINT__DEF* pstReg);

#ifdef __cplusplus
}
#endif
