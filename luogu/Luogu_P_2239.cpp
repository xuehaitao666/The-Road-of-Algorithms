#include <iostream>
#include <algorithm>
using namespace std;

int calculate(int n, int i, int j) {
    if(n == 1) return 1;
    int res_x = -1;
    int res_y = -1;
    if(i <= n / 2){
            res_x = i;
        }else{
            res_x = n + 1 - i;
        }
    if(j <= n / 2){
            res_y = j;
        }else{
            res_y = n + 1 - j;
        }
    return min(res_x, res_y);
}

int count(int n, int cal) {
    return n * n - (n - 2 * cal) * (n - 2 * cal);
}

int new_(int n, int i, int j, int cal) {
    int inner_n = n - 2 * cal;
    if (inner_n == 1) {
        return 1;
    }
    
    int x = i - cal;
    int y = j - cal;
    
    if (x == 1) { 
        return y;
    } else if (y == inner_n) {  
        return inner_n + (x - 1);
    } else if (x == inner_n) {  
        return 2 * inner_n - 1 + (inner_n - y);
    } else {  
        return 3 * inner_n - 2 + (inner_n - x);
    }
}

int main() {
    int n, i, j;
    cin >> n >> i >> j;
    int cal = calculate(n, i, j);
    int outer_count = count(n, cal - 1);
    int inner_num = new_(n, i, j, cal - 1);
    cout << outer_count + inner_num << endl;
    return 0;
}
    