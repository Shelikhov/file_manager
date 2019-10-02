#include "header.h"

int piddd(void){



        pid_t pid = fork();
        int  Stat;
        if (pid == 0){
                execl("/C/test/test2/editor","editor","file.txt", NULL);
                exit(0);
        }
        waitpid(pid, &Stat, 0);

        return Stat;
}
