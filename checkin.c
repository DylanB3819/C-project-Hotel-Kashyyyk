#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int rooms[6] = {0,0,0,0,0,0};
int tables[2][3] = {{0,0,0}, {0,0,0}};
int roomRates[6];
int boardRates[6];
int stayLengths[6];
int adults[6];
int children[6];
int newspapers[6];
int ages[6];
char names[6][30];
char DofBs[6][8];
char bookingIDs[6][35];
char name[30];
int valid = 0;

void checkIn(void);
void checkOut(void);
void bookTable(void);
int validDofB(const char* DofB);
char* generateID(char name[], char* ID);
int findIndex(void);
void calculateAge(const char* DofB, int i);



int main(void) {
    char choice;

    while (1) {
        srand(time(NULL));

        fflush(stdin);
        printf("Main Menu:\n");
        printf("Options:\n");
        printf("1) Check in\n");
        printf("2) Book dinner table\n");
        printf("3) Check out\n");
        printf("4) Exit system\n");
        printf("\nEnter your choice:");

        scanf("%c", &choice);
        fflush(stdin);
        choice = choice - '0';

        switch (choice) {
            case 1:
                checkIn();
                break;
            case 2:
                bookTable();
                break;
            case 3:
                checkOut();
                break;
            case 4:
                return 0;
            default:
                printf("Invalid choice\n\n");
                break;
        }
    }
}




void checkIn(void) {
    char DofB[8];
    char bookingID[35];
    int adult;
    int child;
    int room = 0;
    int boardType;
    int newspaper;
    int stayLength = 0;
    int rates[6] = {100,100,85,75,75,50};
    int index;


    printf("\nEnter your name:");
    scanf("%s", name);
    fflush(stdin);

    valid = 0;
    while (valid != 1) {
        printf("\nEnter your date of birth:");
        scanf("%s", DofB);
        fflush(stdin);
        if (validDofB(DofB) == 1) {
            valid = 1;
        }
        else {
            printf("Invalid date!!!");
        }
    }

    valid = 0;
    while (valid != 1) {
        printf("\nHow many adults: ");
        scanf("%d", &adult);
        printf("How many children: ");
        scanf("%d", &child);
        if (adult + child > 4 || adult == 0 && child == 0) {
            printf("\nMaximum of 4 people per room.\nIf your party is more than 4 then you need to book a second room");
        }
        else {
            valid = 1;
        }
    }

    valid = 0;
    while (valid != 1) {
        printf("\n1) Full board: %c20/day\n2) Half board: %c15/day\n3) Bed and Breakfast: %c5/day\nWhat board:", 156,156,156);
        scanf("%d", &boardType);
        if (boardType > 0 && boardType < 4) {
            valid = 1;
        }
        else {
            printf("Invalid board type\n");
        }
    }

    while (stayLength <= 0) {
        printf("\nHow long will your stay be? (in days):");
        scanf("%d", &stayLength);
    }

    printf("\n1) yes\n2) no\nWould you like a daily newspaper?");
    scanf("%d", &newspaper);

    printf("\nAvailable rooms:\n");
    for (int i = 0; i < 6; i++) {
        if (rooms[i] == 0) {
            printf("Room %d\nDaily rate: %c%d\n\n", i+1, 156, rates[i]);
        }
    }

    valid = 0;
    while (valid != 1) {
        printf("\nWhich room would you like?");
        scanf("%d", &room);
        if (rooms[room-1] == 0 && room <= 6 && room >= 1) {
            rooms[room-1] = 1;
            index = room-1;
            valid = 1;
        }
        else {
            printf("Invalid room!!!\n");
        }
    }

    char ID[35];
    strcpy(bookingID, generateID(name, ID));
    printf("Booking ID: %s\n\n", bookingID);
    strcpy(bookingIDs[index], bookingID);
    strcpy(names[index], name);
    strcpy(DofBs[index], DofB);
    stayLengths[index] = stayLength;
    roomRates[index] = rates[index];
    adults[index] = adult;
    children[index] = child;
    newspapers[index] = newspaper;
    calculateAge(DofB, index);
    switch (boardType) {
        case 1:
            boardRates[index] = 20;
            break;
        case 2:
            boardRates[index] = 15;
            break;
        case 3:
            boardRates[index] = 5;
            break;
    }
}




char* generateID(char name[], char* ID) {
    int randNum = rand() % 10000 + 1;
    sprintf(ID, "%s%d", name, randNum);
    return ID;
}




int validDofB(const char* DofB) {
    if (strlen(DofB) != 8) {
        return 0;
    }
    if (DofB[2] != '/' || DofB[5] != '/') {
        return 0;
    }
    if (!isdigit(DofB[0]) || !isdigit(DofB[1]) || !isdigit(DofB[3]) || !isdigit(DofB[4]) || !isdigit(DofB[6]) || !isdigit(DofB[7])) {
        return 0;
    }
    if ((DofB[3] - '0') > 2 || ((DofB[3] - '0') == 0 && (DofB[4] - '0') == 0) || ((DofB[3] - '0') != 1 && (DofB[3] - '0') > 1)) {
        return 0;
    }
    if ((DofB[0] - '0') > 3 || ((DofB[0] - '0') == 0 && (DofB[1] - '0') == 0) || ((DofB[0] - '0') == 3 && (DofB[1] - '0') > 2)) {
        return 0;
    }
        return 1;
}




