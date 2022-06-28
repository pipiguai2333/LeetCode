// kWeakestRows.cpp : ���ļ����� "main" ����������ִ�н��ڴ˴���ʼ��������
// ���ֲ��� + ����ѡ���㷨���������ս���������� K ��

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
* Helper���װ��һ�ֿ���ѡ�������㷨
* template <typename T> ��C++�����ڶ���ģ��Ĺ̶���ʽ��ģ����ʵ�ִ������û��Ƶ�һ�ֹ��ߣ�������ʵ�����Ͳ��������������Ͷ���Ϊ������ �Ӷ�ʵ���������Ĵ���������ԡ�
  ģ����Է�Ϊ���࣬һ���Ǻ���ģ�棬����һ������ģ�档
*
*/
//ע�⣺ģ��ͷ����ͷ��һ�����壬���Ի��У������м䲻���зֺ�
template<typename T>    //���ﲻ���зֺ�
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

    // ��������Ļ���
    static int randomized_partition(vector<T>& nums, int l, int r) {
        int i = rand() % (r - l + 1) + l;   //rand() % (r - l + 1��+ l �������[l,r]�������
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
            //����ĵ��ĸ�������k-num��ǰnumСԪ���Ѿ��ҵ���ֻ��Ҫ��ʣ�µ�Ԫ��
            randomized_selected(arr, pos + 1, r, k - num);
        }
    }

public:
    static vector<T> getLeastNumbers(vector<T>& arr, int k) {
        /*
        * srand������������������ĳ�ʼ��������ԭ��:void srand(unsigned seed);
        * �÷�:����ʼ��������ӣ����ṩһ�����ӣ�������ӻ��Ӧһ������������ʹ����ͬ�����Ӻ����rand()���������һ�������������: srand(1); ֱ��ʹ��1����ʼ�����ӡ�
          ����Ϊ�˷�ֹ�����ÿ���ظ�������ʹ��ϵͳʱ������ʼ������ʹ�� time���������ϵͳʱ�䣬���ķ���ֵΪ�� 00:00:00 GMT, January 1, 1970 ��������������������
          Ȼ��time_t������ת��Ϊ(unsigned)���ٴ���srand��������: srand((unsigned) time(&t)); ����һ�������÷�������Ҫ����time_t��t����,��: srand((unsigned) time(NULL));
          ֱ�Ӵ���һ����ָ�룬��Ϊ��ĳ���������������Ҫ����������õ�����.
        * ��һ��˵���£�����������ܲ���������������������Ѿ���д�õ�һЩ�޹������е����ִ洢�ڵ��������Щ���ֻ���Ϊ������ȵ�N�ݣ���Ϊÿ�ݼ���һ�������srand()������ȡ�����ţ�
          Ȼ��rand()�Ͱ�˳���ȡ��Щ���֣���srand()�Ĳ���ֵ�̶���ʱ��rand()��õ���Ҳ�ǹ̶��ģ�����һ��srand�Ĳ�����time(NULL)����Ϊϵͳ��ʱ��һֱ�ڱ䣬
          ����rand()��õ�����Ҳ��һֱ�ڱ䣬�൱����������ˡ�ֻҪ�û��������������������ӣ���ô��Ĭ������������������ϵͳʱ�ӡ�
          �������һ��������������������У���Ҫ���������������֮ǰ����һ��������ӡ�
          ����ֻ����������ʼ������srand((unsigned)time(NULL)); ����ֱ����rand�Ϳ����ˡ���Ҫ��for��ѭ������srand((unsigned)time(NULL));

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
        //���ֲ���ÿ�����һ��1��λ��
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

        //Helper���getLeastNumbers���ص�vector�����Ǵ���ȥ�Ĳ���vector�����е�ǰkС��Ԫ�أ�������k��Ԫ��������ģ�����Ҫ����
        vector<pair<int, int>> minimum = Helper<pair<int, int>>::getLeastNumbers(power, k);

        /*
        * sort()����ֻ����ͨ�Ŀ������򣬳��˶���ͨ�Ŀ�����������Ż�����������˲�������Ͷ�����
          ���ݲ�ͬ�����������Լ���ͬ��������Զ�ѡ�ú��ʵ����򷽷������������ϴ�ʱ���ÿ������򣬷ֶεݹ顣
          һ���ֶκ��������С��ĳ����ֵ��Ϊ����ݹ���ô�������Ķ��⸺�ɣ������ò������򡣶�����ݹ��ι���г������������򣬻�����ö�����
        * ����������ͨ������ [first, last) ��Χ�ڵ�Ԫ�ؽ�������Ĭ�Ͻ�����������std::greater<T>()�����������
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