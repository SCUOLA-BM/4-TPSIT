#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>

#define PATH_NAME1 "/tmp/fifo_ping"
#define PATH_NAME2 "/tmp/fifo_pong"
#define BUFFER_SIZE 256

int main(void) {
    signal(SIGINT, SIG_IGN);

    if (mkfifo(PATH_NAME1, 0666) == -1) {
        if (errno != EEXIST) {
            perror("[PING1] Errore mkfifo: ");
            exit(EXIT_FAILURE);
        }
        printf("[PING1] FIFO già presente, nessun errore\n");
    }

    if (mkfifo(PATH_NAME2, 0666) == -1) {
        if (errno != EEXIST) {
            perror("[PING2] Errore mkfifo: ");
            exit(EXIT_FAILURE);
        }
        printf("[PING2] FIFO già esistente, nessun errore\n");
    }

    printf("Entrambe le fifo sono pronte\n");
    fflush(stdout);

    int fdwrite = open(PATH_NAME1, O_WRONLY);

    if (fdwrite == -1) {
        perror("[PING1] Errore open: ");
        exit(EXIT_FAILURE);
    }

    char *invio = "PING";

    write(fdwrite, invio, strlen(invio)+1);

    close(fdwrite);
    printf("[PING1] Messaggio inviato. Canale chiuso\n");

    //2nd operazione di scambio

    int fdread = open(PATH_NAME2, O_RDONLY);
    if (fdread == -1) {
        perror("[PING2] Errore open: ");
        exit(EXIT_FAILURE);
    }

    char buffer[BUFFER_SIZE];

    ssize_t n = read(fdread, buffer, sizeof(buffer));

    if (n>0) printf("[PING2] Messaggio ricevuto con successo : %s\n", buffer);
    else if (n == 0) printf("[PING2] Messaggio ricevuto, ma vuoto\n");
    else perror("[PING2] Errore read: ");

    close(fdread);
    if (unlink(PATH_NAME2) == -1) {
        perror("[PING2] Errore unlink: ");
    }
    else {
        printf("[PING2] FIFO2 rimossa dal filesystem\n");
    }

    return 0;
}
