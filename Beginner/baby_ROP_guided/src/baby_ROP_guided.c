/* gcc -fno-stack-protector -no-pie -o b baby_ROP_guided.c*/
#include <stdio.h>

void win(int a, int b) {
    if (a == 0x1337 && b == 0xdead) {
        printf("testtest\n");
    }
}

int main() {
    printf("Welcome to ROP!\n");
    char buffer[20];
    gets(buffer);
    return 0;
}