#include <iostream>
#include <omp.h>
#include <fstream>
#include <string>
using namespace std;
typedef long long ll;
const ll MAXC = INT32_MAX;
class PrimParallel
{
private:
    ll n;
    ll **c;
    ll *d;
    bool *dd;
    bool connected;
    ll minWeight;

public:
    PrimParallel(ll n);
    ~PrimParallel();
    void PrimPar();
    void Result();
    void Add(ll u, ll v, ll w);
};

PrimParallel::PrimParallel(ll n)
{
    this->n = n;
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
    this->minWeight = 0;
    this->connected = true;
}

PrimParallel::~PrimParallel()
{
    delete[] this->d;
    delete[] this->dd;
    for (ll i = 0; i < this->n; i++)
        delete[] this->c[i];
    delete[] this->c;
}

void PrimParallel::PrimPar()
{
    omp_set_num_threads(8);
    this->d[0] = 0;
    for (ll iter = 0; iter < this->n; iter++)
    {
        ll distanceMin = MAXC, u = -1, i;
#pragma omp parallel
        {
            ll uLocal = -1;
            ll minLocal = distanceMin;
#pragma omp for nowait
            for (i = 0; i < this->n; i++)
            {
                if (this->dd[i] && this->d[i] < minLocal)
                {
                    minLocal = d[i];
                    uLocal = i;
                }
            }
#pragma omp critical
            {
                if (minLocal < distanceMin && uLocal != -1)
                {
                    distanceMin = minLocal;
                    u = uLocal;
                }
            }
        }
        // Nếu không chọn được thì đồ thị không liên thông
        if (u == -1)
        {
            this->connected = false;
            break;
        }
        // Nêú chọn được thì đánh dâú lại và tính toá khoảng cách
        this->dd[u] = false;
        this->minWeight += this->d[u];
        ll v;
#pragma omp parallel for schedule(static)
        for (v = 0; v < this->n; v++)
        {
            if (this->dd[v] && this->d[v] > this->c[u][v])
                this->d[v] = this->c[u][v];
        }
    }
}

void PrimParallel::Result()
{
    // Hiển thị kết quả
    if (this->connected)
        cout << "Cay khung nho nhat cua do thi co tong trong so la: " << this->minWeight << endl;
    else
        cout << "Do thi khong lien thong" << endl;
}

void PrimParallel::Add(ll u, ll v, ll w)
{
    this->c[u][v] = w;
    this->c[v][u] = w;
}
void LoadGraph(PrimParallel &g, fstream &fsi)
{
    ll u, v, w;
    while (fsi >> u >> v >> w)
    {
        g.Add(u, v, w);
    }
}
int main(int argc, const char **argv)
{
    fstream wf;
    wf.open("./src/Prim/resultParallel.txt", ios::out);
    for (int i = 500; i <= 30000; i += 500)
    {
        fstream fsi;
        string file = "./src/Prim/data/graph_" + to_string(i) + "_nodes.txt";
        fsi.open(file, ios::in);
        ll n;
        fsi >> n;
        PrimParallel primparallel(n);
        LoadGraph(primparallel, fsi);
        cout << "Load file: " << file << endl;
        double start = omp_get_wtime();
        primparallel.PrimPar();
        double end = omp_get_wtime();
        primparallel.Result();
        double timeSpent = end - start;
        cout << "Time run file: " << i << " is: " << timeSpent << " s" << endl;
        fsi.close();
        wf << to_string(i) + "," + to_string(timeSpent) + '\n';
    }
    wf.close();
    return 0;
}
