#include <iostream>
#include <omp.h>
#include <time.h>
#include <vector>

using namespace std;
typedef long long ll;
const ll maxC = 9e9;
const ll MAX = 1000;
vector<vector<ll>> c(MAX, vector<ll>(MAX, maxC)); // Ma trận đồ thị
vector<bool> dd(MAX); // Đánh dấu các đỉnh, 0 = chưa thăm, 1 = đã thăm
vector<ll> d(MAX, maxC);
ll n, m, connected = true, minWeight = 0;
void LoadGraph()
{
    ll u, v, w;
    cin >> n >> m;
    // Khởi tạo ma trận trọng số
    for (ll i = 1; i <= n; i++)
        c[i][i] = 0;
    // Đọc dữ liệu và gán trọng số vào ma trận
    for (ll i = 1; i <= m; i++)
    {
        cin >> u >> v >> w;
        c[u][v] = w;
        c[v][u] = w;
    }
}
void PrimParallel()
{
    // Thuật toán song song tìm cây khung nhỏ nhất
    // Ban đầu coi như đồ thị chỉ chưá đỉnh 1
    d[1] = 0;
    for (ll iter = 1; iter <= n; iter++)
    {
        // tìm đỉnh gần cây T nhất trong số các đỉnh ngoài cây T
        ll u_local = 0, distanceMin = maxC, u = 0;
#pragma omp parallel
        {
            ll min_local = distanceMin;
#pragma omp for nowait
            for (ll i = 1; i <= n; i++)
            {
                if (dd[i] == 0 && d[i] < min_local)
                {
                    min_local = d[i];
                    u_local = i;
                }
            }
#pragma omp critical
            {
                if (min_local < distanceMin && u_local != 0)
                {
                    distanceMin = min_local;
                    u = u_local;
                }
            }
        }
        // Nêú không chọn được thì đồ thị không liên thông
        if (u == 0)
        {
            connected = false;
            break;
        }
        // Nêú chọn được thì đánh dâú lại và tính toán lại khoảng cách
        dd[u] = true;
        minWeight += d[u];
#pragma omp parallel for schedule(static)
        for (ll v = 1; v <= n; v++)
        {
            if (dd[v] == 0 && d[v] > c[u][v])
                d[v] = c[u][v];
        }
    }
}
void Result()
{
    // Hiển thị kết quả
    if (connected)
        cout << "Cay khung nho nhat cua do thi co tong trong so la: " << minWeight << endl;
    else
        cout << "Do thi khong lien thong" << endl;
}
int main()
{
    freopen("./Prim/input.txt", "r", stdin);
    LoadGraph();
    clock_t start = clock();
    PrimParallel();
    clock_t end = clock();
    Result();
    cout << "Time: " << end - start << " ms" << endl;
}