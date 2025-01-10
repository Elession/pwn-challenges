/* gcc -o chall chall.c */
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

signed bank_amt = 100000;
signed multiplier = 10;
int choice;

void win() {
    printf("Bank Amount: %d\n", bank_amt);
    printf("You've successfully sabotaged Evil Megacorp! \n");
    FILE *file = fopen("flag.txt", "r");
    char flag[256];
    fgets(flag, 256, file);
    printf("%s", flag);
    fclose(file);
    exit(1);
}

void caught(){
    printf("You've been caught by the system administrator.");
    exit(0);
}

void steal() {
    printf("Money stolen! \n");
    printf("\n");
    bank_amt -= 20000;
}

void weaken() {
    if (multiplier > 10000000) {
        printf("\n");
        printf("You have hit the max multiplier!\n");
    } else {
        multiplier *= 10;
    }
    printf("Current multipler is %d \n", multiplier);
    printf("\n");
}


void hack() {
    bank_amt += 10000 * multiplier;
}

void hackerChoice(){
    printf("Enter your choice: ");
    if (scanf("%d", &choice) != 1) {
        printf("Invalid input. Please enter a number.\n");
        exit(1);
    }
    printf("\n");
    switch (choice){
        case 1:
            hack();
            break;
        case 2:
            weaken();
            break;
        case 3:
            steal();
            break;
        default:
            printf("Re-enter a proper option :)\n"); 
    }
}


void bankStatus() {
    printf("-----------EVIL MEGACORP BANK-----------\n");
    printf("Bank Amount: %d\n", bank_amt);
    printf("----------------------------------------\n");
    printf("\n");
    printf("Options:\n");
    printf("1. Hack\n");
    printf("2. Weaken\n");
    printf("3. Steal\n");
}


int main() {
    //ignore this
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);

    while (bank_amt > 0) {
        bankStatus();
        hackerChoice();
    }

    if (bank_amt <= 0 && bank_amt > -100000) {
        caught();
    } else {
        win();
    }

    return 0;

}