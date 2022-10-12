/*给你一个整数 x ，如果 x 是一个回文整数，返回 true ；否则，返回 false 。

回文数是指正序（从左向右）和倒序（从右向左）读都是一样的整数。

例如，121 是回文，而 123 不是。


示例 1：
输入：x = 121
输出：true

示例 2：
输入：x = -121
输出：false
解释：从左向右读, 为 - 121 。 从右向左读, 为 121 - 。因此它不是一个回文数。

示例 3：
输入：x = 10
输出：false
解释：从右向左读, 为 01 。因此它不是一个回文数。
*/
#include <vector>
using namespace std;

/*
* 这种方法是将int类型的整数放入数组中，然后用两个指针分别从数组头和数组尾同时扫描，只要有一个不同就返回false，否则返回true
*/
class Solution1 {
public:
    bool isPalindrome(int x) {
        if (x < 0) {
            return false;
        }
        else if (0 <= x && x <= 9) {
            return true;
        }
        else {
            vector<int> arr;
            while (x != 0) {
                arr.emplace_back(x % 10);
                x /= 10;
            }
            for (int i = 0, j = arr.size() - 1; i <= j; ++i, --j) {
                if (arr[i] != arr[j]) {
                    return false;
                }
            }
        }
        return true;
    }
};


/*
这种方法是将int类型的整数整个翻转成一个整数，然后这两个数进行比较，相等为true，不等为false
注意：将int类型的整数反转可能会超出int的表示范围，需要用一个比int表示范围大的类型来储存这个数，比如long
*/
class Solution2 {
public:
    bool isPalindrome(int x) {
        if (x < 0) {
            return false;
        }
        else if (0 <= x && x <= 9) {
            return true;
        }
        else {
            long z = 0;
            int y = x;
            while (y != 0) {
                z = z * 10 + (y % 10);
                y /= 10;
            }
            if (z != (long)x) {
                return false;
            }
        }
        return true;
    }
};

/*
不同于第二种方法，这种方法只翻转int类型的整数的后半段，这样做是因为不用考虑溢出的问题
*/
class Solution3 {
public:
    bool isPalindrome(int x) {
        // 特殊情况：
        // 如上所述，当 x < 0 时，x 不是回文数。
        // 同样地，如果数字的最后一位是 0，为了使该数字为回文，
        // 则其第一位数字也应该是 0
        // 只有 0 满足这一属性
        if (x < 0 || (x % 10 == 0 && x != 0)) {
            return false;
        }

        int revertedNumber = 0;
        //①当数字的长度为奇数的时候，revertedNumber总是比x多一位
        //②当数字的长度为偶数的时候，444555：revertedNumber与x的长度相等；555444：revertedNumber比x多两位
        while (x > revertedNumber) {
            revertedNumber = revertedNumber * 10 + x % 10;
            x /= 10;
        }

        // 当数字长度为奇数时，我们可以通过 revertedNumber/10 去除处于中位的数字。
        // 例如，当输入为 12321 时，在 while 循环的末尾我们可以得到 x = 12，revertedNumber = 123，
        // 由于处于中位的数字不影响回文（它总是与自己相等），所以我们可以简单地将其去除。
        return x == revertedNumber || x == revertedNumber / 10;
    }
};