#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_RIGA 256
#define MAX_ARGS 10

int raccogli_terminati() {
    int raccolti = 0;
    int status;
    pid_t pid;

    while (1) {
        pid = waitpid(-1, &status, WNOHANG);

        if (pid > 0) {
            if (WIFEXITED(status))
                printf("\n[shell] figlio %d terminato con codice %d\n",
                       pid, WEXITSTATUS(status));
            else
                printf("\n[shell] figlio %d terminato in modo anomalo\n", pid);
            raccolti++;
        } else {
            break;
        }
    }

    if (raccolti > 0)
        printf("[shell] prompt: ");
    fflush(stdout);

    return raccolti;
}

int main() {
    char riga[MAX_RIGA];
    char *args[MAX_ARGS];
    char *token;
    int nargs;
    pid_t pid;
    int status;

    printf("=== MINI SHELL PARALLELA (non aspetta i figli) ===\n");
    printf("Scrivi un comando, oppure 'exit' per uscire.\n\n");

    while (1) {
        raccogli_terminati();

        printf("\nminshell> ");
        fflush(stdout);

        if (fgets(riga, MAX_RIGA, stdin) == NULL) {
            printf("\n");
            break;
        }

        riga[strcspn(riga, "\n")] = '\0';

        if (riga[0] == '\0')
            continue;

        if (strcmp(riga, "exit") == 0)
            break;

        nargs = 0;
        token = strtok(riga, " \t");
        while (token != NULL && nargs < MAX_ARGS - 1) {
            args[nargs] = token;
            nargs++;
            token = strtok(NULL, " \t");
        }
        args[nargs] = NULL;

        if (nargs == 0)
            continue;

        fflush(stdout);
        pid = fork();

        if (pid == -1) {
            perror("Errore fork");
            continue;
        }

        if (pid == 0) {
            fflush(stdout);

            execvp(args[0], args);

            perror(args[0]);
            exit(127);
        }

        printf("[shell] lanciato '%s' con PID %d (non aspetto)\n",
               riga, pid);
    }

    printf("Aspetto i figli rimasti...\n");
    while (waitpid(-1, &status, 0) > 0) {
        if (WIFEXITED(status))
            printf("[shell] figlio terminato con codice %d\n",
                   WEXITSTATUS(status));
    }

    printf("Arrivederci!\n");
    return 0;
}
