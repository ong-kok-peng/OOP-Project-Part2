#include <iostream>
#include <string>
using namespace std;

class Base {
private:
    string a;
    int b;

public:
    Base(string a, int b) : a(validateA(a)), b(validateB(b)) {}
    string validateA(string a) {
        if (a.compare("hello") == 0) { return a; }
        else { return "NIL"; }
    }
    int validateB(int b) {
        if (b > 0 && b <= 99) { return b; }
        else { return 0; }
    }
    string getA() { return a; }
    int getB() { return b; }
};

class Child : public Base {
private:
    string c;
    int d;

public:
    Child(string a, int b, string c, int d) : Base(a, b), c(validateC(c)), d(validateD(d)) {}
    string validateC(string c) {
        if (c.compare("world") == 0) { return c; }
        else { return "NIL"; }
    }
    int validateD(int d) {
        if (d < 0 && d >= -99) { return d; }
        else { return -1; }
    }
    void printValues() {
        cout << "Attribute A is " << Base::getA() << " and attribute B is " << Base::getB() << "; ";
        cout << "Attribute C is " << c << " and attribute D is " << d << ".\n";
    }
};

int main() {
    Child child("hello", 60, "world", -45);
    child.printValues();

    Child anotherchild("hello", 100, "hello", -77);
    anotherchild.printValues();
    return 0;
}
