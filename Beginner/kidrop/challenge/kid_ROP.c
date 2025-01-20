/* gcc -fno-stack-protector -no-pie -o chall chall.c */
#include <stdio.h>    
#include <stdlib.h>   
#include <string.h>   

void treasureChest(int key1, int key2, int key3) {
    if (key1 == 0x13371337 && key2 == 0xdeadbeef && key3 == 0xc0ff33) {
        printf("Here lies the secret of pwn!\n");
        FILE *file = fopen("flag.txt", "r");
        char flag[256];
        fgets(flag, 256, file);
        printf("%s", flag);
        fclose(file);
        exit(1);
    }
}

void secretKey() {
    printf("There must be something here...or is there?");
}

void executePopRdxRet() {
    /* Why would I add this for? */
    __asm__ volatile (
        "pop %rdx\n\t"  
        "ret\n\t"       
    );
}

int main() {

    //ignore this
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);

    printf("Welcome to the land of pwn!\n");
    printf("Deep down lies the treasure of pwn!\n");
    char buffer[64];
    gets(buffer);  
    return 0;
}