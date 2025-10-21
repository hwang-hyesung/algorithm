
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;

struct Product
{
    int id;
    int revenue;
    int dest;
    int profit;
    struct Comparator
    {
        bool operator()(const Product &a, const Product &b)
        {
            if (a.profit == b.profit)
            {
                return a.id > b.id;
            }
            return a.profit < b.profit;
        }
    };
};

int q, n, origin = 0;
int a[2001][2001], d[2001];
bool ismade[30001], iscanceled[30001];
priority_queue<Product, vector<Product>, Product::Comparator> prod;

void distance()
{
    fill(d, d + 2001, 1e9);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    d[origin] = 0;
    pq.push({0, origin});

    while (!pq.empty())
    {
        auto [dist, cur] = pq.top();
        pq.pop();
        if (d[cur] < dist)
            continue;

        for (int i = 0; i < n; i++)
        {
            if (a[cur][i] == 1e9)
                continue;
            if (d[i] > d[cur] + a[cur][i])
            {
                d[i] = d[cur] + a[cur][i];
                pq.push({d[i], i});
            }
        }
    }
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin >> q;
    fill(&a[0][0], &a[0][0] + 2001 * 2001, (int)1e9);
    int op;
    while (q--)
    {
        cin >> op;
        if (op == 100)
        {
            int m, v, u, w;
            cin >> n >> m;
            for (int i = 0; i < m; i++)
            {
                cin >> v >> u >> w;
                a[v][u] = min(a[v][u], w);
                a[u][v] = min(a[u][v], w);
            }
            distance();
        }
        else if (op == 200)
        {
            Product p;
            cin >> p.id >> p.revenue >> p.dest;
            p.profit = p.revenue - d[p.dest];
            prod.push(p);
            ismade[p.id] = true;
        }
        else if (op == 300)
        {
            int id;
            cin >> id;
            if (ismade[id])
            {
                iscanceled[id] = true;
            }
        }
        else if (op == 400)
        {
            bool flag = false;
            while (!prod.empty())
            {
                Product p = prod.top();
                if (p.profit < 0)
                {
                    break;
                }
                prod.pop();
                if (!iscanceled[p.id])
                {
                    cout << p.id << "\n";
                    flag = true;
                    break;
                }
            }
            if (!flag)
                cout << -1 << "\n";
        }
        else if (op == 500)
        {
            int norigin;
            cin >> norigin;
            origin = norigin;
            distance();
            vector<Product> products;
            while (!prod.empty())
            {
                if (!iscanceled[prod.top().id])
                    products.push_back(prod.top());
                prod.pop();
            }
            for (Product p : products)
            {
                p.profit = p.revenue - d[p.dest];
                prod.push(p);
            }
        }
    }
    return 0;
}
