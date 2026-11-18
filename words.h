#ifndef WORDS_H
#define WORDS_H

#define TOTAL_LETTERS 26

//Read a character only one, replace '\t' and '\n' with space.
int read_char(void);

//Encrypt using Caesar Cipher, replace space with the letter '\''
int encrypt(int character, int key);

//Decrypt the letters, by (char - key) % TOTAL_LETTERS
int decrypt(int character, int key);

//Read a word, skip leading white space, and return the letters number read.
int read_word(char word[], int length);


#endif // WORDS_H
