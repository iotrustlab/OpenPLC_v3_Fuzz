#!/bin/bash
cd core
echo "Configuring AFL++ for current system"
#sudo afl-system-config


echo "Setting up intput corpus"
#setup inputs corpus
export AFL_I_DONT_CARE_ABOUT_MISSING_CRASHES=1
afl-cmin -i ../INPUTS -o ../INPUTS/INPUTS_UNIQUE -- ../harnessing/PLC_harness/plc_harness -someopt @@


#rather optional scirpt to minimize input files for AFL++
# mkdir input
# cd INPUTS_UNIQUE
# for i in *; do
#   afl-tmin -i "$i" -o "../input/$i" -- ../core/openplc -someopt @@
# done
echo "Begin Fuzzing"
afl-fuzz -i ../INPUTS -o ../fuzz_output -- ../harnessing/PLC_harness/plc_harness -someopt @@