#include <iostream>
#include <time.h>
#include <string>
#include <fstream>
using namespace std;
typedef long long ll;
const ll MAXC = INT32_MAX;
class PrimSeq
{
private:
    ll n;
    ll **c;
    ll *d;
    bool *dd;
    bool connected;
    ll minWeight;

public:
    PrimSeq(ll n);
    ~PrimSeq();
    void Prim();
    void Result();
    void Add(ll u, ll v, ll w);
};

PrimSeq::PrimSeq(ll n)
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

PrimSeq::~PrimSeq()
{
    delete[] this->d;
    delete[] this->dd;
    for (ll i = 0; i < this->n; i++)
        delete[] this->c[i];
    delete[] this->c;
}

void PrimSeq::Prim()
{
    // Ban đầu coi như cây T chỉ chưá đỉnh 0
    this->d[0] = 0;
    for (ll iter = 1; iter <= this->n; iter++)
    {
        // Tìm đỉnh gần cây T nhất trong số các đỉnh ngoài cây
        ll u = -1, distanceMin = MAXC;
        for (ll i = 0; i < this->n; i++)
        {
            if (this->dd[i] && this->d[i] < distanceMin)
            {
                u = i;
                distanceMin = d[i];
            }
        }
        // Nếu không chọn được thì đồ thị không liên thông
        if (u == -1)
        {
            this->connected = false;
            break;
        }
        // Nêú chọn được thì đánh dấu lại và tính toán lại khoảng cách
        this->dd[u] = false;
        this->minWeight += this->d[u];
        for (ll v = 0; v < n; v++)
        {
            if (this->dd[v] && this->d[v] > this->c[u][v])
                this->d[v] = this->c[u][v];
        }
    }
}

void PrimSeq::Result()
{
    // Hiển thị kết quả
    if (this->connected)
        cout << "Cay khung nho nhat cua do thi co tong trong so la: " << this->minWeight << endl;
    else
        cout << "Do thi khong lien thong" << endl;
}

void PrimSeq::Add(ll u, ll v, ll w)
{
    this->c[u][v] = w;
    this->c[v][u] = w;
}
void LoadGraph(PrimSeq &g, fstream &fsi)
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
    wf.open("./src/Prim/resultSequential.txt", ios::out);
    for (int i = 500; i <= 30000; i += 500)
    {
        fstream fsi;
        string file = "./src/Prim/data/graph_" + to_string(i) + "_nodes.txt";
        fsi.open(file, ios::in);
        ll n;
        fsi >> n;
        PrimSeq primseq(n);
        LoadGraph(primseq, fsi);
        cout << "Load file: " << file << endl;
        clock_t start = clock();
        primseq.Prim();
        clock_t end = clock();
        primseq.Result();
        double timeSpent = (double)(end - start) / CLOCKS_PER_SEC;
        cout << "Time run file: " << i << " is: " << timeSpent << " s" << endl;
        fsi.close();
        wf << to_string(i) + "," + to_string(timeSpent) + '\n';
    }
    wf.close();
    return 0;
}
