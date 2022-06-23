/*
如果一个数列 至少有三个元素 ，并且任意两个相邻元素之差相同，则称该数列为等差数列。

例如，[1,3,5,7,9]、[7,7,7,7] 和 [3,-1,-5,-9] 都是等差数列。
给你一个整数数组 nums ，返回数组 nums 中所有为等差数组的 子数组 个数。

子数组 是数组中的一个连续序列。

 

示例 1：

输入：nums = [1,2,3,4]
输出：3
解释：nums 中有三个子等差数组：[1, 2, 3]、[2, 3, 4] 和 [1,2,3,4] 自身。
示例 2：

输入：nums = [1]
输出：0
 

提示：

1 <= nums.length <= 5000
-1000 <= nums[i] <= 1000
*/
#include <iostream>
#include <vector>
using namespace std;

/*
第一种解法：找规律
当整个数组为(1, 2, 3, 4, 5, 6)的时候,我们先取出前三个,(1, 2, 3)的等差数列的个数为1,(1, 2, 3, 4)的等差数列的个数为3,
(1, 2, 3, 4, 5)的等差数列的个数为6,(1, 2, 3, 4, 5, 6)的等差数列个数为10,以此类推我们可以很容易的发现在一个等差数列中加入一个数字,
如果还保持着等差数列的特性,每次的增量都会加1,如果刚加进来的数字与原先的序列构不成等差数列,就将增量置为0。
*/
class Solution1 {
public:
    int numberOfArithmeticSlices(vector<int>& nums) {
        //add为增量，三个数为等差数列，add为1，四个数为等差数列，add为2，以此类推
        int n = nums.size(), result = 0, add = 0;
        for (int i = 2; i < n; ++i) {
            if (nums[i - 1] - nums[i] == nums[i - 2] - nums[i - 1]) {
                result += ++add;
            }
            else {
                add = 0;
            }
        }
        return result;
    }
};

/*
第二种解法：两个for循环
*/
class Solution2 {
public:
    int numberOfArithmeticSlices(vector<int>& nums) {
        int result = 0;
        int n = nums.size();
        if (n < 3) {
            return 0;
        }
        for (int i = 0; i <= n - 3; ++i) {
            //等差数列的差，可以减少计算次数
            int diff = 0;
            if (nums[i + 1] - nums[i] == nums[i + 2] - nums[i + 1]) {
                diff = nums[i + 1] - nums[i];
                ++result;
            }
            else {
                continue;
            }
            for (int j = i + 3; j < n; ++j) {
                if (nums[j] - nums[j - 1] == diff) {
                    ++result;
                }
                else {
                    break;
                }
            }
        }
        return result;
    }
};

/*
第三种解法：动态规划
dp数组中的dp[i]表示以nums[i]元素结尾的等差数列的个数
dp[i]的计算公式：如果nums[i - 1] - nums[i] == nums[i - 2] - nums[i - 1]条件成立，那么表示能把nums[i]元素加入到以nums[i-1]元素结尾的等差数列中，
且还能在组成一个新的等差数列，dp[i] = dp[i - 1] + 1，如果条件不成立，dp[i] = 0
将dp中的每一个元素加起来就是答案
*/
class Solution3 {
public:
    int numberOfArithmeticSlices(vector<int>& nums) {
        int n = nums.size(), curNum = 0;
        vector<int> dp(n, 0);
        for (int i = 2; i < n; ++i) {
            if (nums[i - 1] - nums[i] == nums[i - 2] - nums[i - 1]) {
                dp[i] = dp[i - 1] + 1;
                curNum += dp[i];
            }
        }
        return curNum;
    }
};