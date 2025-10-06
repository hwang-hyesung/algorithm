#include <bits/stdc++.h>
using namespace std;
int r, c, t, arr[51][51], temp[51][51], ret;
vector<pair<int, int> > v1, v2;

int dy1[] = {0, -1, 0, 1};
int dx1[] = {1, 0, -1, 0};
int dy2[] = {0, 1, 0, -1};
int dx2[] = {1, 0, -1, 0}; 

int main() {
    cin >> r >> c >> t;
    bool flag = 1; 

	for(int i = 0; i < r; i++){
		for(int j=0;j < c; j++){
			cin >> arr[i][j];
			if(arr[i][j] == -1){
                if(flag){
                	int cnt = 0; 
				    int y = i; 
				    int x = j;
				    while(true){ 
				        int ny = y + dy1[cnt];
				        int nx = x + dx1[cnt];  
				        if(ny == i && nx == j) break;
				        if(ny < 0 || ny >= r || nx < 0 || nx >= c){
				            cnt++; 
				            ny = y + dy1[cnt];
				            nx = x + dx1[cnt];
				        } 
				        if(ny == i && nx == j) break;
				        y = ny; 
						x = nx; 
				        v1.push_back({ny, nx});
				    }
                	flag = false; 
	            }else {
	            	int cnt = 0; 
				    int y = i; 
				    int x = j;
				    while(true){ 
				        int ny = y + dy2[cnt];
				        int nx = x + dx2[cnt];  
				        if(ny == i && nx == j) break;
				        if(ny < 0 || ny >= r || nx < 0 || nx >= c){
				            cnt++; 
				            ny = y + dy2[cnt];
				            nx = x + dx2[cnt];
				        } 
				        if(ny == i && nx == j) break;
				        y = ny; 
						x = nx; 
				        v2.push_back({ny, nx});
				    }
				}
	        }
		}
	}
	
	while(t--){
		memset(temp, 0, sizeof(temp));
	    queue<pair<int, int> > q; 
	    for(int i = 0; i < r; i++){
	        for(int j = 0; j < c; j++){
	            if(arr[i][j] != -1 && arr[i][j]){
	                q.push({i, j});
	            }
	        }
	    }
	    while(q.size()){ 
	    	int y, x;
	        y = q.front().first;
			x = q.front().second; 
			q.pop(); 
	        int spread = arr[y][x] / 5; 
	        for(int i = 0; i < 4; i++){
	            int ny = y + dy1[i];
	            int nx = x + dx1[i]; 
	            if(ny < 0 || ny >= r || nx < 0 || nx >= c || arr[ny][nx] == -1) continue; 
	            temp[ny][nx] += spread;
	            arr[y][x] -= spread;
	        }
	    }
	    for(int i = 0; i < r; i++){
	        for(int j = 0; j < c; j++){
	            arr[i][j] += temp[i][j];
	        }
	    }
	    
	    for(int i = v1.size() - 1; i > 0; i--){
	        arr[v1[i].first][v1[i].second] = arr[v1[i - 1].first][v1[i - 1].second];
	    } 
	    arr[v1[0].first][v1[0].second] = 0;
	    
	    for(int i = v2.size() - 1; i > 0; i--){
	        arr[v2[i].first][v2[i].second] = arr[v2[i - 1].first][v2[i - 1].second];
	    } 
	    arr[v2[0].first][v2[0].second] = 0;
	}
	 
	for(int i = 0; i < r; i++){
        for(int j = 0; j < c; j++){
            if(arr[i][j] != -1) ret += arr[i][j];
        }
    }   
	cout << ret;
    return 0;
}
