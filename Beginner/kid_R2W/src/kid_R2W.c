/* gcc -fno-stack-protector -z execstack -no-pie -o kid_R2W_bin kid_R2W.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void hiddenBlessing() {
    printf("You have been blessed.\n");
    FILE *file = fopen("flag.txt", "r");
    if (file == NULL) {
        printf("Flag file not found.\n");
        exit(1);
    }
    char flag[256];
    fgets(flag, 256, file);
    printf("%s", flag);
    fclose(file);
    exit(1);
}

void nothing() {
    printf("Erm...are you sure? \n");
}

void enlightenment() {
    char wish[128]; 
    printf("What do you want to know? \n");
    gets(wish);  
    printf("Here you go: %s\n", wish);
}

void main() {
    char selection[4]; 
    printf("Option 1: Nothing.\n");
    printf("Option 2: Enlighten me.\n");
    printf("God of Binary Excellence - State your purpose: \n");
    fgets(selection, sizeof(selection), stdin);

    if (selection[0] == '1') {
        nothing();
    } else if (selection[0] == '2') {
        enlightenment();
    } else {
        printf("Invalid option.\n");
    }
}
