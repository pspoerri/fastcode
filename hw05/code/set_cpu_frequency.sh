#!/bin/bash
# Available frequencies
# cat /sys/devices/system/cpu/*/cpufreq/scaling_available_frequencies
# Inspired by: http://www.pantz.org/software/cpufreq/usingcpufreqonlinux.html
sh -c "echo 3400000 > /sys/devices/system/cpu/cpu0/cpufreq/scaling_max_freq"
sh -c "echo 3400000 > /sys/devices/system/cpu/cpu1/cpufreq/scaling_max_freq"
sh -c "echo 3400000 > /sys/devices/system/cpu/cpu2/cpufreq/scaling_max_freq"
sh -c "echo 3400000 > /sys/devices/system/cpu/cpu3/cpufreq/scaling_max_freq"

sh -c "echo 3400000 > /sys/devices/system/cpu/cpu0/cpufreq/scaling_min_freq"
sh -c "echo 3400000 > /sys/devices/system/cpu/cpu1/cpufreq/scaling_min_freq"
sh -c "echo 3400000 > /sys/devices/system/cpu/cpu2/cpufreq/scaling_min_freq"
sh -c "echo 3400000 > /sys/devices/system/cpu/cpu3/cpufreq/scaling_min_freq"

