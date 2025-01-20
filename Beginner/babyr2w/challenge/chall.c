/* gcc -fno-stack-protector -z execstack -no-pie -o chall chall.c */

#include <stdio.h>

void win() {
    //How do I get here??
    printf("Hello from win!\n");
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