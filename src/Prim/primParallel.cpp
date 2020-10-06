#include <iostream>
#include <omp.h>
using namespace std;
const int MAXC = INT32_MAX;
class PrimParallel
{
private:
    int n;
    int **c;
    int *d;
    bool *dd;
    bool connected;
    int minWeight;

public:
    PrimParallel(int n);
    ~PrimParallel();
    void PrimPar();
    void Result();
    void Add(int u, int v, int w);
};

PrimParallel::PrimParallel(int n)
{
    this->n = n;
    this->c = new int *[this->n];
    for (int i = 0; i < this->n; i++)
        this->c[i] = new int[this->n];
    this->d = new int[this->n];
    this->dd = new bool[this->n];
    for (int i = 0; i < this->n; i++)
    {
        for (int j = 0; j < this->n; j++)
        {
            this->c[i][j] = MAXC;
        }
    }
    for (int i = 0; i < this->n; i++)
    {
        this->d[i] = MAXC;
        this->dd[i] = true;
    }
    this->minWeight = 0;
    this->connected = true;
}

PrimParallel::~PrimParallel()
{
    delete[] this->d;
    delete[] this->dd;
    for (int i = 0; i < this->n; i++)
        delete[] this->c[i];
    delete[] this->c;
}

void PrimParallel::PrimPar()
{
    omp_set_num_threads(8);
    this->d[0] = 0;
    for (int iter = 0; iter < this->n; iter++)
    {
        int distanceMin = MAXC, u = -1, i;
#pragma omp parallel
        {
            int uLocal = -1;
            int minLocal = distanceMin;
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
        int v;
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

void PrimParallel::Add(int u, int v, int w)
{
    this->c[u][v] = w;
    this->c[v][u] = w;
}
void LoadGraph(PrimParallel &g)
{
    int u, v, w;
    while (cin >> u >> v >> w)
    {
        g.Add(u, v, w);
    }
}
int main(int argc, const char **argv)
{
    freopen("./graph_20000_nodes_0.txt", "r", stdin);
    int n;
    cin >> n;
    PrimParallel primparallel(n);
    LoadGraph(primparallel);
    cout << "Load graph succesfully!" << endl;
    double start = omp_get_wtime();
    primparallel.PrimPar();
    double end = omp_get_wtime();
    primparallel.Result();
    cout << "Time Prim sequence: " << end - start << " s" << endl;
    return 0;
}
