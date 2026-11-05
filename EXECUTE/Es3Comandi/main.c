#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


void lancia_comando(char *argv[]) {
    pid_t pid;
    int status;

    fflush(stdout);

    pid = fork();

    if (pid == -1) {
        perror("Errore fork");
        exit(-1);
    }

    if (pid == 0) {
        printf("[Figlio] PID: %d -- eseguo '%s'\n", getpid(), argv[0]);
        fflush(stdout);

        execvp(argv[0], argv);
        perror("Errore execvp");
        exit(-1);
    }

    printf("[Padre] ho creato il figlio con PID %d\n", pid);
    fflush(stdout);

    wait(&status);

    if (WIFEXITED(status))
        printf("[Padre] il figlio e' terminato con codice %d\n\n",
               WEXITSTATUS(status));
    else
        printf("[Padre] il figlio e' terminato in modo anomalo\n\n");
}

int main(int argc, char *argv[]) {
    int scelta;

    char *cmd_date[] = { "date", NULL };

    char *cmd_echo[] = { "echo", "ciao", "dal", "figlio", NULL };

    char *cmd_cat[] = { "cat", "/etc/hostname", NULL };

    if (argc < 2) {
        scelta = 0;
    } else {
        scelta = atoi(argv[1]);
        if (scelta < 1 || scelta > 3) {
            printf("Uso: %s [1|2|3]\n", argv[0]);
            printf("  1 = date\n");
            printf("  2 = echo ciao dal figlio\n");
            printf("  3 = cat /etc/hostname\n");
            return 1;
        }
    }

    printf("=== ESERCIZIO A: fork + execvp ===\n\n");

    if (scelta == 0 || scelta == 1) {
        printf("--- comando 1: date ---\n");
        lancia_comando(cmd_date);
    }

    if (scelta == 0 || scelta == 2) {
        printf("--- comando 2: echo ciao dal figlio ---\n");
        lancia_comando(cmd_echo);
    }

    if (scelta == 0 || scelta == 3) {
        printf("--- comando 3: cat /etc/hostname ---\n");
        lancia_comando(cmd_cat);
    }

    printf("[Padre] tutti i figli sono terminati, continuo la mia esecuzione.\n");
    return 0;
}

