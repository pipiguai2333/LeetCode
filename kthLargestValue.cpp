/*
给你一个二维矩阵 matrix 和一个整数 k ，矩阵大小为 m x n 由非负整数组成。

矩阵中坐标 (a, b) 的 值 可由对所有满足 0 <= i <= a < m 且 0 <= j <= b < n 的元素 matrix[i][j]（下标从 0 开始计数）执行异或运算得到。

请你找出 matrix 的所有坐标中第 k 大的值（k 的值从 1 开始计数）。

 

示例 1：

输入：matrix = [[5,2],[1,6]], k = 1
输出：7
解释：坐标 (0,1) 的值是 5 XOR 2 = 7 ，为最大的值。
示例 2：

输入：matrix = [[5,2],[1,6]], k = 2
输出：5
解释：坐标 (0,0) 的值是 5 = 5 ，为第 2 大的值。
示例 3：

输入：matrix = [[5,2],[1,6]], k = 3
输出：4
解释：坐标 (1,0) 的值是 5 XOR 1 = 4 ，为第 3 大的值。
示例 4：

输入：matrix = [[5,2],[1,6]], k = 4
输出：0
解释：坐标 (1,1) 的值是 5 XOR 2 XOR 1 XOR 6 = 0 ，为第 4 大的值。
 

提示：

m == matrix.length
n == matrix[i].length
1 <= m, n <= 1000
0 <= matrix[i][j] <= 106
1 <= k <= m * n
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
这道题有两步：：①先算出异或坐标值；②就是TOPK问题求解
如何算出异或坐标值？有两种方法：
1、先从左到右将二维数组中的每一列中的值异或上一列对应的值，把值保存在原数组中，然后从上到下将二维数组中的每一行的值异或上一行对应的值，把值保存在原数组中，
这样原数组中保存的就是异或坐标值。这种方法可以节省空间，但做了两次双层循环。
2、通过公式来求解：dp[i][j] = dp[i-1][j]^dp[i][j-1]^dp[i-1][j-1]^matrix[i][j]；这种方式要一个二维数组来保存值，其本质上是一种动态规划的思想，
小技巧可以在创造的数组的左边与上边插入一排0，这样就可以不用考虑边界问题。
TOPK问题的几种求解思路：
1、排序，将所有的结果排序。可以使用c++库中的sort()函数，还可以手写排序算法（如果能优化到比sort()更加高效的话可以考虑，不然还是使用sort()，不优化排序算法的话有可能超时）
2、优先队列（堆），建立一个k小根堆，先填满小根堆，对于其他的数据，如果小于或等于堆顶元素，不考虑，大于堆顶元素，则将堆顶元素弹出，将数据放入堆中。
可以使用自带的priority_queue，还可以手写一个堆排序。
3、快速选择算法，排序最常用的是快速排序算法，它的时间复杂度是O(NlogN)，而快速选择算法的时间复杂度是O(N)。可以使用自带的nth_element()函数,还可以手动实现一个(我自己手写的超时了，还不知道咋优化)
*/
class Solution {
public:
    int kthLargestValue(vector<vector<int>>& matrix, int k) {
        int m = matrix.size(), n = matrix[0].size();
        vector<vector<int>> vec(m, vector<int>(n));
        vector<int> result(m * n);
        int index = 0;
        vec[0][0] = matrix[0][0];
        result[index++] = vec[0][0];
        for (int i = 1; i < n; ++i) {
            vec[0][i] = vec[0][i - 1] ^ matrix[0][i];
            result[index] = vec[0][i];
            ++index;
        }
        for (int i = 1; i < m; ++i) {
            vec[i][0] = vec[i - 1][0] ^ matrix[i][0];
            result[index] = vec[i][0];
            ++index;
        }
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                vec[i][j] = vec[i - 1][j] ^ vec[i][j - 1] ^ vec[i - 1][j - 1] ^ matrix[i][j];
                result[index] = vec[i][j];
                ++index;
            }
        }
        nth_element(result.begin(), result.begin() + k - 1, result.end(), greater<int>());
        return result[k - 1];
    }
};