#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int fd[2];
    pid_t pid1, pid2;
    int status1, status2;

    if (pipe(fd) == -1) {
        perror("Errore pipe");
        exit(-1);
    }

    printf("[Padre] pipe creata (lettura fd=%d, scrittura fd=%d)\n",
           fd[0], fd[1]);
    fflush(stdout);

    pid1 = fork();

    if (pid1 == -1) {
        perror("Errore fork (figlio 1)");
        exit(-1);
    }

    if (pid1 == 0) {
        char *args[] = { "ls", "/tmp", NULL };

        close(fd[0]);

        if (dup2(fd[1], STDOUT_FILENO) == -1) {
            perror("Errore dup2 (figlio 1)");
            exit(-1);
        }
        close(fd[1]);

        execvp("ls", args);

        perror("Errore execvp ls");
        exit(-1);
    }

    pid2 = fork();

    if (pid2 == -1) {
        perror("Errore fork (figlio 2)");
        close(fd[0]);
        close(fd[1]);
        wait(&status1);
        exit(-1);
    }

    if (pid2 == 0) {
        char *args[] = { "wc", "-l", NULL };

        close(fd[1]);

        if (dup2(fd[0], STDIN_FILENO) == -1) {
            perror("Errore dup2 (figlio 2)");
            exit(-1);
        }
        close(fd[0]);

        execvp("wc", args);

        perror("Errore execvp wc");
        exit(-1);
    }

    close(fd[0]);
    close(fd[1]);

    printf("[Padre] lanciati: ls (PID %d) | wc -l (PID %d)\n",
           pid1, pid2);
    fflush(stdout);

    wait(&status1);
    wait(&status2);

    if (WIFEXITED(status1)) {
        printf("[Padre] primo comando terminato con codice %d\n",
               WEXITSTATUS(status1));
    }
    if (WIFEXITED(status2)) {
        printf("[Padre] secondo comando terminato con codice %d\n",
               WEXITSTATUS(status2));
    }
    fflush(stdout);

    printf("[Padre] pipe chiusa, fine.\n");
    return 0;
}

