// kWeakestRows.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
// 二分查找 + 快速选择算法解决矩阵中战斗力最弱的 K 行

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
* Helper类封装了一种快速选择排序算法
* template <typename T> 是C++中用于定义模板的固定格式。模板是实现代码重用机制的一种工具，它可以实现类型参数化，即把类型定义为参数， 从而实现了真正的代码可重用性。
  模版可以分为两类，一个是函数模版，另外一个是类模版。
*
*/
//注意：模板头和类头是一个整体，可以换行，但是中间不能有分号
template<typename T>    //这里不能有分号
class Helper {
    static int partition(vector<T>& nums, int l, int r) {
        T pivot = nums[r];
        int i = l - 1;
        for (int j = l; j <= r - 1; ++j) {
            if (nums[j] <= pivot) {
                i = i + 1;
                swap(nums[i], nums[j]);
            }
        }
        swap(nums[i + 1], nums[r]);
        return i + 1;
    }

    // 基于随机的划分
    static int randomized_partition(vector<T>& nums, int l, int r) {
        int i = rand() % (r - l + 1) + l;   //rand() % (r - l + 1）+ l 随机产生[l,r]的随机数
        swap(nums[r], nums[i]);
        return partition(nums, l, r);
    }


    static void randomized_selected(vector<T>& arr, int l, int r, int k) {
        if (l >= r) {
            return;
        }
        int pos = randomized_partition(arr, l, r);
        int num = pos - l + 1;
        if (k == num) {
            return;
        }
        else if (k < num) {
            randomized_selected(arr, l, pos - 1, k);
        }
        else {
            //这里的第四个参数是k-num，前num小元素已经找到，只需要找剩下的元素
            randomized_selected(arr, pos + 1, r, k - num);
        }
    }

public:
    static vector<T> getLeastNumbers(vector<T>& arr, int k) {
        /*
        * srand函数是随机数发生器的初始化函数。原型:void srand(unsigned seed);
        * 用法:它初始化随机种子，会提供一个种子，这个种子会对应一个随机数，如果使用相同的种子后面的rand()函数会出现一样的随机数，如: srand(1); 直接使用1来初始化种子。
          不过为了防止随机数每次重复，常常使用系统时间来初始化，即使用 time函数来获得系统时间，它的返回值为从 00:00:00 GMT, January 1, 1970 到现在所持续的秒数，
          然后将time_t型数据转化为(unsigned)型再传给srand函数，即: srand((unsigned) time(&t)); 还有一个经常用法，不需要定义time_t型t变量,即: srand((unsigned) time(NULL));
          直接传入一个空指针，因为你的程序中往往并不需要经过参数获得的数据.
        * 进一步说明下：计算机并不能产生真正的随机数，而是已经编写好的一些无规则排列的数字存储在电脑里，把这些数字划分为若干相等的N份，并为每份加上一个编号用srand()函数获取这个编号，
          然后rand()就按顺序获取这些数字，当srand()的参数值固定的时候，rand()获得的数也是固定的，所以一般srand的参数用time(NULL)，因为系统的时间一直在变，
          所以rand()获得的数，也就一直在变，相当于是随机数了。只要用户或第三方不设置随机种子，那么在默认情况下随机种子来自系统时钟。
          如果想在一个程序中生成随机数序列，需要至多在生成随机数之前设置一次随机种子。
          即：只需在主程序开始处调用srand((unsigned)time(NULL)); 后面直接用rand就可以了。不要在for等循环放置srand((unsigned)time(NULL));

          void test_rand(void)
          {
             unsigned long n;
             srand((unsigned)time(NULL));
             for(int i = 0; i < 100; i++)
             {
                n = rand();
                printf("d\n", n);
             }
          }
        */
        srand((unsigned)time(NULL));

        randomized_selected(arr, 0, (int)arr.size() - 1, k);
        vector<T> vec;
        for (int i = 0; i < k; ++i) {
            vec.emplace_back(arr[i]);
        }
        return vec;
    }
};

class Solution {
public:
    vector<int> kWeakestRows(vector<vector<int>>& mat, int k) {
        int m = mat.size(), n = mat[0].size();
        vector<pair<int, int>> power;
        //二分查找每行最后一个1的位置
        for (int i = 0; i < m; ++i) {
            int l = 0, r = n - 1, pos = -1;
            while (l <= r) {
                int mid = (l + r) / 2;
                if (mat[i][mid] == 0) {
                    r = mid - 1;
                }
                else {
                    pos = mid;
                    l = mid + 1;
                }
            }
            power.emplace_back(pos + 1, i);
        }

        //Helper类的getLeastNumbers返回的vector数组是传过去的参数vector数组中的前k小个元素，并且这k个元素是无序的，还需要排序
        vector<pair<int, int>> minimum = Helper<pair<int, int>>::getLeastNumbers(power, k);

        /*
        * sort()并非只是普通的快速排序，除了对普通的快速排序进行优化，它还结合了插入排序和堆排序。
          根据不同的数量级别以及不同情况，能自动选用合适的排序方法。当数据量较大时采用快速排序，分段递归。
          一旦分段后的数据量小于某个阀值，为避免递归调用带来过大的额外负荷，便会改用插入排序。而如果递归层次过深，有出现最坏情况的倾向，还会改用堆排序。
        * 对容器或普通数组中 [first, last) 范围内的元素进行排序，默认进行升序排序。std::greater<T>()降序排序规则。
        */
        sort(minimum.begin(), minimum.begin() + k);

        vector<int> ans;
        for (int i = 0; i < k; ++i) {
            ans.emplace_back(minimum[i].second);
        }
        return ans;
    }
};

//int main() {
//    vector<vector<int>> example{ {1,1,0,0,0}, {1,1,1,1,0}, {1,0,0,0,0}, {1,1,0,0,0}, {1,1,1,1,1} };
//    Solution solution;
//    vector<int> ans = solution.kWeakestRows(example, 5);
//    for (int i = 0; i < ans.size(); ++i) {
//        cout << ans[i] << " ";
//    }
//}