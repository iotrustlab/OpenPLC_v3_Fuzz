#!/bin/bash
#compiling the ST file into C
cd ../..
echo "Generating C files..."
./iec2c -f -l -p -r -R -a ./st_files/"328551.st"
if [ $? -ne 0 ]; then
    echo "Error generating C files"
    echo "Compilation finished with errors!"
    exit 1
fi

echo "Moving Files..."
mv -f POUS.c POUS.h LOCATED_VARIABLES.h VARIABLES.csv Config0.c Config0.h Res0.c ./fuzzing/harnessing/PLC_harness/
if [ $? -ne 0 ]; then
    echo "Error moving files"
    echo "Compilation finished with errors!"
    exit 1
fi

cd fuzzing/harnessing/PLC_harness

echo "Generating glueVars..."
./glue_generator
#export AFL_LLVM_ALLOWLIST=../allowlist.txt
afl-clang-fast++ -std=gnu++11 -fpermissive -Wno-error -Wno-c++11-narrowing -Wno-pointer-sign -Wno-incompatible-pointer-types -Wno-int-to-pointer-cast -Wno-cast-align -Wno-non-literal-null-conversion -Wno-unused-variable -Wno-sign-compare -I ../../../core/./lib -c Config0.c -lasiodnp3 -lasiopal -lopendnp3 -lopenpal -w 
afl-clang-fast++ -std=gnu++11 -fpermissive -Wno-error -Wno-c++11-narrowing -Wno-everything -Wno-pointer-sign -Wno-incompatible-pointer-types -Wno-int-to-pointer-cast -Wno-cast-align -Wno-non-literal-null-conversion -Wno-unused-variable -Wno-sign-compare -I ../../../core/./lib -c Res0.c -lasiodnp3 -lasiopal -lopendnp3 -lopenpal -w
afl-clang-fast++ -std=gnu++11 -fpermissive -fms-extensions -Wno-c++11-narrowing -Wno-pointer-sign -Wno-incompatible-pointer-types -Wno-int-to-pointer-cast -Wno-cast-align -Wno-non-literal-null-conversion -Wno-unused-variable -Wno-sign-compare *.cpp *.o -o plc_harness -I ../../../core/./lib -pthread -fpermissive `pkg-config --cflags --libs libmodbus` -lasiodnp3 -lasiopal -lopendnp3 -lopenpal -w