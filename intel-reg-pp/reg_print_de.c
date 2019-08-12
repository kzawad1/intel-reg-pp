#include "reg_print_de.h"
#include <stdio.h>

// https://software.intel.com/sites/default/files/managed/39/c5/325462-sdm-vol-1-2abcd-3abcd.pdf

//#############################################################################
//#
//#############################################################################
static void REG_PRINT_DE__makeBinaryString(unsigned long long ullVal, char* pcBuff, unsigned int uiBuffSize)
{
    unsigned int uiIndex;
    unsigned int uiMaxRegBits = sizeof(unsigned long long) * 8;
    char* pcAddr = pcBuff;

    if (0 != pcBuff)
    {
        if (uiBuffSize >= 67)
        {
            *pcAddr++ = '0';
            *pcAddr++ = 'b';

            for (uiIndex = 0; uiIndex <= uiMaxRegBits; uiIndex++)
            {
                if (ullVal & ((unsigned long long)1 << (uiMaxRegBits - uiIndex)))
                {
                    *pcAddr++ = '1';
                }
                else
                {
                    *pcAddr++ = '0';
                }
            }
        }
    }
}

//#############################################################################
//# IA32_PERF_CTL
//# https://www.intel.com/content/www/us/en/embedded/testing-and-validation/cpu-monitoring-dts-peci-paper.html 
//# 
//#############################################################################
void REG_PRINT_DE__printIA32PerfCtl(unsigned long long ullVal)
{
    char cBuffValAsBin[100] = { 0 };
    unsigned int uiTargPerfStateVal = 0;

    // Create a binary string from value
    REG_PRINT_DE__makeBinaryString(ullVal, cBuffValAsBin, sizeof(cBuffValAsBin));

    uiTargPerfStateVal = (unsigned int)((unsigned long long)0x7FFF & ullVal);

    printf("[199H] IA32_PERF_CTL\n");
    printf("  Command to read: sudo rdmsr 0x199 -f 63:0\n");
    printf("Value of register is: %08llx\n", ullVal);
    printf("  64  60        50        40        30        20        10\n");
    printf("  43210987654321098765432109876543210987654321098765432109876543210\n");
    printf("%s\n", cBuffValAsBin);
    printf("   └───────────────┬─────────────┘│└──────┬───────┘└──────┬───────┘\n");
    printf("              Reserved            │       │               │        \n");
    printf("IDA Engage (R/W) 1:disengage IDA ─┘       │               │        \n");
    printf("Reserved ─────────────────────────────────┘               │        \n");
    printf("Target Performance State Value ───────────────────────────┘  0x%x -> %d  \n", uiTargPerfStateVal, uiTargPerfStateVal);
}

//#############################################################################
//# IA32_CLOCK_MODULATION
//# http://kib.kiev.ua/x86docs/SDMs/335592-063.pdf
//# 
//#############################################################################
void REG_PRINT_DE__print_IA32_CLOCK_MODULATION(unsigned long long ullVal)
{
    char cBuffValAsBin[100] = { 0 };

    // Create a binary string from value
    REG_PRINT_DE__makeBinaryString(ullVal, cBuffValAsBin, sizeof(cBuffValAsBin));

    printf("[19AH] IA32_CLOCK_MODULATION\n");
    printf("  Command to read: sudo rdmsr 0x19A -f 63:0\n");
    printf("Value of register is: %08llx\n", ullVal);
    printf("  64  60        50        40        30        20        10\n");
    printf("  43210987654321098765432109876543210987654321098765432109876543210\n");
    printf("%s\n", cBuffValAsBin);
    printf("   └─────────────────────────────┬───────────────────────────┘│└┬┘│\n");
    printf("                             Reserved                         │ │ │\n");
    printf("On-Demand Clock Modulation Enable ────────────────────────────┘ │ │\n");
    printf("On-Demand Clock Modulation Duty Cycle ──────────────────────────┘ │\n");
    printf("Extended On-Demand Clock Modulation Duty Cycle ───────────────────┘\n");
}

