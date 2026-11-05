#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_RIGA 256
#define MAX_ARGS 10

int main() {
    char riga[MAX_RIGA];
    char *args[MAX_ARGS];
    char *token;
    int nargs;
    pid_t pid;
    int status;

    printf("=== MINI SHELL (fork + execvp) ===\n");
    printf("Scrivi un comando, oppure 'exit' per uscire.\n\n");

    while (1) {
        printf("minshell> ");
        fflush(stdout);

        if (fgets(riga, MAX_RIGA, stdin) == NULL) {
            printf("\n");
            break;
        }

        riga[strcspn(riga, "\n")] = '\0';

        if (riga[0] == '\0')
            continue;

        if (strcmp(riga, "exit") == 0) {
            printf("Uscita dalla mini shell.\n");
            break;
        }

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

        wait(&status);

        if (WIFEXITED(status)) {
            if (WEXITSTATUS(status) == 127)
                printf("[shell] comando non trovato: %s\n", riga);
            else
                printf("[shell] '%s' terminato con codice %d\n",
                       riga, WEXITSTATUS(status));
        } else {
            printf("[shell] '%s' terminato in modo anomalo\n", riga);
        }

        printf("\n");
    }

    printf("Arrivederci!\n");
    return 0;
}

