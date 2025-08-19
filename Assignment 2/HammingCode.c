// 8) Write a C/C++ program to perform error correction using Hamming code method.

#include <stdio.h>
#include <string.h>
#include <math.h>

void generateHammingCode(int data[], int m) {
    int r = 0;
    while ((1 << r) < (m + r + 1)) r++;

    int n = m + r;
    int code[50] = {0};

    int j = 0;
    for (int i = 1; i <= n; i++) {
        if ((i & (i - 1)) == 0)
            code[i] = 0;
        else
            code[i] = data[j++];
    }

    for (int i = 0; i < r; i++) {
        int pos = (1 << i);
        int parity = 0;
        for (int k = 1; k <= n; k++) {
            if (k & pos) {
                parity ^= code[k];
            }
        }
        code[pos] = parity;
    }

    printf("\nGenerated Hamming Code: ");
    for (int i = n; i >= 1; i--)
        printf("%d", code[i]);
    printf("\n");
}

void detectError(int code[], int n) {
    int r = 0;
    while ((1 << r) < (n + 1)) r++;

    int errorPos = 0;
    for (int i = 0; i < r; i++) {
        int pos = (1 << i);
        int parity = 0;
        for (int k = 1; k <= n; k++) {
            if (k & pos) {
                parity ^= code[k];
            }
        }
        if (parity != 0)
            errorPos += pos;
    }

    if (errorPos == 0) {
        printf("\nNo error detected in received code.\n");
    } else {
        printf("\nError detected at bit position: %d\n", errorPos);
        code[errorPos] ^= 1;
        printf("Corrected Code: ");
        for (int i = n; i >= 1; i--)
            printf("%d", code[i]);
        printf("\n");
    }
}

int main() {
    int m;
    printf("Enter number of data bits: ");
    scanf("%d", &m);

    int data[50];
    printf("Enter data bits (LSB first): ");
    for (int i = 0; i < m; i++)
        scanf("%d", &data[i]);

    generateHammingCode(data, m);

    int n = m;
    int r = 0;
    while ((1 << r) < (n + r + 1)) r++;
    n = m + r;

    int recv[50];
    printf("\nEnter received Hamming code (LSB first, %d bits): ", n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &recv[i]);

    detectError(recv, n);

    return 0;
}