//#############################################################################
//# IA32_THERM_INTERRUPT
//# https://www.intel.com/content/www/us/en/embedded/testing-and-validation/cpu-monitoring-dts-peci-paper.html 
//# 
//#############################################################################
void REG_PRINT_DE__printIA32ThermInterrupt(unsigned long long ullVal)
{
    char cBuffValAsBin[100] = { 0 };

    // Create a binary string from value
    REG_PRINT_DE__makeBinaryString(ullVal, cBuffValAsBin, sizeof(cBuffValAsBin));

    printf("[19BH] IA32_THERM_INTERRUPT\n");
    printf("  Command to read: sudo rdmsr 0x19b -f 63:0\n");
    printf("Value of register is: %08llx\n", ullVal);
    printf("  64  60        50        40        30        20        10\n");
    printf("  43210987654321098765432109876543210987654321098765432109876543210\n");
    printf("%s\n", cBuffValAsBin);
    printf("   └───────────────┬──────────────────────┘│└──┬──┘│└──┬──┘└┬┘│││││\n");
    printf("              Reserved                     │   │   │   │    │ │││││\n");
    printf("Threshold #2 INT Enable ───────────────────┘   │   │   │    │ │││││\n");
    printf("Threshold #2 Value ────────────────────────────┘   │   │    │ │││││\n");
    printf("Threshold #1 INT Enable ───────────────────────────┘   │    │ │││││\n");
    printf("Threshold #1 Value ────────────────────────────────────┘    │ │││││\n");
    printf("Reserved ───────────────────────────────────────────────────┘ │││││\n");
    printf("Critical Temperature Enable ──────────────────────────────────┘││││\n");
    printf("FORCEPR# INT Enable ───────────────────────────────────────────┘│││\n");
    printf("PROCHOT# INT enable ────────────────────────────────────────────┘││\n");
    printf("Low-Temperature INT enable ──────────────────────────────────────┘│\n");
    printf("High-Temperature INT Enable ──────────────────────────────────────┘\n");
}

//#############################################################################
//#
//#############################################################################
void REG_PRINT_DE__printThemStatus(unsigned long long ullVal)
{
    char cBuffValAsBin[100] = { 0 };
    //unsigned long long ullTempMask = 0x0078000000;
    unsigned long long ullTempMask = 0x07F0000;
    unsigned long long ullTempValue;
    unsigned int uiTempValueInDegC;
    unsigned int uiTempValueInDegF;

    // Extract the temperature
    ullTempValue = (ullVal & ullTempMask);
    uiTempValueInDegC = (unsigned int)(ullTempValue >> 16);
    uiTempValueInDegF = ((uiTempValueInDegC * 9) / 5) + 32;

    // Create a binary string from value
    REG_PRINT_DE__makeBinaryString(ullVal, cBuffValAsBin, sizeof(cBuffValAsBin));

    printf("[19CH] IA32_HWP_THERM_STATUS Register With HWP Feedback\n");
    printf("  Command to read: sudo rdmsr 0x19c -f 63:0\n");
    printf("Value of register is: %08llx\n", ullVal);
    printf("  64  60        50        40        30        20        10\n");
    printf("  43210987654321098765432109876543210987654321098765432109876543210\n");
    printf("%s\n", cBuffValAsBin);
    printf("  └───────────────┬───────────────┘│└─┬┘└─┬┘└──┬──┘││││││││││││││││\n");
    printf("              Reserved             │  │   │    │   ││││││││││││││││\n");
    printf("Reading Valid ─────────────────────┘  │   │    │   ││││││││││││││││\n");
    printf("Reading in Deg. Celcius ──────────────┘   │    │   ││││││││││││││││\n");
    printf("Reserved ─────────────────────────────────┘    │   ││││││││││││││││\n");
    printf("Digital Readout ───────────────────────────────┘   ││││││││││││││││ %d C -> %d F\n", uiTempValueInDegC, uiTempValueInDegF);
    printf("Cross-domain Limit Log ────────────────────────────┘│││││││││││││││\n");
    printf("Cross-domain Limit Status ──────────────────────────┘││││││││││││││\n");
    printf("Current Limit Log ───────────────────────────────────┘│││││││││││││\n");
    printf("Current Limit Status ─────────────────────────────────┘││││││││││││\n");
    printf("Power Limit Notification Log ──────────────────────────┘│││││││││││\n");
    printf("Power Limit Notification Status ────────────────────────┘││││││││││\n");
    printf("Thermal Threshold #2 Log ────────────────────────────────┘│││││││││\n");
    printf("Thermal Threshold #2 Status ──────────────────────────────┘││││││││\n");
    printf("Thermal Threshold #1 Log ──────────────────────────────────┘│││││││\n");
    printf("Thermal Threshold #1 Status ────────────────────────────────┘││││││\n");
    printf("Critical Temperature Log ────────────────────────────────────┘│││││\n");
    printf("Critical Temperature Status ──────────────────────────────────┘││││\n");
    printf("PROCHOT# or FORCEPR# Log ──────────────────────────────────────┘│││\n");
    printf("PROCHOT# or FORCEPR# Event ─────────────────────────────────────┘││\n");
    printf("Thermal Status Log ──────────────────────────────────────────────┘│\n");
    printf("Thermal Status ───────────────────────────────────────────────────┘\n");
}

