/* gcc -fno-stack-protector -no-pie -o chall chall.c */
#include <stdio.h>   
#include <string.h>

int main(void) {

    //ignore this
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);

    char iridium[100];
    printf("Iridium is superior to diamond right? \n");
    size_t input = read(0, iridium, 0x100);
    return 0;
}