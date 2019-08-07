#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/* Definition(s) for Intel MSR register strings */
#define REG_PRINT__STRING_IA32_PERF_CTL                 (char *)"IA32_PERF_CTL"
#define REG_PRINT__STRING_IA32_CLOCK_MODULATION         (char *)"IA32_CLOCK_MODULATION"
#define REG_PRINT__STRING_IA32_THERM_INTERRUPT          (char *)"IA32_THERM_INTERRUPT"
#define REG_PRINT__STRING_IA32_HWP_THERM_STATUS         (char *)"IA32_HWP_THERM_STATUS"
#define REG_PRINT__STRING_IA32_MISC_ENABLE              (char *)"IA32_MISC_ENABLE"
#define REG_PRINT__STRING_IA32_PACKAGE_THERM_MARGIN     (char *)"IA32_PACKAGE_THERM_MARGIN"
#define REG_PRINT__STRING_IA32_TEMPERATURE_TARGET       (char *)"IA32_TEMPERATURE_TARGET"
#define REG_PRINT__STRING_IA32_PKG_THERM_STATUS         (char *)"IA32_PKG_THERM_STATUS"
#define REG_PRINT__STRING_MSR_PKG_ENERGY_STATUS         (char *)"MSR_PKG_ENERGY_STATUS"
#define REG_PRINT__STRING_MSR_PKG_STATUS                (char *)"MSR_PKG_STATUS"
#define REG_PRINT__STRING_MSR_PPERF                     (char *)"MSR_PPERF"
#define REG_PRINT__STRING_MSR_CORE_PERF_LIMIT_REASONS   (char *)"MSR_CORE_PERF_LIMIT_REASONS"
#define REG_PRINT__STRING_IA32_PM_ENABLE                (char *)"IA32_PM_ENABLE"
#define REG_PRINT__STRING_IA32_HWP_CAPABILITIES         (char *)"IA32_HWP_CAPABILITIES"
#define REG_PRINT__STRING_IA32_HWP_REQUEST_PKG          (char *)"IA32_HWP_REQUEST_PKG"
#define REG_PRINT__STRING_IA32_HWP_INTERRUPT            (char *)"IA32_HWP_INTERRUPT"
#define REG_PRINT__STRING_IA32_HWP_REQUEST              (char *)"IA32_HWP_REQUEST"
#define REG_PRINT__STRING_IA32_HWP_PECI_REQUEST_INFO    (char *)"IA32_HWP_PECI_REQUEST_INFO"
#define REG_PRINT__STRING_IA32_HWP_STATUS               (char *)"IA32_HWP_STATUS"

/* Definition(s) for Intel MSR register address */
#define REG_PRINT__ADDR_IA32_PERF_CTL               0x199
#define REG_PRINT__ADDR_IA32_CLOCK_MODULATION       0x19A
#define REG_PRINT__ADDR_IA32_THERM_INTERRUPT        0x19B
#define REG_PRINT__ADDR_IA32_HWP_THERM_STATUS       0x19C
#define REG_PRINT__ADDR_IA32_MISC_ENABLE            0x1A0
#define REG_PRINT__ADDR_IA32_PACKAGE_THERM_MARGIN   0x1A1
#define REG_PRINT__ADDR_IA32_TEMPERATURE_TARGET     0x1A2
#define REG_PRINT__ADDR_IA32_PKG_THERM_STATUS       0x1B1
#define REG_PRINT__ADDR_MSR_PKG_ENERGY_STATUS       0x611
#define REG_PRINT__ADDR_MSR_PKG_STATUS              0x613
#define REG_PRINT__ADDR_MSR_PPERF                   0x64E
#define REG_PRINT__ADDR_MSR_CORE_PERF_LIMIT_REASONS 0x690
#define REG_PRINT__ADDR_IA32_PM_ENABLE              0x770
#define REG_PRINT__ADDR_IA32_HWP_CAPABILITIES       0x771
#define REG_PRINT__ADDR_IA32_HWP_REQUEST_PKG        0x772
#define REG_PRINT__ADDR_IA32_HWP_INTERRUPT          0x773
#define REG_PRINT__ADDR_IA32_HWP_REQUEST            0x774
#define REG_PRINT__ADDR_IA32_HWP_PECI_REQUEST_INFO  0x775
#define REG_PRINT__ADDR_IA32_HWP_STATUS             0x777

/* Definition(s) for Intel MSR register IDs */
#define REG_PRINT__ID_IA32_PERF_CTL               0
#define REG_PRINT__ID_IA32_CLOCK_MODULATION       1
#define REG_PRINT__ID_IA32_THERM_INTERRUPT        2
#define REG_PRINT__ID_IA32_HWP_THERM_STATUS       3
#define REG_PRINT__ID_IA32_MISC_ENABLE            4
#define REG_PRINT__ID_IA32_PACKAGE_THERM_MARGIN   5
#define REG_PRINT__ID_IA32_TEMPERATURE_TARGET     6
#define REG_PRINT__ID_IA32_PKG_THERM_STATUS       7
#define REG_PRINT__ID_MSR_PKG_ENERGY_STATUS       8
#define REG_PRINT__ID_MSR_PKG_STATUS              9
#define REG_PRINT__ID_MSR_PPERF                   10
#define REG_PRINT__ID_MSR_CORE_PERF_LIMIT_REASONS 11
#define REG_PRINT__ID_IA32_PM_ENABLE              12
#define REG_PRINT__ID_IA32_HWP_CAPABILITIES       13
#define REG_PRINT__ID_IA32_HWP_REQUEST_PKG        14
#define REG_PRINT__ID_IA32_HWP_INTERRUPT          15
#define REG_PRINT__ID_IA32_HWP_REQUEST            16
#define REG_PRINT__ID_IA32_HWP_PECI_REQUEST_INFO  17
#define REG_PRINT__ID_IA32_HWP_STATUS             18
#define REG_PRINT__ID_UNKNOWN                     (unsigned int)-1

typedef struct
{
    const char* pcStr;
    unsigned int  uiID;
    unsigned int  uiAddr;
    void (*fun_ptr)(unsigned long long ullVal);
    unsigned long long ullVal;
} stREG_PRINT__DEF;

void REG_PRINT__Display(unsigned int uiReg, unsigned long long ullVal);
unsigned int REG_PRINT__AddressToId(unsigned int uiAddr);
void REG_PRINT__AddressToStruct(unsigned int uiAddr, stREG_PRINT__DEF* pstReg);
unsigned int REG_PRINT__StringToId(char * pcStr);
void REG_PRINT__StringToStruct(char* pcStr, stREG_PRINT__DEF* pstReg);
void REG_PRINT__DisplaySupported(void);
void REG_PRINT__DisplayDetails(stREG_PRINT__DEF* pstReg);

#ifdef __cplusplus
}
#endif
