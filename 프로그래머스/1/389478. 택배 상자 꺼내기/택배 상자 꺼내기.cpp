#include <string>
#include <vector>

using namespace std;

int solution(int n, int w, int num) {
    num--;
    n--;
    int row = num/w+1;
    int col = row%2==1?(num%w):(w-num%w-1);
    int mxrow = n/w;
    if(mxrow%2==0) mxrow += (col <= n%w) ? 1 : 0;
    else  mxrow += (col >= w-n%w-1) ? 1 : 0;
    return mxrow-row+1;
}