void calculateAge(const char* DofB, int i) {
    int age = 0;
    char date[10];
    time_t current_time = time(NULL);
    strftime(date, 10, "%d/%m/%y", localtime(&current_time));

    int currentDay = (date[0] - '0') * 10 + (date[1] - '0');
    int currentMonth = (date[3] - '0') * 10 + (date[4] - '0');
    int currentYear = (date[6] - '0') * 10 + (date[7] - '0');

    int day = (DofB[0] - '0') * 10 + (DofB[1] - '0');
    int month = (DofB[3] - '0') * 10 + (DofB[4] - '0');
    int year = (DofB[6] - '0') * 10 + (DofB[7] - '0');

    if (year < currentYear) {
        if (month > currentMonth) {
            age = currentYear - year - 1;
        }
        else if (month == currentMonth) {
            if (day >= currentDay) {
                age = currentYear - year - 1;
            }
        }
        else {
            age = currentYear - year;
        }
    }
    else {
        if (month > currentMonth) {
            age = currentYear - year + 99;
        }
        else if (month == currentMonth) {
            if (day >= currentDay) {
                age = currentYear - year + 99;
            }
        }
        else {
            age = currentYear - year + 100;
        }
    }
    ages[i] = age;
}




void bookTable(void) {
    int boardType;
    int choice;
    int i;
    int count = 0;

    valid = 0;
    while (valid != 1) {
        i = findIndex();
        if (i>=0 && i<=5) {
            valid = 1;
        }
        printf("Please enter a valid booking ID\n");
    }
    printf("\n1) Full Board or Half Board\n2) Other\nWhat board type are you staying with?");
    scanf("%d", &boardType);
    fflush(stdin);
    if (boardType == 1 && (boardRates[i] == 20 || boardRates[i] == 15)) {
        for (int j = 0; j<2; j++) {
            for (int k = 0; k<3; k++) {
                if (tables[j][k] == 0) {
                    if (j==0) {
                        if (k==0) {
                            printf("\n1) Endor is available at 7pm");
                            count += 1;
                        }
                        else if (k==1) {
                            printf("\n2) Naboo is available at 7pm");
                            count += 1;
                        }
                        else if (k==2) {
                            printf("\n3) Tatooine is available at 7pm");
                            count += 1;
                        }
                    }
                    if (j==1) {
                        if (k==0) {
                            printf("\n4) Endor is available at 9pm");
                            count += 1;
                        }
                        else if (k==1) {
                            printf("\n5) Naboo is available at 9pm");
                            count += 1;
                        }
                        else if (k==2) {
                            printf("\n6) Tatooine is available at 9pm");
                            count += 1;
                        }
                    }
                }
            }
        }
        if (count == 0) {
            printf("\nThe are no tables available at this time.");
        }
        else {
            valid = 0;
            while(valid != 1) {
                printf("\nWhich table would you like?");
                scanf("%d", &choice);
                fflush(stdin);
                if (choice >= 1 && choice <= 6) {
                    if (choice >= 1 && choice <= 3 && tables[0][choice-1] == 0) {
                        tables[0][choice-1] = i+1;
                        printf("\nTable successfully booked.\n\n");
                        valid = 1;
                    }
                    else if (choice >= 4 && choice <= 6 && tables[1][choice-1] == 0) {
                        tables[0][choice-1] = i+1;
                        printf("\nTable successfully booked.\n\n");
                        valid = 1;
                    }
                }
                else {
                    printf("\nInvalid table choice.\n\n");
                }

            }
        }
    }
    else {
        printf("Invalid choice or board\n\n");
    }
}


int findIndex(void) {
    char ID[30];
    printf("Enter your booking ID:");
    scanf("%s", ID);
    for (int i = 0; i<6; i++) {
        if (strcmp(bookingIDs[i], ID) == 0) {
            return i;
        }
    }
    return 6;
}

void checkOut() {
    int i = findIndex();
    float roomCost = 0;
    float boardCost = 0;
    float newspaperCost = 0;

    if (i>=0 && i<=5) {
        roomCost = roomRates[i] * stayLengths[i];
        boardCost = (adults[i]*boardRates[i] + (0.5 * children[i] * boardRates[i])) * stayLengths[i];

        printf("age: %d", ages[i]);

        if(ages[i] > 65) {
            roomCost *= 0.9;
            printf("room cost: %f", roomCost);
        }

        if(newspapers[i] == 1) {
            newspaperCost = 5.5;
        }
        else {
            newspaperCost = 0;
        }
        float bill = roomCost + boardCost + newspaperCost;

        printf("\nName: %s", names[i]);
        printf("\nBooking ID: %s", bookingIDs[i]);
        printf("\n\nRoom cost: %f", roomCost);
        printf("\nBoard cost: %f", boardCost);
        printf("\nNewspaper cost: %f", newspaperCost);
        printf("\n\nTotal bill: %c%f\n\n", 156, bill);

        rooms[i]=0;
        for (int j = 0; j<2; j++) {
            for (int k = 0; k<3; k++) {
                if (tables[j][k] == i+1) {
                    tables[j][k] = 0;
                }
            }
        }
    }
    else {
        printf("Invalid booking ID");
    }
}


