#include <iostream>
#include "ladder.h"
#include <unistd.h>
#include <vector>
#include <fstream>
#include "accessor.h"

#define NUM_ITERATIONS 10000000 

bool read_file(char* file_path, std::vector<int>* values)
{
    std::ifstream infile(file_path);

    if(!infile)
    {
        std::cerr << "Error: Could not open file.\n";
        return false;
    }
    int val;
    while(infile >> val)
    {
        values->push_back(val);
    }
    return true;
}

void run_plc(std::vector<int>* vals)
{
    config_init__();
    unsigned long tick;
    for (int val: *vals)
    {
        glueVars();
        *int_output[0] = val;
        config_run__(tick++);
    }
}

int main(int argc, char* argv[])
{
    std::cout << argc;
    if(argc != 2)
    {
        std::cout << "Incorrect input types\n";
        return 0;
    }

    std::vector<int>* values = new std::vector<int>();

    if(!read_file(argv[1], values))
    {
        std::cout << "Bad File?\n";
        return 0;
    }

    run_plc(values);
    free(values);
    return 1;
}