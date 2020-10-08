#include <iostream>
#include <omp.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const ll MAXC = INT32_MAX;
class TransitiveClosureParallel
{
private:
    ll n;
    ll **c;

public:
    TransitiveClosureParallel(ll n);
    ~TransitiveClosureParallel();
    void Floyd();
    void Result(ll s, ll f);
    void Add(ll u, ll v);
};

TransitiveClosureParallel::TransitiveClosureParallel(ll n)
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
                this->c[i][j] = 1;
            else
                this->c[i][j] = 0;
        }
    }
}

TransitiveClosureParallel::~TransitiveClosureParallel()
{
    for (ll i = 0; i < this->n; i++)
        delete[] this->c[i];
    delete[] this->c;
}
void TransitiveClosureParallel::Floyd()
{
    ll k, u, v;
    for (k = 0; k < this->n; k++)
    {
#pragma omp parallel for private(u, v)
        for (u = 0; u < this->n; u++)
        {
            for (v = 0; v < this->n; v++)
            {
                this->c[u][v] = this->c[u][v] || (this->c[u][k] & this->c[k][v]);
            }
        }
    }
}
void TransitiveClosureParallel::Result(ll s, ll f)
{
    if (this->c[s][f] == MAXC)
        cout << "Path from " << s << " to " << f << " not found" << endl;
    else
        cout << "Path from " << s << " to " << f << " connected" << endl;
}
void TransitiveClosureParallel::Add(ll u, ll v)
{
    this->c[u][v] = 1;
}
void LoadGraph(TransitiveClosureParallel &g)
{
    ll u, v, w;
    while (cin >> u >> v)
        g.Add(u, v);
}
int main(int argc, const char **argv)
{
    freopen("./test2.txt", "r", stdin);
    ll n, s, f;
    cin >> n >> s >> f;
    TransitiveClosureParallel g(n);
    LoadGraph(g);
    cout << "Load graph succesfully!" << endl;
    double start = omp_get_wtime();
    g.Floyd();
    double end = omp_get_wtime();
    g.Result(s, f);
    cout << "Time Transitive Closure parallel: " << end - start << " s" << endl;
    return 0;
}