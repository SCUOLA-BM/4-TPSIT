#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    pid_t pid = fork();

    if (pid <0) {
        perror("errore fork");
        exit(-1);
    }
    if (!pid) {
        pid_t pid1 = fork();
        if (pid1 <0) {
            perror("errore fork");
            exit(-1);
        }
        if (!pid1) {
            printf("PROCESSO FIGLIO( PID : %d)\n", getpid());
            exit(1);
        }
        wait(NULL);
        printf("PROCESSO PADRE( PID : %d)\n", getpid());
        exit(1);
    }
    wait(NULL);
    printf("PROCESSO NONNO( PID : %d)\n", getpid());
    return 0;
}
