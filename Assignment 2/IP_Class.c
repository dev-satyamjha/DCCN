// Q3) Write a C/C++ program to determine if the IP address is in Class A, B, C, D, or E.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    char ip[20];
    printf("Enter an IP address: ");
    scanf("%19s", ip);

    char *token = strtok(ip, ".");
    if (token == NULL) {
        printf("Invalid IP address\n");
        return 0;
    }

    int firstOctet = atoi(token);

    if (firstOctet >= 1 && firstOctet <= 126)
        printf("Class A\n");
    else if (firstOctet >= 128 && firstOctet <= 191)
        printf("Class B\n");
    else if (firstOctet >= 192 && firstOctet <= 223)
        printf("Class C\n");
    else if (firstOctet >= 224 && firstOctet <= 239)
        printf("Class D (Multicast)\n");
    else if (firstOctet >= 240 && firstOctet <= 255)
        printf("Class E (Experimental)\n");
    else
        printf("Invalid IP Address\n");

    return 0;
}
