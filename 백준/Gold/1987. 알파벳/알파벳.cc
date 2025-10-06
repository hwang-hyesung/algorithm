#include <bits/stdc++.h>
using namespace std;
int r, c, mx=0; 
int dy[] = {-1, 0, 1, 0};
int dx[] = {0, -1, 0, 1};
char arr[21][21];
int visited[26];

void dfs(int y, int x, int count) {
    mx = max(mx, count);

    for (int i = 0; i < 4; i++) {
        int ny = y + dy[i];
        int nx = x + dx[i];
        
		if(ny<0 || ny>=r || nx<0 || nx>=c || visited[arr[ny][nx]-'A']) continue;
        if (!visited[arr[ny][nx]-'A']) {         
            visited[arr[ny][nx]-'A'] = true;
            dfs(ny, nx, count + 1);
            visited[arr[ny][nx]-'A'] = false;   
        }   
    }
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	memset(visited, 0, sizeof(visited));
	
    cin >> r >> c;
    for(int i=0;i<r;i++){
    	string str;
    	cin >> str;
    	for(int j=0;j<c;j++){
    		arr[i][j] = str[j];
		}
	}
    visited[arr[0][0]-'A'] = 1;
	dfs(0,0,1);
	cout << mx;
    return 0;
    
}