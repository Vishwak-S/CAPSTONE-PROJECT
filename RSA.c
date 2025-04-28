#include <stdio.h>
#include <ctype.h>

// Function to compute the modular inverse for d calculation
long long modInverse(long long e, long long phi) {
    long long d = 0;
    long long x1 = 0, x2 = 1, y1 = 1, temp_phi = phi;
    
    while (e > 0) {
        long long temp1 = temp_phi / e;
        long long temp2 = temp_phi - temp1 * e;
        temp_phi = e;
        e = temp2;
        
        long long x = x2 - temp1 * x1;
        long long y = d - temp1 * y1;
        
        x2 = x1;
        x1 = x;
        d = y1;
        y1 = y;
    }
    
    if (temp_phi == 1) {
        return d + phi;
    }
    return 0;
}

// Modular exponentiation function for both encryption and decryption
long long crypt(long long P, long long key, long long n) {
    long long C = 1;
    P = P % n;
    while (key > 0) {
        if (key % 2 == 1) {
            C = (C * P) % n;
        }
        key = key / 2;
        P = (P * P) % n;
    }
    return C;
}

void encrypt() {
    int p = 61, q = 53;
    int n = p * q;
    int e = 17;

    printf("\nEnter message to encrypt (Press ENTER to finish):\n");
    getchar(); // Consume the newline from previous input

    char ch;
    int firstChar = 1;

    while (1) {
        ch = getchar();
        if (ch == '\n') break;
        if (firstChar) {
            printf("\nEncrypted message is:\n");
            firstChar = 0;
        }
        if (ch == ' ') {
            printf("  ");
        } else {
            long long C = crypt((long long)ch, e, n);
            printf("%lld ", C);
        }
    }
    printf("\n");
}

void decrypt() {
    int p = 61, q = 53;
    int n = p * q;
    int e = 17;
    long long phi = (p - 1) * (q - 1);
    long long d = modInverse(e, phi);

    printf("\nEnter encrypted numbers separated by spaces (Press ENTER to finish):\n");
    getchar(); // Consume the newline from previous input

    long long num;
    int firstChar = 1;

    while (1) {
        // Check if the next character is newline
        char peek = getchar();
        if (peek == '\n') break;
        ungetc(peek, stdin);
        
        if (firstChar) {
            printf("\nDecrypted message is:\n");
            firstChar = 0;
        }
        
        // Read the encrypted number
        if (scanf("%lld", &num) == 1) {
            if (num == ' ') {
                printf(" ");
            } else {
                long long P = crypt(num, d, n);
                printf("%c", (char)P);
            }
        }
    }
    printf("\n");
}

int main() {
    int choice;
    char continueChoice;
    
    do {
        printf("\nRSA Encryption/Decryption Program\n");
        printf("1. Encrypt\n");
        printf("2. Decrypt\n");
        printf("3. Exit\n");
        printf("Enter your choice (1, 2, or 3): ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                encrypt();
                printf("The value of p is 61, q is 53 & e is 17");
                break;
            case 2:
                printf("Ensure that the plain text has been encrypted using the values of p=61, q=53 & e=17");
                decrypt();
                break;
            case 3:
                printf("Exiting program...\n");
                return 0;
            default:
                printf("Invalid choice! Please try again.\n");
                continue;
        }
        
        printf("\nDo you want to continue? (y/n): ");
        scanf(" %c", &continueChoice);
        
    } while(tolower(continueChoice) == 'y');
    
    printf("Exiting program...\n");
    return 0;
}
