# File Encryptor

A simple C program to encrypt and decrypt files using a 6-digit PIN. The program uses a custom base62 encoding and a PIN-derived key for encryption and decryption.

## Features
- Encrypt any file with a 6-digit numeric PIN
- Decrypt previously encrypted files with the correct PIN
- Simple command-line interface

## How to Compile

Open a terminal in the project directory and run:

```
gcc file_encryptor.c -o file_encryptor
```

## How to Use

Run the program from the terminal:

```
./file_encryptor
```

You will be prompted for:

1. **Mode**: Type `encrypt` to encrypt a file, or `decrypt` to decrypt a file.
2. **File location**: Enter the path to the file you want to encrypt or decrypt.
3. **6-digit numeric passcode**: Enter a 6-digit PIN (numbers only).
4. **Output file name**: Enter the name for the encrypted or decrypted file to be created.

### Example: Encrypting a File
```
Enter mode (encrypt/decrypt): encrypt
Enter file location to encrypt: myfile.txt
Enter 6-digit numeric passcode: 123456
Enter encrypted file name: myfile.enc
```

### Example: Decrypting a File
```
Enter mode (encrypt/decrypt): decrypt
Enter encrypted file location: myfile.enc
Enter 6-digit numeric passcode: 123456
Enter decrypted file name: myfile_decrypted.txt
```

## Notes
- The same 6-digit PIN used for encryption must be used for decryption.
- If you lose the PIN, the file cannot be decrypted.
- Only use numeric digits for the PIN.

## License
This project is provided as-is for educational purposes.
