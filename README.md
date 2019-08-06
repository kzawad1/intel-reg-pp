# Overview
This tool was created while working on a Thermal Throttling problem associated with Intel® Core™ i5-4300U Processor (formerly Haswell).  Since looking at data sheets required checking specific registers and bits it became useful to draw these in a formate that mimicked the data sheet.  For example, the image below is shown in a datasheet titled "Intel® 64 and IA-32 Architectures Software Developer’s Manual Volume  3B: System Programming Guide, Part 2".

![IA32_THERM_STATUS](./Docs/Example_IA32_THERM_STATUS.png)

A link to the problem description is the following:
https://software.intel.com/en-us/forums/software-tuning-performance-optimization-platform-monitoring/topic/815194

# Prerequiste
This tool is used in conjunction with Linux **msr-tools** because this tool allows one to read the Intel processor specific registers.  This tool was built using Visual Studio for Linux and tested on a Ubuntu 18.04.1 LTS x64 machine.

To install **msr-tools** run the following commands:
```
sudo apt-get update
sudo apt-get -y install msr-tools
```

After that initialize the MSR driver explicitly by running the following command:
```
sudo modprobe msr
```

Last, read a Intel Model Specific register (MSR) using the following command:
```
sudo rdmsr 0x19C -f 63:0
sudo strace rdmsr 0x19C -f 63:0
```

Take the hexidecimal output from the command and pass it to the **intel-reg-pp** application.
```
user1@ubuntu:~$ sudo rdmsr 0x19C -f 63:0
884100800
```


# Example(s)
TO DO: Add Content Here
