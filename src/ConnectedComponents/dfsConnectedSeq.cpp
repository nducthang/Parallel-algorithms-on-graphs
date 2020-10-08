#include <iostream>
#include <time.h>
#include <vector>
#include <string>
#include <fstream>

using namespace std;
typedef long long ll;
class dfsConnectedSeq
{
private:
    ll n;
    ll **c;
    bool *dd;
    ll count;

public:
    dfsConnectedSeq(int n);
    ~dfsConnectedSeq();
    void Add(ll u, ll v);
    void DFS(ll s);
    void Result();
    void ConnectedComponent();
};

dfsConnectedSeq::dfsConnectedSeq(int n)
{
    this->n = n;
    c = new ll *[this->n];
    for (ll i = 0; i < this->n; i++)
        c[i] = new ll[this->n];
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
    this->dd = new bool[this->n];
    for (ll i = 0; i < this->n; i++)
        this->dd[i] = true;
    this->count = 0;
}

dfsConnectedSeq::~dfsConnectedSeq()
{
    for (ll i = 0; i < this->n; i++)
        delete[] c[i];
    delete[] c;
    delete[] dd;
}

void dfsConnectedSeq::Add(ll u, ll v)
{
    this->c[u][v] = 1;
    // this->c[v][u] = 1;
}

void dfsConnectedSeq::DFS(ll s)
{
    vector<ll> st;
    st.push_back(s);
    while (!st.empty())
    {
        ll u = st.back();
        st.pop_back();
        // cout << u << " ";
        this->dd[u] = false;
        for (ll v = 0; v < this->n; v++)
        {
            if (this->dd[v] && this->c[u][v])
            {
                st.push_back(v);
            }
        }
    }
}
void dfsConnectedSeq::ConnectedComponent()
{
    for (ll i = 0; i < this->n; i++)
    {
        if (this->dd[i])
        {
            this->count++;
            // cout << "Thanh phan lien thong thu " << this->count << " gom cac dinh: ";
            this->DFS(i);
            // cout << endl;
        }
    }
}
void LoadGraph(dfsConnectedSeq &g, fstream &fsi)
{
    ll u, v;
    while (fsi >> u >> v)
        g.Add(u, v);
}

void dfsConnectedSeq::Result()
{
    cout << "Do thi co " << this->count << " thanh phan lien thong" << endl;
}
int main()
{
    fstream wf;
    wf.open("./src/ConnectedComponents/resultSequential.txt", ios::out);
    for (int i = 500; i <= 30000; i += 500)
    {
        fstream fsi;
        string file = "./src/ConnectedComponents/data/graph_" + to_string(i) + "_nodes.txt";
        fsi.open(file, ios::in);
        ll n;
        fsi >> n;
        dfsConnectedSeq g(n);
        LoadGraph(g, fsi);
        cout << "Load file: " << file << endl;
        clock_t start = clock();
        g.ConnectedComponent();
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