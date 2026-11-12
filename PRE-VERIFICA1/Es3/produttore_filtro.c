#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

#define FIFO_PATH "/tmp/fifo_pari"

int main(void) {
    int pipefd[2];

    // 1. Creazione della pipe anonima
    if (pipe(pipefd) == -1) {
        perror("Errore creazione pipe anonima");
        exit(1);
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("Errore fork");
        exit(1);
    }

    if (pid == 0) { // --- PROCESSO FIGLIO (Generatore) ---
        close(pipefd[0]); // Il figlio scrive soltanto, chiude la lettura

        srand(time(NULL) ^ getpid());

        printf("[Generatore] Genero 20 numeri casuali...\n");
        for (int i = 0; i < 20; i++) {
            int num = (rand() % 100) + 1; // Numeri tra 1 e 100
            write(pipefd[1], &num, sizeof(int));
        }

        close(pipefd[1]); // Fine scrittura
        exit(0);
    }
    else { // --- PROCESSO PADRE (Filtro) ---
        close(pipefd[1]); // Il padre legge soltanto dalla pipe anonima, chiude la scrittura

        // Creazione della Named Pipe (FIFO)
        // Se esiste gia' la rimuoviamo per sicurezza
        unlink(FIFO_PATH);
        if (mkfifo(FIFO_PATH, 0666) == -1) {
            perror("Errore creazione mkfifo");
            exit(1);
        }

        printf("[Filtro] In attesa di connessione sulla FIFO...\n");
        int fifo_fd = open(FIFO_PATH, O_WRONLY);
        if (fifo_fd == -1) {
            perror("Errore apertura FIFO in scrittura");
            exit(1);
        }

        printf("[Filtro] Connesso. Filtro i numeri pari...\n");

        int num;
        while (read(pipefd[0], &num, sizeof(int)) > 0) {
            if (num % 2 == 0) {
                // Il numero e' pari, lo invio al collettore via FIFO
                write(fifo_fd, &num, sizeof(int));
            }
        }

        close(pipefd[0]);

        // Invio del valore sentinella -1 alla fine
        int sentinella = -1;
        write(fifo_fd, &sentinella, sizeof(int));
        close(fifo_fd);

        // Aspetta che il figlio termini
        wait(NULL);
        printf("[Filtro] Elaborazione completata.\n");
    }

    return 0;
}
