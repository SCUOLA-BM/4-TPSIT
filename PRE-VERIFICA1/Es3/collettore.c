#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define FIFO_PATH "/tmp/fifo_pari"

int main(void) {
    printf("[Collettore] In attesa di dati...\n");

    // Apre la FIFO in lettura (si blocca finche' il filtro non apre la FIFO in scrittura)
    int fifo_fd = open(FIFO_PATH, O_RDONLY);
    if (fifo_fd == -1) {
        perror("Errore apertura FIFO in lettura");
        exit(1);
    }

    int num;
    int conteggio = 0;
    int somma = 0;

    while (read(fifo_fd, &num, sizeof(int)) > 0) {
        // Controllo della sentinella di fine trasmissione
        if (num == -1) {
            break;
        }

        printf("[Collettore] Ricevuto: %d\n", num);
        conteggio++;
        somma += num;
    }

    close(fifo_fd);

    // Rimozione della named pipe dal file system
    unlink(FIFO_PATH);

    printf("[Collettore] Fine. Numeri pari ricevuti: %d, somma: %d\n", conteggio, somma);

    return 0;
}
