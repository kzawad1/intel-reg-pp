#include "reg_print.h"
#include "reg_print_de.h"
#include <stdio.h>
#include <string.h>

/* Mapping for string to id */
static stREG_PRINT__DEF G_pstXlat[] =
{
    {REG_PRINT__STRING_IA32_PERF_CTL              , REG_PRINT__ID_IA32_PERF_CTL              , REG_PRINT__ADDR_IA32_PERF_CTL              , REG_PRINT_DE__printIA32PerfCtl            , 0}, // 0
    {REG_PRINT__STRING_IA32_CLOCK_MODULATION      , REG_PRINT__ID_IA32_CLOCK_MODULATION      , REG_PRINT__ADDR_IA32_CLOCK_MODULATION      , REG_PRINT_DE__print_IA32_CLOCK_MODULATION , 0}, // 1
    {REG_PRINT__STRING_IA32_THERM_INTERRUPT       , REG_PRINT__ID_IA32_THERM_INTERRUPT       , REG_PRINT__ADDR_IA32_THERM_INTERRUPT       , REG_PRINT_DE__printIA32ThermInterrupt     , 0}, // 2
    {REG_PRINT__STRING_IA32_HWP_THERM_STATUS      , REG_PRINT__ID_IA32_HWP_THERM_STATUS      , REG_PRINT__ADDR_IA32_HWP_THERM_STATUS      , REG_PRINT_DE__printThemStatus             , 0}, // 3
    {REG_PRINT__STRING_IA32_MISC_ENABLE           , REG_PRINT__ID_IA32_MISC_ENABLE           , REG_PRINT__ADDR_IA32_MISC_ENABLE           , REG_PRINT_DE__printIA32MiscEnable         , 0}, // 4
    {REG_PRINT__STRING_IA32_PACKAGE_THERM_MARGIN  , REG_PRINT__ID_IA32_PACKAGE_THERM_MARGIN  , REG_PRINT__ADDR_IA32_PACKAGE_THERM_MARGIN  , REG_PRINT_DE__printIA32PackageThermMargin , 0}, // 5
    {REG_PRINT__STRING_IA32_TEMPERATURE_TARGET    , REG_PRINT__ID_IA32_TEMPERATURE_TARGET    , REG_PRINT__ADDR_IA32_TEMPERATURE_TARGET    , REG_PRINT_DE__printIA32TermperatureTarget , 0}, // 6
    {REG_PRINT__STRING_IA32_PKG_THERM_STATUS      , REG_PRINT__ID_IA32_PKG_THERM_STATUS      , REG_PRINT__ADDR_IA32_PKG_THERM_STATUS      , REG_PRINT_DE__print_IA32_PKG_THERM_STATUS , 0}, // 7
    {REG_PRINT__STRING_MSR_PKG_ENERGY_STATUS      , REG_PRINT__ID_MSR_PKG_ENERGY_STATUS      , REG_PRINT__ADDR_MSR_PKG_ENERGY_STATUS      , REG_PRINT_DE__print_MSR_PKG_ENERGY_STATUS , 0}, // 8
    {REG_PRINT__STRING_MSR_PKG_STATUS             , REG_PRINT__ID_MSR_PKG_STATUS             , REG_PRINT__ADDR_MSR_PKG_STATUS             , REG_PRINT_DE__print_MSR_PKG_STATUS        , 0}, // 9
    {REG_PRINT__STRING_MSR_PPERF                  , REG_PRINT__ID_MSR_PPERF                  , REG_PRINT__ADDR_MSR_PPERF                  , 0                                         , 0}, // 10
    {REG_PRINT__STRING_MSR_CORE_PERF_LIMIT_REASONS, REG_PRINT__ID_MSR_CORE_PERF_LIMIT_REASONS, REG_PRINT__ADDR_MSR_CORE_PERF_LIMIT_REASONS, REG_PRINT_DE__printMsrCorePerfLimitReasons, 0}, // 11
    {REG_PRINT__STRING_IA32_PM_ENABLE             , REG_PRINT__ID_IA32_PM_ENABLE             , REG_PRINT__ADDR_IA32_PM_ENABLE             , 0                                         , 0}, // 12
    {REG_PRINT__STRING_IA32_HWP_CAPABILITIES      , REG_PRINT__ID_IA32_HWP_CAPABILITIES      , REG_PRINT__ADDR_IA32_HWP_CAPABILITIES      , 0                                         , 0}, // 13
    {REG_PRINT__STRING_IA32_HWP_REQUEST_PKG       , REG_PRINT__ID_IA32_HWP_REQUEST_PKG       , REG_PRINT__ADDR_IA32_HWP_REQUEST_PKG       , 0                                         , 0}, // 14
    {REG_PRINT__STRING_IA32_HWP_INTERRUPT         , REG_PRINT__ID_IA32_HWP_INTERRUPT         , REG_PRINT__ADDR_IA32_HWP_INTERRUPT         , 0                                         , 0}, // 15
    {REG_PRINT__STRING_IA32_HWP_REQUEST           , REG_PRINT__ID_IA32_HWP_REQUEST           , REG_PRINT__ADDR_IA32_HWP_REQUEST           , 0                                         , 0}, // 16
    {REG_PRINT__STRING_IA32_HWP_PECI_REQUEST_INFO , REG_PRINT__ID_IA32_HWP_PECI_REQUEST_INFO , REG_PRINT__ADDR_IA32_HWP_PECI_REQUEST_INFO , 0                                         , 0}, // 17
    {REG_PRINT__STRING_IA32_HWP_STATUS            , REG_PRINT__ID_IA32_HWP_STATUS            , REG_PRINT__ADDR_IA32_HWP_STATUS            , 0                                         , 0}  // 18
};

