/* Epitech Security Lab
 * http://esl.epitech.net - <staff@esl.epitech.net>
 *
 * Vincent Guasconi wrote this.
 * As long as you retain this notice you can do whatever
 * you want with this stuff. If we meet some day, and you
 * think this stuff is worth it, you can buy me an absinthe in return.
 *
 */

/* code your exploit.c with a shellcode :)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int     main(int argc, char **argv, char **environ)
{
  if (argc != 2)
    {
      printf("[-] I need args\n");
      return 1;
    }
  (void) ((void (*)(void))argv[1])();
  return 1;
