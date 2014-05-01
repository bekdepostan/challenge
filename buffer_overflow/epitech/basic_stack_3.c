/* tcsh is unable to parse something like : "` '"" ""'`"
 * If your adress contain a \x20 (space) or a tab, a htab (\x09), etc.
 * -> your shell will split your payload in two arguments, so try to use
 * sh or bash if you've got problems. In case it doesn't works, code
 * an 'exploit.c' who forge the string, and do directly an execve with it.
 *
 * And if you have a null byte, good luck to pass it through argv or env :).
 *
 * $ ./basic_stack_3 "`perl -e 'print "A"x256 ; print "\xff\xff\xff\xff"'`"
 * [+] The function `overflow_the_jew` is at 0x08048620
 * Segmentation fault
 * $
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void            overflow_kenny(void)
{
  extern char   **environ;
  char          arg[] = "/bin/sh";
  char          *args[] = {
    arg,
    (char *)0
  };

  printf("[+] Cartman make fun of Kenny...\n");
  if (!(setreuid(geteuid(), getegid()) + 1))
    perror("[-] setreuid");
  execve(arg, args, environ);
  perror("[-] evecve");
  (void) exit(1);
  return ;
}

void            je_vous_emmerde(void)
{
  printf("[-] et je rentre a ma maison\n");
  (void) exit(1);
  return ;
}

int             main(int argc, char **argv, char **environ)

{
  void  (*kenny)(void) = je_vous_emmerde;
  char  cartman[256];

  printf("[+] The function `overflow_kenny` is at 0x%08x\n", (void *)overflow_kenny);
  memset(cartman, '\0', 256);
  if (argc != 2)
    {
      printf("[-] I need args\n");
      return 1;
    }
  memcpy(cartman, argv[1], strlen(argv[1]));
  (void) kenny();
  return 0;
}

