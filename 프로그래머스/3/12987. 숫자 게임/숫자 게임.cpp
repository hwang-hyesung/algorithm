#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<int> A, vector<int> B) {
    int answer = 0;
    sort(A.begin(), A.end());
    sort(B.begin(), B.end());
    int len = A.size();
    for(int i=0,j=0;i<len;i++){
        while(j<len){
            if(A[i]<B[j]) {
                answer++;
                j++;
                break;
            }else {
                j++;
            }  
        }
    }
    return answer;
}