/* gcc -fno-stack-protector -no-pie -o baby_ROP_bin baby_ROP.c*/
#include <stdio.h>

void win(int a, int b) {
    if (a == 0x1337 && b == 0xdead) {
        printf("You completed the ROP exercise!\n");
    }
}

int main() {
    printf("Welcome to ROP!\n");
    char buffer[20];
    gets(buffer);
    return 0;
}