//view.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SEATS 35
#define MAX_NAME_LENGTH 50
#define FILENAME "bookings.txt"

struct Booking {
    char name[MAX_NAME_LENGTH];
    int seatNo;
    char source[MAX_NAME_LENGTH];
    char destination[MAX_NAME_LENGTH];
};

void viewAllReservations() {
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("\nNo reservations in the system.\n");
        printf("The booking list is empty.\n");
        return;
    }
    
    struct Booking temp;
    int count = 0;
    int totalBookings = 0;
    
    fseek(file, 0, SEEK_END);
    totalBookings = ftell(file) / sizeof(struct Booking);
    fseek(file, 0, SEEK_SET);
    
    if (totalBookings == 0) {
        printf("\nNo reservations in the system.\n");
        fclose(file);
        return;
    }
    
    printf("\n╔══════════════════════════════════════════════════════════════════════╗\n");
    printf("║                     ALL BOOKINGS (%d reservations)                   ║\n", totalBookings);
    printf("╠══════════════════════════════════════════════════════════════════════╣\n");
    printf("║ Seat ║ Passenger Name        ║ Source          ║ Destination       ║\n");
    printf("╠══════╬═══════════════════════╬═════════════════╬═══════════════════╣\n");
    
    while(fread(&temp, sizeof(struct Booking), 1, file)) {
        printf("║ %4d ║ %-20s ║ %-15s ║ %-17s ║\n", 
               temp.seatNo, 
               temp.name, 
               temp.source, 
               temp.destination);
        count++;
    }
    
    printf("╚══════╩═══════════════════════╩═════════════════╩═══════════════════╝\n");
    printf("\nTotal bookings: %d\n", count);
    
    fclose(file);
}

void searchReservation() {
    int searchSeat;
    printf("\nEnter seat number to search: ");
    scanf("%d", &searchSeat);
    
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("\nNo reservations in the system.\n");
        return;
    }
    
    struct Booking temp;
    int found = 0;
    
    while(fread(&temp, sizeof(struct Booking), 1, file)) {
        if(temp.seatNo == searchSeat) {
            printf("\n══════════════════════════════════════════════\n");
            printf("           RESERVATION DETAILS\n");
            printf("══════════════════════════════════════════════\n");
            printf("Seat Number:    %d\n", temp.seatNo);
            printf("Passenger:      %s\n", temp.name);
            printf("From:           %s\n", temp.source);
            printf("To:             %s\n", temp.destination);
            printf("══════════════════════════════════════════════\n");
            found = 1;
            break;
        }
    }
    
    fclose(file);
    
    if(!found) {
        printf("\nNo reservation found for Seat %d\n", searchSeat);
    }
}

void viewMenu() {
    printf("\n╔══════════════════════════════════════════════╗\n");
    printf("║            VIEW RESERVATIONS                ║\n");
    printf("╚══════════════════════════════════════════════╝\n");
    
    int choice;
    do {
        printf("\n1. View All Reservations\n");
        printf("2. Search Specific Reservation\n");
        printf("3. Return to Main Menu\n");
        printf("\nEnter your choice (1-3): ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                viewAllReservations();
                break;
            case 2:
                searchReservation();
                break;
            case 3:
                printf("\nReturning to Main Menu...\n");
                break;
            default:
                printf("\nInvalid choice! Please enter 1, 2, or 3.\n");
        }
    } while(choice != 3);
}