#include <iostream>
using namespace std;

int modPow(int a, int b) {
    int result = 1;
    a %= 10;
    
    while(b > 0) {
        if(b % 2 == 1)
            result = (result * a) % 10;
        
        a = (a * a) % 10;
        b /= 2;
    }
    
    return result;
}

int main() {
    int T, a, b;
    cin >> T;
    
    while(T--) {
        cin >> a >> b;
        int ans = modPow(a, b);
        if(ans == 0) ans = 10;
        cout << ans << "\n";
    }
}