#include <iostream>
#include <string>
#include <vector>

using namespace std;

int solution(vector<int> cookie) {
    int answer = 0;
    int n = cookie.size();

    for (int m = 0; m < n - 1; m++) {
        int l = m;
        int r = m + 1;

        int left = cookie[l];
        int right = cookie[r];

        while (true) {
            if (left == right) {
                answer = max(answer, left);
            }

            if (left <= right) {
                l--;
                if (l < 0) break;
                left += cookie[l];
            } else {
                r++;
                if (r >= n) break;
                right += cookie[r];
            }
        }
    }

    return answer;
}
