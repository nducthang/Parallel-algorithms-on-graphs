#include <iostream>
#include <algorithm>
#include <omp.h>
using namespace std;
typedef long long ll;
const ll MAXC = INT32_MAX;
class FloydParallel
{
private:
    ll n;
    ll **c;

public:
    FloydParallel(ll n);
    ~FloydParallel();
    void FloydPar();
    void Result(ll s, ll f);
    void Add(ll u, ll v, ll w);
};

FloydParallel::FloydParallel(ll n)
{
    this->n = n;
    this->c = new ll *[this->n];
    for (ll i = 0; i < this->n; i++)
        this->c[i] = new ll[this->n];

    for (ll i = 0; i < this->n; i++)
    {
        for (ll j = 0; j < this->n; j++)
        {
            if (i == j)
                this->c[i][j] = 0;
            else
                this->c[i][j] = MAXC;
        }
    }
}

FloydParallel::~FloydParallel()
{
    for (ll i = 0; i < this->n; i++)
        delete[] this->c[i];
    delete[] this->c;
}
void FloydParallel::FloydPar()
{
    omp_set_num_threads(8);
    ll k, u, v;
    for (k = 0; k < this->n; k++)
    {
#pragma omp parallel for private(u, v)
        for (u = 0; u < this->n; u++)
        {
            for (v = 0; v < this->n; v++)
            {
                this->c[u][v] = min(this->c[u][v], this->c[u][k] + this->c[k][v]);
            }
        }
    }
}
void FloydParallel::Result(ll s, ll f)
{
    if (this->c[s][f] == MAXC)
        cout << "Path from " << s << " to " << f << " not found" << endl;
    else
        cout << "Distance from " << s << " to " << f << " is: " << this->c[s][f] << endl;
}
void FloydParallel::Add(ll u, ll v, ll w)
{
    this->c[u][v] = w;
}
void LoadGraph(FloydParallel &g)
{
    ll u, v, w;
    while (cin >> u >> v >> w)
        g.Add(u, v, w);
}
int main(int argc, const char **argv)
{
    freopen("./graph_5000_nodes_0.txt", "r", stdin);
    ll n, s, f;
    cin >> n >> s >> f;
    FloydParallel g(n);
    LoadGraph(g);
    cout << "Load graph succesfully!" << endl;
    double start = omp_get_wtime();
    g.FloydPar();
    double end = omp_get_wtime();
    g.Result(s, f);
    cout << "Time Floyd sequence: " << end - start << " s" << endl;
    return 0;
}