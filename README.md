# 8-Character Passcode File Encryptor

A C program to encrypt and decrypt any file using a custom base62 encoding and an 8-character alphanumeric passcode. The encryption is deterministic and reversible with the same passcode.

## Features
- Encrypts and decrypts any file type (text, images, documents, etc.)
- Uses an 8-character alphanumeric passcode for security
- Custom base62 encoding for output
- Simple command-line interface

## How to Compile

Open a terminal in the project directory and run:

```
gcc 8char.c -o 8char
```

## How to Use

Run the program from the terminal:

```
./8char
```

You will be prompted for:

1. **Mode**: Type `encrypt` to encrypt a file, or `decrypt` to decrypt a file.
2. **File location**: Enter the path to the file you want to encrypt or decrypt.
3. **8-character alphanumeric passcode**: Enter a passcode (letters and numbers only).
4. **Output file name**: Enter the name for the encrypted or decrypted file to be created.

### Example: Encrypting a File
```
Enter mode (encrypt/decrypt): encrypt
Enter file location to encrypt: myfile.pdf
Enter 8-character alphanumeric passcode: Abc12345
Enter encrypted file name: myfile.enc
```

### Example: Decrypting a File
```
Enter mode (encrypt/decrypt): decrypt
Enter encrypted file location: myfile.enc
Enter 8-character alphanumeric passcode: Abc12345
Enter decrypted file name: myfile_decrypted.pdf
```

## Notes
- The same 8-character passcode used for encryption must be used for decryption.
- If you lose the passcode, the file cannot be decrypted.
- The program works with any file type, not just text files.
- Output files are saved in the current directory unless you specify a full path.

## License
This project is provided as-is for educational purposes.
