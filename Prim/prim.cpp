#include <iostream>
#include <vector>

using namespace std;
typedef long long ll;
const ll maxC = 9e9;
const ll MAX = 1000;

ll n, m, minWeight = 0;
bool connected;
vector<vector<ll>> c(MAX, vector<ll>(MAX, maxC));
vector<ll> d(MAX, maxC);
vector<bool> dd(MAX);

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

void Prim()
{
    // Thuật toán tuân tự Prim tìm cây khung nhỏ nhất
    // Ban đầu coi như cây chỉ chưá đỉnh 1
    d[1] = 0;
    connected = true;
    for (ll iter = 1; iter <= n; iter++)
    {
        // Tìm đỉnh gần cây T nhất trong số các đỉnh ngoài cây
        ll u = 0, distanceMin = maxC;
        for (ll i = 1; i <= n; i++)
        {
            if (dd[i] == 0 && d[i] < distanceMin)
            {
                u = i;
                distanceMin = d[i];
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
    Prim();
    Result();
}