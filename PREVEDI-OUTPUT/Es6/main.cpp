#include <iostream>
#include <string>
using namespace std;

class Materiale {
protected:
    string codice;
    string titolo;
    int anno;

    virtual string getDediSpecifico() const=0;
    virtual int getGiorniPrestito() const=0;
    virtual double getTariffaMora() const = 0;

public:
    Materiale(const string& c ,const string& t, int a) : codice(c), titolo(t), anno(a) {}

    virtual ~Materiale() {}

    void descrivi() const {
        cout<<"["<<codice<<"] "<<titolo<<" ("<<anno<<"), "<< getDediSpecifico() << " - prestito "<< getGiorniPrestito() <<" giorni"<<endl;
    }

    double calcolaMora(int giorniRitardo) const {
        if (giorniRitardo <= 0) return 0.0;
        return giorniRitardo * getTariffaMora();
    }
};
class Libro : public Materiale {
    int pagine;

    string getDediSpecifico() const override {
        return to_string(pagine)+ " pagine";
    }


    int getGiorniPrestito() const override {
        return 30;
    }

    double getTariffaMora() const override {
        return 0.10;
    }

public:
    Libro(const string& c ,const string& t, int a, int p) : Materiale(c,t,a), pagine(p) {}
};

class DvD : public Materiale {
    int minuti;

    string getDediSpecifico() const override {
        return to_string(minuti)+ " minuti";
    }

    int getGiorniPrestito() const override {
        return 7;
    }

    double getTariffaMora() const override {
        return 0.50;
    }
public:
    DvD(const string& c ,const string& t, int a, int m) : Materiale(c,t,a), minuti(m) {}
};

class Rivista : public Materiale {
    int numeroUscita;

    string getDediSpecifico() const override {
        return "n. "+to_string(numeroUscita);
    }

    int getGiorniPrestito() const override {
        return 14;
    }

    double getTariffaMora() const override {
        return 0.20;
    }
public:
    Rivista(const string& c ,const string& t, int a, int n) : Materiale(c,t,a), numeroUscita(n) {}
};

int main() {
    Materiale* archivio[4];

    archivio[0] = new Libro("L01", "I promessi sposi", 1827, 720);
    archivio[1] = new DvD("D01", "Il sorpasso", 1962, 105);
    archivio[2] = new Rivista("R01", "Informatica Oggi", 2026, 12);
    archivio[3] = new Libro("L02", "Il nome della Rosa", 1980, 512);

    double moraTotale = 0.0;

    for (int i = 0; i < 4; i++) {
        archivio[i]->descrivi();
        double mora = archivio[i]->calcolaMora(10);
        cout<<"Mora (10 giorni): "<<mora<<" euro"<<endl;
        moraTotale += mora;
    }

    cout<<"Totale: "<<moraTotale<<" euro"<<endl;


    for (int i = 0; i < 4; i++) {
        delete archivio[i];
    }

    return 0;
}