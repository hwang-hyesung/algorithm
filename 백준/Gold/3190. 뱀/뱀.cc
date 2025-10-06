#include <bits/stdc++.h>
using namespace std;

int n, k, l, t = 0;
vector<pair<int, int> > snake;
queue<pair<int, char> > dir;
int dy[] = {0, -1, 0, 1}, dx[] = {1, 0, -1, 0};
int apple[104][104];
int main() {
	memset(apple, 0, sizeof(apple));
    cin >> n >> k;
	for(int i = 0; i < k; i++){
		int x, y;
		cin >> x >> y;
		apple[x-1][y-1] = 1;
	}
	cin >> l;
	for(int i=0;i<l;i++){
		int x;
		char c;
		cin >> x >> c;
		dir.push({x, c});
	}
	
	int hx=0, hy=0, d=0;
	snake.push_back({hy, hx});
	while(1){		
		t++;
		
		int ny = hy + dy[d];
		int nx = hx + dx[d];
		
		if(ny < 0 || nx < 0 || ny >= n || nx >= n) {
			break;
		}
		
		if(find(snake.begin(), snake.end(), pair<int, int> {ny, nx}) != snake.end()) {
			break;
		}
		
		if(apple[ny][nx] != 1) {
			snake.erase(snake.begin());	
		}else{
			apple[ny][nx] = 0;
		}

		hy = ny;
		hx = nx;		
		snake.push_back({hy, hx});

		if(!dir.empty()){
			int x = dir.front().first;
			char c = dir.front().second;
			if(t == x){
				dir.pop();
				if(c == 'L'){
					d = (d+1)%4;
				}else if(c == 'D'){
					d = (d+3)%4;
				}
			}
		}
					
	}
	cout << t;
    return 0;
}
