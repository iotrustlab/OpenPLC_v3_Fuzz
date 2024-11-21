#!/bin/bash
cd core
echo "Configuring AFL++ for current system"
#sudo afl-system-config


echo "Setting up intput corpus"
#setup inputs corpus
export AFL_I_DONT_CARE_ABOUT_MISSING_CRASHES=1
afl-cmin -i ../fuzzing/INPUTS -o INPUTS_UNIQUE -- ../core/openplc -someopt @@


#rather optional scirpt to minimize input files for AFL++
# mkdir input
# cd INPUTS_UNIQUE
# for i in *; do
#   afl-tmin -i "$i" -o "../input/$i" -- ../core/openplc -someopt @@
# done
echo "Begin Fuzzing"
afl-fuzz -i ../fuzzing/INPUTS -o ../fuzzing/fuzz_output -- ../core/openplc -someopt @@