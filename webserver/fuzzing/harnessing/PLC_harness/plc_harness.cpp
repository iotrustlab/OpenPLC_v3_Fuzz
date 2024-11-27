#include "POUS.h"

extern PLC2 RES0__INSTANCE0;

void serialize_plc_data(const char *filename)
{
    FILE *file = fopen(filename, "ab+");
    if (file)
    {
        fwrite(&RES0__INSTANCE0, sizeof(PLC2), 1, file);
        fclose(file);
    }
}

void save_plc_to_file()
{
    serialize_plc_data("plc_data.bin");
}

int deserialize_plc_data(const char *filename)
{
    FILE *file = fopen(filename, "rb");
    PLC2 *vals;
    int ret = 0;
    if (file)
    {
        ret = fread(vals, sizeof(PLC2), 1, file);
        fclose(file);
    }

    RES0__INSTANCE0 = *vals;
    return ret;
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    return deserialize_plc_data(argv[1]);
}