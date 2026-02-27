#include <string>

using namespace std;

int countOne(int x){
    int cnt = 0;
    while(x){
        if(x % 2 == 1) cnt++;
        x /= 2;
    }
    return cnt;
}

int solution(int n) {
    int target = countOne(n);
    
    while(true){
        n++;
        if(countOne(n) == target)
            return n;
    }
}