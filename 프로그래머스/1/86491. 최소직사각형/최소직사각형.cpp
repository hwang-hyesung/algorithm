#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<vector<int>> sizes) {
    int min = 0;
    int max = 0;
    for(vector<int> size : sizes){
        
        sort(size.begin(), size.end());
        if(min < size[0]) min = size[0];
        if(max < size[1]) max = size[1];
        
    }
    return min*max;
}