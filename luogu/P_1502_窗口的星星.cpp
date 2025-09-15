#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

struct Node {
    int max_val;
    int lazy;
    Node() : max_val(0), lazy(0) {}
};

class SegmentTree {
private:
    vector<Node> tree;
    int n;

    void push(int node, int l, int r) {
        if (tree[node].lazy != 0) {
            tree[node].max_val += tree[node].lazy;
            if (l != r) {
                tree[2*node].lazy += tree[node].lazy;
                tree[2*node+1].lazy += tree[node].lazy;
            }
            tree[node].lazy = 0;
        }
    }

    void update_range(int node, int l, int r, int ul, int ur, int val) {
        push(node, l, r);
        if (ul > r || ur < l) return;
        if (ul <= l && r <= ur) {
            tree[node].lazy += val;
            push(node, l, r);
            return;
        }
        int mid = (l + r) / 2;
        update_range(2*node, l, mid, ul, ur, val);
        update_range(2*node+1, mid+1, r, ul, ur, val);
        tree[node].max_val = max(tree[2*node].max_val, tree[2*node+1].max_val);
    }

public:
    SegmentTree(int size) {
        n = 1;
        while (n < size) n <<= 1;
        tree.resize(2 * n);
    }

    void update(int l, int r, int val) {
        update_range(1, 0, n-1, l, r, val);
    }

    int get_max() {
        push(1, 0, n-1);
        return tree[1].max_val;
    }
};

struct Star {
    int x, y, l;
    Star(int x, int y, int l) : x(x), y(y), l(l) {}
};

// 事件类型：0-添加星星，1-移除星星
struct Event {
    int x, y_start, y_end, val, type;
    Event(int x, int y_start, int y_end, int val, int type) 
        : x(x), y_start(y_start), y_end(y_end), val(val), type(type) {}
    
    bool operator<(const Event& other) const {
        if (x != other.x) return x < other.x;
        return type < other.type; // 先处理添加事件，再处理移除事件
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int T;
    cin >> T;
    while (T--) {
        int n, W, H;
        cin >> n >> W >> H;
        
        vector<Star> stars;
        set<int> y_coords;
        
        for (int i = 0; i < n; ++i) {
            int x, y, l;
            cin >> x >> y >> l;
            stars.emplace_back(x, y, l);
            y_coords.insert(y);
            y_coords.insert(y + H);
        }
        
        // 坐标压缩
        vector<int> y_list(y_coords.begin(), y_coords.end());
        sort(y_list.begin(), y_list.end());
        int y_size = y_list.size();
        
        // 创建事件
        vector<Event> events;
        for (const auto& star : stars) {
            int x1 = star.x;
            int x2 = star.x + W;
            int y1 = star.y;
            int y2 = star.y + H;
            
            // 查找y坐标在压缩后的索引
            int y_start = lower_bound(y_list.begin(), y_list.end(), y1) - y_list.begin();
            int y_end = lower_bound(y_list.begin(), y_list.end(), y2) - y_list.begin() - 1;
            
            if (y_start <= y_end) {
                events.emplace_back(x1, y_start, y_end, star.l, 0);
                events.emplace_back(x2, y_start, y_end, star.l, 1);
            }
        }
        
        sort(events.begin(), events.end());
        
        // 处理事件，计算最大亮度和
        SegmentTree st(y_size);
        int max_bright = 0;
        int i = 0;
        int event_count = events.size();
        
        while (i < event_count) {
            int current_x = events[i].x;
            
            // 处理同一x坐标的所有事件
            while (i < event_count && events[i].x == current_x) {
                if (events[i].type == 0) {
                    st.update(events[i].y_start, events[i].y_end, events[i].val);
                } else {
                    st.update(events[i].y_start, events[i].y_end, -events[i].val);
                }
                i++;
            }
            
            max_bright = max(max_bright, st.get_max());
        }
        
        cout << max_bright << endl;
    }
    
    return 0;
}
