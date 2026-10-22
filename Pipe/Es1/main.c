#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h> //definizione tipi dato come pid_t
#include <sys/wait.h> // per funzione wait

int main(void) {

    int fd[2];
    int numeri[10] = {1,2,3,4,5,6,7,8,9,10};

    //apriamo pipe e se torna -1 è errore
    if (pipe(fd) == -1) {
        perror("pipe");
        exit(-1);
    }

    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(-2);
    }

    if (!pid) {
        close(fd[0]);
        int sp = 0;
        for (int i = 0; i<10; i++) {
            if (numeri[i] % 2 == 0) sp += numeri[i];
        }
        write(fd[1], &sp, sizeof(sp));

        close(fd[1]);
        exit(0);
    }
    wait(NULL);
    close(fd[1]);
    int sommap;
    read(fd[0], &sommap, sizeof(sommap));

    int sommad = 0;
    for (int i = 0; i<10; i++) {
        if (numeri[i] % 2 == 1) sommad += numeri[i];
    }

    close(fd[0]);

    printf("Somma numeri pari: %d\n", sommap);
    printf("Somma numeri dispari: %d\n", sommad);
    printf("Somma di tutti i numeri: %d\n", sommad+sommap);

    return 0;
}
