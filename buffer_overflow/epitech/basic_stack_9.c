/* YOU CAN REALLY SMASH THE STACK
 * SMASH IT, if it succeed, it doesn't matter
 *
 * The same as above, but try to exploit it from env,
 * with a template like : http://xx
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int     pouf(char *paf)
{
  char  pif[16];

  strncpy(pif, paf, 24);
  return 0;
}

int     main(int argc, char **argv, char **environ)
{
  if (argc != 2)
    {
      printf("[-] I need args\n");
      return 1;
    }
  return (pouf(argv[1]));
}