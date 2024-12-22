/* gcc -fno-stack-protector -no-pie -o baby_ROP_bin baby_ROP.c*/
#include <stdio.h>

void treasureChest(int key1, int key2, int key3) {
    if (key1 == 0x13371337 && key2 == 0xdeadbeef && key3 == 0xc0ff33) {
        printf("Here lies the secret of pwn!\n");
        FILE *file = fopen("flag.txt", "r");
        char flag[256];
        fgets(flag, 256, file);
        print("%s", flag);
        fclose(file);
        exit(1);
    }
}

void secretKey() {
    printf("There must be something here...or is there?");
}


int main() {
    printf("Welcome to the land of pwn!\n");
    printf("Deep down lies the treasure of pwn!\n");
    char buffer[64];
    gets(buffer);
    return 0;
}