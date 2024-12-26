/* gcc -fno-stack-protector -z execstack -no-pie -o kid_BOF_bin kid_BOF.c */
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>

void pizza(int sig) {
    printf("Machine broke!\n");
    printf("We apologise. Please have this instead:\n");

    FILE *file = fopen("flag.txt", "r");
    char flag[256];
    fgets(flag, 256, file);
    printf("%s", flag);
    fclose(file);
    exit(1);
}

void burger() {
    char order[200]; 
    printf("Please tell me your order: ");
    gets(order);
    printf("You have just ordered: %s\n", order);
}

int main() {
    // Runs pizza() when a segmentation fault occurs
    signal(SIGSEGV, pizza);

    printf("Hello! Welcome to Pizzeria!\n");
    burger();
    printf("Goodbye!\n");
}

