#include <iostream>
#include <time.h>
#include <fstream>
#include <string>
using namespace std;
typedef long long ll;
const ll MAXC = INT32_MAX;

class DijkstraSeq
{
private:
    ll n;
    ll **c;
    ll *d;
    bool *dd;
    ll s;

public:
    DijkstraSeq(ll n, ll s);
    ~DijkstraSeq();
    void Dijkstra();
    void Add(ll u, ll v, ll w);
};

DijkstraSeq::DijkstraSeq(ll n, ll s)
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

DijkstraSeq::~DijkstraSeq()
{
    delete[] this->d;
    delete[] this->dd;
    for (ll i = 0; i < this->n; i++)
        delete[] this->c[i];
    delete[] this->c;
}

void DijkstraSeq::Dijkstra()
{
    this->d[this->s] = 0;
    while (true)
    {
        ll u = -1, distanceMin = MAXC;
        // Tìm trong các nhãn tự do ra nhãn u có d[u] nhỏ nhất
        for (ll i = 0; i < this->n; i++)
        {
            if (this->dd[i] && this->d[i] < distanceMin)
            {
                distanceMin = this->d[i];
                u = i;
            }
        }
        // Điều kiện dừng
        if (u == -1)
            break;
        // Cố định nhãn u
        this->dd[u] = false;
        // Dùng đỉnh u tối ưu nhãn những đỉnh tự do kề u
        for (ll v = 0; v < this->n; v++)
        {
            if (this->dd[v] && this->d[v] > this->d[u] + this->c[u][v])
                this->d[v] = this->d[u] + this->c[u][v];
        }
    }
}
void DijkstraSeq::Add(ll u, ll v, ll w)
{
    this->c[u][v] = w;
}

void LoadGraph(DijkstraSeq &g, fstream &fsi)
{
    ll u, v, w;
    while (fsi >> u >> v >> w)
        g.Add(u, v, w);
}

int main(int argc, char const *argv[])
{
    fstream wf;
    wf.open("./src/Dijkstra/resultSequential.txt", ios::out);
    for (int i = 1000; i <= 40000; i += 1000)
    {
        fstream fsi;
        string file = "./src/Dijkstra/data/graph_" + to_string(i) + "_nodes.txt";
        fsi.open(file, ios::in);
        ll n, s, f;
        fsi >> n >> s;
        DijkstraSeq g(n, s);
        LoadGraph(g, fsi);
        cout << "Load file: " << file << endl;
        clock_t start = clock();
        g.Dijkstra();
        clock_t end = clock();
        double timeSpent = (double)(end - start) / CLOCKS_PER_SEC;
        cout << "Time run file: " << i << " is: " << timeSpent << " s" << endl;
        fsi.close();
        wf << to_string(i) + "," + to_string(timeSpent) + '\n';
    }
    wf.close();
    return 0;
}
