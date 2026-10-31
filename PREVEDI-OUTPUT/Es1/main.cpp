#include <iostream>
using namespace std;
class Veicolo {
public:
    void descrivi() const { cout << "Veicolo generico" << endl; }
    virtual void suono() const { cout << "..." << endl; }
};
class Auto : public Veicolo {
public:
    void descrivi() const { cout << "Automobile" << endl; }
    void suono() const override { cout << "Beep beep" << endl; }
};
class Moto : public Veicolo {
public:
    void descrivi() const { cout << "Motocicletta" << endl; }
    void suono() const override { cout << "Vroom" << endl; }
};
void presenta(Veicolo v) {
    v.descrivi();
    v.suono();
}
void presentaRif(const Veicolo& v) {
    v.descrivi();
    v.suono();
}
int main() {
    Auto a;
    Moto m;
    Veicolo* p = &a; // riga A
    p->descrivi(); // (1)
    p->suono(); // (2)
    p = &m; // riga B
    p->descrivi(); // (3)
    p->suono(); // (4)
    presenta(m); // (5) e (6)
    presentaRif(m); // (7) e (8)
    a.descrivi(); // (9)
    return 0;
}
