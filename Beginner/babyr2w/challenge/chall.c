/* gcc -fno-stack-protector -z execstack -no-pie -o chall chall.c */

#include <stdio.h>

void win() {
    //How do I get here??
    printf("Hello from win!\n");
    FILE *file = fopen("flag.txt", "r");
    char flag[256];
    fgets(flag, 256, file);
    printf("%s", flag);
    fclose(file);
}

void vuln() {

    char buffer[32];
    printf("Enter some text: \n");

    //BOF vulnerability here
    gets(buffer); 
}

int main() {
    //ignore this
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
    
    vuln();
    return 0;
}