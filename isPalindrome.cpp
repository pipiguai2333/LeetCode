// isPalindrome.cpp : ���ļ����� "main" ����������ִ�н��ڴ˴���ʼ��������
// ����ָ�������ĵ�����
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

        //����ָ����Ѱ��ǰ�벿�������β���
        while (fast->next != nullptr && fast->next->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }

        //��ת��벿������
        ListNode* current = slow->next;
        ListNode* pre = nullptr;
        ListNode* nextOne;
        while (current != nullptr) {
            nextOne = current->next;
            current->next = pre;
            pre = current;
            current = nextOne;
        }
        //ѭ��������preָ��ָ��ԭ�����β���
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