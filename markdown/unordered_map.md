# <mark>**unordered_map**</mark> 📢

# 454. 四数相加 II
## 题目描述
给你四个整数数组 nums1、nums2、nums3 和 nums4 ，数组长度都是 n ，请你计算有多少个元组 (i, j, k, l) 能满足：
- 0 <= i, j, k, l < n
- nums1[i] + nums2[j] + nums3[k] + nums4[l] == 0


## 示例
### 示例 1
- 输入：nums1 = [1,2], nums2 = [-2,-1], nums3 = [-1,2], nums4 = [0,2]
- 输出：2
- 解释：
  两个元组如下：
  1. (0, 0, 0, 1) -> nums1[0] + nums2[0] + nums3[0] + nums4[1] = 1 + (-2) + (-1) + 2 = 0
  2. (1, 1, 0, 0) -> nums1[1] + nums2[1] + nums3[0] + nums4[0] = 2 + (-1) + (-1) + 0 = 0

### 示例 2
- 输入：nums1 = [0], nums2 = [0], nums3 = [0], nums4 = [0]
- 输出：1


## 提示
- n == nums1.length == nums2.length == nums3.length == nums4.length
- 1 <= n <= 200
- -2²⁸ <= nums1[i], nums2[i], nums3[i], nums4[i] <= 2²⁸


## 代码
    #include <vector>
    #include <unordered_map>

    using namespace std;

    class Solution {
    public:
        int fourSumCount(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3, vector<int>& nums4) {
            int n = nums1.size();
            unordered_map<int, int> sumCount; 😐这个地方应该使用map，因为相同的数字可能会出现重复，如果用set的话，可能会被直接删除，所以使用map，键值对就可以记录对应的值以及出现的次数。
            for(int i = 0; i < n; i++){
                for(int j = 0; j < n; j++){
                    int sum = nums3[i] + nums4[j];
                    sumCount[sum]++;
                }
            }
            
            int cnt = 0;
            for(int i = 0; i < n; i++){
                for(int j = 0; j < n; j++){
                    int target = -(nums1[i] + nums2[j]);
                    if(sumCount.find(target) != sumCount.end()){
                        cnt += sumCount[target];
                    }
                }
            }
            
            return cnt;
        }
    };
