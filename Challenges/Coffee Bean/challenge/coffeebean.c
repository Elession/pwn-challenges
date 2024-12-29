#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int keg(const char *beans) {
    if (strcmp(beans, "perfect") == 0){
        printf("The beans are great! Here's the coffee \n");
        FILE *file = fopen("flag.txt", "r");
        char flag[256];
        fgets(flag, 256, file);
        printf("%s", flag);
        fclose(file);
    } else {
        printf("The beans are not fresh enough.");
    }
    return 0;
}


void harvest() {
    char value[100];
    char preharvest[] = "notgood";

    printf("It's time to harvest my crops!");
    scanf("%s", value);
    keg(preharvest);
}


int main()
{
    //ignore this
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);

    harvest();
    return 0;
}