//Write a C program that performs error detection using:
//1.Single Parity Checking
//2.Two-Dimensional Parity Checking
//3.Cyclic Redundancy Check (CRC)
//4.Internet Checksum

#include <stdio.h>
#include <string.h>

#define MAX 500

void singleParity();
void twoDParity();
void crcCheck();
void checksumMethod();
int isValidBinary(char *s);
void clearBuffer();

void singleParity() {
    char bits[MAX], received[MAX];
    int ones = 0, type;

    printf("\n--- Single Parity Check ---\n");
    printf("Enter your binary data: ");
    scanf("%s", bits);

    if (!isValidBinary(bits)) {
        printf("Oops! Only 0s and 1s please.\n");
        return;
    }

    for (int i = 0; i < strlen(bits); i++) {
        if (bits[i] == '1') ones++;
    }

    printf("Pick parity - 1 for Even, 2 for Odd: ");
    scanf("%d", &type);

    if (type != 1 && type != 2) {
        printf("Invalid choice!\n");
        return;
    }

    int parityBit = (type == 1) ? (ones % 2) : (1 - ones % 2);

    printf("\nYour data: %s\n", bits);
    printf("Ones count: %d\n", ones);
    printf("Parity bit: %d\n", parityBit);
    printf("Final code: %s%d\n", bits, parityBit);

    printf("\nNow enter what you received: ");
    scanf("%s", received);

    if (!isValidBinary(received) || strlen(received) != strlen(bits) + 1) {
        printf("Something's wrong with that input!\n");
        return;
    }

    int checkOnes = 0;
    for (int i = 0; i < strlen(received); i++) {
        if (received[i] == '1') checkOnes++;
    }

    int good = (type == 1) ? (checkOnes % 2 == 0) : (checkOnes % 2 == 1);

    if (good)
        printf("All good! No errors found.\n");
    else
        printf("Uh oh! Error detected!\n");
}

void twoDParity() {
    int rows, cols;

    printf("\n--- 2D Parity Check ---\n");
    printf("How many rows? ");
    scanf("%d", &rows);
    printf("How many columns? ");
    scanf("%d", &cols);

    if (rows <= 0 || cols <= 0 || rows > 50 || cols > 50) {
        printf("That's not gonna work!\n");
        clearBuffer();
        return;
    }

    int grid[rows][cols + 1];
    int colCheck[cols + 1];

    for (int i = 0; i <= cols; i++) colCheck[i] = 0;

    printf("\nEnter your data row by row:\n");
    for (int i = 0; i < rows; i++) {
        printf("Row %d: ", i + 1);
        for (int j = 0; j < cols; j++) {
            scanf("%d", &grid[i][j]);
            if (grid[i][j] != 0 && grid[i][j] != 1) {
                printf("Only 0 or 1 allowed!\n");
                clearBuffer();
                return;
            }
            colCheck[j] ^= grid[i][j];
        }

        int rowCheck = 0;
        for (int j = 0; j < cols; j++) rowCheck ^= grid[i][j];
        grid[i][cols] = rowCheck;
        colCheck[cols] ^= rowCheck;
    }

    printf("\nHere's your data with parity:\n");
    for (int j = 0; j < cols; j++) printf(" %d ", j);
    printf(" P\n");

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j <= cols; j++) printf(" %d ", grid[i][j]);
        printf("\n");
    }

    for (int j = 0; j <= cols; j++) printf(" %d ", colCheck[j]);
    printf(" <- Parity\n");
}

