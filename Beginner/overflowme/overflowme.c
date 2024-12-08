// gcc -m32 -fno-stack-protector -z execstack -no-pie -o overflowme overflowme.c
#include <stdio.h>
#include <string.h>

void vuln() {
    char buffer[32];
    char flag[] = "MACCTF{REACTED}"; 

    printf("Enter your input: ");
    gets("%s", buffer); 

    printf("Output: %s\n", buffer);
}

int main() {
    vuln();
    return 0;
}