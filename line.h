#ifndef LINE_H
#define LINE_H


//Add word to line buffer, check whether word is at starting of the line.
//if no add space before the word.
void add_word(char line_buffer[], int line_buffer_pos, char word[]);

//Print the content of line buffer, without any justification.
//Flush line can be used after justifying the line buffer to print its output.
void flush_line(char line_buffer[]);

//Print the content of line buffer, with justification calculating where to put the remaining spaces.
void justify(char line_buffer[], int length, int remaining_space);

//Clear the line buffer. set it all to 0.
void clear_buffer(char line_buffer[], int length, int* line_buffer_pos);

//Encrypt the buffer line.
void encrypt_line(char line_buffer[], int key);

//Decrypt the buffer line.
void decrypt_line(char line_buffer[], int key);

#endif // LINE_H