// LEGACY FUNCTION
void REG_PRINT__Display(unsigned int uiReg, unsigned long long ullVal)
{

    switch (uiReg)
    {
        case REG_PRINT__ID_IA32_PERF_CTL:
        {
            REG_PRINT_DE__printIA32PerfCtl(0x01200);

            printf("\n\n");
            break;
        }

        case REG_PRINT__ID_IA32_CLOCK_MODULATION:
        {
            printf("NOT IMPLEMENTED\n\n");
            break;
        }

        case REG_PRINT__ID_IA32_THERM_INTERRUPT:
        {
            REG_PRINT_DE__printIA32ThermInterrupt(0x013); // Sunrise

            printf("\n\n");
            break;
        }

        case REG_PRINT__ID_IA32_HWP_THERM_STATUS:
        {
            // IA32_THERM_STATUS 
            //printThemStatus(0x0883a0800);
            REG_PRINT_DE__printThemStatus(0x88410800); // Sunrise

            printf("\n\n");
            break;
        }

        case REG_PRINT__ID_IA32_MISC_ENABLE:
        {
            REG_PRINT_DE__printIA32MiscEnable(0x04000840089); // Sunrise

            printf("\n\n");
            break;
        }

        case REG_PRINT__ID_IA32_PACKAGE_THERM_MARGIN:
        {
            REG_PRINT_DE__printIA32PackageThermMargin(0x417F);

            printf("\n\n");
            break;
        }

        case REG_PRINT__ID_IA32_TEMPERATURE_TARGET:
        {
            REG_PRINT_DE__printIA32TermperatureTarget(0X0640000);
            printf("\n\n");
            break;
        }

        case REG_PRINT__ID_IA32_PKG_THERM_STATUS:
        {
            printf("NOT IMPLEMENTED\n\n");
            break;
        }

        case REG_PRINT__ID_MSR_PKG_ENERGY_STATUS:
        {
            printf("NOT IMPLEMENTED\n\n");
            break;
        }

        case REG_PRINT__ID_MSR_PKG_STATUS:
        {
            printf("NOT IMPLEMENTED\n\n");
            break;
        }

        case REG_PRINT__ID_MSR_PPERF:
        {
            printf("NOT IMPLEMENTED\n\n");
            break;
        }

        case REG_PRINT__ID_MSR_CORE_PERF_LIMIT_REASONS:
        {
            // MSR_CORE_PERF_LIMIT_REASONS
            //printMsrCorePerfLimitReasons(0x01c220002);
            REG_PRINT_DE__printMsrCorePerfLimitReasons(0x1c220002); // Sunrise
            printf("\n\n");
            break;
        }

        case REG_PRINT__ID_IA32_PM_ENABLE:
        {
            printf("NOT IMPLEMENTED\n\n");
            break;
        }

        case REG_PRINT__ID_IA32_HWP_CAPABILITIES:
        {
            printf("NOT IMPLEMENTED\n\n");
            break;
        }

        case REG_PRINT__ID_IA32_HWP_REQUEST_PKG:
        {
            printf("NOT IMPLEMENTED\n\n");
            break;
        }

        case REG_PRINT__ID_IA32_HWP_INTERRUPT:
        {
            printf("NOT IMPLEMENTED\n\n");
            break;
        }

        case REG_PRINT__ID_IA32_HWP_REQUEST:
        {
            printf("NOT IMPLEMENTED\n\n");
            break;
        }

        case REG_PRINT__ID_IA32_HWP_PECI_REQUEST_INFO:
        {
            printf("NOT IMPLEMENTED\n\n");
            break;
        }

        case REG_PRINT__ID_IA32_HWP_STATUS:
        {
            printf("NOT IMPLEMENTED\n\n");
            break;
        }

        case REG_PRINT__ID_UNKNOWN:
        default:
        {
            printf("UNKNOWN REGISTER\n\n");
            break;
        }
    }
}

