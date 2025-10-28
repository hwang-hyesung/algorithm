#include <string>
#include <vector>
#include <map>
#include <unordered_set>

using namespace std;

int getNs(int N, int idx){
    int res = N;
    for(int i=1;i<idx;i++){
        res = res*10 + N;
    }
    return res;
}

int solution(int N, int number) {
    int answer = 0;
    if (N == number) return 1; 
    
    vector< unordered_set<int> > v(8); 
    
    v[0].insert(N);
    
    for (int k = 1; k < 8; k++) {
        v[k].insert(getNs(N, k+1));

        for (int i = 0; i < k; i++) {
            int j = k - 1 - i;
            for (int a : v[i]) {
                for (int b : v[j]) {
                    v[k].insert(a + b);
                    v[k].insert(a - b);
                    v[k].insert(a * b);
                    if (b != 0) v[k].insert(a / b);
                }
            }
        }

        if (v[k].find(number) != v[k].end())
            return k + 1;
    }

    return -1; 
}