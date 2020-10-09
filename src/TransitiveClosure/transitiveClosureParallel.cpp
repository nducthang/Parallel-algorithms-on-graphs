#include <iostream>
#include <omp.h>
#include <algorithm>
#include <fstream>
#include <string>
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

void TransitiveClosureParallel::Add(ll u, ll v)
{
    this->c[u][v] = 1;
}
void LoadGraph(TransitiveClosureParallel &g, fstream &fsi)
{
    ll u, v, w;
    while (fsi >> u >> v)
        g.Add(u, v);
}
int main(int argc, const char **argv)
{
    fstream wf;
    wf.open("./src/TransitiveClosure/resultParallel.txt", ios::out);
    for (int i = 200; i <= 3000; i += 200)
    {
        fstream fsi;
        string file = "./src/TransitiveClosure/data/graph_" + to_string(i) + "_nodes.txt";
        fsi.open(file, ios::in);
        ll n;
        fsi >> n;
        TransitiveClosureParallel g(n);
        LoadGraph(g, fsi);
        cout << "Load file: " << file << endl;
        double start = omp_get_wtime();
        g.Floyd();
        double end = omp_get_wtime();
        double timeSpent = end - start;
        cout << "Time run file: " << i << " is: " << timeSpent << " s" << endl;
        fsi.close();
        wf << to_string(i) + "," + to_string(timeSpent) + '\n';
    }
    wf.close();
    return 0;
}