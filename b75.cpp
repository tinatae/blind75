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
//-------------------------------------------------------------
// 15. 3 Sum
    // return array of triplets == 0. all must be distinct triplet values (with different idx)
    // O(n^2) time
    // O(logn) || O(n) space depending sort space

    class Solution {
    public:
        vector<vector<int>> threeSum(vector<int>& nums) {
            vector<vector<int>> answer;
            
            if (nums.size() < 3)
                return answer;
            
            sort(nums.begin(), nums.end());
            
            int size = nums.size(); 
            
            for (int i = 0; i < size - 2; i++)
            {
                if (nums[i] > 0) break;
                if (i > 0 && nums[i] == nums[i - 1]) continue;
                
                int second = i + 1, third = size - 1;
                
                while (second < third)
                {
                    int currSum = nums[i] + nums[second] + nums[third];
                    
                    if (currSum < 0)
                        second++;
                    else if (currSum > 0)
                        third--;
                    else
                    {
                        answer.push_back({nums[i], nums[second], nums[third]});
                        
                        int currSecond = nums[second], currThird = nums[third];
                    
                        while (second < third && nums[second] == currSecond) second++;
                        while (second < third && nums[third] == currThird) third--;
                    }
                }
            }
            return answer;    
        }
    };
//-------------------------------------------------------------
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
            ListNode * curr = &holder;      // & gives address of holder    // cout << curr->val  // 0
            
            while (list1 && list2)
            {
                if (list1->val < list2->val)
                {
                    curr->next = list1;
                    list1 = list1->next;
                } 
                else
                {
                    curr->next = list2;
                    list2 = list2->next;
                }
                curr = curr->next;                    // to check value of curr: cout << curr->val << endl;
            }
            
            curr->next = list1 ? list1 : list2;
            
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
            
            if (list1->val < list2->val)
            {
                list1->next = mergeTwoLists(list1->next, list2);
                return list1;
            }
            else
            {
                list2->next = mergeTwoLists(list1, list2->next);
                return list2; 
            }
        }      
    };
