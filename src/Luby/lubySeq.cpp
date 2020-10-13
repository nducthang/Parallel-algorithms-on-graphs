#include <iostream>
#include <vector>
#include <set>
#include <iterator>
#include <time.h>
#include <fstream>
#include <string>
using namespace std;
typedef long long ll;

class LubySeq
{
private:
    ll n;
    vector<ll> *adj;
    set<ll> I;
    // set<ll> C;
    ll *C;

public:
    LubySeq(ll n);
    ~LubySeq();
    void AddEdge(ll u, ll v);
    void Luby();
    void Result();
};

LubySeq::LubySeq(ll n)
{
    this->n = n;
    this->adj = new vector<ll>[this->n];
    // for (ll i = 0; i < this->n; i++)
    //     this->C.insert(i);
    this->C = new ll[this->n];
    for (ll i = 0; i < this->n; i++)
    {
        // this->I[i] = 0;
        this->C[i] = 1;
    }
}

LubySeq::~LubySeq()
{
}
void LubySeq::AddEdge(ll u, ll v)
{
    this->adj[u].push_back(v);
    this->adj[v].push_back(u);
}
void LubySeq::Luby()
{
    // set<ll>::iterator it;
    // while (!this->C.empty())
    // {
    //     it = this->C.begin();
    //     I.insert(*it);
    //     C.erase(*it);
    //     vector<ll>::iterator neighbor;
    //     for (neighbor = this->adj[*it].begin(); neighbor != this->adj[*it].end(); neighbor++)
    //         this->C.erase(*neighbor);
    // }
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
void LubySeq::Result()
{
    cout << "MIS has " << this->I.size() << " node: ";
    // copy(this->I.begin(), this->I.end(), ostream_iterator<ll>(cout, " "));
    cout << endl;
}
void LoadGraph(LubySeq &g, fstream &fsi)
{
    ll u, v;
    while (fsi >> u >> v)
        g.AddEdge(u, v);
}

int main(int argc, char const *argv[])
{
    fstream wf;
    wf.open("./src/Luby/resultSequential.txt", ios::out);
    for (int i = 5000; i <= 900000; i += 5000)
    {
        fstream fsi;
        string file = "./src/Luby/data/graph_" + to_string(i) + "_nodes.txt";
        fsi.open(file, ios::in);
        ll n;
        fsi >> n;
        LubySeq g(n);
        LoadGraph(g, fsi);
        cout << "Load file: " << file << endl;
        clock_t start = clock();
        g.Luby();
        clock_t end = clock();
        g.Result();
        double timeSpent = (double)(end - start) / CLOCKS_PER_SEC;
        cout << "Time run file: " << i << " is: " << timeSpent << " s" << endl;
        fsi.close();
        wf << to_string(i) + "," + to_string(timeSpent) + '\n';
    }
    wf.close();
    return 0;
}
