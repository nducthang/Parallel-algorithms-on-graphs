#include <iostream>
#include <omp.h>
#include <vector>

using namespace std;
typedef long long ll;
class dfsConnectedPar
{
private:
    ll n;
    ll **c;
    bool *dd;
    ll count;

public:
    dfsConnectedPar(int n);
    ~dfsConnectedPar();
    void Add(ll u, ll v);
    void pDFS(ll s);
    void Result();
    void ConnectedComponent();
};

dfsConnectedPar::dfsConnectedPar(int n)
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

dfsConnectedPar::~dfsConnectedPar()
{
    for (ll i = 0; i < this->n; i++)
        delete[] c[i];
    delete[] c;
    delete[] dd;
}

void dfsConnectedPar::Add(ll u, ll v)
{
    this->c[u][v] = 1;
    this->c[v][u] = 1;
}

void dfsConnectedPar::pDFS(ll s)
{
    vector<ll> st;
    st.push_back(s);
    while (!st.empty())
    {
        ll u = st.back();
        st.pop_back();
        cout << u << " ";
        this->dd[u] = false;
#pragma omp parallel shared(st)
        {
            // Mỗi luồng có 1 stack riêng (giả định là vector)
            vector<ll> stPrivate;
#pragma omp for nowait schedule(static)
            for (ll v = 0; v < this->n; v++)
            {
                if (this->dd[v] && this->c[u][v])
                {
                    stPrivate.push_back(v);
                }
            }
#pragma omp critical
            st.insert(st.end(), stPrivate.begin(), stPrivate.end());
        }
    }
}
void dfsConnectedPar::ConnectedComponent()
{
    for (ll i = 0; i < this->n; i++)
    {
        if (this->dd[i])
        {
            this->count++;
            cout << "Thanh phan lien thong thu " << this->count << " gom cac dinh: ";
            this->pDFS(i);
            cout << endl;
        }
    }
}
void LoadGraph(dfsConnectedPar &g)
{
    ll u, v;
    while (cin >> u >> v)
        g.Add(u, v);
}
int main()
{
    freopen("./test3.txt", "r", stdin);
    ll n;
    cin >> n;
    dfsConnectedPar g(n);
    LoadGraph(g);
    cout << "Load graph succesfully!" << endl;
    double start = omp_get_wtime();
    g.ConnectedComponent();
    double end = omp_get_wtime();
    cout << "Time parallel: " << end - start << " s" << endl;
}