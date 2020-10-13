#include <iostream>
#include <vector>
#include <set>
#include <iterator>
#include <fstream>
#include <string>
#include <algorithm>
#include <time.h>
#include <omp.h>
using namespace std;
typedef long long ll;

class LubyParallel
{
private:
    ll n;
    vector<ll> *adj;
    ll *C;
    set<ll> I;

public:
    LubyParallel(ll n);
    ~LubyParallel();
    void AddEdge(ll u, ll v);
    void LubyPar();
    void Result();
};

LubyParallel::LubyParallel(ll n)
{
    this->n = n;
    this->adj = new vector<ll>[this->n];
    // this->I = new ll[this->n];
    this->C = new ll[this->n];
    for (ll i = 0; i < this->n; i++)
    {
        // this->I[i] = 0;
        this->C[i] = 1;
    }
    // for (ll i = 0; i < this->n; i++)
    //     this->C.insert(i);
}

LubyParallel::~LubyParallel()
{
}
void LubyParallel::AddEdge(ll u, ll v)
{
    this->adj[u].push_back(v);
    this->adj[v].push_back(u);
}
void LubyParallel::LubyPar()
{
// for (ll i = 0; i < this->n; i++)
// {
//     if (this->C[i])
//     {
//         this->I[i] = 1;
//         this->C[i] = 0;
//         vector<ll>::iterator it;
//         for (it = this->adj[i].begin(); it != this->adj[i].end(); it++)
//             this->C[*it] = 0;
//     }
// }
#pragma omp for nowait
    for (ll i = 0; i < this->n; i++)
    {
        if (this->C[i])
        {
            I.insert(i);
            this->C[i] = 0;
            vector<ll>::iterator neighbor;
            for (neighbor = this->adj[i].begin(); neighbor != this->adj[i].end(); neighbor++)
                this->C[*neighbor] = 0;
        }
    }
}
void LubyParallel::Result()
{
    // cout << "MIS has " << count(this->I, this->I + sizeof(this->I) / sizeof(ll), 1) << " node: ";
    // copy(this->I, this->I + sizeof(this->I) / sizeof(ll), ostream_iterator<ll>(cout, " "));
    // cout << endl;
    // for (ll i = 0; i < this->n; i++)
    //     if (this->I[i])
    //         cout << i << " ";
    // cout << endl;
    // copy(this->I.begin(), this->I.end(), ostream_iterator<ll>(cout, " "));
    // cout<<endl;
}
void LoadGraph(LubyParallel &g, fstream &fsi)
{
    ll u, v;
    while (fsi >> u >> v)
        g.AddEdge(u, v);
}

int main(int argc, char const *argv[])
{
    fstream wf;
    wf.open("./src/Luby/resultParallel.txt", ios::out);
    for (int i = 5000; i <= 900000; i += 5000)
    {
        fstream fsi;
        string file = "./src/Luby/data/graph_" + to_string(i) + "_nodes.txt";
        fsi.open(file, ios::in);
        ll n;
        fsi >> n;
        LubyParallel g(n);
        LoadGraph(g, fsi);
        cout << "Load file: " << file << endl;
        // double start = omp_get_wtime();
        clock_t start = clock();
        g.LubyPar();
        // double end = omp_get_wtime();
        clock_t end = clock();
        // g.Result();
        // double timeSpent = end - start;
        double timeSpent = (double)(end - start) / CLOCKS_PER_SEC;
        cout << "Time run file: " << i << " is: " << timeSpent << " s" << endl;
        fsi.close();
        wf << to_string(i) + "," + to_string(timeSpent) + '\n';
    }
    wf.close();

    // freopen("./test.txt", "r", stdin);
    // ll n;
    // cin >> n;
    // LubyParallel g(n);
    // LoadGraph(g);
    // cout << "Load file: " << endl;
    // double start = omp_get_wtime();
    // g.LubyPar();
    // double end = omp_get_wtime();
    // g.Result();
    // cout<<end-start<<endl;
    return 0;
}