//-------------------------------------------------------------
// 39. Combination Sum
    // given array of distinct integers, retunr list of all unique combos where chosen nums sum to target. can return combos in any order
    // O(num candidates ^ ((targetVal / minCandVal) + 1))) time
    // O(targetVal / minCandVal) space

    class Solution {
    public:
        vector<vector<int>> combos;                                                     // higher scope
        
        void getCombos(vector<int> subArr, int remaining, int startIdx, vector<int> &candidates) {
            if (remaining == 0)
                return combos.push_back(subArr);

            if (remaining < 0) return;

            for (int i = startIdx; i < candidates.size(); i++)
            {
                int currCand = candidates[i];
                subArr.push_back(currCand);
                getCombos(subArr, remaining - currCand, i, candidates);
                subArr.pop_back();        
            }     
        } 
        
        vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
            getCombos({}, target, 0, candidates);                                       // cannot nest function
            return combos;  
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
// 55. Jump Game
    // O(n) time, O(1) space
    // initially positioned at first index, and each element represents max jump length in that position
    // determine if can reach last index
    
    class Solution {
    public:
        bool canJump(vector<int>& nums) {
            int maxIdx = 0, targetIdx = nums.size()-1;
            
            for (int i = 0; i <= maxIdx; i++)
            {
                maxIdx = max(i + nums[i], maxIdx);
                if (maxIdx >= targetIdx) 
                    return true;
            }
            return false;   
        }
    };
//-------------------------------------------------------------
// 56. Merge Intervals
    // O(nlogn) time
    // O(n) space

    // can have 3 scenarios for merging: 
        // prevEnd less than currStart
        // prevEnd <= to currStart but less than currEnd
        // greater than currStart, greater than currEnd

    class Solution {
    public:
        vector<vector<int>> merge(vector<vector<int>>& intervals) {
            int size = intervals.size();
            
            if (size <= 1) return intervals;
            
            sort(intervals.begin(), intervals.end());
            
            vector <vector<int>> merged;
            merged.push_back(intervals[0]);
            
            for (int i = 1; i < size; i++)
            {
                int currStart = intervals[i][0], currEnd = intervals[i][1], 
                    prevEnd = merged.back()[1];
                
                if (prevEnd >= currEnd) continue;     
                if (prevEnd >= currStart)        
                {
                    merged.back()[1] = currEnd;
                    continue;
                }
                merged.push_back(intervals[i]);      
            }
            return merged;
        }
    };
//-------------------------------------------------------------
// 62. Unique Paths
    // go from top-left corner to bottom-right moving only down or right.
    // how many unique paths to bottom right
    // O(n*m) time, O(n*m) space

    class Solution {
    public:
        int uniquePaths(int m, int n) {
            int grid[m][n];

            for (int i = 0; i < m; i++)
                for (int j = 0; j < n; j++)
                {
                    if (i == 0 || j == 0)
                        grid[i][j] = 1;
                    else
                        grid[i][j] = grid[i-1][j] + grid[i][j-1];
                } 

            return grid[m-1][n-1];
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
// 98. Validate BST
    // O(n) time, O(n) space. keep up to entire tree

    class Solution {
    public:
        bool validate(TreeNode* root, TreeNode* min=nullptr, TreeNode* max=nullptr) {           // whole node for now. ideally int pointer val
            if (!root) 
                return true;
    
            if (min && root->val <= min->val || max && root->val >= max->val)
                return false;

            return validate(root->left, min, root) && validate(root->right, root, max);
        }

        bool isValidBST(TreeNode* root) {
            return validate(root);
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
            if (p->val != q->val) return false;
            
            return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);   
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
            return 1 + max(maxDepth(root->left), maxDepth(root->right));        // std::max(a, b) also works?
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
// 125. Valid Palindrome
    // ignore spaces, non alphanumeric chars. allow mixed case
    // O(n) time, O(1) space

    class Solution {
    public:
        bool isPalindrome(string s) {
            int start = 0, end = s.size() - 1;
            
            while (start < end)
            {
                if (!isalnum(s[start]))                             // int isalnum(c char) checks if alphanumeric
                    start++;
                else if (!isalnum(s[end]))                          // int isdigit(c char), int isalpha(c char) also exist
                    end--;     
                else if (tolower(s[start]) != tolower(s[end]))
                    return false;
                else 
                {
                    start++; 
                    end--;
                }
            }
            return true;
        }
    };
//-------------------------------------------------------------
//-------------------------------------------------------------
// 141. Linked List Cycle
    // O(n) time, O(1) space

    class Solution {
    public:
        bool hasCycle(ListNode *head) {
            if (!head) 
                return false;
            
            ListNode *fast = head, *slow = head;
            
            while (fast && fast->next)
            {
                fast = fast->next->next;
                slow = slow->next;
                if (fast == slow) return true;
            }
            return false; 
        }
    };
//-------------------------------------------------------------
//-------------------------------------------------------------
// 200. Number of Islands
    // O(n * m) time, O(n * m) space

    // alter grid
    class Solution {
    public:
        void dfs(int x, int y, vector<vector<char>>& grid) {
            if (x < 0 || y < 0 || x >= grid.size() || y >= grid[0].size()) return;
            if (grid[x][y] == '0' || grid[x][y] == '2' ) return;
            
            grid[x][y] = '2';
            
            dfs(x + 1, y, grid);
            dfs(x - 1, y, grid);
            dfs(x, y + 1, grid);
            dfs(x, y - 1, grid);
        }

        int numIslands(vector<vector<char>>& grid) {
            int count = 0;
            
            for (int i = 0; i < grid.size(); i++)
            {
                for (int j = 0; j < grid[0].size(); j++)
                {
                    if (grid[i][j] == '1')
                    {
                        dfs(i, j, grid);
                        count++;  
                    }
                }
            }
            return count;
        }
    };
    //-------------------------------------------------------------
    // no-alter
    // class Solution {
    // public:
    //     unordered_set<string> seen;
        
    //     string makeKey(int a, int b) {
    //         return to_string(a).append("-").append(to_string(b));
    //     }
        
    //     void dfs(int x, int y, vector<vector<char>>& grid) {
    //         if (x < 0 || y < 0 || x >= grid.size() || y >= grid[0].size() || grid[x][y] == '0') return;
            
    //         string key = makeKey(x, y);

    //         if (seen.find(key) == seen.end()) {
    //             seen.insert(key);

    //             dfs(x + 1, y, grid);
    //             dfs(x - 1, y, grid);
    //             dfs(x, y + 1, grid);
    //             dfs(x, y - 1, grid);
    //         }
    //     }

    //     int numIslands(vector<vector<char>>& grid) {
    //         int count = 0;

    //         for (int i = 0; i < grid.size(); i++)
    //         {
    //             for (int j = 0; j < grid[0].size(); j++)
    //             {
    //                 if (grid[i][j] == '1')
    //                 {
    //                     if (seen.find(makeKey(i, j)) == seen.end()) {       // doesn't have in set
    //                         dfs(i, j, grid);
    //                         count++;  
    //                     } 
    //                 }
    //             }
    //         }
    //         return count;
    //     }
    // };
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
                ListNode *next = curr->next;
                curr->next = prev;
                prev = curr;
                curr = next;
            } 
            return prev;    
        }
    };
//-------------------------------------------------------------
// 217. Contains Duplicate
    // if has duplicate, return true. else false
    // O(n) time, O(n) space

    class Solution {
    public:
        bool containsDuplicate(vector<int>& nums) {
            unordered_set<int> uSet;
            
            for (int i = 0; i < nums.size(); i++) {
                uSet.insert(nums[i]);
                
                if (uSet.size() != i + 1) 
                    return true;
            }
            return false;
        }
    };
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
            
            swap(root->left, root->right);              // .swap() is built-in!

            // TreeNode *currLeft = root->left;           // don't need to do this
            // root->left = root->right;
            // root->right = currLeft;
            
            invertTree(root->left);
            invertTree(root->right);

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
                
                if (currNode->left)
                    st.push(currNode->left);
                if (currNode->right)
                    st.push(currNode->right);
                
                swap(currNode->left, currNode->right);      // can swap before or after pushing to stack
            }
            return root;
        }
    };
