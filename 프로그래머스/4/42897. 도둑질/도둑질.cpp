#include <vector>
#include <algorithm>
using namespace std;

int robLinear(const vector<int>& money, int start, int end) {
    int prev = 0;
    int curr = 0;
    for (int i = start; i <= end; ++i) {
        int skip = max(prev, curr);
        int take = prev + money[i];
        prev = skip;
        curr = take;
    }
    return max(prev, curr);
}

int solution(vector<int> money) {
    int n = money.size();
    if (n == 1) return money[0]; 

    int case1 = robLinear(money, 0, n - 2);
    int case2 = robLinear(money, 1, n - 1);
    return max(case1, case2);
}
