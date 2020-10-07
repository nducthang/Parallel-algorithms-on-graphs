#include <iostream>
#include <omp.h>
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
    ll s, f;

public:
    DijkstraSeq(ll n, ll s, ll f);
    ~DijkstraSeq();
    void DijkstraPar();
    void Result();
    void Add(ll u, ll v, ll w);
};

DijkstraSeq::DijkstraSeq(ll n, ll s, ll f)
{
    this->n = n;
    this->s = s;
    this->f = f;
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

void DijkstraSeq::DijkstraPar()
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
        if (u == this->f || u == -1)
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
void DijkstraSeq::Result()
{
    if (this->d[this->f] == MAXC)
        cout << "There is no path from " << this->s << " to " << this->f << endl;
    else
        cout << "Distance from " << this->s << " to " << this->f << " is: " << this->d[this->f] << endl;
}
void DijkstraSeq::Add(ll u, ll v, ll w)
{
    this->c[u][v] = w;
}

void LoadGraph(DijkstraSeq &g)
{
    ll u, v, w;
    while (cin >> u >> v >> w)
        g.Add(u, v, w);
}
int main(int argc, char const *argv[])
{
    freopen("./graph_30000_nodes_0.txt", "r", stdin);
    ll n, s, f;
    cin >> n >> s >> f;
    DijkstraSeq g(n, s, f);
    LoadGraph(g);
    cout << "Load graph succesfully!" << endl;
    double start = omp_get_wtime();
    g.DijkstraPar();
    double end = omp_get_wtime();
    g.Result();
    cout << "Time Dijkstra parallel: " << end - start << " s" << endl;
    return 0;
}
