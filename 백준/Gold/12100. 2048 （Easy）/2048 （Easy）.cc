#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cmath>
#include <cstring>
using namespace std;
const int MAX_N = 21;

int n,a[MAX_N][MAX_N], ret = -1e9;

void move(int d, int cnt, int board[][MAX_N]){
    // cout << d << " " << cnt << "\n";
    // for(int i=0;i<n;i++){
    //     for(int j=0;j<n;j++){
    //         cout << board[i][j] << " ";
    //     }
    //     cout <<"\n";
    // }
    // cout << "\n";
    if(cnt == 5) {
        int mx = -1e9;
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                mx = max(mx, board[i][j]);
            }
        }
        ret = max(ret, mx);
        return;
    }
    int temp[MAX_N][MAX_N];
    bool visited[MAX_N][MAX_N];
    memset(temp, 0, sizeof(temp));
    memset(visited, true, sizeof(visited));
    if(d==0){ //상
        for(int i=0;i<n;i++){
            queue<int> q;
            for(int j=0;j<n;j++){
                if(board[j][i]!=0) {
                    q.push(board[j][i]);
                }
            }
            int row=0;
            while(!q.empty()){
                if(row>0 && temp[row-1][i]==q.front() && visited[row-1][i]){
                    temp[row-1][i] += q.front();    
                    visited[row-1][i] = false;
                } 
                else temp[row++][i] = q.front(); 
                
                q.pop();
            }
        }

    }else if(d==1){ // 하
        for(int i=0;i<n;i++){
            queue<int> q;
            for(int j=n-1;j>=0;j--){
                if(board[j][i]!=0) q.push(board[j][i]);
            }
            int row=n-1;
            while(!q.empty()){
                if(row<n && temp[row+1][i]==q.front() && visited[row+1][i]){
                    temp[row+1][i] += q.front();    
                    visited[row+1][i] = false;
                } 
                else temp[row--][i] = q.front(); 
                q.pop();
            }
            
        }
    }else if(d==2){ // 좌
        for(int i=0;i<n;i++){
            queue<int> q;
            for(int j=0;j<n;j++){
                if(board[i][j]!=0) q.push(board[i][j]);
            }
            int col=0;
            while(!q.empty()){
                if(col>0 && temp[i][col-1]==q.front() && visited[i][col-1]){
                    temp[i][col-1] += q.front();    
                    visited[i][col-1] = false;
                } 
                else temp[i][col++] = q.front(); 
                q.pop();
            }
            
        }
    }else if(d==3){ // 우
        for(int i=0;i<n;i++){
            queue<int> q;
            for(int j=n-1;j>=0;j--){
                if(board[i][j]!=0) q.push(board[i][j]);
            }
            int col = n-1;
            while(!q.empty()){
                if(col<n && temp[i][col+1]==q.front() && visited[i][col+1]){
                    temp[i][col+1] += q.front();    
                    visited[i][col+1] = false;
                } 
                else temp[i][col--] = q.front(); 
                q.pop();
            }
        }
    }
    
    for(int i=0;i<4;i++){
        move(i, cnt+1, temp);
    }
    return;
}

int main() {
    cin >> n;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin >> a[i][j];
        }
    }
    for(int i=0;i<4;i++){
        int board[MAX_N][MAX_N];
        memcpy(board, a, sizeof(a));
        move(i, 0, board);
    }
    cout << ret;
    return 0;
}
