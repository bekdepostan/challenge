/* Epitech Security Lab
 * http://esl.epitech.net - <staff@esl.epitech.net>
 *
 * Vincent Guasconi wrote this.
 * As long as you retain this notice you can do whatever
 * you want with this stuff. If we meet some day, and you
 * think this stuff is worth it, you can buy me an absinthe in return.
 *
 */

/* > ./basic_stack_2 `perl -e 'print "A"x256; print "\xff\xff\xff\xff"'`
 * [-] There's 4294967295 vampires with spike, t's not fun...
 * >
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void            i_ve_done_it(void)
{
  extern char   **environ;
  char          arg[] = "/bin/sh";
  char          *args[] = {
    arg,
    (char *)0
  };

  if (!(setreuid(geteuid(), getegid()) + 1))
    perror("[-] setreuid");
  execve(arg, args, environ);
  perror("[-] evecve");
  (void) exit(1);
  return ;
}

int             main(int argc, char **argv, char **environ)
{
  unsigned int  vampires = 3;
  char          spike[256];

  memset(spike, '\0', 256);
  if (argc != 2)
    {
      printf("[-] I need args\n");
      return 1;
    }
  memcpy(spike, argv[1], strlen(argv[1]));
  if (vampires == 666)
    {
      printf("[+] spike likes it like that!\n");
      (void) i_ve_done_it();
    }
	 printf("[-] There's %u vampires with spike, t's not fun...\n", vampires);
  return 0;
}

