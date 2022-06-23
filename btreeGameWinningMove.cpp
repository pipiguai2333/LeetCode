/*有两位极客玩家参与了一场「二叉树着色」的游戏。游戏中，给出二叉树的根节点 root，树上总共有 n 个节点，且 n 为奇数，其中每个节点上的值从 1 到 n 各不相同。



游戏从「一号」玩家开始（「一号」玩家为红色，「二号」玩家为蓝色），最开始时，

「一号」玩家从[1, n] 中取一个值 x（1 <= x <= n）；

「二号」玩家也从 [1, n] 中取一个值 y（1 <= y <= n）且 y != x。

「一号」玩家给值为 x 的节点染上红色，而「二号」玩家给值为 y 的节点染上蓝色。



之后两位玩家轮流进行操作，每一回合，玩家选择一个他之前涂好颜色的节点，将所选节点一个 未着色 的邻节点（即左右子节点、或父节点）进行染色。

如果当前玩家无法找到这样的节点来染色时，他的回合就会被跳过。

若两个玩家都没有可以染色的节点时，游戏结束。着色节点最多的那位玩家获得胜利 ✌️。



现在，假设你是「二号」玩家，根据所给出的输入，假如存在一个 y 值可以确保你赢得这场游戏，则返回 true；若无法获胜，就请返回 false。
*/

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
 
class Solution {
public:
    bool btreeGameWinningMove(TreeNode* root, int n, int x) {
        //leftNum为左子树的结点个数，rightNum为右子树的结点个数
        int leftNum = 0, rightNum = 0;
        //0代表在根节点，1代表在左子树，2代表在右子树
        int flag;
        //find->val == x
        TreeNode* find = root;
        if (root->val == x) {
            flag = 0;
        }
        flag = FindFlag(root, find, x);
        leftNum = TreeNodeNum(root->left);
        rightNum = TreeNodeNum(root->right);
        if (rightNum == leftNum) {
            if (root->val != x) {
                return true;
            }
            else {
                return false;
            }
        }
        else {
            if (leftNum < rightNum) {
                switch (flag) {
                case 1: return true; break;
                case 0: return rightNum > leftNum + 1 ? true : false; break;
                case 2: int tempNum = TreeNodeNum(find);
                    int temp1 = TreeNodeNum(find->left);
                    int temp2 = TreeNodeNum(find->right);
                    int max = temp1 > temp2 ? temp1 : temp2;
                    if ((n - max) < max) {
                        return true;
                    }
                    else {
                        return (n - tempNum) > tempNum ? true : false;
                    }
                    break;
                }
            }
            else {
                switch (flag) {
                case 2: return true; break;
                case 0: return leftNum > rightNum + 1 ? true : false; break;
                case 1: int tempNum = TreeNodeNum(find);
                    int temp1 = TreeNodeNum(find->left);
                    int temp2 = TreeNodeNum(find->right);
                    int max = temp1 > temp2 ? temp1 : temp2;
                    if ((n - max) < max) {
                        return true;
                    }
                    else {
                        return (n - tempNum) > tempNum ? true : false;
                    }
                }
            }
        }
        return 0;
    }

    //统计一颗二叉树的结点个数
    int TreeNodeNum(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }
        return TreeNodeNum(root->left) + TreeNodeNum(root->right) + 1;
    }

    //找出x值在左子树还是右子树
    int FindFlag(TreeNode* root, TreeNode*& find, int x) {
        bool result = false;
        Find(root->left, find, x, result);
        //在左子树找到
        if (result) {
            return 1;
        }
        //在右子树找到
        else {
            Find(root->right, find, x, result);
            return 2;
        }
    }

    //在树中寻找结点
    void Find(TreeNode* root, TreeNode*& find, int x, bool& flag) {
        if (root) {
            Find(root->left, find, x, flag);
            if (root->val == x) {
                find = root;
                flag = true;
            }
            Find(root->right, find, x, flag);
        }
    }
};