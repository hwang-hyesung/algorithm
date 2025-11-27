#include <iostream>
#include <vector>
using namespace std;

int take(const vector<int>& sticker, int start, int end) {
    int prev = 0;
    int curr = 0;
    for (int i = start; i <= end; ++i) {
        int skip = max(prev, curr);
        int take = prev + sticker[i];
        prev = skip;
        curr = take;
    }
    return max(prev, curr);
}

int solution(vector<int> sticker)
{
    int n = sticker.size();
    if (n == 1) return sticker[0]; 

    int case1 = take(sticker, 0, n - 2);
    int case2 = take(sticker, 1, n - 1);
    return max(case1, case2);
}