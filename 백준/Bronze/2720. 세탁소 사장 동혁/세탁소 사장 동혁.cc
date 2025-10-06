#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    int t;
    cin >> t;
    
    
    for(int i=0;i<t;i++){
        int c;
        cin >> c;
        
        int q,d,n,p;
        
        q = c / 25;
        c = c % 25;
        d = c / 10;
        c = c % 10;
        n = c / 5;
        p = c % 5;
        
        cout << q << " " << d << " " << n << " " << p << endl;
        
        
    }
    
    

    return 0;
}
