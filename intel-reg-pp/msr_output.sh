#!/bin/bash
#
# Script that reads Intel MSRs and displays them in readable format.

#------------------------------------------------------------------------------

# Globals
declare -a g_arr_MsrName=(\
'IA32_PERF_CTL' \
'IA32_CLOCK_MODULATION' \
'IS32_THERM_INTERRUPT' \
'IA32_HWP_THERM_STATUS' \
'IA32_MISC_ENABLE' \
'IA32_PACKAGE_THERM_MARGIN' \
'IA32_TEMPERATURE_TARGET' \
'IA32_PKG_THERM_STATUS' \
'MSR_PKG_ENERGY_STATUS' \
'MSR_PKG_STATUS' \
'MSR_PPERF' \
'MSR_CORE_PERF_LIMIT_REASONS' \
'IA32_PM_ENABLE' \
'IA32_HWP_CAPABILITIES' \
'IA32_HWP_REQUEST_PKG' \
'IA32_HWP_INTERRUPT' \
'IA32_HWP_REQUEST' \
'IA32_HWP_PECI_REQUEST_INFO' \
'IA32_HWP_STATUS' \
)

declare -a g_arr_MsrAddr=(\
'0x199' \
'0x19A' \
'0x19B' \
'0x19C' \
'0x1A0' \
'0x1A1' \
'0x1A2' \
'0x1B1' \
'0x611' \
'0x613' \
'0x64E' \
'0x690' \
'0x770' \
'0x771' \
'0x772' \
'0x773' \
'0x774' \
'0x775' \
'0x777' \
)

###############################################################################
# Main
# Globals:
#   None
# Arguments:
#   None
# Returns:
#   None
###############################################################################
function MSR_OUTPUT__main()
{
  echo "MSR Dump, Script Version 1.0"
  
  MSR_OUTPUT__displayAsTable
  MSR_OUTPUT__displayAsPrettyPrint
}

###############################################################################
# Sub-Function
# Globals:
#   None
# Arguments:
#   None
# Returns:
#   None
###############################################################################
function MSR_OUTPUT__displayAsTable()
{
  local l_var_core_count
  local l_var_reg_val
  local l_var_arr_len
  declare -a l_var_arr_cmd
  local l_var_num
  local l_var_num_mod
  local l_var_modulo

  # Determine how many cores there are
  l_var_core_count=$(grep -Pc '^processor\t' /proc/cpuinfo)

  # Trigger the msr driver to load explicitly
  sudo modprobe msr

  printf "+----+------------------------------+---------+----------+----------+----------+----------+\n"
  printf "| % 2s | % -28s | %s | %08s | % 8s | % 8s | % 8s |\n" "#" "MSR Register" "Address" \
         "Core 0" "Core 1" "Core 2" "Core 3"
  printf "+----+------------------------------+---------+----------+----------+----------+----------+\n"

  l_var_num=0

  l_var_arr_len=${#g_arr_MsrName[@]}
  for (( index=0; index < l_var_arr_len; index++))
  do
      printf "| % 2s | % -28s | % 7s |" "${l_var_num}" "${g_arr_MsrName[index]}" "${g_arr_MsrAddr[index]}"
      # Loop for all the cores and display the values
      for (( core=0; core < l_var_core_count; core++))
      do
        l_var_arr_cmd=("${l_var_arr_cmd[@]}" "sudo rdmsr -p ${core} ${g_arr_MsrAddr[index]} -f 63:0 2>&1")
        l_var_reg_val=$(sudo rdmsr -p ${core} "${g_arr_MsrAddr[index]}" -f 63:0 2>&1)
        if [[ $l_var_reg_val =~ "rdmsr" ]]
        then
          l_var_reg_val="N/A"
        fi

        printf " % 8s |" "${l_var_reg_val}"
      done

      ((l_var_num++))
      printf "\n"
  done
  printf "+----+------------------------------+---------+----------+----------+----------+----------+\n"

  ((l_var_num=1))
  ((l_var_num_mod=0))

  echo "Generated table by executing commands:"
  for i in "${l_var_arr_cmd[@]}"
  do
    printf "  [% 2s] %s\n" "${l_var_num_mod}" "${i}"

    l_var_modulo=$(( l_var_num % 4 ))
    if [[ $l_var_modulo == "0" ]]
    then
      ((l_var_num_mod++))
    fi

    ((l_var_num++))
  done
}

###############################################################################
# Sub-Function
# Globals:
#   None
# Arguments:
#   None
# Returns:
#   None
###############################################################################
function MSR_OUTPUT__displayAsPrettyPrint()
{
  local l_var_core_count
  local l_var_arr_len
  local l_var_reg_val

  echo ""

  # Determine how many cores there are
  l_var_core_count=$(grep -Pc '^processor\t' /proc/cpuinfo)

  for (( core=0; core < l_var_core_count; core++))
  do
    echo ""
    printf "###########################################################################\n"
    printf "CORE: %s\n" "${core}"
    
    l_var_arr_len=${#g_arr_MsrName[@]}
    for (( index=0; index < l_var_arr_len; index++))
    do
      # X
      l_var_reg_val=$(sudo rdmsr -p ${core} "${g_arr_MsrAddr[index]}" -f 63:0 2>&1)
      if [[ $l_var_reg_val =~ "rdmsr" ]]
      then
        l_var_reg_val="N/A"
      fi

      if [[ "${l_var_reg_val}" != "N/A" ]]
      then
        echo ""
        echo ""
        echo "./intel-reg-pp.out -a ${g_arr_MsrAddr[index]} ${l_var_reg_val}"
        ./intel-reg-pp.out -a "${g_arr_MsrAddr[index]}" "${l_var_reg_val}"
      fi
    done
  done
  
  echo ""
}

MSR_OUTPUT__main "$@"

