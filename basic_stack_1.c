/* Epitech Security Lab
 * http://esl.epitech.net - <staff@esl.epitech.net>
 *
 * Vincent Guasconi wrote this.
 * As long as you retain this notice you can do whatever
 * you want with this stuff. If we meet some day, and you
 * think this stuff is worth it, you can buy me an absinthe in return.
 *
 */

/* > ./basic_stack_1 `perl -e 'print "A"x256'`"9"
 * [-] buffy has been killed by 9 vampires... :(
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

int     main(int argc, char **argv, char **environ)
{
  char  vampires = '3';
  char  buffy[256];

  memset(buffy, '\0', 256);
  if (argc != 2)
    {
      printf("[-] I need args\n");
      return 1;
    }
  memcpy(buffy, argv[1], strlen(argv[1]));
  if (vampires == '0')
    {
      printf("[+] buffy killed the vampires!\n");
      (void) i_ve_done_it();
    }
  printf("[-] buffy has been killed by %c vampires... :(\n", vampires);
  return 0;
}
