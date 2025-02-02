#include <stdio.h>
#include <string.h>

void flag(){
    FILE *file = fopen("flag.txt", "r");
    char flag[256];
    fgets(flag,256,file);
    printf("%s",flag);
    fclose(file);
}

void instructions() {
    printf("Here are some instructions: \n");
    printf("POP\n");
    printf("POP\n");
    printf("POP\n");
    printf("PUSH 0x7FFF\n");
    printf("PUSH 0xABCD\n");
    printf("\n");

    char answer[20];
    printf("What is the 2nd and 4th item in the stack, starting from lower address? \n\n");

    printf("Put your answer in (ans1_ans2) format: ");
    fgets(answer, sizeof(answer), stdin);

    //remove newline
    answer[strcspn(answer, "\n")] = '\0';

    if (strcmp(answer, "0x7FFF_0x1337") == 0) {
        printf("Correct! Here's your flag:\n");
        flag();
    } else {
        printf("Incorrect answer. Try again!\n");
    }
}

void stack() {

    printf("WELCOME TO THE STACK EXERCISE\n\n");

    char *addr[] = {"1234", "1337", "2979", "DEAD", "BEEF", "CAFE"};
    for (int i = 0; i < 6; i++) {
        printf("-------------------\n");
        printf("-     0x%s      -\n", addr[i]);
    }
    printf("-------------------\n\n");
    printf("\n");
    printf("0x1234 has the highest address.\n");
    printf("\n");
}

int main(){
    stack();
    instructions();
}

