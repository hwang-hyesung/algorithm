#include <string>
#include <vector>

using namespace std;

int solution(int chicken) {
    int answer = 0, coupon = chicken;
    
    while(true){
        int nc = coupon/10;
        if(nc==0) break;
        answer += nc;
        coupon = coupon%10 + nc; 
    }
    return answer;
}