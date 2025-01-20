#include <stdio.h>
#include <string.h>

int main(void)
{
    //ignore this
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);

    char buffer[100];
    char buffer2[100];
    
    printf("If you can see it, and have the courage enough to speak it, it will happen.\n");
    gets(buffer);
    strncpy(buffer2, buffer, 100);

    return 0;
}