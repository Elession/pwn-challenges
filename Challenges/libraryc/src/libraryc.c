/* gcc -fno-stack-protector -no-pie -o libraryc libraryc.c */
#include <stdio.h>   
#include <string.h>

int main(void) {
    char thought[64];
    printf("If you can imagine it, you can make it!");
    memset(thought, 0x0, sizeof(thought));
    scanf("%s",thought);
    return 0;
}