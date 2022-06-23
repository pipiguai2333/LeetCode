// isPalindrome.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
// 快慢指针解决回文单链表
#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;
struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};
class Solution {

public:
    bool isPalindrome(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head;

        //快慢指针来寻找前半部分链表的尾结点
        while (fast->next != nullptr && fast->next->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }

        //反转后半部分链表
        ListNode* current = slow->next;
        ListNode* pre = nullptr;
        ListNode* nextOne;
        while (current != nullptr) {
            nextOne = current->next;
            current->next = pre;
            pre = current;
            current = nextOne;
        }
        //循环结束后，pre指针指向原链表的尾结点
        ListNode* first = head;
        while (pre != nullptr) {
            if (first->val != pre->val)
                return false;
            first = first->next;
            pre = pre->next;
        }
        return true;
    }
};


//int main() {
//    string s;
//    bool result;
//    int i = 1;
//    ListNode* head = new ListNode();
//    ListNode* end = new ListNode();
//    ListNode* tem = new ListNode();
//    Solution solution;
//    cin >> s;
//    while (i < s.size()) {
//        if (i == 1)
//        {
//            head->val = (int)s[i];
//            end = head;
//        }
//        else {
//            tem = new ListNode((int)s[i]);
//            end->next = tem;
//            end = tem;
//        }
//        i += 2;
//    }
//    result = solution.isPalindrome(head);
//    cout << "result:" << result << endl;
//    /*char c = 'a';
//    cout << "c:" << (int)c << endl;*/
//    return 0;
//}
//int main() {
//    vector<int> values{ 21, 22, 12, 3, 24, 54, 56 };
//    priority_queue<int, vector<int>, greater<int>> q(greater<int>(), move(values));
//    cout << values.size() << endl;
//     while(q.size() > 0) {
//         cout << q.top() << endl;
//         q.pop();
//     }
//    return 0;
//}