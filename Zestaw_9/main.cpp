#include <iostream>
#include <cassert>
#include <climits>
#include <vector>
#include <iomanip>

// liczba wierzcholkow
static const int N = 10;

static const int INF = INT_MAX / 2;

// macierz nxn
typedef std::vector<std::vector<int>> Matrix;

// macierz na stdout
void printMatrix(const Matrix& D, const std::string& name) {
    std::cout << name << ":\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (D[i][j] >= INF)
                std::cout << std::setw(5) << "INF";
            else
                std::cout << std::setw(5) << D[i][j];
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

// rekonstruuje i wypisuje sciezke z s do t
void printPath(const Matrix& Parent, int s, int t) {
    if (s == t) {
        std::cout << s;
        return;
    }
    if (Parent[s][t] == -1) {
        std::cout << "brak sciezki";
        return;
    }
    printPath(Parent, s, Parent[s][t]);
    std::cout << " -> " << t;
}

// Floyd-Warshall
// zwraca true jesli nie wykryto ujemnego cyklu.
// macierz Parent[i][j] = poprzednik j na najkrotszej sciezce z i.
bool floydWarshall(const Matrix& Weight, Matrix& D, Matrix& Parent) {
    // set D^{(0)} to Weight
    D = Weight;

    // inicjalizacja macierzy poprzednikow
    // parent[i][j] = i jesli istnieje krawedz (i,j) lub -1 jak nie
    Parent.assign(N, std::vector<int>(N, -1));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (i != j && Weight[i][j] < INF)
                Parent[i][j] = i;

    for (int k = 0; k < N; k++) {
        // jedna macierz - zlozonosc pamieciowa O(n^2))
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                // D[i,j]^{(k)} = min{ D[i,j]^{(k-1)}, D[i,k]^{(k-1)} + D[k,j]^{(k-1)} }
                if (D[i][k] < INF && D[k][j] < INF &&
                    D[i][k] + D[k][j] < D[i][j]) {
                    D[i][j] = D[i][k] + D[k][j];
                    Parent[i][j] = Parent[k][j];
                }
            }
        }
    }

    // Sprawdzenie czy sa negatywne cykle
    for (int i = 0; i < N; i++) {
        if (D[i][i] < 0)
            return false;
    }

    return true;
}

// przykladowy graf skierowany wazony z n=10
Matrix buildExampleGraph() {
    // weight[i,j] = 0 dla i = j
    // weight[i,j] = w(i,j) dla (i,j) nalezy do E(G)
    // weight[i,j] = +inf dla i != j oraz (i,j) nie nalezy do E(G)
    Matrix W(N, std::vector<int>(N, INF));
    for (int i = 0; i < N; i++)
        W[i][i] = 0;

    // krawedzie (indeksy 0-9)
    auto addEdge = [&](int u, int v, int w) { W[u][v] = w; };
    addEdge(0, 1, 3);
    addEdge(0, 4, 7);
    addEdge(1, 2, 4);
    addEdge(1, 3, 1);
    addEdge(2, 5, 2);
    addEdge(3, 2, 1);
    addEdge(3, 6, 5);
    addEdge(4, 3, 2);
    addEdge(4, 7, 3);
    addEdge(5, 8, 6);
    addEdge(6, 5, 1);
    addEdge(6, 9, 4);
    addEdge(7, 6, 2);
    addEdge(7, 8, 1);
    addEdge(8, 9, 2);
    addEdge(9, 5, 3);

    return W;
}

// Floyd-Warshall dla dowolnego rozmiaru n
bool floydWarshallN(int n, const Matrix& Weight, Matrix& D, Matrix& Parent) {
    D = Weight;
    Parent.assign(n, std::vector<int>(n, -1));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (i != j && Weight[i][j] < INF)
                Parent[i][j] = i;

    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (D[i][k] < INF && D[k][j] < INF &&
                    D[i][k] + D[k][j] < D[i][j]) {
                    D[i][j] = D[i][k] + D[k][j];
                    Parent[i][j] = Parent[k][j];
                }

    for (int i = 0; i < n; i++)
        if (D[i][i] < 0) return false;
    return true;
}

void runTests() {
    // prosty graf 3-wierzcholkowy: 0->1 (1), 1->2 (2), 0->2 (10)
    // najkrotsza z 0 do 2: 0->1->2 = 3
    {
        const int n = 3;
        Matrix W(n, std::vector<int>(n, INF));
        for (int i = 0; i < n; i++) W[i][i] = 0;
        W[0][1] = 1; W[1][2] = 2; W[0][2] = 10;

        Matrix D, P;
        bool ok = floydWarshallN(n, W, D, P);
        assert(ok);
        assert(D[0][2] == 3);
        assert(D[0][0] == 0);
        assert(D[1][0] >= INF); // brak krawedzi wstecz
    }

    // bezposrednia krawedz krotsza niz przez posrednika
    {
        const int n = 3;
        Matrix W(n, std::vector<int>(n, INF));
        for (int i = 0; i < n; i++) W[i][i] = 0;
        W[0][1] = 5; W[1][2] = 5; W[0][2] = 1;

        Matrix D, P;
        floydWarshallN(n, W, D, P);
        assert(D[0][2] == 1); // krawedz bezposrednia wygrywa
    }

    // graf bez krawedzi (2 wierzcholki)
    {
        const int n = 2;
        Matrix W(n, std::vector<int>(n, INF));
        W[0][0] = 0; W[1][1] = 0;
        Matrix D, P;
        bool ok = floydWarshallN(n, W, D, P);
        assert(ok);
        assert(D[0][1] >= INF);
    }

    std::cout << "Wszystkie testy przeszly.\n\n";
}

int main() {
    runTests();

    Matrix Weight = buildExampleGraph();
    printMatrix(Weight, "Macierz wag");

    Matrix D, Parent;
    bool ok = floydWarshall(Weight, D, Parent);

    if (!ok) {
        std::cout << "Wykryto ujemny cykl\n";
        return 1;
    }

    printMatrix(D, "Macierz odleglosci (D)");

    // kilka przykladowych sciezek
    std::cout << "Przykladowe najkrotsze sciezki:\n";
    int pairs[][2] = {{0,9},{0,8},{1,9},{4,9},{3,8}};
    for (auto& p : pairs) {
        int s = p[0], t = p[1];
        std::cout << "  " << s << " -> " << t
                  << "  (dlugosc: " << D[s][t] << ")  trasa: ";
        printPath(Parent, s, t);
        std::cout << "\n";
    }

    return 0;
}