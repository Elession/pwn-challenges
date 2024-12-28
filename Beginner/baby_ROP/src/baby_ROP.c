/* gcc -fno-stack-protector -no-pie -o baby_ROP_bin baby_ROP.c*/
#include <stdio.h>

void win(int a, int b) {
    if (a == 0x1337 && b == 0xdead) {
        printf("You completed the ROP exercise!\n");
        FILE *file = fopen("flag.txt", "r");
        char flag[256];
        fgets(flag, 256, file);
        printf("%s", flag);
        fclose(file);
    }
}

int main() {
    printf("Welcome to ROP!\n");
    char buffer[20];
    gets(buffer);
    return 0;
}