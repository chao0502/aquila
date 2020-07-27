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
struct instruction
{
    char* opcode;
    char* opstring;
    char* funct3;
    char* funct7;
}ins[100];

void initial();
char* int_to_str(char*);
void riscv_decode(char*);
char* str_traverse(char*);
char* str_to_hex(char*);
int str_to_int(char*);
//int str_to_int(char* str);