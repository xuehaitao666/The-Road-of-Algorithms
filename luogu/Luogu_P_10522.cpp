#include <iostream>
#include <deque>
#include <vector>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<int> v(n);
        for (int i = 0; i < n; i++) {
            cin >> v[i];
        }
        long long sum = 0;
        deque<pair<int,int>> q;
        q.push_back({v[0], 1});
        for (int i = 1; i < n; i++) {
            int h = v[i];
            int cnt = 1;
            while (!q.empty() && q.back().first < h) {
                sum += q.back().second;
                q.pop_back();
            }
            if (!q.empty() && q.back().first == h) {
                int c = q.back().second;
                q.pop_back();
                sum += c;
                if (!q.empty()) sum += 1;
                q.push_back({h, c+1});
            }
            else {
                if (!q.empty()) sum += 1;
                q.push_back({h,1});
            }
        }

        cout << sum << "\n";
    }

    return 0;
}
