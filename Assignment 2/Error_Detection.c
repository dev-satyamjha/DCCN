/* 7)  Write a C/C++ program to perform error detection method using-
➢ Single parity checking method
➢ Two dimension parity checking method
➢ Cyclic redundancy check(CRC) method
➢ Internet checksum method */


#include <stdio.h>
#include <string.h>

int singleParity(char data[]) {
    int count = 0;
    for (int i = 0; i < strlen(data); i++) {
        if (data[i] == '1')
            count++;
    }
    return count % 2;  
}

void twoDimParity(char data[4][5], int row, int col) {
    int i, j;
    int rowParity[4], colParity[5];

    printf("\nOriginal 2D Data:\n");
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++)
            printf("%c ", data[i][j]);
        printf("\n");
    }

    printf("\nRow Parities: ");
    for (i = 0; i < row; i++) {
        int count = 0;
        for (j = 0; j < col; j++) {
            if (data[i][j] == '1')
                count++;
        }
        rowParity[i] = count % 2;
        printf("%d ", rowParity[i]);
    }

    printf("\nColumn Parities: ");
    for (j = 0; j < col; j++) {
        int count = 0;
        for (i = 0; i < row; i++) {
            if (data[i][j] == '1')
                count++;
        }
        colParity[j] = count % 2;
        printf("%d ", colParity[j]);
    }
    printf("\n");
}

void xorOperation(char *a, char *b, int n) {
    for (int i = 1; i < n; i++)
        a[i] = (a[i] == b[i]) ? '0' : '1';
}

void crc(char data[], char gen[]) {
    int dlen = strlen(data), glen = strlen(gen);
    char temp[50], rem[50];

    strcpy(temp, data);
    for (int i = 0; i < glen - 1; i++)
        strcat(temp, "0"); // append zeros

    strncpy(rem, temp, glen);
    int n = strlen(temp);

    for (int i = glen; i <= n; i++) {
        if (rem[0] == '1')
            xorOperation(rem, gen, glen);
        memmove(rem, rem + 1, glen - 1);
        rem[glen - 1] = temp[i];
    }
    rem[glen - 1] = '\0';

    printf("\nCRC Remainder: %s", rem);
    printf("\nTransmitted Frame: %s%s\n", data, rem);
}

unsigned short checksum(unsigned short arr[], int n) {
    unsigned long sum = 0;
    for (int i = 0; i < n; i++) {
        sum += arr[i];
        if (sum & 0x10000) { // carry
            sum = (sum & 0xFFFF) + 1;
        }
    }
    return ~sum;
}

int main() {
    char data1[50];
    printf("Enter bit stream for single parity check: ");
    scanf("%s", data1);
    int p = singleParity(data1);
    printf("Parity bit (even parity): %d\n", p);

    char data2[4][5] = {{"1010"}, {"1100"}, {"1001"}, {"0110"}};
    twoDimParity(data2, 4, 4);

    char data3[50], gen[50];
    printf("\nEnter data bits for CRC: ");
    scanf("%s", data3);
    printf("Enter generator bits: ");
    scanf("%s", gen);
    crc(data3, gen);

    unsigned short arr[4];
    printf("\nEnter 4 16-bit words (in hex) for checksum: ");
    for (int i = 0; i < 4; i++)
        scanf("%hx", &arr[i]);

    unsigned short csum = checksum(arr, 4);
    printf("Internet Checksum: %04X\n", csum);

    return 0;
}