#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>
#include <list>

using namespace std;

class TreeNode
{
public:
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int val)
    {
        this->val - val;
    }
};

//Binary Tree==================================================================
// 236. Lowest Common Ancestor of a Binary Tree
vector<TreeNode *> rootToNodePath(TreeNode *root, TreeNode *node)
{
    if (root == nullptr)
        return {};
    if (root == node)
    {
        vector<TreeNode *> base;
        base.push_back(root);
        return base;
    }

    vector<TreeNode *> leftPath = rootToNodePath(root->left, node);
    if (leftPath.size() != 0)
    {
        leftPath.push_back(root);
        return leftPath;
    }

    vector<TreeNode *> rightPath = rootToNodePath(root->right, node);
    if (rightPath.size() != 0)
    {
        rightPath.push_back(root);
        return rightPath;
    }

    return {};
}

TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
{
    vector<TreeNode *> path1 = rootToNodePath(root, p);
    vector<TreeNode *> path2 = rootToNodePath(root, q);

    int i = path1.size() - 1;
    int j = path2.size() - 1;
    TreeNode *lca;

    while (i >= 0 && j >= 0)
    {
        if (path1[i] != path2[j])
            break;
        lca = path1[i];
        i--;
        j--;
    }

    return lca;
}

// 112. Path Sum
bool hasPathSum(TreeNode *root, int sum)
{
    if (root == nullptr)
        return false;

    if (root->left == nullptr && root->right == nullptr)
    {
        if (sum - root->val == 0)
            return true;
    }

    return hasPathSum(root->left, sum - root->val) || hasPathSum(root->right, sum - root->val);
}

// 113. Path Sum II
void getPaths(TreeNode *root, int sum, vector<int> &myPath, vector<vector<int>> &paths)
{
    if (root == nullptr)
        return;

    if (root->left == nullptr && root->right == nullptr)
    {
        if (sum - root->val == 0)
        {
            myPath.push_back(root->val);
            paths.push_back(myPath);
            myPath.pop_back();
            return;
        }
    }

    myPath.push_back(root->val);
    getPaths(root->left, sum - root->val, myPath, paths);
    getPaths(root->right, sum - root->val, myPath, paths);
    myPath.pop_back();
}

vector<vector<int>> pathSum(TreeNode *root, int sum)
{
    vector<int> myPath;
    vector<vector<int>> paths;
    getPaths(root, sum, myPath, paths);
    return paths;
}

//geeks: https://www.geeksforgeeks.org/find-maximum-path-sum-two-leaves-binary-tree/
struct Node
{
    int data;
    struct Node *left;
    struct Node *right;

    Node(int x)
    {
        data = x;
        left = right = NULL;
    }
};
int maxSum;
int leafToleaf(Node *root)
{
    if (root == nullptr)
        return 0;

    //node to leaf leftSum and rightSum
    int leftSum = leafToleaf(root->left);
    int rightSum = leafToleaf(root->right);

    if (root->left != nullptr && root->right != nullptr)
    {
        int leafToLeafSum = leftSum + root->data + rightSum;
        maxSum = max(leafToLeafSum, maxSum);

        return max(rightSum, leftSum) + root->data;
    }

    return (root->left == nullptr ? rightSum : leftSum) + root->data;
}
int maxPathSum(Node *root)
{
    maxSum = -1e8;
    leafToleaf(root);
    return maxSum;
}

// 543. Diameter of Binary Tree
int maxDia = 0;
int diameter(TreeNode *root)
{
    if (root == nullptr)
        return -1;
    int lh = diameter(root->left);
    int rh = diameter(root->right);

    maxDia = max(maxDia, lh + rh + 2);
    return max(lh, rh) + 1;
}
int diameterOfBinaryTree(TreeNode *root)
{
    maxDia = 0;
    diameter(root);
    return maxDia;
}

