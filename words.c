#include <stdio.h>
#include <ctype.h>
#include "words.h"
#include "debug_f.h"

int read_char(void){
    int temp_char = getchar();
    if(temp_char == '\t' || temp_char == '\n')
        return ' ';
    else
        return temp_char;
}

int encrypt(int character, int key)
{
    if (isupper(character))
        return 'A' + (character - 'A' + key) % TOTAL_LETTERS;

    else if (islower(character))
        return 'a' + (character - 'a' + key) % TOTAL_LETTERS;

    else if (character == ' ')
        return '*';

    else
        return character;
}

int decrypt(int character, int key)
{
    if (isupper((unsigned char)character))
        return 'A' + (character - 'A' - key + TOTAL_LETTERS) % TOTAL_LETTERS;

    else if (islower((unsigned char)character))
        return 'a' + (character - 'a' - key + TOTAL_LETTERS) % TOTAL_LETTERS;

    else if (character == '*')
        return ' ';

    else
        return character;
}

int read_word(char word[], int length){
    int temp_char, word_position = 0;
    while((temp_char = read_char()) == ' ')
        ;

    while(temp_char != ' ' && temp_char != EOF){
        if(word_position < length - 1)
            word[word_position++] = temp_char;
        temp_char = read_char();
    }
    word[word_position] = '\0';

    PRINT_DEBUG_LOCATION();
    PRINT_DEBUG_MSG(word);
    PRINT_DEBUG_int(word_position);

    return word_position;
}
