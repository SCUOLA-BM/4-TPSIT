#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>

#define PATH_NAME1 "/tmp/fifo_ping"
#define PATH_NAME2 "/tmp/fifo_pong"
#define BUFFER_SIZE 256

int main(void) {
    signal(SIGINT, SIG_IGN);

    int fdread = open(PATH_NAME1, O_RDONLY);
    printf("[PONG1] Comunicazione aperta\n");
    fflush(stdout);

    if (fdread == -1) {
        perror("[PONG1] Errore open: ");
        exit(EXIT_FAILURE);
    }

    char buffer[BUFFER_SIZE];

    ssize_t n = read(fdread, buffer, BUFFER_SIZE);
    if (n>0) printf("[PONG1] Messaggio ricevuto con successo : %s\n", buffer);
    else if (n == 0) printf("[PONG1] Messaggio ricevuto, ma vuoto\n");
    else perror("[PONG1] Errore read: ");
    close(fdread);

    if (unlink(PATH_NAME1) == -1) {
        perror("[PONG1] Errore unlink: ");
    }
    else {
        printf("[PONG1] FIFO1 rimossa dal filesystem\n");
    }

    int fdwrite = open(PATH_NAME2, O_WRONLY);

    if (fdwrite == -1) {
        perror("[PONG2] Errore open: ");
        exit(EXIT_FAILURE);
    }

    char *message = "PONG";
    write(fdwrite, message, strlen(message));
    close(fdwrite);
    printf("[PONG2] Messaggio inviato. Canale chiuso\n");



}