// 124. Binary Tree Maximum Path Sum
int maxSum = -1e8;
int maxPathSum_(TreeNode *root)
{
    if (root == nullptr)
        return 0;
    int leftSum = maxPathSum_(root->left);
    int rightSum = maxPathSum_(root->right);

    int max_ = max(leftSum, rightSum) + root->val;
    maxSum = max(max(leftSum + rightSum + root->val, root->val), max(maxSum, max_));

    return max(max_, root->val);
}
int maxPathSum(TreeNode *root)
{
    maxSum = -1e8;
    maxPathSum_(root);
    return maxSum;
}

// 863. All Nodes Distance K in Binary Tree
//using block Node
vector<TreeNode *> rootToNodePath(TreeNode *root, TreeNode *node)
{
    if (root == nullptr)
        return {};
    if (root == node)
    {
        vector<TreeNode *> base;
        base.push_back(root);
        return base;
    }

    vector<TreeNode *> leftPath = rootToNodePath(root->left, node);
    if (leftPath.size() != 0)
    {
        leftPath.push_back(root);
        return leftPath;
    }

    vector<TreeNode *> rightPath = rootToNodePath(root->right, node);
    if (rightPath.size() != 0)
    {
        rightPath.push_back(root);
        return rightPath;
    }

    return {};
}
void kdown(TreeNode *node, TreeNode *blockNode, int level, vector<int> &ans)
{
    if (node == nullptr || node == blockNode)
        return;

    if (level == 0)
        ans.push_back(node->val);

    kdown(node->left, blockNode, level - 1, ans);
    kdown(node->right, blockNode, level - 1, ans);
}
vector<int> distanceK(TreeNode *root, TreeNode *target, int K)
{
    vector<TreeNode *> path = rootToNodePath(root, target);
    vector<int> ans;
    TreeNode *blockNode = nullptr;

    for (int i = 0; i < path.size(); i++)
    {
        kdown(path[i], blockNode, K - i, ans);
        blockNode = path[i];
    }

    return ans;
}

//BST============================================================================
// 450. Delete Node in a BST
TreeNode *deleteNode(TreeNode *root, int key)
{
    if (root == nullptr)
        return root;

    //find key
    if (key < root->val)
        root->left = deleteNode(root->left, key);
    else if (key > root->val)
        root->right = deleteNode(root->right, key);

    else //key found
    {
        if (root->left == nullptr || root->right == nullptr) //if left or right is null then just return the non null node
            return root->left == nullptr ? root->right : root->left;

        //else swap the value with max of left subtree or min of right subtree and remove that node
        TreeNode *leftNode = root->left;
        while (leftNode->right != nullptr)
            leftNode = leftNode->right;
        root->val = leftNode->val;
        root->left = deleteNode(root->left, leftNode->val);
    }
    return root;
}

// 235. Lowest Common Ancestor of a Binary Search Tree- both p and q will definitely be present in the bst
//recursive
TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
{
    if (root == nullptr)
        return root;

    if (p->val < root->val && q->val < root->val)
        return lowestCommonAncestor(root->left, p, q);

    else if (p->val > root->val && q->val > root->val)
        return lowestCommonAncestor(root->right, p, q);

    else
        return root;
}

//iterative
TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
{
    TreeNode *curr = root;
    while (curr != nullptr)
    {
        if (p->val < curr->val && q->val < curr->val)
            curr = curr->left;
        else if (p->val > curr->val && q->val > curr->val)
            curr = curr->right;
        else
            return curr;
    }
    return nullptr;
}

// 938. Range Sum of BST
int rangeSum = 0;
void rangeSumBST_(TreeNode *root, int L, int R)
{
    if (root == nullptr)
        return;

    rangeSumBST(root->left, L, R);

    if (L <= root->val && root->val <= R)
        rangeSum += root->val;

    rangeSumBST(root->right, L, R);
}
int rangeSumBST(TreeNode *root, int L, int R)
{
    rangeSumBST_(root, L, R);
    return rangeSum;
}

// 98. Validate Binary Search Tree
long long prev = -1e12;
bool isValidBST(TreeNode *root)
{
    if (root == nullptr)
        return true;

    bool res = true;
    res = res && isValidBST(root->left);
    if (root->val <= prev)
        return false;
    prev = root->val;

    res = res && isValidBST(root->right);

    return res;
}

