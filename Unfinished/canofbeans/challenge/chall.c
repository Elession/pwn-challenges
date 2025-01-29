#include <stdio.h>

int main() {
    //ignore this
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);

    char buffer[128];

    printf("Canned food...Canned drinks...you can do it!\n");
    printf("Enter input: ");
    gets(buffer);
    printf(buffer);

    return 0;
}