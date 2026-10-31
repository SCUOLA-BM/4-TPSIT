#include <iostream>
#include <string>
using namespace std;

class CSensore {
protected:
    string nome;
    int grezzo;

public:
    CSensore(const string& n, int g) : nome(n), grezzo(g) {}

    virtual ~CSensore() {}

    virtual double Valore() const = 0;
    virtual string Unita() const = 0;
    virtual bool Allarme() const = 0;

    string Nome() const {
        return nome;
    }
};

class CTemperatura : public CSensore {
public:
    CTemperatura(const string& n, int g) : CSensore(n, g) {}

    double Valore() const override {
        return static_cast<double>(grezzo) / 10.0;
    }

    string Unita() const override {
        return "gradi C";
    }

    bool Allarme() const override {
        return Valore() > 30.0;
    }
};

class CUmidita : public CSensore {
public:
    CUmidita(const string& n, int g) : CSensore(n, g) {}

    double Valore() const override {
        return static_cast<double>(grezzo) * 100.0 / 1023.0;
    }

    string Unita() const override {
        return "%";
    }

    bool Allarme() const override {
        return Valore() > 70.0;
    }
};

class CLuce : public CSensore {
public:
    CLuce(const string& n, int g) : CSensore(n, g) {}

    double Valore() const override {
        return static_cast<double>(grezzo);
    }

    string Unita() const override {
        return "lux";
    }

    bool Allarme() const override {
        return false;
    }
};

class CCentralina {
    CSensore* sens[10];
    int nSens;

public:
    CCentralina() : nSens(0) {
        for (int i = 0; i < 10; i++) {
            sens[i] = nullptr;
        }
    }

    bool Agg(CSensore* s) {
        if (nSens >= 10) {
            return false;
        }
        sens[nSens++] = s;
        return true;
    }

    int report() const {
        int all = 0;
        for (int i = 0; i < nSens; i++) {
            cout << sens[i]->Nome() << ": "
                 << sens[i]->Valore() << " "
                 << sens[i]->Unita();

            if (sens[i]->Allarme()) {
                cout << " <-- ALLARME";
                all++;
            }
            cout << endl;
        }
        return all;
    }
};

int main() {
    CTemperatura t1("TEMP AULA", 215);
    CTemperatura t2("TEMP SERVER", 342);
    CUmidita u1("UMIDITA' BAGNO", 818);
    CLuce l1("LUCE CORRIDIOI", 350);

    CCentralina c;
    c.Agg(&t1);
    c.Agg(&t2);
    c.Agg(&u1);
    c.Agg(&l1);

    int sensAll = c.report();
    cout << "Sensori in allarme: " << sensAll << endl;

    return 0;
}