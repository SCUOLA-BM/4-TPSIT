#include <stdio.h>
#include <stdlib.h>

int main(void) {

    int fd[2];
    if (pipe(fd)== -1) {
        perror("errore pipe");
        exit(-1);
    }

    pid_t ritorno = fork();
    if (ritorno == -1) {
        perror("errore fork");
    }

    if (ritorno == 0) {
        //processo figlio
        int array[5] = {1, 2, 3, 4, 5};
        write(fd[1], array, sizeof(array));
    }else {
        int arrayRicevuto[5];
        read(fd[0], &arrayRicevuto, sizeof(arrayRicevuto)/sizeof(arrayRicevuto[0]));

        for (int i = 0; i < 5; i++) {
            printf("array[%d] = %d\n", i, arrayRicevuto[i]);
        }
    }
    return 0;
}
