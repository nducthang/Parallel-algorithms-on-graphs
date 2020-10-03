#include <iostream>
#include <vector>
#include <time.h>

using namespace std;
typedef long long ll;
const ll maxC = 9e9;
const ll MAX = 1000;
vector<vector<ll>> c(MAX, vector<ll>(MAX, maxC));
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
void Floyd()
{
    for (ll k = 1; k <= n; k++)
    {
        for (ll u = 1; u <= n; u++)
        {
            for (ll v = 1; v <= m; v++)
            {
                c[u][v] = min(c[u][v], c[u][k] + c[k][v]);
            }
        }
    }
}
void Result()
{
    if (c[s][f] == maxC)
        cout << "There is no path from " << s << " to " << f << endl;
    else
        cout << "Distance from " << s << " to " << f << " is: " << c[s][f] << endl;
}

int main()
{
    freopen("./Floyd/input.txt", "r", stdin);
    LoadGraph();
    clock_t start = clock();
    Floyd();
    clock_t end = clock();
    Result();
    cout << "Time: " << end - start << " ms" << endl;
}