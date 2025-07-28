#!/bin/bash

target_directory=./fuzzing/PLC_Harness
st_path=$target_directory/plc2.st
lib_path=../../core/./lib
flags=-std="gnu++11 -g -O0 -fpermissive -Wno-c++11-narrowing -Wno-pointer-sign -Wno-incompatible-pointer-types -Wno-int-to-pointer-cast -Wno-cast-align -Wno-non-literal-null-conversion -Wno-unused-variable -Wno-sign-compare"
after_flags="-lasiodnp3 -lasiopal -lopendnp3 -lopenpal -w"
cd ../..

echo "Generating C files..."
./iec2c -f -l -p -r -R -a $st_path
if [ $? -ne 0 ]; then
    echo "Error generating C files"
    echo "Compilation finished with errors!"
    exit 1
fi

echo "Moving Files..."
mv -f POUS.c POUS.h LOCATED_VARIABLES.h VARIABLES.csv Config0.c Config0.h Res0.c $target_directory/
if [ $? -ne 0 ]; then
    echo "Error moving files"
    echo "Compilation finished with errors!"
    exit 1
fi

cd $target_directory

echo "Generating glueVars..."
./glue_generator
#export AFL_LLVM_ALLOWLIST=../allowlist.txt
#AFL_USE_ASAN=1

afl-clang-fast++ $flags  -I $lib_path -c Config0.c $after_flags 
afl-clang-fast++ $flags -I $lib_path -c Res0.c $after_flags
afl-clang-fast++ $flags *.cpp *.o -o plc_harness -I $lib_path -pthread -fpermissive `pkg-config --cflags --libs libmodbus` $after_flags