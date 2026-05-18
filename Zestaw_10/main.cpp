#include <iostream>
#include <vector>
#include <cassert>

std::vector<std::vector<int>> transitiveClosure(int n, const std::vector<std::vector<int>>& adj) {
    std::vector<std::vector<int>> T(n, std::vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j || adj[i][j] == 1)
                T[i][j] = 1;
        }
    }

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                T[i][j] = T[i][j] || (T[i][k] && T[k][j]);
            }
        }
    }
    return T;
}

void printMatrix(const std::vector<std::vector<int>>& T) {
    int n = T.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << T[i][j];
            if (j < n - 1) std::cout << " ";
        }
        std::cout << "\n";
    }
}

void runTests() {
    // prosty graf: 0->1, 1->2, wiec 0 dosiegnie 2
    int n = 3;
    std::vector<std::vector<int>> adj(n, std::vector<int>(n, 0));
    adj[0][1] = 1;
    adj[1][2] = 1;

    std::vector<std::vector<int>> T = transitiveClosure(n, adj);

    // kazdy wierzcholek dosiegnie siebie
    assert(T[0][0] == 1);
    assert(T[1][1] == 1);
    assert(T[2][2] == 1);

    // sciezka 0->1->2
    assert(T[0][1] == 1);
    assert(T[0][2] == 1);
    assert(T[1][2] == 1);

    // brak krawedzi w odwrotna strone
    assert(T[2][0] == 0);
    assert(T[2][1] == 0);

    // cykl: 0->1->0
    std::vector<std::vector<int>> adj2(2, std::vector<int>(2, 0));
    adj2[0][1] = 1;
    adj2[1][0] = 1;
    std::vector<std::vector<int>> T2 = transitiveClosure(2, adj2);
    assert(T2[0][1] == 1);
    assert(T2[1][0] == 1);

    std::cout << "Testy zakonczone pomyslnie.\n";
}

int main() {
    runTests();

    int n = 10;
    std::vector<std::vector<int>> adj(n, std::vector<int>(n, 0));

    adj[0][1] = 1;
    adj[0][2] = 1;
    adj[1][3] = 1;
    adj[2][3] = 1;
    adj[3][4] = 1;
    adj[4][5] = 1;
    adj[5][6] = 1;
    adj[6][7] = 1;
    adj[7][8] = 1;
    adj[8][9] = 1;
    adj[9][3] = 1; // cykl: 3-->4-->5-->6-->7-->8-->9-->3

    std::cout << "\nMacierz sasiedztwa grafu:\n";
    printMatrix(adj);

    std::vector<std::vector<int>> T = transitiveClosure(n, adj);

    std::cout << "\nDomkniecie przechodnie T:\n";
    printMatrix(T);

    return 0;
}