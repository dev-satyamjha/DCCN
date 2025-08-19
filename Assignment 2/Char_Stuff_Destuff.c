// 6)Write a C/C++ program to perform character stuffing and de-stuffing.

#include <stdio.h>
#include <string.h>

#define MAX 100
#define FLAG 'F'   
#define ESC  'E'   

void charStuffing(char input[], char stuffed[]) {
    int i, j = 0;
    stuffed[j++] = FLAG;  

    for (i = 0; i < strlen(input); i++) {
        if (input[i] == FLAG || input[i] == ESC) {
            stuffed[j++] = ESC;  
        }
        stuffed[j++] = input[i];
    }

    stuffed[j++] = FLAG;  
    stuffed[j] = '\0';
}

void charDeStuffing(char stuffed[], char destuffed[]) {
    int i, j = 0;

    for (i = 1; i < strlen(stuffed) - 1; i++) {
        if (stuffed[i] == ESC) {
            i++; 
        }
        destuffed[j++] = stuffed[i];
    }
    destuffed[j] = '\0';
}

int main() {
    char input[MAX], stuffed[MAX], destuffed[MAX];

    printf("Enter the data string: ");
    scanf("%s", input);

    charStuffing(input, stuffed);
    printf("After Character Stuffing:   %s\n", stuffed);

    charDeStuffing(stuffed, destuffed);
    printf("After Character De-stuffing:%s\n", destuffed);

    return 0;
}