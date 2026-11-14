#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>

#define PATH_FIFO "/tmp/fifo_test"

int main(void) {
    if (mkfifo(PATH_FIFO, 0666) == -1) {
        if (errno != EEXIST) { //variabile globale errno impostata dal kernel quando qualcosa fallisce
            perror("[FIFO] error: ");//stampa la stringa, poi messaggio di errore
            exit(EXIT_FAILURE);
        }
        printf("FIFO già presente, nessun errore\n");
    }
    printf("PERCORSO FIFO : %s", PATH_FIFO);
    sleep(30);
    unlink(PATH_FIFO);
    return 0;
}
