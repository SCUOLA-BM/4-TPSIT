#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    int dati[12] = {3, 7, 2, 9, 4, 6, 8, 1, 5, 10, 2, 7};
    for (int i = 0; i<3;i++) {
        pid_t pid = fork();
        if(pid == -1) {
            perror("errore nel fork");
            exit(-1);
        }
        if(pid == 0) { //processo figlio
            int somma = dati[i*4] + dati[i*4+1] + dati[i*4+2] + dati[i*4+3];
            printf("Somma parziale: %d\n", somma);
            exit(somma);
        }else {
            //Processo padre
            printf("Processo Padre\n");
            wait(NULL); //aspetta figlio
            //Prendiamo exit status
            int status;
            wait(&status);

            if (WIFEXITED(status)) {
                int exit_code = WEXITSTATUS(status);
                printf("[Padre] Il figlio %d ", exit_code);

                if (exit_code == 1) printf(" con numero dispari");
                else printf(" con numero pari");
            }
        }
    }
    return 0;
}
