#include <iostream>
#include <time.h>
using namespace std;
const int MAXC = INT32_MAX;
class PrimSeq
{
private:
    int n;
    int **c;
    int *d;
    bool *dd;
    bool connected;
    int minWeight;

public:
    PrimSeq(int n);
    ~PrimSeq();
    void Prim();
    void Result();
    void Add(int u, int v, int w);
};

PrimSeq::PrimSeq(int n)
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

PrimSeq::~PrimSeq()
{
    delete[] this->d;
    delete[] this->dd;
    for (int i = 0; i < this->n; i++)
        delete[] this->c[i];
    delete[] this->c;
}

void PrimSeq::Prim()
{
    // Ban đầu coi như cây T chỉ chưá đỉnh 0
    this->d[0] = 0;
    for (int iter = 1; iter <= this->n; iter++)
    {
        // Tìm đỉnh gần cây T nhất trong số các đỉnh ngoài cây
        int u = -1, distanceMin = MAXC;
        for (int i = 0; i < this->n; i++)
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
            connected = false;
            break;
        }
        // Nêú chọn được thì đánh dấu lại và tính toán lại khoảng cách
        this->dd[u] = false;
        minWeight += this->d[u];
        for (int v = 0; v < n; v++)
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

void PrimSeq::Add(int u, int v, int w)
{
    this->c[u][v] = w;
    this->c[v][u] = w;
}
void LoadGraph(PrimSeq &g)
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
    PrimSeq primseq(n);
    LoadGraph(primseq);
    cout << "Load graph succesfully!" << endl;
    clock_t start = clock();
    primseq.Prim();
    clock_t end = clock();
    primseq.Result();
    double timeSpent = (double)(end - start) / CLOCKS_PER_SEC;
    cout << "Time Prim sequence: " << timeSpent << " s" << endl;
    return 0;
}
