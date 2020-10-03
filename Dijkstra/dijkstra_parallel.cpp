#include <iostream>
#include <vector>
#include <omp.h>
using namespace std;
using namespace std;
typedef long long ll;
const ll maxC = 9e9;
const ll MAX = 1000;
vector<vector<ll>> c(MAX, vector<ll>(MAX, maxC));
vector<ll> d(MAX, maxC); // d[v] = khoang cach tu v den s
vector<bool> dd(MAX);    // dd[v] = 0 tức là nhãn v tự do
ll n, m, s, f;

void LoadGraph()
{
    ll u, v, w;
    cin >> n >> m >> s >> f;
    // Khởi tạo ma trận trọng số
    for (ll i = 1; i <= n; i++)
        c[i][i] = 0;
    for (ll i = 1; i <= m; i++)
    {
        cin >> u >> v >> w;
        c[u][v] = w;
    }
}
void Dijkstra()
{
    d[s] = 0;
    while (true)
    {
        ll u = 0, distanceMin = maxC;
// tìm trong các nhãn tự do ra nhãn u có d[u] nhỏ nhất
// Thực hiện song song
#pragma omp parallel
        {
            ll uLocal = 0, distanceMinLocal = maxC;
#pragma omp for nowait
            for (ll i = 1; i <= n; i++)
            {
                if (dd[i] == 0 && d[i] < distanceMinLocal)
                {
                    distanceMinLocal = d[i];
                    uLocal = i;
                }
            }
#pragma omp critical
            {
                if (distanceMinLocal < distanceMin && uLocal != 0)
                {
                    distanceMin = distanceMinLocal;
                    u = uLocal;
                }
            }
        }
        // Điều kiện dừng
        if (u == f || u == 0)
            break;
        // Cố định nhãn đỉnh u
        dd[u] = 1;
// Dùng đỉnh u tối ưu nhãn những đỉnh tự do kề u
#pragma omp parallel for schedule(static)
        for (ll v = 1; v <= n; v++)
        {
            if (dd[v] == 0 && d[v] > d[u] + c[u][v])
            {
                d[v] = d[u] + c[u][v];
            }
        }
    }
}
void Result()
{
    if (d[f] == maxC)
        cout << "There is no path from " << s << " to " << f << endl;
    else
        cout << "Distance from " << s << " to " << f << " is: " << d[f] << endl;
}
int main()
{
    freopen("./Dijkstra/input.txt", "r", stdin);
    LoadGraph();
    clock_t start = clock();
    Dijkstra();
    clock_t end = clock();
    Result();
    cout << "Time: " << end - start << " ms" << endl;
}