//#############################################################################
//# IA32_MISC_ENABLE
//# https://www.intel.com/content/dam/www/public/us/en/documents/datasheets/atom-processor-s1200-datasheet-vol-2.pdf
//# 
//#############################################################################
void REG_PRINT_DE__printIA32MiscEnable(unsigned long long ullVal)
{
    char cBuffValAsBin[100] = { 0 };

    // Create a binary string from value
    REG_PRINT_DE__makeBinaryString(ullVal, cBuffValAsBin, sizeof(cBuffValAsBin));

    printf("[1A0H] IA32_MISC_ENABLE\n");
    printf("  Command to read: sudo rdmsr 0x1a0 -f 63:0\n");
    printf("Value of register is: %08llx\n", ullVal);
    printf("  64  60        50        40        30        20        10\n");
    printf("   43210987654321098765432109876543210987654321098765432109876543210\n");
    printf(" %s\n", cBuffValAsBin);
    printf("   └────────────────┬───────────┘│││└┬─┘│││└┤│││││││└┤│└┤│└┤│└┬┘│└┤│\n");
    printf("               Reserved          │││ │  │││ ││││││││ ││ ││ ││ │ │ ││\n");
    printf("Execute-Disable Bit Disable(R/W) ┘││ │  │││ ││││││││ ││ ││ ││ │ │ ││\n");
    printf("Hard C4E Enable (R/W)  ───────────┘│ │  │││ ││││││││ ││ ││ ││ │ │ ││\n");
    printf("C4E Enable (R/W)  ─────────────────┘ │  │││ ││││││││ ││ ││ ││ │ │ ││\n");
    printf("Reserved ────────────────────────────┘  │││ ││││││││ ││ ││ ││ │ │ ││\n");
    printf("ACNT2 Enable (R/W) ─────────────────────┘││ ││││││││ ││ ││ ││ │ │ ││\n");
    printf("C2E Enable (R/W) ────────────────────────┘│ ││││││││ ││ ││ ││ │ │ ││\n");
    printf("C1E Enable (R/W) ─────────────────────────┘ ││││││││ ││ ││ ││ │ │ ││\n");
    printf("Reserved ───────────────────────────────────┘│││││││ ││ ││ ││ │ │ ││\n");
    printf("Limit CPUID Maxval (R/W) ────────────────────┘││││││ ││ ││ ││ │ │ ││\n");
    printf("RORCEPR Input Enable (R/W) ───────────────────┘│││││ ││ ││ ││ │ │ ││\n");
    printf("SpeedStep Tech. Select Lock (R/W) ─────────────┘││││ ││ ││ ││ │ │ ││\n");
    printf("Reserved ───────────────────────────────────────┘│││ ││ ││ ││ │ │ ││\n");
    printf("Enable Monitor FSM (R/W) ────────────────────────┘││ ││ ││ ││ │ │ ││\n");
    printf("Bi-Dir PROCHOT# Enable (R0) ──────────────────────┘│ ││ ││ ││ │ │ ││\n");
    printf("SpeedStep Tech. Enable (R/W) ──────────────────────┘ ││ ││ ││ │ │ ││\n");
    printf("Reserved ────────────────────────────────────────────┘│ ││ ││ │ │ ││\n");
    printf("TM2 Enable (R/W) ─────────────────────────────────────┘ ││ ││ │ │ ││\n");
    printf("Reserved ───────────────────────────────────────────────┘│ ││ │ │ ││\n");
    printf("FERR# Multiplexing Enable (R/W) ─────────────────────────┘ ││ │ │ ││\n");
    printf("Reserved ──────────────────────────────────────────────────┘│ │ │ ││\n");
    printf("Performance Monitoring Available (R0) ──────────────────────┘ │ │ ││\n");
    printf("Reserved ─────────────────────────────────────────────────────┘ │ ││\n");
    printf("TM1 Enable (R/W) ───────────────────────────────────────────────┘ ││\n");
    printf("Reserved ─────────────────────────────────────────────────────────┘│\n");
    printf("Fast String Enable (R/W) ──────────────────────────────────────────┘\n");
}

