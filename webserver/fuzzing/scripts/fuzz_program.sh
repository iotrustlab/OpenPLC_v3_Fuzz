#!/bin/bash
cd fuzzing/scripts
echo "Configuring AFL++ for current system"

#Either change core dump pattern or declare that you don't care about missing crashes
#export AFL_I_DONT_CARE_ABOUT_MISSING_CRASHES=1
#echo core | sudo tee /proc/sys/kernel/core_pattern

#echo "Setting up intput corpus"
#setup inputs corpus
#afl-cmin -i ../seeds -o ../INPUTS/INPUTS_UNIQUE -- ../PLC_harness/plc_harness @@


echo "Begin Fuzzing"
afl-fuzz -i ../INPUTS -o ../fuzz_output -- ../PLC_Harness/plc_harness @@
