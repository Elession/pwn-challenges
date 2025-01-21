/* gcc -o chall chall.c */
#include <stdio.h>

int main() {

    //ignore this 
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);

    char input[5];

    printf("==============================\n");
    printf("=                            =\n");
    printf("=            PWN             =\n");
    printf("=                            =\n");
    printf("==============================\n");
    printf("\n");
    printf("Are you ready to embark on your pwn journey? (Enter READY): ");

    if (fgets(input, sizeof(input), stdin)) {
        input[strcspn(input, "\n")] = '\0';

        if (strcmp(input, "READY") == 0) {
            printf("Alright! For starters, here ya go\n");
            FILE *file = fopen("flag.txt","r");
            char flag[256];
            fgets(flag,256,file);
            printf("%s",flag);
            fclose(file);
        } else {
            printf("Re-try again :)\n");
        }
    }

}
