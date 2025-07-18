// cact_io.h
#ifndef CACT_IO_H
#define CACT_IO_H

#ifdef __cplusplus
extern "C" {
#endif

void print_int(int value);
void print_float(float value);
void print_char(char value);

int get_int();
float get_float();
char get_char();

#ifdef __cplusplus
}
#endif

#endif
