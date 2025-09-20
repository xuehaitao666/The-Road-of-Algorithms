# 分治策略

# 1.交换排序问题

## 题目描述
对于一个 `1` 到 `n` 的排列，我们引入了一种新的排序方式，称为**交换排序**：  
每次操作可以选择排列中任意两个**差的绝对值恰好为 1** 的数字进行交换。  
请计算对该排列进行升序排序时，所需交换操作次数的最小值。

**说明**：1 到 n 的排列中，每个数均出现且仅出现一次。

## 输入格式
- 第一行输入一个正整数 `T`，表示数据组数。
- 对于每组数据：
  1. 第一行输入一个整数 `n`，表示排列的长度。
  2. 第二行输入 `n` 个整数，为 `1` 到 `n` 的一个排列。

**数据约束**：所有数据的 `n` 之和不大于 `1e5`。

## 输出格式
每组数据输出一行一个整数，代表最小交换次数。

## 测试样例
### 输入
```
2
3
1 3 2
5
5 3 2 1 4
```

### 输出
```
1
7
```

## 题目分析与思路分析（补充）
- 核心观察：每次只能交换相邻数字（差的绝对值为 1），因此该问题等价于计算排列的**逆序对数量**。📌
- 例如：
  - 第一组样例 `[1,3,2]` 中，逆序对为 `(3,2)`，数量为 1，故输出 1。
  - 第二组样例 `[5,3,2,1,4]` 中，逆序对数量为 7（(5,3),(5,2),(5,1),(5,4),(3,2),(3,1),(2,1)），故输出 7。
- 求解方法：需使用高效的逆序对计数算法（如归并排序、树状数组），时间复杂度为 `O(n log n)`，以满足数据规模要求。


## 代码
    #include <iostream>
    #include <vector>
    using namespace std;


    long long mergeCount(vector<int>& arr, vector<int>& temp, int left, int mid, int right) {
        int i = left;
        int j = mid + 1;
        int k = left;
        long long count = 0;
        while (i <= mid && j <= right) {
            if (arr[i] <= arr[j]) {
                temp[k++] = arr[i++];
            }else {
                temp[k++] = arr[j++];
                count +=(mid - i + 1);
            }
        }
        while (i <= mid) {
            temp[k++] = arr[i++];
        }
        while (j <= right) {
            temp[k++] = arr[j++];
        }
        for (int i = left; i <= right; i++) {
            arr[i] = temp[i];
        }
        return count;
    }


    long long  merge_sort_count(vector<int>& arr, vector<int>& temp, int left, int right) {
        long long count = 0;
        if (left < right) {
            int mid = (left + right) / 2;
            count += merge_sort_count(arr, temp, left, mid);
            count += merge_sort_count(arr, temp, mid + 1, right);
            count += mergeCount(arr, temp, left, mid, right);
        }
        return count;
    }


    int main() {
        int T;
        cin >> T;
        while (T--) {
            int n;
            cin >> n;
            vector<int> v(n);
            for(int i = 0; i < n; i++) {
                cin >> v[i];
            }
            long long count = 0;
            vector<int> temp(n);
            count = merge_sort_count(v, temp, 0, n - 1);
            cout << count << "\n";
        }
        return 0;
    }


## tip：
- 首先这一题，最重要的一点就是我们需要知道这道题目的思路。交换并且差值只能为1，我们可以在模拟的时候发现，似乎和逆序数有关联（也是一种经验的总结）
- 本题还需要注意的就是题目数据的问题，当然这种问题经常会出现，写题目的时候注意一下就行了，如果没过的话就需要注意一下是不是数据范围的问题了。
- 其次就是，就算我们知道了是逆序对的思路了，我们仍然需要注意本题的一个时间复杂度，如果只是使用两个for循环来查看有多少个逆序对的话，就会被这道题目卡掉。
- 通过分治思想，我们发现可以把这些数组全部分成一半一半的，先算内部的逆序对，然后再合并的时候来计算总的逆序对。然后我们不难发现这就是归并排序的思想，所以如果这道题目你用归并排序，记录交换次数也可以算出这道题目。


