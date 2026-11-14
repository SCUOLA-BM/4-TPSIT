#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //per write() e close
#include <sys/wait.h>
#include <sys/stat.h> // per makefifo()
#include <string.h> //per strlen(), lunghezzo del puntatore ad una stringa
#include <errno.h>
#include <fcntl.h> // per open() e WRONLY

#define FIFO_PATH "/tmp/mia_fifo"

int main(void) {

    if (mkfifo(FIFO_PATH, 0666) == -1) {
        if (errno != EEXIST) {
            perror("[MKFIFO] Errore :");
            exit(EXIT_FAILURE);
        }
        printf("Fifo già esistenet, nessun errore\n");
    }

    printf("[Writer] FIFO pronta. Attendo un reader...\n");

    int fd = open(FIFO_PATH, O_WRONLY); //continua codice solo quando si è aperta la comunicazione
    if (fd == -1) {
        perror("[OPEN] Errore : ");
        exit(EXIT_FAILURE);
    }

    printf("[WRITER] Reader connesso. Invio messaggio...\n");

    const char *msg="Ciao dal processo Writer";
    write(fd, msg, strlen(msg)); //continua quando il reader ha letto
    close(fd);

    printf("[WRITER] Messagio inviato. Canale chiuso.\n");
    return 0;
}
