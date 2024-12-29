/* gcc -fno-stack-protector -no-pie -o chall chall.c */
#include <stdio.h>   
#include <string.h>

int main(void) {

    //ignore this
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);

    char thought[64];
    printf("If you can imagine it, you can make it!");
    memset(thought, 0x0, sizeof(thought));
    scanf("%s",thought);
    return 0;
}