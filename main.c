#include <stdio.h>
#include <stdlib.h>
#include "route-records.h"

int main( int argc, char *argv[] )
{
    /* 1. Declare variables here */
    FILE *fileIn;
    RouteRecord *records;
    int totalRecords;
    
    /* 2. Check command line arguments here. If a command line argument (for the file name) is missing, print out the following: ERROR: Missing file name and end the program */
    if (argc < 2) {
        printf("ERROR: Missing file name\n");
        return 1;
    }
    
    /* 3. Attempt to open the file. Print out Opening <filename>... before you call fopen(). */
    printf("Opening %s...\n", argv[1]);
    fileIn = fopen(argv[1], "r");
    
    /* 4. Check to see if the file opens. If it does not open, print out ERROR: Could not open file and end the program. */
    if (fileIn == NULL) {
        printf("ERROR: Could not open file\n");
        return 1;
    }

    /* 5. Do the following to load the records into an array of RouteRecords */
    records = createRecords(fileIn); /* 5.1 */
    totalRecords = fillRecords(records, fileIn); /* 5.2 */
    printf("Unique routes operated by airlines: %d\n", totalRecords); /* 5.2 */

    fclose(fileIn); /* 5.3 */
    
    /* 6. Create an infinite loop that will do the following: */
    while (1) {
        printMenu(); /* 6.1 */
        
        int choice;
        char key1[4], key2[4]; /* Assuming airport codes are 3 characters + null terminator */
        SearchType searchType;
        
        /* 6.2 Ask the user to input a value for the menu */
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            break;
        }
        
        // 6.4 Create a switch/case statement to handle all the menu options
        switch (choice) {
            case 1: // Search by Route
                {
                    char origin[4], destination[4];
                    printf("Enter origin: ");
                    scanf("%s", origin);
                    printf("Enter destination: ");
                    scanf("%s", destination);

                    searchRecords(records, totalRecords, origin, destination, ROUTE);
                }
                break;
            case 2: // Search by Origin Airport
                {
                    char origin[4];
                    printf("Enter origin: ");
                    scanf("%s", origin);

                    searchRecords(records, totalRecords, origin, NULL, ORIGIN);
                }
                break;
            case 3: // Search by Destination Airport
                {
                    char destination[4];
                    printf("Enter destination: ");
                    scanf("%s", destination);

                    searchRecords(records, totalRecords, destination, NULL, DESTINATION);
                }
                break;
            case 4: // Search by Airline
                {
                    char airline[3];
                    printf("Enter airline: ");
                    scanf("%s", airline);

                    searchRecords(records, totalRecords, airline, NULL, AIRLINE);
                }
                break;
            case 5: // Quit
                free(records); // Free dynamically allocated memory
                printf("Goodbye!");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }
    
    return 0;
}