//-------------------------------------------------------------
// 235. Lowest Common Ancestor of a Binary Search Tree
    // O(n) time worst case.. O(h) time average, O(1) space

    struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;
        
        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
    };

    class Solution {
    public:
        TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
            while (root)
            {
                if (p->val < root->val && q->val < root->val)
                    root = root->left;
                else if (p->val > root->val && q->val > root->val)
                    root = root->right;
                else
                    return root;
            }
            return root;    
        }
    };
//-------------------------------------------------------------
// 238. Product of Array Except Self
    // O(n) time, O(1) space (not including answer array)

    class Solution {
    public:
        vector<int> productExceptSelf(vector<int>& nums) {
            int size = nums.size();
            
            vector<int> answer(size, 1);

            int product = 1;
            
            for (int i = 0; i < size; i++)
            {
                answer[i] *= product;
                product *= nums[i];   
            }
            
            product = 1;
            
            for (int i = size-1; i >= 0; i--)
            {
                answer[i] *= product;
                product *= nums[i];   
            }
            return answer;
        }
    };
//-------------------------------------------------------------
// 242. Valid Anagram
    // given two strings (lowercase char only) determine if anagram
    // O(n) time, O(1) space

    class Solution {
    public:
        bool isAnagram(string s, string t) {
            if (s.size() != t.size()) return false;
            
            int arr[26] = {};

            for (auto c:s)
            {
                arr[int(c) - 97]++;
            }
            
            for (auto c:t)
            {
                if (arr[int(c)-97] == 0) return false;
                arr[int(c)-97]--;
            }
            return true;
        }
    };
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
// 252. Meeting Rooms
    // O(nlogn) time, O(1) space

    class Solution {
    public:
        bool canAttendMeetings(vector<vector<int>>& intervals) {
            sort(intervals.begin(), intervals.end());
            
            for (int i = 1; i < intervals.size(); i++)
            {
                if (intervals[i][0] < intervals[i-1][1]) 
                    return false;    
            }
            return true;  
        }
    };
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
// 268. Missing Number
    // O(n) time, O(1) space 

    class Solution {
    public:
        int missingNumber(vector<int>& nums) {
            int sum = 0, size = nums.size();

            for (auto num:nums)
            {
                sum += num;
            }
            return (size * (size + 1)/2) - sum;   

            // return (size * (size + 1)/2) - accumulate(nums.begin(), nums.end(), 0);          // .accumulate()
        }                                                                                       // int product = accumulate(v.begin(), v.end(), 1, std::multiplies<int>());
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
// 572. Subtree of Another Tree
    // O(n*m) time. average O(nlogm) ?      // for each of n nodes, there is max m computations
    // O(logn + logm) space ?               // height of each tree together

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
        bool isSameTree(TreeNode* a, TreeNode* b)
        {
            if (!a || !b) return a == b;
            if (a->val != b->val) return false;
            return isSameTree(a->left, b->left) && isSameTree(a->right, b->right);
        }
        
        bool isSubtree(TreeNode* root, TreeNode* subRoot) {
            stack<TreeNode*> st;
            st.push(root);
            
            while (st.size())
            {
                TreeNode *currNode = st.top();
                st.pop();
                
                if (currNode->val == subRoot->val && isSameTree(currNode, subRoot))
                    return true;
            
                if (currNode->left)
                    st.push(currNode->left);
                if (currNode->right)
                    st.push(currNode->right);
            }
            return false;
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