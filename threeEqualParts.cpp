// threeEqualParts.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

/*
给定一个由 0 和 1 组成的数组 arr ，将数组分成  3 个非空的部分 ，使得所有这些部分表示相同的二进制值。

如果可以做到，请返回任何 [i, j]，其中 i+1 < j，这样一来：

arr[0], arr[1], ..., arr[i] 为第一部分；
arr[i + 1], arr[i + 2], ..., arr[j - 1] 为第二部分；
arr[j], arr[j + 1], ..., arr[arr.length - 1] 为第三部分。
这三个部分所表示的二进制值相等。
如果无法做到，就返回 [-1, -1]。

注意，在考虑每个部分所表示的二进制时，应当将其看作一个整体。例如，[1,1,0] 表示十进制中的 6，而不会是 3。此外，前导零也是被允许的，所以 [0,1,1] 和 [1,1] 表示相同的值。

 

示例 1：

输入：arr = [1,0,1,0,1]
输出：[0,3]
示例 2：

输入：arr = [1,1,0,1,1]
输出：[-1,-1]
示例 3:

输入：arr = [1,1,0,0,1]
输出：[0,2]
 

提示：1、3 <= arr.length <= 3 * 10^4   2、arr[i] 是 0 或 1
*/

#include <iostream>
#include <vector>
using namespace std;

//标准解决方法
//三部分要想相同，1、1的个数要相同，这说明数组中1的总数要能被3整除；2、有效长度要相同
class Solution {
public:
    vector<int> threeEqualParts(vector<int>& arr) {
        int oneNumber = 0;
        int first = 0, third = 0;
        int leftFirstOneIndex = 0, rightFirstOneIndex;
        int left = 0, right = arr.size() - 1;
        int i, j;
        //统计数组中1的个数
        for (int i = 0; i < arr.size(); ++i) {
            if (arr[i] == 1) {
                ++oneNumber;
            }
        }
        //全是0的特殊情况
        if (oneNumber == 0) {
            return { 0, right };
        }
        //如果数组中1的个数不能被3整除，就代表这个数组不能划分成相等的三份
        if (oneNumber % 3 != 0) {
            return { -1, -1 };
        }
        //去掉第一部分的前导0
        while (arr[leftFirstOneIndex] != 1) {
            ++leftFirstOneIndex;
        }
        int each = oneNumber / 3;
        while (first != each) {
            if (arr[left] == 1) {
                ++first;
            }
            ++left;
        }
        int leftEndOneIndex = left - 1;
        while (third != each) {
            if (arr[right] == 1) {
                ++third;
            }
            --right;
        }
        rightFirstOneIndex = right + 1;

        //找到第二部分的开头
        while (arr[left] != 1) {
            ++left;
        }
        //要相同，三部分的有效的长度要相同，而有效长度可以通过第三部分算出来
        int length = arr.size() - rightFirstOneIndex;
        j = left + length;
        i = length + leftFirstOneIndex - 1;
        while (arr[leftFirstOneIndex] == arr[left] && arr[left] == arr[rightFirstOneIndex] && length > 0) {
            ++leftFirstOneIndex;
            ++left;
            ++rightFirstOneIndex;
            --length;
        }
        if (length != 0)
        {
            return { -1, -1 };
        }
        else {
            return { i, j };
        }
    }
};

////这种方法只能用于arr.length不大的情况
//class Solution {
//public:
//    vector<int> threeEqualParts(vector<int>& arr) {
//        int i = 0, j = arr.size() - 1;
//        int leftSum = arr[i], midSum = 0, rightSum = arr[j];
//        int jIndex = 1;
//        while (leftSum != rightSum) {
//            if (leftSum < rightSum) {
//                ++i;
//                leftSum = leftSum * 2 + arr[i];
//            }
//            else {
//                --j;
//                jIndex *= 2;
//                rightSum = rightSum + arr[j] * jIndex;
//            }
//        }
//        int midIndex = 1;
//        for (int k = j - 1; k >= i + 1; --k) {
//            midSum += arr[k] * midIndex;
//            if (k != i + 1) {
//                midIndex *= 2;
//            }
//        }
//        if (leftSum == midSum) {
//            return { i, j };
//        }
//        //第一次进入while循环体的时候leftSum==rightSum
//        while (i + 2 <= j && leftSum < midSum && rightSum < midSum) {
//            if (leftSum == rightSum) {
//                --j;
//                jIndex *= 2;
//                midIndex /= 2;
//                rightSum = rightSum + arr[j] * jIndex;
//                if (rightSum == leftSum) {
//                    midSum /= 2;
//                }
//                else {
//                    midSum = (midSum - 1) / 2;
//                }
//            }
//            else {
//                while (leftSum != rightSum) {
//                    if (leftSum < rightSum) {
//                        ++i;
//                        leftSum = leftSum * 2 + arr[i];
//                        midSum = midSum - arr[i] * midIndex;
//                        midIndex /= 2;
//                    }
//                    else {
//                        --j;
//                        jIndex *= 2;
//                        midIndex /= 2;
//                        rightSum = rightSum + arr[j] * jIndex;
//                        if (arr[j] == 0) {
//                            midSum /= 2;
//                        }
//                        else {
//                            midSum = (midSum - 1) / 2;
//                        }
//                    }
//                }
//            }
//            if (leftSum == midSum && midSum == rightSum) {
//                return{ i, j };
//            }
//        }
//        return { -1, -1 };
//    }
//};
int main()
{
    std::cout << "Hello World!\n";
}