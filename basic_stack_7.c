/* Epitech Security Lab
 * http://esl.epitech.net - <staff@esl.epitech.net>
 *
 * Vincent Guasconi wrote this.
 * As long as you retain this notice you can do whatever
 * you want with this stuff. If we meet some day, and you
 * think this stuff is worth it, you can buy me an absinthe in return.
 *
 */

/* It's time to prove it.
 * Learn it the easy way
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int     pouf(char *paf)
{
  char  pif[256];

  strcpy(pif, paf);
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
