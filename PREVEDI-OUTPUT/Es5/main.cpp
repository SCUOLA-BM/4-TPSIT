#include <iostream>
using namespace std;
class Base {
public:
    Base() { cout << "B+ "; }
    virtual ~Base() { cout << "B- "; }
    virtual void f() const { cout << "Base::f "; }
    void g() const { cout << "Base::g "; f(); }
};
class Der : public Base {
public:
    Der() { cout << "D+ "; }
    ~Der() override { cout << "D- "; }
    void f() const override { cout << "Der::f "; }
    void g() const { cout << "Der::g "; f(); }
};
void perValore(Base b) { b.f(); }
void perPuntatore(const Base* p) { p->g(); }
int main() {
    {
        cout << "[1] "; Der d; cout << endl;
        cout << "[2] "; perValore(d); cout << endl;
        cout << "[3] "; perPuntatore(&d); cout << endl;
        cout << "[4] "; d.g(); cout << endl;
        cout << "[5] "; Base* p = new Der();
        p->g();
        delete p; cout << endl;
        cout << "[6] "; Base b = d;
        b.g(); cout << endl;
        cout << "[7] ";
    }
    cout << endl;
    return 0;
}
