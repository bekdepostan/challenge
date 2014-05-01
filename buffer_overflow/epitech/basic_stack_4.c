/* Epitech Security Lab
 * http://esl.epitech.net - <staff@esl.epitech.net>
 *
 * Vincent Guasconi wrote this.
 * As long as you retain this notice you can do whatever
 * you want with this stuff. If we meet some day, and you
 * think this stuff is worth it, you can buy me an absinthe in return.
 *
 */

/* calling convention guys
 *
 * Sometimes gcc align buffers, don't forget to verify if you
 * have problems in your offsets.
 *
 * In order to have the same value in your stack, call the vuln
 * setuid with execve() AND a const **env size AND
 * const **args size.
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

int     a_freebsd(char *something)
{
  char  someone[253];

  memcpy(someone, something, strlen(something));
  printf("[+] $ebp of main contain 0x%08x\n", *((void **)(someone + 253)));
  printf("[+] when I return to main(), I'll go to 0x%08x\n",
         *((void **)(someone + 253 + 4)));
  return 0;
}

int             main(int argc, char **argv, char **environ)
{
  printf("[+] impossible_to_access is at 0x%08x\n", (void *)impossible_to_access);
  if (argc != 2)
    {
      printf("[-] I need args\n");
      return 1;
    }
  return (a_freebsd(argv[1]));
}
