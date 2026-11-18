#include <stdio.h>
#include <string.h>
#include "words.h"
#include "line.h"
#include "debug_f.h"

void add_word(char line_buffer[], int line_buffer_pos, char word[]){
    if(line_buffer_pos != 0)
        strcat(line_buffer, " ");

    strcat(line_buffer, word);
    PRINT_DEBUG_LOCATION();
    PRINT_DEBUG_MSG(line_buffer);
    return;
}

void flush_line(char line_buffer[]){
    puts(line_buffer);
    return;
}

void clear_buffer(char line_buffer[], int length, int* line_buffer_pos){
    memset(line_buffer, 0, length);
    *line_buffer_pos = 0;
    return;
}

//find the number of spaces we have in a string.
int no_gaps(char line_buffer[]){
    int gaps_no = 0;
    for(int i = 0; line_buffer[i] != '\0'; i++){
        if(line_buffer[i] == ' ')
            gaps_no++;
    }
    PRINT_DEBUG_LOCATION();
    PRINT_DEBUG_int(gaps_no);
    return gaps_no;
}

//drag the string of special index one space forward.
void implement_space(char line_buffer[], int *ptr_length, int space_pos, int space_amount){
    PRINT_DEBUG_LOCATION();
    for(int i = *ptr_length; i >= space_pos; i--)
        line_buffer[i+space_amount] = line_buffer[i];

    //from space position up to space amount.
    for(int i = space_pos; i <= space_pos + space_amount; i++)
        line_buffer[i] = ' ';

    *ptr_length = strlen(line_buffer);

    PRINT_DEBUG_MSG(line_buffer);
    PRINT_DEBUG_int(*ptr_length);
    return;
}

//find the indexes of spaces inside the line buffer, store them in arr_space_index.
void find_arr_space_index(char line_buffer[], int arr_space_index[]){
    int j = 0;
    for(int i = 0; line_buffer[i] != '\0'; i++){
        if(line_buffer[i] == ' ')
            arr_space_index[j++] = i;
    }

    PRINT_DEBUG_LOCATION();
    PRINT_DEBUG_ARR_int(arr_space_index, j);
    return;
}

void justify(char line_buffer[], int length, int remaining_space){
    int gaps_no = no_gaps(line_buffer); //no of spaces inside a string.
    int each_space = remaining_space / gaps_no;//Each space how many spaces it needs;
    int additional_space = remaining_space % gaps_no;

    int arr_space_index[gaps_no];
    find_arr_space_index(line_buffer, arr_space_index);


    //The point here is like this, if we have additional spaces, we will add only extra one
    //space not more, to a limited amount of the total gaps, if have for each one
    //of them a one additional space, we wont have have from start any additional spaces to add
    //because of additional space = remaining space % gaps, so we have if additional space equal 3
    //lets say, we will add only one extra space from the gap first gap up to the third gap, which
    //is arr_space_index[0] up to arr_space_index[2].
    PRINT_DEBUG_int(each_space);
    PRINT_DEBUG_int(additional_space);

    for(int i = 0; i < gaps_no; i ++){
        if(additional_space != 0 && i < additional_space){
            implement_space(line_buffer, &length, arr_space_index[i], each_space + 1);
            for(int j = i+1; j < gaps_no; j++)
                arr_space_index[j] += each_space + 1;
            PRINT_DEBUG_int(i);
            PRINT_DEBUG_int(arr_space_index[i + 1]);
            PRINT_DEBUG_ARR_int(arr_space_index, gaps_no);
        }
        else{
            implement_space(line_buffer, &length, arr_space_index[i], each_space);
            for(int j = i+1; j < gaps_no; j++)
                arr_space_index[j] += each_space;
            PRINT_DEBUG_int(i);
            PRINT_DEBUG_int(arr_space_index[i + 1]);
            PRINT_DEBUG_ARR_int(arr_space_index, gaps_no);
        }
    }
    PRINT_DEBUG_LOCATION();
    PRINT_DEBUG_MSG(line_buffer);
    return;
}

void encrypt_line(char line_buffer[], int key){
    for(int i = 0; line_buffer[i] != '\0'; i++)
        line_buffer[i] = encrypt(line_buffer[i], key);
    PRINT_DEBUG_LOCATION();
    PRINT_DEBUG(line_buffer);
    return;
}


void decrypt_line(char line_buffer[], int key){
    for(int i = 0; line_buffer[i] != '\0'; i++)
        line_buffer[i] = decrypt(line_buffer[i], key);

    PRINT_DEBUG_LOCATION();
    PRINT_DEBUG(line_buffer);
    return;
}