void crcCheck() {
    char data[MAX], gen[MAX], work[MAX];

    printf("\n--- CRC Method ---\n");
    printf("Enter data bits: ");
    scanf("%s", data);

    if (!isValidBinary(data)) {
        printf("Binary only please!\n");
        return;
    }

    printf("Enter generator: ");
    scanf("%s", gen);

    if (!isValidBinary(gen) || gen[0] != '1') {
        printf("Generator must be binary and start with 1!\n");
        return;
    }

    int dLen = strlen(data);
    int gLen = strlen(gen);

    if (gLen > dLen) {
        printf("Generator too long!\n");
        return;
    }

    strcpy(work, data);
    for (int i = 0; i < gLen - 1; i++) strcat(work, "0");

    printf("\nData: %s\n", data);
    printf("Generator: %s\n", gen);
    printf("Working string: %s\n", work);

    char temp[MAX];
    strcpy(temp, work);

    for (int i = 0; i <= strlen(temp) - gLen; i++) {
        if (temp[i] == '1') {
            for (int j = 0; j < gLen; j++) {
                temp[i + j] = (temp[i + j] == gen[j]) ? '0' : '1';
            }
        }
    }

    char remainder[MAX];
    int idx = 0;
    for (int i = strlen(temp) - (gLen - 1); i < strlen(temp); i++) {
        remainder[idx++] = temp[i];
    }
    remainder[idx] = '\0';

    printf("CRC bits: %s\n", remainder);

    char code[MAX];
    strcpy(code, data);
    strcat(code, remainder);
    printf("Send this: %s\n", code);

    printf("\nWhat did you receive? ");
    char recv[MAX];
    scanf("%s", recv);

    if (!isValidBinary(recv) || strlen(recv) != strlen(code)) {
        printf("That doesn't look right!\n");
        return;
    }

    strcpy(temp, recv);
    for (int i = 0; i <= strlen(temp) - gLen; i++) {
        if (temp[i] == '1') {
            for (int j = 0; j < gLen; j++) {
                temp[i + j] = (temp[i + j] == gen[j]) ? '0' : '1';
            }
        }
    }

    int err = 0;
    for (int i = strlen(temp) - (gLen - 1); i < strlen(temp); i++) {
        if (temp[i] == '1') {
            err = 1;
            break;
        }
    }

    printf(err ? "Error found!\n" : "Looks good!\n");
}

void checksumMethod() {
    int bits, count;

    printf("\n--- Internet Checksum ---\n");
    printf("Segment size in bits (8 or 16): ");
    scanf("%d", &bits);

    if (bits != 8 && bits != 16) {
        printf("Use 8 or 16 bits!\n");
        clearBuffer();
        return;
    }

    printf("How many segments? ");
    scanf("%d", &count);

    if (count <= 0 || count > 100) {
        printf("That's too many or too few!\n");
        clearBuffer();
        return;
    }

    unsigned long vals[count];
    unsigned long total = 0;
    unsigned long limit = (1UL << bits) - 1;

    printf("\nEnter segments (as numbers):\n");
    for (int i = 0; i < count; i++) {
        printf("Segment %d: ", i + 1);
        scanf("%lu", &vals[i]);

        if (vals[i] > limit) {
            printf("Too big for %d bits!\n", bits);
            clearBuffer();
            return;
        }

        total += vals[i];
        while (total > limit) {
            unsigned long carry = total >> bits;
            total = (total & limit) + carry;
        }
    }

    unsigned long check = limit - total;

    printf("\nSum: %lu\n", total);
    printf("Checksum: %lu\n", check);
    printf("Send all segments plus this checksum!\n");

    printf("\nReceiving side - enter all segments (data + checksum):\n");
    int recvCount;
    printf("How many total? ");
    scanf("%d", &recvCount);

    if (recvCount != count + 1) {
        printf("Should be %d segments!\n", count + 1);
        clearBuffer();
        return;
    }

    unsigned long recvTotal = 0;
    for (int i = 0; i < recvCount; i++) {
        unsigned long v;
        printf("Segment %d: ", i + 1);
        scanf("%lu", &v);

        if (v > limit) {
            printf("Value too large!\n");
            clearBuffer();
            return;
        }

        recvTotal += v;
        while (recvTotal > limit) {
            unsigned long carry = recvTotal >> bits;
            recvTotal = (recvTotal & limit) + carry;
        }
    }

    printf("Final sum: %lu\n", recvTotal);
    printf(recvTotal == limit ? "Perfect! No errors.\n" : "Oops! Error detected!\n");
}

int isValidBinary(char *s) {
    if (strlen(s) == 0 || strlen(s) >= MAX) return 0;
    for (int i = 0; i < strlen(s); i++) {
        if (s[i] != '0' && s[i] != '1') return 0;
    }
    return 1;
}

void clearBuffer() {
    while (getchar() != '\n');
}

int main() {
    int pick;

    do {
        printf("\n==============================\n");
        printf("  Error Detection Methods\n");
        printf("==============================\n");
        printf("1. Single Parity\n");
        printf("2. Two Dimension Parity\n");
        printf("3. CRC\n");
        printf("4. Checksum\n");
        printf("5. Exit\n");
        printf("==============================\n");
        printf("What would you like to try? ");

        if (scanf("%d", &pick) != 1) {
            printf("That's not a number!\n");
            clearBuffer();
            continue;
        }

        switch (pick) {
            case 1: singleParity(); break;
            case 2: twoDParity(); break;
            case 3: crcCheck(); break;
            case 4: checksumMethod(); break;
            case 5: printf("\nThanks for using this program!\n"); break;
            default: printf("Pick 1 to 5!\n");
        }

    } while (pick != 5);

    return 0;
}
