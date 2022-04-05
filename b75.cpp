// std::cout << x << std::endl;
//-------------------------------------------------------------
// 1. Two Sum
    // given array of nums, return indices of 2 numbers that equal target
    // assume only one solution.
    // O(n) time, O(n) space

    class Solution {
    public:
        vector<int> twoSum(vector<int>& nums, int target) {
            unordered_map<int, int> uMap;
            
            for (int i = 0; i < nums.size(); i++) 
            {
                int currNum = nums[i];
                int diff = target - currNum;

                if (uMap.find(diff) != uMap.end())        // .find() returns iterator to k-v pair if foud, else iterator to end of container if not 
                    return {uMap[diff], i};
                else
                    uMap[currNum] = i;
            }
            return {};    
        }
    };
//-------------------------------------------------------------
// 20. Valid Parentheses
    // O(n) time, O(n) space

    class Solution {
    public:
        bool isValid(string s) {
            unordered_map<char, char> uMap;
            stack<char> stack;
    
            uMap[')'] = '(';
            uMap['}'] = '{';
            uMap[']'] = '[';
            
            // for (int i = 0; i < s.size(); i++)                   // can also write like this
            for(auto c:s)
            {        
                if (uMap.find(c) == uMap.end())                     // if opening char, push to stack
                    stack.push(c);
                else                                                // if closing char
                {
                    if (stack.empty() || stack.top() != uMap[c])    // must check if empty before checking .top()
                        return false;
                    stack.pop();   
                }       
            }
            return stack.empty();
        }
    };
//-------------------------------------------------------------
// 21. Merge Two Sorted Lists
    struct ListNode {
        int val;
        ListNode *next;

        ListNode() : val(0), next(nullptr) {}
        ListNode(int x) : val(x), next(nullptr) {}
        ListNode(int x, ListNode *next) : val(x), next(next) {}
    };

    // iterative
    // O(n + m) time, O(1) space

    class Solution {
    public:
        ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
            ListNode holder = ListNode();                                   // cout << holder.val   // 0
            ListNode * curr = &holder;      // & gives address of holder    // cout << curr -> val  // 0
            
            while (list1 && list2)
            {
                if (list1 -> val < list2 -> val)
                {
                    curr -> next = list1;
                    list1 = list1 -> next;
                } 
                else
                {
                    curr -> next = list2;
                    list2 = list2 -> next;
                }
                curr = curr -> next;                    // to check value of curr: cout << curr -> val << endl;
            }
            
            curr -> next = list1 ? list1 : list2;
            
            return holder.next;                         // note list1, list2, curr are pointers so access attribute with '->'
        }                                               // holder not pointer so can access attribute with '.'
    };
    //---------------------------------------------------------------
    // recursive
    // O(n + m) time, O(n + m) space

    class Solution {
    public:
        ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
            if (!list1) return list2;
            if (!list2) return list1;
            
            if (list1 -> val < list2 -> val)
            {
                list1 -> next = mergeTwoLists(list1 -> next, list2);
                return list1;
            }
            else
            {
                list2 -> next = mergeTwoLists(list1, list2 -> next);
                return list2; 
            }
        }      
    };
//-------------------------------------------------------------
// 53. Maximum Subarray
    // find contiguous (connected idx) subarray that has largest sum and return sum
    // O(n) time, O(1) space
    // Kadane's Algo. 

    class Solution {
    public:
        int maxSubArray(vector<int>& nums) {
            int currSum = nums[0], runMax = nums[0];
            
            for (int i = 1; i < nums.size(); i++)
            {
                int currNum = nums[i];
                currSum = max(currSum + currNum, currNum);          // do not name variable 'max' if write 'max' as function name
                                                                    // can use variable 'max' if function name is std::max
                runMax = max(currSum, runMax);
            }
            return runMax; 
        }
    };
//-------------------------------------------------------------
// 70. Climbing Stairs
    // O(n) time, O(1) space

    class Solution {
    public:
        int climbStairs(int n) {
            if (n == 0 || n == 1) return 1;
            int twoBack = 1, oneBack = 1;
            
            for (int i = 2; i <= n; i++)
            {
                int curr = twoBack + oneBack;
                twoBack = oneBack;
                oneBack = curr;
            }
            return oneBack;
        }
    };
//-------------------------------------------------------------
//-------------------------------------------------------------
// 100. Same Tree
    // O(n) time, O(logn) space

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
        bool isSameTree(TreeNode* p, TreeNode* q) {
            if (!p || !q) return p == q;
            if (p -> val != q -> val) return false;
            
            return isSameTree(p -> left, q -> left) && isSameTree(p -> right, q -> right);   
        }
    };
//-------------------------------------------------------------
//-------------------------------------------------------------
// 104. Maximum Depth of Binary Tree
    // O(n) time, O(logn) space

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
        int maxDepth(TreeNode* root) {
            if (!root) return 0;
            return 1 + max(maxDepth(root -> left), maxDepth(root -> right));        // std::max(a, b) also works?
        }
    };
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
// 121. Best Time to Buy and Sell Stock
    // O(n) time, O(1) space

    class Solution {
    public:
        int maxProfit(vector<int>& prices) {
            int lowPrice = prices[0], profit = 0;
            
            for (int i = 1; i < prices.size(); i++)
            {
                int currPrice = prices[i];
                
                if (currPrice < lowPrice)
                    lowPrice = currPrice;
                else
                    profit = max(profit, currPrice - lowPrice);
            }
            return profit;
        }
    };
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
// 206. Reverse Linked List
    // O(n) time, O(1) space

    struct ListNode {
        int val;
        ListNode *next;

        ListNode() : val(0), next(nullptr) {}
        ListNode(int x) : val(x), next(nullptr) {}
        ListNode(int x, ListNode *next) : val(x), next(next) {}
    };

    class Solution {
    public:
        ListNode* reverseList(ListNode* head) {
            ListNode *curr = head, *prev = NULL;            // note: must be NULL (NOT null, Null, etc.)
            
            while (curr)
            {
                ListNode *next = curr -> next;
                curr -> next = prev;
                prev = curr;
                curr = next;
            } 
            return prev;    
        }
    };
//-------------------------------------------------------------
//-------------------------------------------------------------
// 226. Invert Binary Tree
    // O(n) time, O(height) space
    // recursive

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
        TreeNode* invertTree(TreeNode* root) {
            if (!root) return root;
            
            swap(root -> left, root -> right);              // .swap() is built-in!

            // TreeNode *currLeft = root -> left;           // don't need to do this
            // root -> left = root -> right;
            // root -> right = currLeft;
            
            invertTree(root -> left);
            invertTree(root -> right);

            return root;  
        }
    };
    //---------------------------------------------------------------
    // iterative
    // O(n) time, O(n) space

    class Solution {
    public:
        TreeNode* invertTree(TreeNode* root) {
            if (!root) return root;
            
            stack<TreeNode*> st;
            st.push(root);
            
            while (st.size())
            {
                TreeNode* currNode = st.top();                  // top() will give value
                st.pop();                                       // pop() will remove. no return value
                
                if (currNode -> left)
                    st.push(currNode -> left);
                if (currNode -> right)
                    st.push(currNode -> right);
                
                swap(currNode -> left, currNode -> right);      // can swap before or after pushing to stack
            }
            return root;
        }
    };
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------