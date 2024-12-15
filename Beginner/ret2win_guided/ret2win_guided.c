#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void win() {
    //How do I get here??
    printf("Hello from win!\n");
}

void vuln() {
    char buffer[20];
    printf("Enter some text: ");

    //BOF vulnerability here
    gets(buffer); 
}

int main() {
    vuln();
    return 0;
}