//#############################################################################
//# IA32_PACKAGE_THERM_MARGIN
//# https://www.intel.com/content/dam/www/public/us/en/documents/design-guides/4th-gen-core-family-desktop-tmsdg.pdf
//# 
//#############################################################################
void REG_PRINT_DE__printIA32PackageThermMargin(unsigned long long ullVal)
{
    char cBuffValAsBin[100] = { 0 };
    unsigned int uiPkgThermMargin = 0;

    // Create a binary string from value
    REG_PRINT_DE__makeBinaryString(ullVal, cBuffValAsBin, sizeof(cBuffValAsBin));

    uiPkgThermMargin = (unsigned int)((unsigned long long)0xFFFF & ullVal);

    printf("[1A1H] IA32_PACKAGE_THERM_MARGIN\n");
    printf("  Command to read: sudo rdmsr 0x1a1 -f 63:0\n");
    printf("Value of register is: %08llx\n", ullVal);
    printf("  64  60        50        40        30        20        10\n");
    printf("  43210987654321098765432109876543210987654321098765432109876543210\n");
    printf("%s\n", cBuffValAsBin);
    printf("   └────────────────────────┬─────────────────────┘└──────┬───────┘\n");
    printf("                        Reserved                          │        \n");
    printf("THERM Marging  ───────────────────────────────────────────┘  0x%x -> %d\n", uiPkgThermMargin, uiPkgThermMargin);
}

//#############################################################################
//# IA32_TEMPERATURE_TARGET
//# cpu-monitoring-dts-peci-paper.pdf
//# 
//#############################################################################
void REG_PRINT_DE__printIA32TermperatureTarget(unsigned long long ullVal)
{
    char cBuffValAsBin[100] = { 0 };
    unsigned int uiTargPerfStateVal = 0;

    // Create a binary string from value
    REG_PRINT_DE__makeBinaryString(ullVal, cBuffValAsBin, sizeof(cBuffValAsBin));

    uiTargPerfStateVal = (unsigned int)((unsigned long long)0x7FFF & ullVal);

    printf("[1A2H] IA32_TEMPERATURE_TARGET\n");
    printf("  Command to read: sudo rdmsr 0x1a2 -f 63:0\n");
    printf("Value of register is: %08llx\n", ullVal);
    printf("  64  60        50        40        30        20        10\n");
    printf("  43210987654321098765432109876543210987654321098765432109876543210\n");
    printf("%s\n", cBuffValAsBin);
    printf("   └────────────────────┬─────────────────┘└──────────┬───────────┘\n");
    printf("                    Reserved                          │            \n");
    printf("Temperature Target, min (deg C) ──────────────────────┘  0x%x -> %d\n", uiTargPerfStateVal, uiTargPerfStateVal);
}

