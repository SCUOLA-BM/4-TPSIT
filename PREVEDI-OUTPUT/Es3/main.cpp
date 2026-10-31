#include <iostream>
#include <string>
using namespace std;
class Dipendente {
protected:
    string nome;
public:
    Dipendente(const string& n) : nome(n) {}
    ~Dipendente() {}
    double stipendio() const { return 1200.0; }
    void scheda() const {
        cout << nome << ": " << stipendio() << " euro" << endl;
    }
};
class Programmatore : public Dipendente {
    int progetti;
public:
    Programmatore(const string& n, int p) : Dipendente(n), progetti(p) {}  double stipendio() const { return 1500.0 + 100.0 * progetti; } };
class Responsabile : public Dipendente {
    int collaboratori;
public:
    Responsabile(const string& n, int c) : Dipendente(n), collaboratori(c) {}  double stipendio() const { return 2000.0 + 50.0 * collaboratori; } };

int main() {
    Dipendente* staff[4];

    staff[0] = new Dipendente("Rossi");
    staff[1] = new Programmatore("Bianchi",3);
    staff[2] = new Responsabile("Verdi",6);
    staff[3] = new Programmatore("Neri",1);

    double totale = 0.0;
    for (int i = 0; i < 4; i++) {
        staff[i]->scheda();
        totale += staff[i]->stipendio();
    }

    cout << "Totale: "<< totale << "euro"<< endl;

    Dipendente copie[2] = {
        Programmatore("Bianchi", 3),
        Responsabile("Verdi", 6)
    };

    for (int i = 0; i < 2; i++)
        copie[i].scheda();


    for (int i = 0; i < 4; i++) {
        delete staff[i];
    }
    return 0;
}
