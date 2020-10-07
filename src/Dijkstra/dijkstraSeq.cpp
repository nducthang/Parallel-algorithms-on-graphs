#include <iostream>
#include <time.h>
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
    void Dijkstra();
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
        if (u == this->f || u == -1)
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
    clock_t start = clock();
    g.Dijkstra();
    clock_t end = clock();
    g.Result();
    double timeSpent = (double)(end - start) / CLOCKS_PER_SEC;
    cout << "Time Dijkstra sequence: " << timeSpent << " s" << endl;
    return 0;
}
