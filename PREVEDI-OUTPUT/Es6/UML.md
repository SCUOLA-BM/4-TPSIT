```mermaid
classDiagram
    class Materiale {
        # string codice
        # string titolo
        # int anno
        + Materiale(string, string, int)
        + virtual ~Materiale()
        + void descrivi() const
        + double calcolaMora(int) const
        # string getDediSpecifico() const*
        # int getGiorniPrestito() const*
        # double getTariffaMora() const*
    }

    class Libro {
        - int pagine
        + Libro(string, string, int, int)
        # string getDediSpecifico() const
        # int getGiorniPrestito() const
        # double getTariffaMora() const
    }

    class Dvd {
        - int minuti
        + Dvd(string, string, int, int)
        # string getDediSpecifico() const
        # int getGiorniPrestito() const
        # double getTariffaMora() const
    }

    class Rivista {
        - int numeroUscita
        + Rivista(string, string, int, int)
        # string getDediSpecifico() const
        # int getGiorniPrestito() const
        # double getTariffaMora() const
    }

%%RELAZIONI

    Materiale <|-- Libro
    Materiale <|-- Dvd
    Materiale <|-- Rivista


```mermaid