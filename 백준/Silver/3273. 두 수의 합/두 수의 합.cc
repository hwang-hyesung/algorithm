#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
	vector<int> v(n);
	for(int i=0;i<n;i++){
		cin >> v[i];
	}
	int x;
	cin >> x;
	
	sort(v.begin(), v.end());
	
    int l = 0, r = n-1, cnt = 0;

    while(l < r){
        if(v[l] + v[r] == x){
        	r--;
        	cnt++;
		}else if(v[l] + v[r] > x) r--;
        else if(v[l] + v[r] < x) l++;
    }

    cout << cnt << "\n";
    return 0;
}
