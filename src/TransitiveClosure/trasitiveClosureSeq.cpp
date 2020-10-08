#include <iostream>
#include <time.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const ll MAXC = INT32_MAX;
class TransitiveClosureSeq
{
private:
    ll n;
    ll **c;

public:
    TransitiveClosureSeq(ll n);
    ~TransitiveClosureSeq();
    void Floyd();
    void Result(ll s, ll f);
    void Add(ll u, ll v);
};

TransitiveClosureSeq::TransitiveClosureSeq(ll n)
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

TransitiveClosureSeq::~TransitiveClosureSeq()
{
    for (ll i = 0; i < this->n; i++)
        delete[] this->c[i];
    delete[] this->c;
}
void TransitiveClosureSeq::Floyd()
{
    ll k, u, v;
    for (k = 0; k < this->n; k++)
    {
        for (u = 0; u < this->n; u++)
        {
            for (v = 0; v < this->n; v++)
            {
                this->c[u][v] = this->c[u][v] || (this->c[u][k] & this->c[k][v]);
            }
        }
    }
}
void TransitiveClosureSeq::Result(ll s, ll f)
{
    if (this->c[s][f] == MAXC)
        cout << "Path from " << s << " to " << f << " not found" << endl;
    else
        cout << "Path from " << s << " to " << f << " connected" << endl;
}
void TransitiveClosureSeq::Add(ll u, ll v)
{
    this->c[u][v] = 1;
}
void LoadGraph(TransitiveClosureSeq &g)
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
    TransitiveClosureSeq g(n);
    LoadGraph(g);
    cout << "Load graph succesfully!" << endl;
    clock_t start = clock();
    g.Floyd();
    clock_t end = clock();
    g.Result(s, f);
    double timeSpent = (double)(end - start) / CLOCKS_PER_SEC;
    cout << "Time Transitive Closure sequence: " << timeSpent << " s" << endl;
    return 0;
}