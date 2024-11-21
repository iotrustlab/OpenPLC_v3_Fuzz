#ifndef FUZZ_H
#define FUZZ

void save_plc_to_file();

void serialize_plc_data( const char *filename);

void deserialize_struct(const char *filename);

#endif