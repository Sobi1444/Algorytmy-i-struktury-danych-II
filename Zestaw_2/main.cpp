#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class KolejkaPriorytetowa {
private:
    vector<int> dane;

public:
    bool pusty() { return dane.empty(); }
    int rozmiar() { return dane.size(); }

    void dodaj(int x) {
        dane.push_back(x);
        push_heap(dane.begin(), dane.end());
    }

    int szczyt() { return dane.front(); }

    void usun() {
        pop_heap(dane.begin(), dane.end());
        dane.pop_back();
    }

    void wyczysc() { dane.clear(); }

    void wypisz() {
        vector<int> kopia = dane;
        cout << "[ ";
        while (!kopia.empty()) {
            pop_heap(kopia.begin(), kopia.end());
            cout << kopia.back() << " ";
            kopia.pop_back();
        }
        cout << "]" << endl;
    }
};

int main() {
    
    KolejkaPriorytetowa kp;

    kp.dodaj(3);
    kp.dodaj(1);
    kp.dodaj(5);
    kp.dodaj(2);
    kp.dodaj(4);

    cout << "Rozmiar: " << kp.rozmiar() << endl;
    cout << "Szczyt: " << kp.szczyt() << endl;
    cout << "Kolejka: "; kp.wypisz();

    kp.usun();
    cout << "Po usunieciu szczytu: "; kp.wypisz();
    cout << "Nowy szczyt: " << kp.szczyt() << endl;

    return 0;
}