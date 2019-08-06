#include "reg_print_args.h"
#include "reg_print.h"
#include <stdio.h>
#include <stdlib.h>

void REG_PRINT_ARGS__DisplayHelp(void)
{
    printf("\n");
    printf("Usage: intel-reg-pp -a address_hex value_hex_string\n");
    printf("Usage: intel-reg-pp -n name_string value_hex_string\n");
    printf(" -a Register addres in hexidecimal\n");
    printf(" -n Register name as string, currently supported:\n");
    REG_PRINT__DisplaySupported();
    printf("\n");
    printf("intel-reg-pp -n MSR_CORE_PERF_LIMIT_REASONS 0x1c220002\n");
    printf("intel-reg-pp -a 0x64F 0x1c220002\n");
    printf("intel-reg-pp -a 64FH 0x1c220002\n");
    printf("\n");
}

void REG_PRINT_ARGS__Parse(int argc, char * argv[], stREG_PRINT__DEF* pstReg)
{
    int iIndex;
    char * pcParam = 0;
    char * pcRegAddr = 0;
    char * pcRegName = 0;
    char * pcRegValue = 0;
    unsigned long int uliRegAddr = 0 ;
    unsigned long long ullValLocal = 0;

    if (0 != pstReg)
    {
        if (argc >= 4)
        {
            for (iIndex = 1; iIndex < argc; iIndex++)
            {
                //printf("argv[%d]: %s\n", iIndex, argv[iIndex]);
                pcParam = argv[iIndex];

                if ('-' == *pcParam)
                {
                    pcParam++;

                    switch (*pcParam)
                    {
                    case 'a':
                    {
                        // Extract the address string (Examples: '0x19C' or '19CH' or '19C')
                        pcRegAddr = argv[++iIndex];
                        uliRegAddr = (unsigned long int)strtol(pcRegAddr, 0, 16);
                        REG_PRINT__AddressToStruct((unsigned int)uliRegAddr, pstReg);

                        // Now, extract the actual value
                        pcRegValue = argv[++iIndex];
                        ullValLocal = (unsigned long long)strtoll(pcRegValue, 0, 16);
                        pstReg->ullVal = ullValLocal;
                        break;
                    }

                    case 'n':
                    {
                        // Extract the register name string
                        pcRegName = argv[++iIndex];
                        REG_PRINT__StringToStruct(pcRegName, pstReg);

                        // Now, extract the actual value
                        pcRegValue = argv[++iIndex];
                        ullValLocal = (unsigned long long)strtoll(pcRegValue, 0, 16);
                        pstReg->ullVal = ullValLocal;
                        break;
                    }

                    default:
                    {
                        printf("Invalid argument!\n");
                        REG_PRINT_ARGS__DisplayHelp();
                        break;
                    }
                    }
                }
                else
                {
                    printf("Invalid argument!\n");
                    REG_PRINT_ARGS__DisplayHelp();
                }
            }
        }
        else
        {
            REG_PRINT_ARGS__DisplayHelp();
        }
    }
    else
    {
        printf("Program Error, null pointer in Parse().");
    }
}
