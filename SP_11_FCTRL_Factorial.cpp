#include <iostream>
using namespace std;

// 计算n!末尾零的个数
int countTrailingZeros(int n) {
    int count = 0;
    // 累加所有5的倍数、25的倍数、125的倍数等贡献的5的因子
    while (n > 0) {
        n /= 5;
        count += n;
    }
    return count;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    cin >> T;
    
    while (T--) {
        int n;
        cin >> n;
        cout << countTrailingZeros(n) << "\n";
    }
    
    return 0;
}
    