unsigned int REG_PRINT__AddressToId(unsigned int uiAddr)
{
    unsigned int uiRegId = (unsigned int)REG_PRINT__ID_UNKNOWN;
    unsigned int uiTableSize = sizeof(G_pstXlat)/sizeof(stREG_PRINT__DEF);
    unsigned int uiIndex;

    for (uiIndex = 0; uiIndex < uiTableSize; uiIndex++)
    {
        if (uiAddr == G_pstXlat[uiIndex].uiAddr)
        {
            uiRegId = G_pstXlat[uiIndex].uiID;
            break;
        }
    }

    return uiRegId;
}

void REG_PRINT__AddressToStruct(unsigned int uiAddr, stREG_PRINT__DEF* pstReg)
{
    unsigned int uiTableSize = sizeof(G_pstXlat) / sizeof(stREG_PRINT__DEF);
    unsigned int uiIndex;

    if (0 != pstReg)
    {
        for (uiIndex = 0; uiIndex < uiTableSize; uiIndex++)
        {
            if (uiAddr == G_pstXlat[uiIndex].uiAddr)
            {
                pstReg->pcStr = G_pstXlat[uiIndex].pcStr;
                pstReg->uiID = G_pstXlat[uiIndex].uiID;
                pstReg->uiAddr = G_pstXlat[uiIndex].uiAddr;
                pstReg->fun_ptr = G_pstXlat[uiIndex].fun_ptr;
                break;
            }
        }
    }
}

unsigned int REG_PRINT__StringToId(char* pcStr)
{
    unsigned int uiRegId = (unsigned int)REG_PRINT__ID_UNKNOWN;
    unsigned int uiStrLen = 0;
    unsigned int uiTableSize = sizeof(G_pstXlat) / sizeof(stREG_PRINT__DEF);
    unsigned int uiIndex;

    if (0 != pcStr)
    {
        uiStrLen = strlen(pcStr);
        if (uiStrLen > 0)
        {
            for (uiIndex = 0; uiIndex < uiTableSize; uiIndex++)
            {
                if (0 != G_pstXlat[uiIndex].pcStr)
                {
                    uiStrLen = strlen(G_pstXlat[uiIndex].pcStr);
                    if (uiStrLen > 0)
                    {
                        if (0 == strcmp(pcStr, G_pstXlat[uiIndex].pcStr))
                        {
                            uiRegId = G_pstXlat[uiIndex].uiID;
                            break;
                        }
                    }
                }
            }
        }
    }

    return uiRegId;
}

void REG_PRINT__StringToStruct(char * pcStr, stREG_PRINT__DEF * pstReg)
{
    unsigned int uiStrLen = 0;
    unsigned int uiTableSize = sizeof(G_pstXlat) / sizeof(stREG_PRINT__DEF);
    unsigned int uiIndex;

    if (0 != pstReg)
    {
        if (0 != pcStr)
        {
            uiStrLen = strlen(pcStr);
            if (uiStrLen > 0)
            {
                for (uiIndex = 0; uiIndex < uiTableSize; uiIndex++)
                {
                    if (0 != G_pstXlat[uiIndex].pcStr)
                    {
                        uiStrLen = strlen(G_pstXlat[uiIndex].pcStr);
                        if (uiStrLen > 0)
                        {
                            if (0 == strcmp(pcStr, G_pstXlat[uiIndex].pcStr))
                            {
                                pstReg->pcStr = G_pstXlat[uiIndex].pcStr;
                                pstReg->uiID = G_pstXlat[uiIndex].uiID;
                                pstReg->uiAddr = G_pstXlat[uiIndex].uiAddr;
                                pstReg->fun_ptr = G_pstXlat[uiIndex].fun_ptr;
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
}

void REG_PRINT__DisplaySupported(void)
{
    unsigned int uiTableSize = sizeof(G_pstXlat) / sizeof(stREG_PRINT__DEF);
    unsigned int uiIndex;
    unsigned int uiStrLen = 0;

    for (uiIndex = 0; uiIndex < uiTableSize; uiIndex++)
    {
        if (0 != G_pstXlat[uiIndex].pcStr)
        {
            uiStrLen = strlen(G_pstXlat[uiIndex].pcStr);
            if (uiStrLen > 0)
            {
                printf("    %xH %s\n", G_pstXlat[uiIndex].uiAddr, G_pstXlat[uiIndex].pcStr);
            }
        }
    }
}

void REG_PRINT__DisplayDetails(stREG_PRINT__DEF* pstReg)
{
    void (*fun_ptr)(unsigned long long ullVal);
    unsigned long long ullVal = 0;

    if (0 != pstReg)
    {
        ullVal = pstReg->ullVal;
        fun_ptr = pstReg->fun_ptr;

        if (REG_PRINT__ID_UNKNOWN != pstReg->uiID)
        {
            if (0 != fun_ptr)
            {
                fun_ptr(ullVal);
            }
            else
            {
                printf("No function specified for register!\n");
            }
        }
        else
        {
            printf("Unknow Register ID!\n");
        }
    }
    else
    {
        printf("Program Error!\n");
    }
}
