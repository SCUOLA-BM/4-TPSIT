```mermaid
classDiagram
    class Sensore {
        # string nome
        # int grezzo
        + Sensore(string, int)
        + virtual ~Sensore()
        + virtual double getValore() const*
        + virtual string getUnita() const*
        + virtual bool inAllarme() const*
        + string getNome() const
    }

    class Temperatura {
        + Temperatura(string, int)
        + double getValore() const override
        + string getUnita() const override
        + bool inAllarme() const override
    }

    class Umidita {
        + Umidita(string, int)
        + double getValore() const override
        + string getUnita() const override
        + bool inAllarme() const override
    }

    class Luce {
        + Luce(string, int)
        + double getValore() const override
        + string getUnita() const override
        + bool inAllarme() const override
    }
    
    class Centralina {
        - Sensore* sensori[10]
        - int nSensori
        + Centralina()
        + bool aggiungi(Sensore* s)
        + int report() const
    }

%%RELAZIONI

    Sensore <|-- Temperatura
    Sensore <|-- Umidita
    Sensore <|-- Luce
    Centralina o-- Sensore : gestisce (0..10)

```mermaid