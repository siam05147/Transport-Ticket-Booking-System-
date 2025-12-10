#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Include all module files
#include "admin.c"
#include "booking.c"
#include "view.c"
#include "ticket.c"

void displayWelcome() {
    printf("\n");
    printf("╔══════════════════════════════════════════════════════════╗\n");
    printf("║        WELCOME TO TRANSPORT TICKET BOOKING SYSTEM       ║\n");
    printf("║                    Version 2.0                           ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n");
}

void displayGoodbye() {
    printf("\n");
    printf("╔══════════════════════════════════════════════════════════╗\n");
    printf("║    Thank you for using Transport Booking System!        ║\n");
    printf("║               Have a safe journey!                       ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n");
}

int main() {
    int choice;
    
    displayWelcome();
    
    do {
        printf("\n");
        printf("┌──────────────────────────────────────────────────────┐\n");
        printf("│                   MAIN MENU                          │\n");
        printf("├──────────────────────────────────────────────────────┤\n");
        printf("│  1. ADMINISTRATOR FUNCTIONS                          │\n");
        printf("│  2. BOOK A SEAT                                      │\n");
        printf("│  3. VIEW RESERVATIONS                                │\n");
        printf("│  4. PRINT TICKETS                                    │\n");
        printf("│  5. EXIT SYSTEM                                      │\n");
        printf("└──────────────────────────────────────────────────────┘\n");
        printf("\nPlease select an option (1-5): ");
        
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                adminMenu();
                break;
            case 2:
                bookingMenu();
                break;
            case 3:
                viewMenu();
                break;
            case 4:
                ticketMenu();
                break;
            case 5:
                displayGoodbye();
                break;
            default:
                printf("\nInvalid choice! Please enter a number between 1 and 5.\n");
        }
    } while(choice != 5);
    
    return 0;
}