---

# 2.最大连续和
## 题目描述
给出一个数列，请寻找整数 \(i, j\)（\(1 \leq i \leq j \leq n\)），使得 \(\sum_{k=i}^{j} a_k\) 最大。

> 我求求你们了，不要用动态规划好不好

## 输入格式
本题有多组数据。
1. 第一行为整数 \(T\)，表示数据组数。
2. 对于每组数据：
   - 第一行为整数 \(n\)，代表数列的数字个数。
   - 接下来一行有 \(n\) 个整数，表示数列的元素。

**数据约束**：所有数据的 \(n\) 之和不超过 \(10^5\)，数列元素的绝对值不超过 \(10^4\)。

## 输出格式
每组数据输出一行一个整数，表示最大的 \(\sum_{k=i}^{j} a_k\)。

## 测试样例
### 输入
```
2
4
1 2 -1 10
3
-1 -2 -3
```

### 输出
```
12
-1
```

## 题目注解
> 我知道你很急着用动态规划，但是这节课讲了分治，所以你先别急.jpg

## 代码
    #include <iostream>
    #include <vector>
    #include <climits>
    #include <algorithm> // 用于max函数

    using namespace std;
    using ll = long long;
    ll maxSum(const vector<ll>& nums, ll left, ll right, ll mid) {
        ll leftSum = LONG_LONG_MIN;
        ll currentSum = 0;
        for (ll i = mid; i >= left; i--) {
            currentSum += nums[i];
            if (currentSum > leftSum) {
                leftSum = currentSum;
            }
        }
        ll rightSum = LONG_LONG_MIN;
        currentSum = 0;
        for(ll i = mid + 1; i <= right; i++) {
            currentSum += nums[i];
            if (currentSum > rightSum) {
                rightSum = currentSum;
            }
        }
        return leftSum + rightSum;
    }
    ll maxSumTwo(const vector<ll>& nums, ll left, ll right) {
        if(left == right) {
            return nums[left];
        }
        ll mid = left + (right - left) / 2;
        return max({
            maxSumTwo(nums, left, mid),
            maxSumTwo(nums, mid + 1, right),
            maxSum(nums, left, right, mid)
        });
    }
    int main() {
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        int T;
        cin >> T;
        while (T--) {
            int n;
            cin >> n;
            vector<ll> v(n);
            for (int i = 0; i < n; i++) {
                cin >> v[i];
            }
            cout << maxSumTwo(v,0,n-1) << "\n";
        }
        return 0;
    }

## 代码思路：
# 分治算法解决最大子数组问题

## 算法解释

分治算法解决最大子数组问题的核心思路是将问题分解为三个子问题：

1. **左半部分的最大子数组和**：递归处理数组左半部分
2. **右半部分的最大子数组和**：递归处理数组右半部分
3. **跨越中间点的最大子数组和**：这是合并步骤的关键，需要单独计算

## 关键函数解析

### maxCrossingSum 函数：
- 计算跨越中间点的最大子数组和
- 从中间点向左扩展，找到左侧最大子数组和
- 从中间点向右扩展，找到右侧最大子数组和
- 返回左右两部分的和（即跨越中间点的最大子数组和）

### maxSubarraySum 函数：
- 递归函数，实现分治逻辑
- 基本情况：当子数组只有一个元素时，返回该元素
- 递归情况：将数组分为两半，分别计算左半部分、右半部分和跨越中间的最大子数组和，返回三者中的最大值

### main 函数：
- 处理多组输入数据
- 读取每组数据并调用分治函数计算结果
- 输出每组数据的最大子数组和

## 时间复杂度分析

- 每次递归将问题规模减半，递归深度为 O(log n)
- 每层递归中，maxCrossingSum 函数需要 O(n) 时间
- 总体时间复杂度为 O(n log n)

这种分治方法虽然比动态规划的 O(n) 时间复杂度稍高，但很好地体现了分治算法 "分而治之" 的思想，适用于理解递归和分治策略的应用。

---
        