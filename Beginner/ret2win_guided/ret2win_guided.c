#include <stdio.h>
#include <string.h>

void win() {
    printf("Hello from win!\n");
}

void vuln() {
    char buffer[20];
    printf("Enter some text: ");
    gets(buffer); 
}

int main() {
    vuln();
    return 0;
}