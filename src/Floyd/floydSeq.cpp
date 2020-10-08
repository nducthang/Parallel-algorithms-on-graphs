#include <iostream>
#include <time.h>
#include <algorithm>
#include <string>
#include <fstream>
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
void FloydSeq::Add(ll u, ll v, ll w)
{
    this->c[u][v] = w;
}
void LoadGraph(FloydSeq &g, fstream &fsi)
{
    ll u, v, w;
    while (fsi >> u >> v >> w)
        g.Add(u, v, w);
}
int main(int argc, const char **argv)
{

    fstream wf;
    wf.open("./src/Floyd/resultSequential.txt", ios::out);
    for (int i = 200; i <= 3000; i += 200)
    {
        fstream fsi;
        string file = "./src/Floyd/data/graph_" + to_string(i) + "_nodes.txt";
        fsi.open(file, ios::in);
        ll n;
        fsi >> n;
        FloydSeq g(n);
        LoadGraph(g, fsi);
        cout << "Load file: " << file << endl;
        clock_t start = clock();
        g.Floyd();
        clock_t end = clock();
        double timeSpent = (double)(end - start) / CLOCKS_PER_SEC;
        cout << "Time run file: " << i << " is: " << timeSpent << " s" << endl;
        fsi.close();
        wf << to_string(i) + "," + to_string(timeSpent) + '\n';
    }
    wf.close();
    return 0;
}