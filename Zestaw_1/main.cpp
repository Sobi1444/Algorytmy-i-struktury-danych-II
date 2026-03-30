#include <iostream>
#include <list>
#include <cassert>

class Zbior {
private:
    static const int BUCKET = 10;
    std::list<int> tabela[BUCKET];

    int hash(int x) const { return (x % BUCKET + BUCKET) % BUCKET; }

public:
    bool pusty() { return rozmiar() == 0; }
    int rozmiar() {
        int licznik = 0;
        for (int i = 0; i < BUCKET; i++)
            licznik += tabela[i].size();
        return licznik;
    }
    void dodaj(int x) {
        if (!zawiera(x)) tabela[hash(x)].push_back(x);
    }
    void usun(int x) { tabela[hash(x)].remove(x); }
    bool zawiera(int x) {
        for (int e : tabela[hash(x)])
            if (e == x) return true;
        return false;
    }
    void wyczysc() {
        for (int i = 0; i < BUCKET; i++)
            tabela[i].clear();
    }
    Zbior suma(Zbior& inny) {
        Zbior wynik = *this;
        for (int i = 0; i < BUCKET; i++)
            for (int x : inny.tabela[i]) wynik.dodaj(x);
        return wynik;
    }
    Zbior czescWspolna(Zbior& inny) {
        Zbior wynik;
        for (int i = 0; i < BUCKET; i++)
            for (int x : tabela[i])
                if (inny.zawiera(x)) wynik.dodaj(x);
        return wynik;
    }
    Zbior roznica(Zbior& inny) {
        Zbior wynik;
        for (int i = 0; i < BUCKET; i++)
            for (int x : tabela[i])
                if (!inny.zawiera(x)) wynik.dodaj(x);
        return wynik;
    }
    bool podzbior(Zbior& inny) {
        for (int i = 0; i < BUCKET; i++)
            for (int x : tabela[i])
                if (!inny.zawiera(x)) return false;
        return true;
    }
    void wypisz() {
        std::cout << "{ ";
        for (int i = 0; i < BUCKET; i++)
            for (int x : tabela[i]) std::cout << x << " ";
        std::cout << "}" << std::endl;
    }
};

int main() {
    Zbior A, B;
    A.dodaj(1); A.dodaj(2); A.dodaj(3); A.dodaj(4);
    B.dodaj(3); B.dodaj(4); B.dodaj(5); B.dodaj(6);
    std::cout << "A = "; A.wypisz();
    std::cout << "B = "; B.wypisz();
    Zbior s = A.suma(B);
    std::cout << "A u B = "; s.wypisz();
    Zbior cw = A.czescWspolna(B);
    std::cout << "A n B = "; cw.wypisz();
    Zbior r = A.roznica(B);
    std::cout << "A - B = "; r.wypisz();
    Zbior C;
    C.dodaj(1); C.dodaj(2);
    std::cout << "C = "; C.wypisz();
    std::cout << "czy C to podzbior A? " << (C.podzbior(A) ? "tak" : "nie") << std::endl;
    return 0;
}