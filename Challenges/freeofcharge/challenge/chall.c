/* gcc -o chall chall.c */
#include <stdio.h>
#include <stdlib.h>

signed short int balance = 50; 

void flag() {
    FILE *file = fopen("flag.txt", "r");
    char flag[256];
    fgets(flag, 256, file);
    printf("%s",flag);
    fclose(file);
    exit(0);
}

void buy_tickets() {
    unsigned int num_tickets;
    printf("Enter number of tickets (each costs 100) to buy: ");
    scanf("%u", &num_tickets);

    int ticket_price = 100;

    balance = balance - (num_tickets * ticket_price);

    if(balance > 0) {
        printf("Your remaining balance: %d credits\n", balance);
        printf("Here's your tickets!\n");
        flag();
    } else {
        printf("You need to top up more credits! \n");
        exit(0);
    }

}

int main() {
    //ignore this
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);

    printf("Welcome to the Lottery!\n");
    printf("Your starting balance: %d credits\n", balance);

    while (1) {
        printf("\nOptions:\n1. Buy Tickets\n2. Exit\nYour choice: ");
        int choice;
        scanf("%d", &choice);
        if (choice == 1) {
            buy_tickets();
        } else if (choice == 2) {
            printf("Goodbye!\n");
            exit(0);
        } else {
            printf("Invalid choice.\n");
        }
    }
    return 0;
}