//#############################################################################
//# IA32_PKG_THERM_STATUS/IA32_PACKAGE_THERM_STATUS
//# https://tc.gtisc.gatech.edu/cs3210/2016/fall/r/ia32/IA32-3B.pdf
//# 
//#############################################################################
void REG_PRINT_DE__print_IA32_PKG_THERM_STATUS(unsigned long long ullVal)
{
    char cBuffValAsBin[100] = { 0 };

    // Create a binary string from value
    REG_PRINT_DE__makeBinaryString(ullVal, cBuffValAsBin, sizeof(cBuffValAsBin));

    printf("[1B1H] IA32_PKG_THERM_STATUS/IA32_PACKAGE_THERM_STATUS\n");
    printf("  Command to read: sudo rdmsr 0x1B1 -f 63:0\n");
    printf("Value of register is: %08llx\n", ullVal);
    printf("  64  60        50        40        30        20        10\n");
    printf("  43210987654321098765432109876543210987654321098765432109876543210\n");
    printf("%s\n", cBuffValAsBin);
    printf("   └──────────────────┬────────────────────┘└──┬──┘└─┬┘││││││││││││\n");
    printf("                  Reserved                     │     │ ││││││││││││\n");
    printf("Pkg Digital Readout (RO) ──────────────────────┘     │ ││││││││││││\n");
    printf("Reserved ────────────────────────────────────────────┘ ││││││││││││\n");
    printf("Pkg Power Limitation log (R/WC0) ──────────────────────┘│││││││││││\n");
    printf("Pkg Power Limitation Status (RO) ───────────────────────┘││││││││││\n");
    printf("Pkg Thermal Threshold #1 log (R/WC0) ────────────────────┘│││││││││\n");
    printf("Pkg Thermal Threshold #2 Status (RO) ─────────────────────┘││││││││\n");
    printf("Pkg Thermal Threshold #1 log (R/WC0) ──────────────────────┘│││││││\n");
    printf("Pkg Thermal Threshold #1 Status (RO) ───────────────────────┘││││││\n");
    printf("Pkg Critical Temperature Status log (R/WC0) ─────────────────┘│││││\n");
    printf("Pkg Critical Temperature Status (RO) ─────────────────────────┘││││\n");
    printf("Pkg PROCHOT # log (R/WC0) ─────────────────────────────────────┘│││\n");
    printf("Pkg PROCHOT # event (RO) ───────────────────────────────────────┘││\n");
    printf("Pkg Thermal Status Log (R/W): ───────────────────────────────────┘│\n");
    printf("Pkg Thermal Status (RO): ─────────────────────────────────────────┘\n");
}

//#############################################################################
//# MSR_PKG_ENERGY_STATUS/MSR_RAPL_POWER_UNIT
//# http://kib.kiev.ua/x86docs/SDMs/335592-063.pdf
//# https://tc.gtisc.gatech.edu/cs3210/2016/fall/r/ia32/IA32-3B.pdf
//# 
//#############################################################################
void REG_PRINT_DE__print_MSR_PKG_ENERGY_STATUS(unsigned long long ullVal)
{
    char cBuffValAsBin[100] = { 0 };

    // Create a binary string from value
    REG_PRINT_DE__makeBinaryString(ullVal, cBuffValAsBin, sizeof(cBuffValAsBin));

    printf("[611H] MSR_PKG_ENERGY_STATUS/MSR_RAPL_POWER_UNIT\n");
    printf("  Command to read: sudo rdmsr 0x611 -f 63:0\n");
    printf("Value of register is: %08llx\n", ullVal);
    printf("  64  60        50        40        30        20        10\n");
    printf("  43210987654321098765432109876543210987654321098765432109876543210\n");
    printf("%s\n", cBuffValAsBin);
    printf("   └─────────────────────┬────────────────────┘└─┬┘└┬┘└─┬─┘└─┬┘└─┬┘\n");
    printf("                     Reserved                    │  │   │    │   │\n");
    printf("Time Units ──────────────────────────────────────┘  │   │    │   │\n");
    printf("Reserved ───────────────────────────────────────────┘   │    │   │\n");
    printf("Energy Status Units ────────────────────────────────────┘    │   │\n");
    printf("Reserved ────────────────────────────────────────────────────┘   │\n");
    printf("Power Units ─────────────────────────────────────────────────────┘\n");
}

