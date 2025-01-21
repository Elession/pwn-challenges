/* gcc -fno-stack-protector -o chall chall.c */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void piefect() {
    printf("Secret Menu Item???? \n");
    FILE *file = fopen("flag.txt", "r");
    char flag[256];
    fgets(flag, 256, file);
    printf("%s", flag);
    fclose(file);
    exit(1);
}

void decision() {
    char final[100];
    printf("Alright! I've made up my mind. \n");
    gets(final);
}

void suggest() {
    char buffer[40]; 
    printf("Suggest me a flavour to try before I decide: \n");
    fgets(buffer, sizeof(buffer), stdin);
    printf("Here's a taste: \n");
    printf(buffer);
}

int main() {
    //ignore this
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
    
    printf("I can't decide which PIE to go with...\n");
    suggest();
    decision();
}