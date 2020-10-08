#include <iostream>
#include <omp.h>
#include <fstream>
#include <string>
using namespace std;
typedef long long ll;
const ll MAXC = INT32_MAX;

class DijkstraParallel
{
private:
    ll n;
    ll **c;
    ll *d;
    bool *dd;
    ll s;

public:
    DijkstraParallel(ll n, ll s);
    ~DijkstraParallel();
    void DijkstraPar();
    void Add(ll u, ll v, ll w);
};

DijkstraParallel::DijkstraParallel(ll n, ll s)
{
    this->n = n;
    this->s = s;
    this->c = new ll *[this->n];
    for (ll i = 0; i < this->n; i++)
        this->c[i] = new ll[this->n];
    this->d = new ll[this->n];
    this->dd = new bool[this->n];
    for (ll i = 0; i < this->n; i++)
    {
        for (ll j = 0; j < this->n; j++)
        {
            this->c[i][j] = MAXC;
        }
    }
    for (ll i = 0; i < this->n; i++)
    {
        this->d[i] = MAXC;
        this->dd[i] = true;
        this->c[i][i] = 0;
    }
}

DijkstraParallel::~DijkstraParallel()
{
    delete[] this->d;
    delete[] this->dd;
    for (ll i = 0; i < this->n; i++)
        delete[] this->c[i];
    delete[] this->c;
}

void DijkstraParallel::DijkstraPar()
{
    this->d[this->s] = 0;
    while (true)
    {
        ll u = -1, distanceMin = MAXC;
// Tìm trong các nhãn tự do ra nhãn u có d[u] nhỏ nhất
// Thực hiện song song
#pragma omp parallel
        {
            ll uLocal = -1, distanceMinLocal = MAXC;
#pragma omp for nowait
            for (ll i = 0; i < this->n; i++)
            {
                if (this->dd[i] && this->d[i] < distanceMinLocal)
                {
                    distanceMinLocal = this->d[i];
                    uLocal = i;
                }
            }
#pragma omp critical
            {
                if (distanceMinLocal < distanceMin && uLocal != -1)
                {
                    distanceMin = distanceMinLocal;
                    u = uLocal;
                }
            }
        }
        // Điều kiện dừng
        if (u == -1)
            break;
        // Cố định nhãn u
        this->dd[u] = false;
#pragma omp parallel for schedule(static)
        // Dùng đỉnh u tối ưu nhãn những đỉnh tự do kề u
        for (ll v = 0; v < this->n; v++)
        {
            if (this->dd[v] && this->d[v] > this->d[u] + this->c[u][v])
                this->d[v] = this->d[u] + this->c[u][v];
        }
    }
}
void DijkstraParallel::Add(ll u, ll v, ll w)
{
    this->c[u][v] = w;
}

void LoadGraph(DijkstraParallel &g, fstream &fsi)
{
    ll u, v, w;
    while (fsi >> u >> v >> w)
        g.Add(u, v, w);
}
int main(int argc, char const *argv[])
{
    fstream wf;
    wf.open("./src/Dijkstra/resultParallel.txt", ios::out);
    for (int i = 1000; i <= 40000; i += 1000)
    {
        fstream fsi;
        string file = "./src/Dijkstra/data/graph_" + to_string(i) + "_nodes.txt";
        fsi.open(file, ios::in);
        ll n, s, f;
        fsi >> n >> s;
        DijkstraParallel g(n, s);
        LoadGraph(g, fsi);
        cout << "Load file: " << file << endl;
        double start = omp_get_wtime();
        g.DijkstraPar();
        double end = omp_get_wtime();
        double timeSpent = end - start;
        cout << "Time run file: " << i << " is: " << timeSpent << " s" << endl;
        fsi.close();
        wf << to_string(i) + "," + to_string(timeSpent) + '\n';
    }
    wf.close();
    return 0;
}
