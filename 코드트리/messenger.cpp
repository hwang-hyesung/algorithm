#include <iostream>
#include <vector>

using namespace std;

#define MAX_N 100001
#define MAX_D 22

int n, q;
int a[MAX_N], p[MAX_N], val[MAX_N];
bool noti[MAX_N];
int nx[MAX_N][MAX_D];

void init()
{
    for (int i = 1; i <= n; i++)
    {
        cin >> p[i];
    }
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        if (a[i] > 20)
            a[i] = 20;
    }

    for (int i = 1; i <= n; i++)
    {
        int cur = i;
        int x = a[i];
        nx[cur][x]++;
        while (p[cur] && x)
        {
            cur = p[cur];
            x--;
            if (x)
                nx[cur][x]++;
            val[cur]++;
        }
    }
}

void toggle_noti(int chat)
{
    if (noti[chat])
    {
        int cur = p[chat];
        int num = 1;
        while (cur)
        {
            for (int i = num; i <= 21; i++)
            {
                val[cur] += nx[chat][i];
                if (i > num)
                    nx[cur][i - num] += nx[chat][i];
            }
            if (noti[cur])
                break;
            cur = p[cur];
            num++;
        }
        noti[chat] = false;
    }
    else
    {
        int cur = p[chat];
        int num = 1;
        while (cur)
        {
            for (int i = num; i <= 21; i++)
            {
                val[cur] -= nx[chat][i];
                if (i > num)
                    nx[cur][i - num] -= nx[chat][i];
            }
            if (noti[cur])
                break;
            cur = p[cur];
            num++;
        }
        noti[chat] = true;
    }
}

void change_power(int chat, int power)
{
    int bef_power = a[chat];
    power = min(power, 20);
    a[chat] = power;

    nx[chat][bef_power]--;
    if (!noti[chat])
    {
        int cur = p[chat];
        int num = 1;
        while (cur)
        {
            if (bef_power >= num)
                val[cur]--;
            if (bef_power > num)
                nx[cur][bef_power - num]--;
            if (noti[cur])
                break;
            cur = p[cur];
            num++;
        }
    }

    nx[chat][power]++;
    if (!noti[chat])
    {
        int cur = p[chat];
        int num = 1;
        while (cur)
        {
            if (power >= num)
                val[cur]++;
            if (power > num)
                nx[cur][power - num]++;
            if (noti[cur])
                break;
            cur = p[cur];
            num++;
        }
    }
}

void change_parent(int chat1, int chat2)
{
    bool bef_noti1 = noti[chat1];
    bool bef_noti2 = noti[chat2];

    if (!noti[chat1])
        toggle_noti(chat1);
    if (!noti[chat2])
        toggle_noti(chat2);

    swap(p[chat1], p[chat2]);

    if (!bef_noti1)
        toggle_noti(chat1);
    if (!bef_noti2)
        toggle_noti(chat2);
}

void print_count(int chat)
{
    cout << val[chat] << "\n";
}

int main()
{
    cin >> n >> q;
    while (q--)
    {
        int query;
        cin >> query;
        if (query == 100)
        {
            init();
        }
        else if (query == 200)
        {
            int chat;
            cin >> chat;
            toggle_noti(chat);
        }
        else if (query == 300)
        {
            int chat, power;
            cin >> chat >> power;
            change_power(chat, power);
        }
        else if (query == 400)
        {
            int chat1, chat2;
            cin >> chat1 >> chat2;
            change_parent(chat1, chat2);
        }
        else if (query == 500)
        {
            int chat;
            cin >> chat;
            print_count(chat);
        }
    }
    return 0;
}
