#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include </usr/include/x86_64-linux-gnu/sys/mman.h>
int main(){

    int fd;
    fd = open("123.txt",O_RDWR);
    printf("%d\n",fd);
    int size;
    //size = write(fd,"123123",6);
    
    return 0;
}