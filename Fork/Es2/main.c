#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int main(void) {
    pid_t pid;
    int i;
    int nfigli = 3;

    printf("PADRE (PID: %d): inizio generazione di %d figli...\n", getpid(), nfigli);

    for (i = 1; i<=nfigli; i++) {
        pid = fork();
        if (pid <0) {
            perror("fork error");
            exit(-1);
        }
        else if (!pid) {
            printf("Figlio %d (PID: %d) avviato.\n", i, getpid());

            sleep(2);

            printf("Figlio %d (PID: %d) terminato.\n", i, getpid());

            exit(1);
        }
        sleep(3);
    }

    printf("Padre: in attesa che tutti i figli terminino...\n");

    for (i = 0; i<nfigli; i++) {
        wait(NULL);
    }

    printf("Padre (PID: %d): tutti i figli hanno completato l'esecuzione. Fine programma.\n)", getpid());

    return 0;
}
