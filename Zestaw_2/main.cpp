#include <iostream>
#include <vector>
#include <algorithm>

class KolejkaPriorytetowa {
private:
    std::vector<int> dane;
public:
    bool pusty() { return dane.empty(); }
    int rozmiar() { return dane.size(); }
    void dodaj(int x) {
        dane.push_back(x);
        std::push_heap(dane.begin(), dane.end());
    }
    int szczyt() { return dane.front(); }
    void usun() {
        std::pop_heap(dane.begin(), dane.end());
        dane.pop_back();
    }
    void wyczysc() { dane.clear(); }
    void wypisz() {
        std::vector<int> kopia = dane;
        std::cout << "[ ";
        while (!kopia.empty()) {
            std::pop_heap(kopia.begin(), kopia.end());
            std::cout << kopia.back() << " ";
            kopia.pop_back();
        }
        std::cout << "]" << std::endl;
    }
};

int main() {
    KolejkaPriorytetowa kp;
    kp.dodaj(3);
    kp.dodaj(1);
    kp.dodaj(5);
    kp.dodaj(2);
    kp.dodaj(4);
    std::cout << "Rozmiar: " << kp.rozmiar() << std::endl;
    std::cout << "Szczyt: " << kp.szczyt() << std::endl;
    std::cout << "Kolejka: "; kp.wypisz();
    kp.usun();
    std::cout << "Po usunieciu szczytu: "; kp.wypisz();
    std::cout << "Nowy szczyt: " << kp.szczyt() << std::endl;
    return 0;
}
