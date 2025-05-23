#include <stdio.h> // Standard input/output functions
#include <stdlib.h> // Standard library functions (exit, srand, rand)
#include <string.h> // String manipulation functions
#include <ctype.h> // Character type checking functions

char base62[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"; // Base62 character set for encoding

// Generates the encryption and decryption maps and key modifiers from the passcode
void generate_key(const char *passcode, char *enc_map, char *dec_map, int key_mod[8]) {
    strcpy(enc_map, base62); // Copy base62 into enc_map for shuffling
    int seed = 0; // Seed for random number generator
    for (int i = 0; i < 8; i++) {
        if (!isalnum(passcode[i])) { // Ensure each passcode character is alphanumeric
            printf("Invalid passcode. Must be alphanumeric.\n");
            exit(1); // Exit if invalid
        }
        key_mod[i] = (int)passcode[i];  // Store ASCII value of passcode character
        seed += key_mod[i] * (i + 1);   // Weighted sum for better randomness
    }
    srand(seed); // Seed the random number generator for deterministic shuffling
    for (int i = 61; i > 0; i--) {
        int j = rand() % (i + 1); // Get a random index for shuffling
        char temp = enc_map[i]; // Swap enc_map[i] and enc_map[j]
        enc_map[i] = enc_map[j];
        enc_map[j] = temp;
    }
    for (int i = 0; i < 128; i++) dec_map[i] = -1; // Initialize dec_map to -1 (invalid)
    for (int i = 0; i < 62; i++) {
        dec_map[(int)enc_map[i]] = i; // Map each encoded character to its index for decoding
    }
}

// Encrypts the input file and writes the encrypted output file
void encrypt_file(const char *infile, const char *outfile, const char *enc_map, int key_mod[8]) {
    FILE *fin = fopen(infile, "rb"); // Open input file in binary mode
    if (!fin) {
        printf("Cannot open input file.\n");
        exit(1);
    }
    FILE *fout = fopen(outfile, "w"); // Open output file in text mode
    if (!fout) {
        printf("Cannot open output file.\n");
        fclose(fin);
        exit(1);
    }
    int i = 0; // Byte index
    int ch;
    while ((ch = fgetc(fin)) != EOF) { // Read each byte from input
        unsigned char val = (unsigned char)ch; // Get byte value
        val = (val + (i * key_mod[i % 8])) % 256; // Modify byte using key_mod and index
        int hi = val / 62; // High part for base62 encoding
        int lo = val % 62; // Low part for base62 encoding
        fputc(enc_map[hi], fout); // Write encoded high character
        fputc(enc_map[lo], fout); // Write encoded low character
        i++;
    }
    fclose(fin); // Close input file
    fclose(fout); // Close output file
    printf("File encrypted and saved as %s\n", outfile);
}

// Decrypts the encrypted file and writes the decrypted output file
void decrypt_file(const char *infile, const char *outfile, const char *dec_map, int key_mod[8]) {
    FILE *fin = fopen(infile, "r"); // Open encrypted file in text mode
    if (!fin) {
        printf("Cannot open encrypted file.\n");
        exit(1);
    }
    FILE *fout = fopen(outfile, "wb"); // Open output file in binary mode
    if (!fout) {
        printf("Cannot open output file.\n");
        fclose(fin);
        exit(1);
    }
    int i = 0; // Byte index
    int c1, c2;
    while ((c1 = fgetc(fin)) != EOF && (c2 = fgetc(fin)) != EOF) { // Read two encoded chars
        int hi = dec_map[c1]; // Decode high part
        int lo = dec_map[c2]; // Decode low part
        if (hi == -1 || lo == -1) { // Check for invalid characters
            printf("Decryption error: invalid character.\n");
            fclose(fin);
            fclose(fout);
            exit(1);
        }
        int val = hi * 62 + lo; // Combine to get original value
        val = (val - (i * key_mod[i % 8]) + 256) % 256; // Reverse the key_mod transformation
        fputc((unsigned char)val, fout); // Write original byte
        i++;
    }
    fclose(fin); // Close encrypted file
    fclose(fout); // Close output file
    printf("File decrypted and saved as %s\n", outfile);
}

int main() {
    char infile[260]; // Input file path
    char outfile[260]; // Output file path
    char passcode[9]; // 8-character passcode + null terminator
    char enc_map[63]; // Encoded character map
    char dec_map[128]; // Decoding map
    int key_mod[8]; // Key modifiers
    char mode[10]; // Mode string (encrypt/decrypt)

    printf("Enter mode (encrypt/decrypt): "); // Prompt for mode
    scanf("%9s", mode); // Read mode

    if (strcmp(mode, "encrypt") == 0) {
        printf("Enter file location to encrypt: ");
        scanf("%259s", infile); // Read input file path
        printf("Enter 8-character alphanumeric passcode: ");
        scanf("%8s", passcode); // Read passcode
        printf("Enter encrypted file name: ");
        scanf("%259s", outfile); // Read output file name
        generate_key(passcode, enc_map, dec_map, key_mod); // Generate key and maps
        encrypt_file(infile, outfile, enc_map, key_mod); // Encrypt file
    } else if (strcmp(mode, "decrypt") == 0) {
        printf("Enter encrypted file location: ");
        scanf("%259s", infile); // Read encrypted file path
        printf("Enter 8-character alphanumeric passcode: ");
        scanf("%8s", passcode); // Read passcode
        printf("Enter decrypted file name: ");
        scanf("%259s", outfile); // Read output file name
        generate_key(passcode, enc_map, dec_map, key_mod); // Generate key and maps
        decrypt_file(infile, outfile, dec_map, key_mod); // Decrypt file
    } else {
        printf("Invalid mode.\n"); // Invalid mode entered
    }
    return 0; // End program
}
