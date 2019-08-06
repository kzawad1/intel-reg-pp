#pragma once

#ifdef __cplusplus
extern "C" {
#endif

    void REG_PRINT_DE__printIA32PerfCtl(unsigned long long ullVal);
    void REG_PRINT_DE__print_IA32_CLOCK_MODULATION(unsigned long long ullVal);
    void REG_PRINT_DE__printIA32ThermInterrupt(unsigned long long ullVal);
    void REG_PRINT_DE__printThemStatus(unsigned long long ullVal);
    void REG_PRINT_DE__printIA32MiscEnable(unsigned long long ullVal);
    void REG_PRINT_DE__printIA32PackageThermMargin(unsigned long long ullVal);
    void REG_PRINT_DE__printIA32TermperatureTarget(unsigned long long ullVal);
    void REG_PRINT_DE__print_IA32_PKG_THERM_STATUS(unsigned long long ullVal);
    void REG_PRINT_DE__print_MSR_PKG_ENERGY_STATUS(unsigned long long ullVal);
    void REG_PRINT_DE__print_IA32_PKG_THERM_STATUS(unsigned long long ullVal);
    void REG_PRINT_DE__print_MSR_PKG_STATUS(unsigned long long ullVal);
    void REG_PRINT_DE__printMsrCorePerfLimitReasons(unsigned long long ullVal);

#ifdef __cplusplus
}
#endif