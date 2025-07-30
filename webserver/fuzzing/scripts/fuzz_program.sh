#!/bin/bash
cd fuzzing/scripts
echo "Configuring AFL++ for current system"
#sudo afl-system-config


#echo "Setting up intput corpus"

#setup inputs corpus
export AFL_I_DONT_CARE_ABOUT_MISSING_CRASHES=1
#afl-cmin -i ../seeds -o ../INPUTS/INPUTS_UNIQUE -- ../PLC_harness/plc_harness @@


#rather optional scirpt to minimize input files for AFL++
# mkdir input
# cd INPUTS_UNIQUE
# for i in *; do
#   afl-tmin -i "$i" -o "../input/$i" -- ../core/openplc -someopt @@
# done

echo "Begin Fuzzing"
afl-fuzz -i ../seeds -o ../fuzz_output -- ../PLC_Harness/plc_harness @@
