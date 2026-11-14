#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //per write() e close
#include <sys/wait.h>
#include <sys/stat.h> // per makefifo()
#include <string.h> //per strlen(), lunghezzo del puntatore ad una stringa
#include <fcntl.h> // per open() e WRONLY

#define FIFO_PATH "/tmp/mia_fifo"
#define BUF_SIZE 256 //spazio dedicato alla comunicazione

int main(void) {

    printf("[Reader] Attendo un writer...\n");
    fflush(stdout);

    int fd = open(FIFO_PATH, O_RDONLY); //O_ == aspetta il writer
    if (fd == -1) {
        perror("Errore open reader");
        exit(EXIT_FAILURE);
    }
    printf("[READER] Writer connesso. Lettura in corso...\n");

    char buf[BUF_SIZE];

    ssize_t n = read(fd, buf, BUF_SIZE-1);

    if (n>0) {
        buf[n] = '\0';
        printf("[READER] Ricevuto: %s\n",buf);
    }else if (n == 0) printf("[READER] Il writer ha chiuso senza inviare dati.\n");
    else perror("Errore read");

    close(fd);

    if (unlink(FIFO_PATH) == -1) perror("Errore unlink");
    else printf("[READER] FIFO rimossa dal fylesystem\n");

    return 0;
}
