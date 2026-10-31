#include <iostream>
using namespace std;
class Documento {
public:
 Documento() { cout << "Costruttore Documento" << endl; }
 virtual ~Documento() { cout << "Distruttore Documento" << endl; }
 virtual void stampa() const { cout << "Documento vuoto" << endl; }
};
class Lettera : public Documento {
 int* righe; // memoria allocata dinamicamente
public:
 Lettera() {
 righe = new int[100];
 cout << "Costruttore Lettera (alloco 100 righe)" << endl;
 }
 ~Lettera() {
 delete[] righe;
 cout << "Distruttore Lettera (libero 100 righe)" << endl;
 }
 void stampa() const override { cout << "Gentile cliente, ..." << endl; } };
int main() {
 Documento* d = new Lettera();
 d->stampa();
 delete d;
 return 0;
}
