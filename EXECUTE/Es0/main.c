#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    int status;

    printf("[Padre] PID: %d -- sto per fare fork()\n", getpid());
    fflush(stdout);

    pid = fork();

    if (pid == -1) {
        perror("Errore fork");
        exit(-1);
    }

    if (pid == 0) {
        printf("[Figlio] PID: %d -- chiamo execvp()\n", getpid());

        fflush(stdout);
        char *args[] = { "ls", "-l", "/tmp", NULL };

        execvp("ls", args);

        perror("Errore execvp");
        exit(-1);
    }

    printf("[Padre] ho creato il figlio con PID %d\n", pid);

    wait(&status);

    if (WIFEXITED(status))
        printf("[Padre] figlio terminato con codice %d\n",
               WEXITSTATUS(status));

    printf("[Padre] continuo la mia esecuzione.\n");
    return 0;
}
