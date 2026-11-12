#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
        printf("[Livello 0]Il mio pid %d\n",getpid());

    for (int i = 0;i<5;i++) {
        pid_t ritorno = fork();
        if (ritorno != 0)
            break;
        printf("[Livello %d]Il mio pid %d,pid di mio padre %d\n", i+1, getpid(), getppid());
    }
    wait(NULL);
    return 0;
}
