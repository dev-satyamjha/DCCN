// 4) Write a C/C++ program to translate dotted decimal IP address into 32 bit address.

#include <stdio.h>
#include <string.h>

int main() {
    char ip[20];
    unsigned int a, b, c, d;
    unsigned long ipAddress = 0;

    printf("Enter an IP address: ");
    scanf("%19s", ip);

    if (sscanf(ip, "%u.%u.%u.%u", &a, &b, &c, &d) != 4) {
        printf("Invalid IP address format!\n");
        return 1;
    }

    if (a > 255 || b > 255 || c > 255 || d > 255) {
        printf("Invalid IP address: octet out of range (0-255)\n");
        return 1;
    }

    ipAddress = (a << 24) | (b << 16) | (c << 8) | d;

    printf("32-bit representation: %lu\n", ipAddress);

    return 0;
}
