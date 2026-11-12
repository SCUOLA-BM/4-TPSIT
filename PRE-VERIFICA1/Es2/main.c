#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {

    int n = 0;
    do {
        printf("\nQuanti numeri?");
        scanf("%d",&n);
    }while (n<=0);
    int fd[2];
    int fd1[2];

    if (pipe(fd) == -1 || pipe(fd1) == -1) {
        perror("\nErrore creazione pipe");
        exit(-1);
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("\nErrore");
        exit(-1);
    }
    if (pid == 0) { //processo padre

        int num[n];

        read(fd[0], num, sizeof(num));
        close(fd[0]);
        printf("\n[Figlio]Ricevuti %d numeri, calcolo...", n);
        int s = num[0];
        int min = num[0];
        int max = num[0];
        for (int i = 1; i < n; i++) {
            s+= num[i];
            if (num[i] < min) min = num[i];
            else if (num[i] > max) max = num[i];
        }
        int ris[3] = {s, min, max};

        write(fd1[1], ris, sizeof(ris));
        close(fd1[1]);

    }
    else //processo padre
    {

        int num[n];

        for (int j = 0; j <n; j++) {
            printf("\nNumero %d: ", j+1);
            scanf("%d",&num[j]);
        }

        printf("\n[Padre]Invio %d numeri al figlio...", n);

        write(fd[1], num, sizeof(num));
        close(fd[1]);

        wait(NULL);

        int ris[3];

        read(fd1[0], ris, sizeof(ris));
        close(fd1[0]);

        printf("\n[Padre] Somma: %d Minimo: %d Massimo: %d",ris[0], ris[1], ris[2]);

    }






    return 0;
}
