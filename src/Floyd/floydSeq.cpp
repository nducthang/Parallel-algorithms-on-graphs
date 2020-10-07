#include <iostream>
#include <time.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const ll MAXC = INT32_MAX;
class FloydSeq
{
private:
    ll n;
    ll **c;

public:
    FloydSeq(ll n);
    ~FloydSeq();
    void Floyd();
    void Result(ll s, ll f);
    void Add(ll u, ll v, ll w);
};

FloydSeq::FloydSeq(ll n)
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

FloydSeq::~FloydSeq()
{
    for (ll i = 0; i < this->n; i++)
        delete[] this->c[i];
    delete[] this->c;
}
void FloydSeq::Floyd()
{
    ll k, u, v;
    for (k = 0; k < this->n; k++)
    {
        for (u = 0; u < this->n; u++)
        {
            for (v = 0; v < this->n; v++)
            {
                this->c[u][v] = min(this->c[u][v], this->c[u][k] + this->c[k][v]);
            }
        }
    }
}
void FloydSeq::Result(ll s, ll f)
{
    if (this->c[s][f] == MAXC)
        cout << "Path from " << s << " to " << f << " not found" << endl;
    else
        cout << "Distance from " << s << " to " << f << " is: " << this->c[s][f] << endl;
}
void FloydSeq::Add(ll u, ll v, ll w)
{
    this->c[u][v] = w;
}
void LoadGraph(FloydSeq &g)
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
    FloydSeq g(n);
    LoadGraph(g);
    cout << "Load graph succesfully!" << endl;
    clock_t start = clock();
    g.Floyd();
    clock_t end = clock();
    g.Result(s, f);
    double timeSpent = (double)(end - start) / CLOCKS_PER_SEC;
    cout << "Time Floyd sequence: " << timeSpent << " s" << endl;
    return 0;
}