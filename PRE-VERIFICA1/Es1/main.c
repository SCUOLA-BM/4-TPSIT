#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    printf("[Padre] Creo 3 figli...\n");
    int dati[12] = {3, 7, 2, 9, 4, 6, 8, 1, 5, 10, 2, 7};
    pid_t pid[3];

    for (int i = 0; i<3;i++) {
        pid[i] = fork();
        if(pid[i] == -1) {
            perror("errore nel fork");
            exit(-1);
        }
        if(pid[i] == 0) { //processo figlio
            int somma = dati[i*4] + dati[i*4+1] + dati[i*4+2] + dati[i*4+3];
            printf("[Figlio %d, PID %d] somma parziale: %d\n", i+1,getpid(),somma);
            exit(somma);
        }
    }
    int status;
    int ris;
    int somma = 0;
    for (int i = 0; i<3; i++) {
        waitpid(pid[i], &status, 0);
        if (WIFEXITED(status)) {
            ris = WEXITSTATUS(status);
            printf("[Padre] Figlio %d terminato con codice %d\n",getpid(),ris);
            somma += ris;
        }
    }
    printf("[Padre] Somma totale :%d \n", somma);
    return 0;
}
