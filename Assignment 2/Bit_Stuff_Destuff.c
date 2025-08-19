// 5) Write a C/C++ program to perform bit stuffing and de-stuffing.

#include <stdio.h>
#include <string.h>

#define MAX 100

void bitStuffing(char input[], char stuffed[]) {
    int i, count = 0, j = 0;
    for (i = 0; i < strlen(input); i++) {
        stuffed[j++] = input[i];
        if (input[i] == '1') {
            count++;
            if (count == 5) {
                stuffed[j++] = '0';
                count = 0;
            }
        } else {
            count = 0;
        }
    }
    stuffed[j] = '\0';
}

void bitDeStuffing(char stuffed[], char destuffed[]) {
    int i, count = 0, j = 0;
    for (i = 0; i < strlen(stuffed); i++) {
        destuffed[j++] = stuffed[i];
        if (stuffed[i] == '1') {
            count++;
            if (count == 5) {
                i++; 
                count = 0;
            }
        } else {
            count = 0;
        }
    }
    destuffed[j] = '\0';
}

int main() {
    char input[MAX], stuffed[MAX], destuffed[MAX];

    printf("Enter the bit stream (only 0s and 1s): ");
    scanf("%s", input);

    bitStuffing(input, stuffed);
    printf("After Bit Stuffing:   %s\n", stuffed);

    bitDeStuffing(stuffed, destuffed);
    printf("After Bit De-stuffing:%s\n", destuffed);

    return 0;
}