//Extra===================================================================================================

// 1367. Linked List in Binary Tree
struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

typedef pair<TreeNode *, ListNode *> pr;
bool isSubPath(ListNode *head, TreeNode *root, ListNode *curr, map<pr, bool> &dp)
{
    if (curr == nullptr)
        return dp[{root, curr}] = true;
    if (root == nullptr)
        return dp[{root, curr}] = false;

    if (dp.find({root, curr}) != dp.end())
        return dp[{root, curr}];

    bool res = false;
    if (curr->val == root->val)
        res = res || isSubPath(head, root->left, curr->next, dp) || isSubPath(head, root->right, curr->next, dp);

    res = res || isSubPath(head, root->left, head, dp) || isSubPath(head, root->right, head, dp);

    return dp[{root, curr}] = res;
}
bool isSubPath(ListNode *head, TreeNode *root)
{
    map<pr, bool> dp;
    return isSubPath(head, root, head, dp);
}

// 1339. Maximum Product of Splitted Binary Tree
long MOD = 1000000007;
long long ans = 0;
int totalSum(TreeNode *root, unordered_map<TreeNode *, int> &dp)
{
    if (root == nullptr)
        return 0;

    if (dp.find(root) != dp.end())
        return dp[root];

    int lsum = totalSum(root->left, dp);
    int rsum = totalSum(root->right, dp);
    int sum = lsum + rsum + root->val;
    return dp[root] = sum;
}
void maxProduct(TreeNode *root, int totSum, unordered_map<TreeNode *, int> &dp)
{
    if (root == nullptr)
        return;

    long long subtreeSum = totalSum(root, dp);
    long long myProduct = (totSum - subtreeSum) * subtreeSum;
    ans = max(ans, myProduct);

    maxProduct(root->left, totSum, dp);
    maxProduct(root->right, totSum, dp);
}
int maxProduct(TreeNode *root)
{
    unordered_map<TreeNode *, int> dp;
    int totSum = totalSum(root, dp);
    maxProduct(root, totSum, dp);
    return ans % MOD;
}

// 297. Serialize and Deserialize Binary Tree// Encodes a tree to a single string.
//using Preorder
string serialize(TreeNode *root)
{
    if (root == nullptr)
        return "n,"; //n for null

    string str = "";
    str += to_string(root->val) + ",";
    str += serialize(root->left);
    str += serialize(root->right);

    return str;
}
int idx = 0;
string str;
TreeNode *deserialize(string data)
{
    if (idx == data.size() || data[idx] == 'n')
    {
        if (data[idx] == 'n')
        {
            idx += 2;
        }
        return nullptr;
    }

    int val = 0, sign = 0; //0=+ve , 1=-ve

    //check sign
    if (data[idx] == '-')
    {
        sign = 1;
        idx++;
    }
    //get value of node
    while (data[idx] != ',')
        val = val * 10 + (data[idx++] - '0');

    if (sign == 1)
        val *= -1;

    TreeNode *root = new TreeNode(val);
    idx++;
    root->left = deserialize(data);
    root->right = deserialize(data);

    return root;
}

// 662. Maximum Width of Binary Tree
int widthOfBinaryTree(TreeNode *root)
{
    list<TreeNode *> que;
    int maxWidth = 0;

    que.push_back(root);

    while (que.size() != 0)
    {
        int size = que.size();
        vector<int> level;
        while (size > 0)
        {
            TreeNode *node = que.front();
            que.pop_front();

            level.push_back(node->val);
            if (node->left != nullptr)
                que.push_back(node->left);
            if (node->right != nullptr)
                que.push_back(node->right);
        }

        int i;
        for (i = level.size() - 1; i >= 0; i--)
        {
            if (level[i] != 1e8)
                break;
        }

        maxWidth = max(i + 1, maxWidth);
    }

    return maxWidth;
}

void solve()
{
}
int main()
{
    solve();
    return 0;
}