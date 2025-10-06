#include <bits/stdc++.h>
using namespace std;
long long n, c, a[31], ret;
vector<int> v, v2;

void go(int s, int e, vector<int> &v, int sum){
	if(sum > c) return; 
	if(s > e){
		v.push_back(sum); return;
	}  
	go(s + 1, e, v, sum + a[s]);  
	go(s + 1, e, v, sum); 
	return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n >> c;
    for (long long i = 0; i < n; i++) {
        cin >> a[i];
    }

    go(0, n / 2 - 1, v, 0); 
	go(n / 2, n - 1, v2, 0);
	sort(v.begin(), v.end()); 
	sort(v2.begin(), v2.end()); 
	for(long long i = 0; i < v.size(); i++){
		if(c - v[i] >= 0)ret += ((int)(upper_bound(v2.begin(),v2.end(),c - v[i]) - v2.begin()));
	}
	cout << ret << "\n";  
    
    return 0;
}
