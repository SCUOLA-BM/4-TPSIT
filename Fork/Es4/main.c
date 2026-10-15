#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    pid_t pid = fork();
    int n, tro = 0;

    if (pid < 0) {
        perror("errore fork!!");
        exit(-1);
    }

    if (pid == 0) { // Processo figlio
        printf("INSERISCI UN NUMERO: ");
        if (scanf("%d", &n) != 1) {
            exit(-1);
        }

        if (n <= 1) {
            exit(3); // Non primo
        }

        // Sostituito i <= sqrt(n) con i * i <= n (evita l'errore di linking)
        for (int i = 2; i * i <= n; i++) {
            if (n % i == 0) {
                tro = 1;
                break;
            }
        }

        if (tro == 0) {
            exit(1); // Il numero è primo
        } else if (n % 2 == 0) {
            exit(2); // Il numero è pari (e non primo)
        } else {
            exit(3); // Il numero è dispari (e non primo)
        }
    }
    else { // Processo padre
        int status;
        pid_t child_pid = wait(&status);

        if (WIFEXITED(status)) {
            int uscita = WEXITSTATUS(status);
            if (uscita == 1) {
                printf("IL NUMERO E' PRIMO\n");
            } else if (uscita == 2) {
                printf("IL NUMERO E' PARI\n");
            } else if (uscita == 3) {
                printf("IL NUMERO E' DISPARI\n");
            } else {
                perror("errore nel programma");
                exit(-1);
            }
        } else {
            perror("il figlio non e' terminato correttamente");

            exit(-1);
        }
    }
    return 0;
}