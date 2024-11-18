#!/bin/bash
cd core
echo "Configuring AFL++ for current system"
#sudo afl-system-config


echo "Setting up intput corpus"
#setup inputs corpus
afl-cmin -i ../fuzzing/INPUTS -o INPUTS_UNIQUE -- ../core/openplc -someopt @@


#rather optional scirpt to minimize input files for AFL++
# mkdir input
# cd INPUTS_UNIQUE
# for i in *; do
#   afl-tmin -i "$i" -o "../input/$i" -- bin/target -someopt @@
# done
echo "Begin Fuzzing"
afl-fuzz -i ../fuzzing/INPUTS -o output -- ../core/openplc -someopt @@