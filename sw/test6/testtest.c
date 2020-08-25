#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

int main(){

    int fd;
    fd = open("./123.txt",O_RDWR);
    return 0;
}