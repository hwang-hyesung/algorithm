#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

bool check(vector<vector<string>> park, int r, int c, int m){
    if(r+m > park.size() || c+m > park[0].size()) return false;
    
    for(int i=r;i<r+m;i++){
        for(int j=c;j<c+m;j++){
            if(park[i][j]!="-1") return false;
        }
    }
    return true;
}

int solution(vector<int> mats, vector<vector<string>> park) {
    int answer = -1;
    int h = park.size(), w = park[0].size();
    sort(mats.rbegin(), mats.rend());
    for(int m : mats){
        for(int i=0;i<h;i++){
            for(int j=0;j<w;j++){
                cout << m << i << j << "\n";
                if(check(park, i, j, m)){
                    return m;
                }
            }
        }
    }
    return answer;
}