//#############################################################################
//# MSR_PKG_STATUS/MSR_PKG_PERF_STATUS
//# http://kib.kiev.ua/x86docs/SDMs/335592-063.pdf
//# https://tc.gtisc.gatech.edu/cs3210/2016/fall/r/ia32/IA32-3B.pdf
//# 
//#############################################################################
void REG_PRINT_DE__print_MSR_PKG_STATUS(unsigned long long ullVal)
{
    char cBuffValAsBin[100] = { 0 };

    // Create a binary string from value
    REG_PRINT_DE__makeBinaryString(ullVal, cBuffValAsBin, sizeof(cBuffValAsBin));

    printf("[613H] MSR_PKG_STATUS/MSR_PKG_PERF_STATUS\n");
    printf("  Command to read: sudo rdmsr 0x613 -f 63:0\n");
    printf("Value of register is: %08llx\n", ullVal);
    printf("  64  60        50        40        30        20        10\n");
    printf("  43210987654321098765432109876543210987654321098765432109876543210\n");
    printf("%s\n", cBuffValAsBin);
    printf("   └───────────────┬──────────────┘└────────────────┬─────────────┘\n");
    printf("                Reserved                            │              \n");
    printf("Accumulated Package Throttle Time  ─────────────────┘              \n");
}

//#############################################################################
//# MSR_CORE_PERF_LIMIT_REASONS
//# http://kib.kiev.ua/x86docs/SDMs/335592-066.pdf
//# https://stackoverflow.com/questions/45472147/lost-cycles-on-intel-an-inconsistency-between-rdtsc-and-cpu-clk-unhalted-ref-ts
//# 
//#############################################################################
void REG_PRINT_DE__printMsrCorePerfLimitReasons(unsigned long long ullVal)
{
    char cBuffValAsBin[100] = { 0 };

    // Create a binary string from value
    REG_PRINT_DE__makeBinaryString(ullVal, cBuffValAsBin, sizeof(cBuffValAsBin));

    printf("[690H] MSR_CORE_PERF_LIMIT_REASONS\n");
    printf("  Command to read: sudo rdmsr 0x690 -f 63:0\n");
    printf("Value of register is: %08llx\n", ullVal);
    printf("  64  60        50        40        30        20        10\n");
    printf("  43210987654321098765432109876543210987654321098765432109876543210\n");
    printf("%s\n", cBuffValAsBin);
    printf("   └───────────────┬───────────────┘││││││└─┬─┘│││││││││││└─┬─┘││││\n");
    printf("              Reserved              ││││││  │  │││││││││││  │  ││││\n");
    printf("Maximum Efficiency Frequency Log ───┘│││││  │  │││││││││││  │  ││││\n");
    printf("Turbo Transistion Attenuation Log ───┘││││  │  │││││││││││  │  ││││\n");
    printf("Electical Design Point Log ───────────┘│││  │  │││││││││││  │  ││││\n");
    printf("Max Turbo Limit Log ───────────────────┘││  │  │││││││││││  │  ││││\n");
    printf("VR Them Alert Log ──────────────────────┘│  │  │││││││││││  │  ││││\n");
    printf("Core Power Limiting Log ─────────────────┘  │  │││││││││││  │  ││││\n");
    printf("Reserved ───────────────────────────────────┘  │││││││││││  │  ││││\n");
    printf("Package-Level PL2 Power Limiting Log ──────────┘││││││││││  │  ││││\n");
    printf("Package-Level PL1 Power Limiting Log ───────────┘│││││││││  │  ││││\n");
    printf("Thermal Log ─────────────────────────────────────┘││││││││  │  ││││\n");
    printf("PROCHOT Log ──────────────────────────────────────┘│││││││  │  ││││\n");
    printf("Reserved ──────────────────────────────────────────┘││││││  │  ││││\n");
    printf("Maximum Efficiency Frequency Status (R0)────────────┘│││││  │  ││││\n");
    printf("Turbo Transition Attenuation Status (R0)─────────────┘││││  │  ││││\n");
    printf("Electrical Design Point Status (R0)───────────────────┘│││  │  ││││\n");
    printf("Max Turbo Limit Status (R0) ───────────────────────────┘││  │  ││││\n");
    printf("VR Therm Alert Status (R0)──────────────────────────────┘│  │  ││││\n");
    printf("Core Power Limiting Status (R0)──────────────────────────┘  │  ││││\n");
    printf("Reserved ───────────────────────────────────────────────────┘  ││││\n");
    printf("Package-Level PL2 Power Limiting Status (R0) ──────────────────┘│││\n");
    printf("Package-Level Power Limiting PL1 Status (R0)────────────────────┘││\n");
    printf("Thermal Status (R0) ─────────────────────────────────────────────┘│\n");
    printf("PROCHOT Status (R0) ──────────────────────────────────────────────┘\n");
}
