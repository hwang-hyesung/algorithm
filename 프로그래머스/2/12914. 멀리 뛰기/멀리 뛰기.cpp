#include <string>
#include <vector>

using namespace std;

long long solution(int n) {
    long long answer = 0;
    vector<int> v;
    v.push_back(0);
    v.push_back(1);
    v.push_back(2);
    for(int i=3;i<=n;i++){
        v.push_back((v[i-1] + v[i-2])%1234567);
    }
    return v[n];
}