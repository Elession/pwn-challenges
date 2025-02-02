/* gcc -fno-stack-protector -no-pie -o chall chall.c */
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>

void sigsegv_trigger(int sig) {
    printf("Segmentation Fault!\n");
    printf("Here is your flag: \n");
    
    // reads the flag content
    FILE *file = fopen("flag.txt", "r");
    char flag[256];
    fgets(flag, 256, file);
    printf("%s", flag);
    fclose(file);
    exit(1);
}

void vuln() {

    // buffer size
    char buffer[20]; 
    printf("Enter some text: ");
    
    // vulnerable c function
    gets(buffer);
    
    printf("You entered: %s\n", buffer);
}

int main() {
    //ignore this
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
    
    // runs sigsegv_trigger() when a segmentation fault occurs
    signal(SIGSEGV, sigsegv_trigger);
    
    printf("Hello World!\n");
    vuln();
    printf("Goodbye!\n");
}