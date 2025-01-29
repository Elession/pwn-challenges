#include <stdio.h>
#include <string.h>

void flag(){
    FILE *file = fopen("flag.txt", "r");
    char flag[256];
    fgets(flag, 256, file);
    printf("%s", flag);
    fclose(file);
}

void instructions() {
    printf("Here are some instructions: \n");
    printf("MOV RAX, 0x1234\n");
    printf("MOV RBX, RAX\n");
    printf("ADD RBX, 0x23\n");
    printf("SUB RDI, 0x4\n");
    printf("ADD RSI, RDI\n");


    char answer[20];
    printf("What is the value in RBX and RSI? \n\n");

    printf("Put your answer in (ans1_ans2) format: ");
    fgets(answer, sizeof(answer), stdin);

    // Remove newline
    answer[strcspn(answer, "\n")] = '\0';

    if (strcmp(answer, "0x8_0x0") == 0) {
        printf("Correct! Here's your flag:\n");
        flag();
    } else {
        printf("Incorrect answer. Try again!\n");
    }
}

void registers() {
    printf("WELCOME TO THE REGISTER EXERCISE\n\n");

    printf("Here are the current contents of the registers:\n\n");
    printf("----------------------------------\n");
    printf("|   Register   |     Value       |\n");
    printf("----------------------------------\n");
    printf("|     RAX      |    0x0          |\n");
    printf("|     RBX      |    0x1          |\n");
    printf("|     RCX      |    0x10         |\n");
    printf("|     RDX      |    0x0          |\n");
    printf("|     RSI      |    0x0          |\n");
    printf("|     RDI      |    0xC          |\n");
    printf("----------------------------------\n\n");
}

int main() {
    registers();
    instructions();
}
