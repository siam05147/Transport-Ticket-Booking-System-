//ticket.c


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_SEATS 35
#define MAX_NAME_LENGTH 50
#define FILENAME "bookings.txt"

struct Booking {
    char name[MAX_NAME_LENGTH];
    int seatNo;
    char source[MAX_NAME_LENGTH];
    char destination[MAX_NAME_LENGTH];
};

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void printTicket() {
    int seatToPrint;
    printf("\nEnter seat number to print ticket: ");
    scanf("%d", &seatToPrint);
    
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("\nNo reservations found in the system.\n");
        return;
    }
    
    struct Booking temp;
    int found = 0;
    
    while(fread(&temp, sizeof(struct Booking), 1, file)) {
        if(temp.seatNo == seatToPrint) {
            time_t t = time(NULL);
            struct tm tm = *localtime(&t);
            
            printf("\n");
            printf("┌─────────────────────────────────────────────────────┐\n");
            printf("│              TRANSPORT TICKET                       │\n");
            printf("├─────────────────────────────────────────────────────┤\n");
            printf("│ Ticket No:    T%03d-%04d-%02d%02d                │\n", 
                   seatToPrint, rand()%10000, tm.tm_mon+1, tm.tm_mday);
            printf("│ Seat No.:     %-35d│\n", temp.seatNo);
            printf("│ Passenger:    %-35s│\n", temp.name);
            printf("│ From:         %-35s│\n", temp.source);
            printf("│ To:           %-35s│\n", temp.destination);
            printf("│ Date:         %02d/%02d/%04d                         │\n", 
                   tm.tm_mday, tm.tm_mon+1, tm.tm_year+1900);
            printf("│ Time:         %02d:%02d                               │\n", 
                   tm.tm_hour, tm.tm_min);
            printf("│ Status:       CONFIRMED                             │\n");
            printf("│                                                     │\n");
            printf("│  Terms & Conditions:                                │\n");
            printf("│  1. Ticket is non-transferable                      │\n");
            printf("│  2. Arrive 30 mins before departure                 │\n");
            printf("│  3. Carry valid ID proof                            │\n");
            printf("└─────────────────────────────────────────────────────┘\n");
            printf("\nTicket printed successfully!\n");
            
            found = 1;
            break;
        }
    }
    
    fclose(file);
    
    if(!found) {
        printf("\nNo ticket found for Seat %d\n", seatToPrint);
        printf("Please check the seat number and try again.\n");
    }
}

void printAllTickets() {
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("\nNo reservations found in the system.\n");
        return;
    }
    
    struct Booking temp;
    int count = 0;
    
    printf("\nPrinting all tickets...\n");
    
    while(fread(&temp, sizeof(struct Booking), 1, file)) {
        printf("\n══════════════════════════════════════════════\n");
        printf("           TICKET FOR SEAT %d\n", temp.seatNo);
        printf("══════════════════════════════════════════════\n");
        printf("Passenger: %s\n", temp.name);
        printf("Seat:      %d\n", temp.seatNo);
        printf("Route:     %s → %s\n", temp.source, temp.destination);
        printf("Ticket ID: T%d-%04d\n", temp.seatNo, rand()%10000);
        printf("══════════════════════════════════════════════\n");
        count++;
    }
    
    fclose(file);
    
    if(count == 0) {
        printf("\nNo tickets to print.\n");
    } else {
        printf("\nPrinted %d ticket(s) successfully!\n", count);
    }
}

void ticketMenu() {
    printf("\n╔══════════════════════════════════════════════╗\n");
    printf("║            TICKET PRINTING                   ║\n");
    printf("╚══════════════════════════════════════════════╝\n");
    
    int choice;
    do {
        printf("\n1. Print Single Ticket\n");
        printf("2. Print All Tickets\n");
        printf("3. Return to Main Menu\n");
        printf("\nEnter your choice (1-3): ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                printTicket();
                break;
            case 2:
                printAllTickets();
                break;
            case 3:
                printf("\nReturning to Main Menu...\n");
                break;
            default:
                printf("\nInvalid choice! Please enter 1, 2, or 3.\n");
        }
    } while(choice != 3);
}