#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <string.h>
#include <map>
#include <cstdint>

using namespace std;

#define instruction_count 66

void initial();
char* int_to_str(unsigned int);
void riscv_decode(char*, fstream* log_file);
char* str_inverse(char*);
char* str_to_hex(char*);
int str_to_int(char*);