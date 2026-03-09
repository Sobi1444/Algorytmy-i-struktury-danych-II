#include <iostream>
#include <unordered_set>
using namespace std;

class Zbior {
private:
    unordered_set<int> dane;

public:
    bool pusty() { return dane.empty(); }
    int rozmiar() { return dane.size(); }
    void dodaj(int x) { dane.insert(x); }
    void usun(int x) { dane.erase(x); }
    bool zawiera(int x) { return dane.count(x) > 0; }
    void wyczysc() { dane.clear(); }

    Zbior suma(Zbior& inny) {
        Zbior wynik = *this;
        for (int x : inny.dane) wynik.dodaj(x);
        return wynik;
    }

    Zbior czescWspolna(Zbior& inny) {
        Zbior wynik;
        for (int x : dane)
            if (inny.zawiera(x)) wynik.dodaj(x);
        return wynik;
    }

    Zbior roznica(Zbior& inny) {
        Zbior wynik;
        for (int x : dane)
            if (!inny.zawiera(x)) wynik.dodaj(x);
        return wynik;
    }

    bool podzbior(Zbior& inny) {
        for (int x : dane)
            if (!inny.zawiera(x)) return false;
        return true;
    }

    void wypisz() {
        cout << "{ ";
        for (int x : dane) cout << x << " ";
        cout << "}" << endl;
    }
};

int main() {
    Zbior A, B;

    A.dodaj(1); A.dodaj(2); A.dodaj(3); A.dodaj(4);
    B.dodaj(3); B.dodaj(4); B.dodaj(5); B.dodaj(6);

    cout << "A = "; A.wypisz();
    cout << "B = "; B.wypisz();

    Zbior s = A.suma(B);
    cout << "A u B = "; s.wypisz();

    Zbior cw = A.czescWspolna(B);
    cout << "A n B = "; cw.wypisz();

    Zbior r = A.roznica(B);
    cout << "A - B = "; r.wypisz();

    Zbior C;
    C.dodaj(1); C.dodaj(2);
    cout << "C = "; C.wypisz();
    cout << "czy C to podzbior A? " << (C.podzbior(A) ? "tak" : "nie") << endl;

    return 0;
}