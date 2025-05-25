#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char base62[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";

void generate_key(const char *passcode, char *enc_map, char *dec_map, int key_mod[6]) {
    strcpy(enc_map, base62);
    int seed = 0;
    for (int i = 0; i < 6; i++) {
        if (!isdigit(passcode[i])) {
            printf("Invalid passcode.\n");
            exit(1);
        }
        key_mod[i] = passcode[i] - '0';
        seed = seed * 10 + key_mod[i];
    }
    srand(seed);
    for (int i = 61; i > 0; i--) {
        int j = rand() % (i + 1);
        char temp = enc_map[i];
        enc_map[i] = enc_map[j];
        enc_map[j] = temp;
    }
    for (int i = 0; i < 62; i++) {
        dec_map[(int)enc_map[i]] = i;
    }
}

void encrypt_file(const char *infile, const char *outfile, const char *enc_map, int key_mod[6]) {
    FILE *fin = fopen(infile, "rb");
    if (!fin) {
        printf("Cannot open input file.\n");
        exit(1);
    }
    FILE *fout = fopen(outfile, "w");
    if (!fout) {
        printf("Cannot open output file.\n");
        fclose(fin);
        exit(1);
    }
    int i = 0;
    int ch;
    while ((ch = fgetc(fin)) != EOF) {
        unsigned char val = (unsigned char)ch;
        val = (val + (i * key_mod[i % 6])) % 256;
        int hi = val / 62;
        int lo = val % 62;
        fputc(enc_map[hi], fout);
        fputc(enc_map[lo], fout);
        i++;
    }
    fclose(fin);
    fclose(fout);
    printf("File encrypted and saved as %s\n", outfile);
}

void decrypt_file(const char *infile, const char *outfile, const char *dec_map, int key_mod[6]) {
    FILE *fin = fopen(infile, "r");
    if (!fin) {
        printf("Cannot open encrypted file.\n");
        exit(1);
    }
    FILE *fout = fopen(outfile, "wb");
    if (!fout) {
        printf("Cannot open output file.\n");
        fclose(fin);
        exit(1);
    }
    int i = 0;
    int c1, c2;
    while ((c1 = fgetc(fin)) != EOF && (c2 = fgetc(fin)) != EOF) {
        int hi = dec_map[c1];
        int lo = dec_map[c2];
        int val = hi * 62 + lo;
        val = (val - (i * key_mod[i % 6]) + 256) % 256;
        fputc((unsigned char)val, fout);
        i++;
    }
    fclose(fin);
    fclose(fout);
    printf("File decrypted and saved as %s\n", outfile);
}

int main() {
    char infile[260];
    char outfile[260];
    char passcode[7];
    char enc_map[63];
    char dec_map[128];
    int key_mod[6];
    char mode[10];

    printf("Enter mode (encrypt/decrypt): ");
    scanf("%9s", mode);

    if (strcmp(mode, "encrypt") == 0) {
        printf("Enter file location to encrypt: ");
        scanf("%259s", infile);
        printf("Enter 6-digit numeric passcode: ");
        scanf("%6s", passcode);
        printf("Enter encrypted file name: ");
        scanf("%259s", outfile);
        generate_key(passcode, enc_map, dec_map, key_mod);
        encrypt_file(infile, outfile, enc_map, key_mod);
    } else if (strcmp(mode, "decrypt") == 0) {
        printf("Enter encrypted file location: ");
        scanf("%259s", infile);
        printf("Enter 6-digit numeric passcode: ");
        scanf("%6s", passcode);
        printf("Enter decrypted file name: ");
        scanf("%259s", outfile);
        generate_key(passcode, enc_map, dec_map, key_mod);
        decrypt_file(infile, outfile, dec_map, key_mod);
    } else {
        printf("Invalid mode.\n");
    }
    return 0;
}
