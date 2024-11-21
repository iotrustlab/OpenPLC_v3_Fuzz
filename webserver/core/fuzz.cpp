#include "fuzz.h"
#include "POUS.h"

extern PLC2 RES0__INSTANCE0;

// int main(int argc, char **argv) 
// {
//     if (argc != 2) 
//     {
//         fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
//         return 1;
//     }

//     deserialize_struct(argv[1]);
// }

void fuzzing(const char* filename)
{
    deserialize_struct(filename);
}

void save_plc_to_file()
{
    serialize_plc_data("plc_data");
}

void serialize_plc_data( const char *filename)
{
    FILE *file = fopen(filename, "ab+");
    if (file) {
        fwrite(&RES0__INSTANCE0, sizeof(PLC2), 1, file);
        fclose(file);
    }
}

void deserialize_struct(const char *filename) 
{
    FILE *file = fopen(filename, "rb");
    PLC2* vals;
    if (file) {
        fread(vals, sizeof(PLC2), 1, file);
        fclose(file);
    }

    RES0__INSTANCE0 = *vals;
}