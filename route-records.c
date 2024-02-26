#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "route-records.h"

RouteRecord* createRecords(FILE* fileIn) {
    int recordCount = 0;

    // Count the number of records in the file (skipping the header)
    char line[1000];
    while (fgets(line, sizeof(line), fileIn) != NULL) {
        if (strstr(line, "Month,usg_apt,fg_apt,carrier,type,Total") == NULL) {
            recordCount++;
        }
    }

    // Rewind the file pointer
    rewind(fileIn);

    // Dynamically allocate memory for an array of RouteRecords
    RouteRecord* records = (RouteRecord*)malloc(recordCount * sizeof(RouteRecord));

    // Initialize passenger counts to 0
    int i = 0;
    for (i; i < recordCount; i++) {
        int j = 0;
        for (j; j < 6; j++) {
            records[i].passengers[j] = 0;
        }
    }

    return records;
}

int fillRecords(RouteRecord* r, FILE* fileIn) {
    char line[100];
    int count = 0;

    // Skip the header row
    fgets(line, sizeof(line), fileIn);

    while (fgets(line, sizeof(line), fileIn)) {
        int month;
        char origin[4], destination[4], airline[3];
        int passengers;

        // Parse the CSV line
        sscanf(line, "%d,%3s,%3s,%2s,Passengers,%d",
               &month, origin, destination, airline, &passengers);

        // Call findAirlineRoute to check if the route exists
        int index = findAirlineRoute(r, count, origin, destination, airline, 0);

        if (index != -1) {
            // Route already exists, update passenger count for the month
            r[index].passengers[month - 1] += passengers;
        } else {
            // Route doesn't exist, add it to the array
            strcpy(r[count].origin, origin);
            strcpy(r[count].destination, destination);
            strcpy(r[count].airline, airline);
            r[count].passengers[month - 1] = passengers;
            count++;
        }
    }

    return count;
}

int findAirlineRoute(RouteRecord* r, int length, const char* origin, const char* destination, const char* airline, int curIdx) {
    if (curIdx >= length) {
        return -1;
    }

    if (strcmp(r[curIdx].origin, origin) == 0 && strcmp(r[curIdx].destination, destination) == 0 && strcmp(r[curIdx].airline, airline) == 0) {
        return curIdx;
    }

    return findAirlineRoute(r, length, origin, destination, airline, curIdx + 1);
}

void searchRecords(RouteRecord* r, int length, const char* key1, const char* key2, SearchType st) {
    int totalPassengers = 0;
    int totalPassengersByMonth[6] = {0};
    int numMatches = 0;

    printf("\nSearching by ");

    switch (st) {
        case ROUTE:
            printf("route...\n");
            break;
        case ORIGIN:
            printf("origin...\n");
            break;
        case DESTINATION:
            printf("destination...\n");
            break;
        case AIRLINE:
            printf("airline...\n");
            break;
        default:
            break;
    }
    int i = 0;
    for (i; i < length; i++) {
        int match = 0;

        switch (st) {
            case ROUTE:
                match = (strcmp(r[i].origin, key1) == 0 && strcmp(r[i].destination, key2) == 0);
                break;
            case ORIGIN:
                match = (strcmp(r[i].origin, key1) == 0);
                break;
            case DESTINATION:
                match = (strcmp(r[i].destination, key1) == 0);
                break;
            case AIRLINE:
                match = (strcmp(r[i].airline, key1) == 0);
                break;
            default:
                break;
        }

        if (match) {
            totalPassengers += r[i].passengers[0] + r[i].passengers[1] + r[i].passengers[2] + r[i].passengers[3] + r[i].passengers[4] + r[i].passengers[5];
            int j = 0;
            for (j; j < 6; j++) {
                totalPassengersByMonth[j] += r[i].passengers[j];
            }
            printf("%s (%s-%s) ", r[i].airline, r[i].origin, r[i].destination);
            numMatches++;
        }
    }

    printf("\n%d matches were found.\n\n", numMatches);

    if (totalPassengers > 0) {
        printf("Statistics\n");
        printf("Total Passengers:\t%d\n", totalPassengers);
        i = 0;
        for (i; i < 6; i++) {
            printf("Total Passengers in Month %d:\t%d\n", i + 1, totalPassengersByMonth[i]);
        }
        printf("\nAverage Passengers per Month:\t%d\n", totalPassengers / 6);
    }
}

void printMenu() {
    printf("\n\n######### Airline Route Records Database MENU #########\n");
    printf("1. Search by Route\n");
    printf("2. Search by Origin Airport\n");
    printf("3. Search by Destination Airport\n");
    printf("4. Search by Airline\n");
    printf("5. Quit\n");
    printf("Enter your selection: ");
}
