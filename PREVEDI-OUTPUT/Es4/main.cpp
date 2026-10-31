#include <iostream>
#include <string>
using namespace std;
class Strumento {
public:
    string nome() const { return "strumento"; }
    virtual string suono() const { return "..."; }
    virtual int corde() const { return 0; }
    void presentati() const {
        cout << nome() << " fa " << suono()
        << " con " << corde() << " corde" << endl;
    }
};
class Chitarra : public Strumento {
public:
    string nome() const { return "chitarra"; }
    string suono() const override { return "dlin"; }
    int corde() const override { return 6; }
};
class ChitarraElettrica : public Chitarra {
public:
    string nome() const { return "chitarra elettrica"; }
    string suono() const override { return "dzzz"; }
    // corde() non viene ridefinito
};
int main() {
    ChitarraElettrica e;
    Chitarra c;
    Strumento* s = &e;
    s->presentati(); // (1)
    Chitarra* pc = &e;
    cout << pc->nome() << endl; // (2)
    cout << pc->suono() << endl; // (3)
    Strumento& r = c;
    r.presentati(); // (4)
    Strumento copia = e;
    copia.presentati(); // (5)
    e.presentati(); // (6)
    cout << e.nome() << endl; // (7)
    return 0;
}
