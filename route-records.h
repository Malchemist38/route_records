#ifndef ROUTE_RECORDS_H
#define ROUTE_RECORDS_H

// Define the SearchType enum
typedef enum SearchType {
    ROUTE,
    ORIGIN,
    DESTINATION,
    AIRLINE
} SearchType;

// Define the RouteRecord struct
typedef struct RouteRecord {
    char origin[4];
    char destination[4];
    char airline[3];
    int passengers[6]; // Array of passenger counts for six months
} RouteRecord;

// Prototypes for the functions defined in route-records.c
RouteRecord* createRecords(FILE* fileIn);
int fillRecords(RouteRecord* r, FILE* fileIn);
int findAirlineRoute(RouteRecord* r, int length, const char* origin, const char* destination, const char* airline, int curIdx);
void searchRecords(RouteRecord* r, int length, const char* key1, const char* key2, SearchType st);
void printMenu();

#endif /* ROUTE_RECORDS_H */
