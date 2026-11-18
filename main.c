#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "words.h"
#include "line.h"
#include "debug_f.h"

#define MAX_LINE_BUFFER_LEN 60  //Without counting '\0' with it, it would be 61
#define MAX_WORD_LENGTH 20      //Without counting '\0' with it, it would be 21

int main(int argc, char *argv[]){
    //flag
    int e = 0, d = 0, key = 0, only = 0;
    int opt;
    opterr = 0;


    //accept options throw command line.
    while((opt = getopt(argc, argv, "e:d:o")) != -1){
        switch(opt){
            case 'e':   e = 1; key = atoi(optarg);//encryption
                        if(key == 0){
                            fprintf(stderr, "Error key invalid or missing!\n");
                            return -1;
                        }break;
            case 'd':   d = 1; key = atoi(optarg);//decryption
                        if(key == 0){
                            fprintf(stderr, "Error key invalid or missing!\n");
                            return -1;
                        }break;
            case 'o':   only = 1; break;
            case '?':   fprintf(stderr, "Error invalid option -%c!\n", optopt); return -1;
        }
    }

    if(e == 1 && d == 1){
        fprintf(stderr, "Error! can't do both encrypt and decrypt!\n");
        return -1;
    }


    char line_buffer[MAX_LINE_BUFFER_LEN + 1];
    char word[MAX_WORD_LENGTH + 1];

    //Line_buffer_pos is the length of content inside line buffer.
    int word_length = 0, remaining_space = MAX_LINE_BUFFER_LEN, line_buffer_pos = 0;


    while(1 && only == 0){
        word_length = read_word(word, MAX_WORD_LENGTH + 1);
        PRINT_DEBUG_LOCATION();
        PRINT_DEBUG_int(word_length);

        //If word length == 0 it means EOF so we print line buffer without justification and terminate.
        if(word_length == 0){
            if(e == 1 && d == 0)
                encrypt_line(line_buffer, key);
            else if(e == 0 && d == 1)
                decrypt_line(line_buffer, key);

            flush_line(line_buffer);
            PRINT_DEBUG("Line flushed!");
            break;
        //Here word_length + 1, the 1 is because we are adding usually a space before word
        }else if(word_length + 1 > remaining_space){
            justify(line_buffer, line_buffer_pos, remaining_space);

            //Encrypt Decrypt functions.
            if(e == 1 && d == 0)
                encrypt_line(line_buffer, key);
            else if(e == 0 && d == 1)
                decrypt_line(line_buffer, key);


            flush_line(line_buffer);
            PRINT_DEBUG("Line flushed!");
            clear_buffer(line_buffer, MAX_LINE_BUFFER_LEN + 1, &line_buffer_pos);
            PRINT_DEBUG_int(line_buffer_pos);
        }

        add_word(line_buffer, line_buffer_pos, word);
        line_buffer_pos = strlen(line_buffer);
        remaining_space = MAX_LINE_BUFFER_LEN - line_buffer_pos;
        PRINT_DEBUG_int(remaining_space);
        PRINT_DEBUG_int(line_buffer_pos);
    }


    //Encrypt Decrypt only.
    while(only == 1 && (fgets(line_buffer, sizeof(line_buffer), stdin)) != NULL){
        ;
        //Encrypt Decrypt functions.
        if(e == 1 && d == 0)
            encrypt_line(line_buffer, key);
        else if(e == 0 && d == 1)
            decrypt_line(line_buffer, key);

        printf(line_buffer);
    }
}
