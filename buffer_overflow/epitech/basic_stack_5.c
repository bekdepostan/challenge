/* Epitech Security Lab
 * http://esl.epitech.net - <staff@esl.epitech.net>
 *
 * Vincent Guasconi wrote this.
 * As long as you retain this notice you can do whatever
 * you want with this stuff. If we meet some day, and you
 * think this stuff is worth it, you can buy me an absinthe in return.
 *
 */

/* code me a beautiful 'exploit.c', and a usefull exec*. fix the size
 * of your env and your argv, or your stack will never have the same
 * address in main.
 *
 * it's time to learn to use objdump/nm/ldd/gdb in order to get the
 * addr/offset by yourself.
 *
 * don't forget that everything's in hex :)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void            impossible_to_access(void)
{
  extern char   **environ;
  char          arg[] = "/bin/sh";
  char          *args[] = {
    arg,
    (char *)0
  };

  printf("[+] AFS is unbreakable, unless you used it like a noob\n");
  if (!(setreuid(geteuid(), getegid()) + 1))
    perror("[-] setreuid");
  execve(arg, args, environ);
  perror("[-] evecve");
  (void) exit(1);
  return ;
}

int     you_can_do_it(char *dick)
{
  char  ass[256];

  printf("[+] last time I do it : 0x%08x\n", ass);
  memcpy(ass, dick, strlen(dick));
  return 0;
}

int             main(int argc, char **argv, char **environ)
{
  if (argc != 2)
    {
      printf("[-] I need args\n");
      return 1;
    }
  return (you_can_do_it(argv[1]));
}


