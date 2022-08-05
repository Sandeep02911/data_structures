#include <bits/stdc++.h>
using namespace std;

class TreeNode {
public:
	int val;
	TreeNode* left, *right;

	TreeNode(int val) : val(val), left(NULL), right(NULL){}
	TreeNode(int val, TreeNode* left, TreeNode* right) : val(val), left(left), right(right){}
};

template <class T>
void printv(vector<T> v) {
	for(auto x: v) cout<<x<<" ";
	cout<<endl;
}

void printv(vector<vector<int>> v) {
	for(auto row: v) {
		for(auto x: row) {
			cout<<x<<" ";
		}
		cout<<endl;
	}
}



// void printst(stack<pair<TreeNode*, int>> st) {
// 	cout<<"---------------stack.begin()------------------"<<endl;
// 	while(st.size()) {
// 		auto p = st.top();
// 		st.pop();
// 		cout<<p.first->val<<" "<<p.second<<endl;
// 	}
// 	cout<<"----------------stack.end()----------------------\n\n\n"<<endl;
// }

void constructBinaryTree(TreeNode* root, vector<string>& arr) {
	int n = arr.size();
	if(n == 1) return;

	int i = 1;
	queue<TreeNode*> que;
	que.push(root);

	while(que.size()) {
		TreeNode* node = que.front();
		que.pop();

		if(i < n) {
			if(arr[i] != "null" && arr[i] != "n") {
				node->left = new TreeNode(stoi(arr[i]));
				que.push(node->left);
			}
			i++;
		}

		if(i < n) {
			if(arr[i] != "null" && arr[i] != "n") {
				node->right = new TreeNode(stoi(arr[i]));
				que.push(node->right);
			}
			i++;
		}
	}
}

TreeNode* buildTree(string str) {
	int n = str.size();
	str = str.substr(1, n-2);
	vector<string> arr;
	int prev = 0;
	for (int i = 0; i < n; ++i)
	{	
		if(str[i] == ',') {
			arr.push_back(str.substr(prev, i-prev));
			while(i < n && str[i+1] == ' ')i++;
			prev = i+1;
		}
	}
	arr.push_back(str.substr(prev, n-prev));
	TreeNode* root = new TreeNode(stoi(arr[0]));
	constructBinaryTree(root, arr);
	return root;
}

vector<int> inorderTraversal(TreeNode* root) {
	if(!root) return{};

	vector<int> left = inorderTraversal(root->left);
	left.push_back(root->val);
	vector<int> right = inorderTraversal(root->right);
	left.insert(left.end(), right.begin(), right.end());
	return left;
}

vector<int> preorderTraversal(TreeNode* root) {
	if(!root) return{};

	vector<int> res;
	res.push_back(root->val);
	vector<int> left = inorderTraversal(root->left);
	vector<int> right = inorderTraversal(root->right);
	res.insert(res.end(), left.begin(), left.end());
	res.insert(res.end(), right.begin(), right.end());
	return res;
}

vector<int> postorderTraversal(TreeNode* root) {
	if(!root) return{};

	vector<int> res;
	vector<int> left = postorderTraversal(root->left);
	vector<int> right = postorderTraversal(root->right);
	res.insert(res.end(), left.begin(), left.end());
	res.insert(res.end(), right.begin(), right.end());
	res.push_back(root->val);

	return res;
}

// getbottomView --> bfs

vector<int> getbottomViewIterative(TreeNode* root) {
	queue<pair<TreeNode*, int>> que;
	map<int, int> mp;

	que.push({root, 0});
	while(que.size()) {
		auto p = que.front();
		que.pop();

		mp[p.second] = p.first->val;
		if(p.first->left) que.push({p.first->left, p.second-1});
		if(p.first->right) que.push({p.first->right, p.second+1});
	}

	vector<int> ans;
	for(auto x: mp) {
		ans.push_back(x.second);
	}
	return ans;
}

void bottomViewHelper(TreeNode* root, map<int, pair<int, int>>& mp, int vl, int hl) {
	if(!root) return;

	if(mp.find(vl) == mp.end() || (mp[vl].second < hl)) {
		mp[vl] = {root->val, hl};
	} 

	bottomViewHelper(root->left, mp, vl-1, hl+1);
	bottomViewHelper(root->right, mp, vl+1, hl+1);
}


// getbottomView --> dfs
vector<int> getbottomView(TreeNode* root) {
	map<int, pair<int, int>> mp;
	bottomViewHelper(root, mp, 0, 0);

	vector<int> ans;
	for(auto x: mp) {
		ans.push_back(x.second.first);
	}

	return ans;
}


vector<int> gettopView(TreeNode* root) {
	queue<pair<TreeNode*, int>> que;
	map<int, int> mp;

	que.push({root, 0});
	while(que.size()) {
		auto p = que.front();
		que.pop();

		if(mp.find(p.second) == mp.end())
			mp[p.second] = p.first->val;
		if(p.first->left) que.push({p.first->left, p.second-1});
		if(p.first->right) que.push({p.first->right, p.second+1});
	}

	vector<int> ans;
	for(auto x: mp) {
		ans.push_back(x.second);
	}
	return ans;
}

vector<vector<int>> getPreInPost(TreeNode* root) {
	if(!root) return {};

	stack<pair<TreeNode*, int>> st;
	st.push({root, 0});

	vector<vector<int>> ans(3);

	while(st.size()) {
		// printst(st);
		auto &p = st.top();

		if(p.second == 0) {
			ans[0].push_back(p.first->val);
			p.second++;
			if(p.first->left) st.push({p.first->left, 0});
		} else if(p.second == 1) {
			ans[1].push_back(p.first->val);
			p.second++;
			if(p.first->right) st.push({p.first->right, 0});
		} else {
			ans[2].push_back(p.first->val);
			st.pop();
		}
	}

	return ans;
}

int getMaxWidth(TreeNode* root) {
	if(!root) return 0;

	queue<pair<TreeNode*, unsigned long long>> q;
	q.push({root, 0});
	unsigned long long max_ = 0;
	while(q.size()) {
		int size = q.size();

		unsigned long long left, right;
		unsigned long long currMin = q.front().second;
		for(int i = 0; i < size; i++) {
			auto p = q.front();
			q.pop();
			
			unsigned long long curr_idx = p.second-currMin;
			if(i == 0) left = curr_idx;
			if(i == size-1) right = curr_idx;
			
			// cout<<curr_idx<<endl;
			
			if(p.first->left)
				q.push({p.first->left, 2*curr_idx+1});
			if(p.first->right)
				q.push({p.first->right, 2*curr_idx+2});
		}

		max_ = max(max_, right-left+1); 
		// cout<<max_<<endl;
		// cout<<endl;
	}

	return (int)max_;
}


vector<vector<int>> getVerticalOrderTraversal(TreeNode* root) {
        if(!root) return {};

		map<int, map<int, multiset<int>>> mp;
		queue<pair<TreeNode*, pair<int, int>>> que;
		que.push({root, {0, 0}});

		while(que.size()) {
			auto p = que.front();
			que.pop();
			TreeNode* node = p.first;
			int vl = p.second.first;
			int hl = p.second.second;

			mp[vl][hl].insert(node->val);

			if(node->left) {
				que.push({node->left, {vl-1, hl+1}});
			}

			if(node->right) {
				que.push({node->right, {vl+1, hl+1}});
			}
		}

		vector<vector<int>> ans;
		for(auto y: mp) {
			vector<int> v;
			for(auto x: y.second) {
				v.insert(v.end(), x.second.begin(), x.second.end());
			}
			ans.push_back(v);
		}

		return ans;
}

vector<vector<int>> getlevelOrderTraversal(TreeNode* root) {
	if(!root) return {};
	vector<vector<int>> ans;
	queue<TreeNode*> q;
	q.push(root);

	while(q.size()) {
		int size = q.size();

		vector<int> level;
		for(int i = 0; i < size; i++) {
			TreeNode* node = q.front();
			q.pop();

			level.push_back(node->val);
			if(node->left) q.push(node->left);
			if(node->right) q.push(node->right);
		}

		ans.push_back(level);
	}

	return ans;
}

int height(TreeNode* root) {
	if(!root) return 0;

	return max(height(root->left), height(root->right) + 1);
}

pair<int, int> diameterOfBinaryTreeHelper(TreeNode* root) {
	if(!root) return {0, -1};

	pair<int, int> lp = diameterOfBinaryTreeHelper(root->left);
	pair<int, int> rp = diameterOfBinaryTreeHelper(root->right);
	pair<int, int> mp = {max(max(lp.first, rp.first), lp.second + rp.second+2), max(lp.second, rp.second)+1};
	return mp;
}

int diameterOfBinaryTree(TreeNode* root) {
	if(!root) return 0;

	pair<int, int> p = diameterOfBinaryTreeHelper(root);
	return p.first;
}

TreeNode* getLca(TreeNode* root, int p, int q) {
	if(!root || root->val == p || root->val == q) return root;

	TreeNode* left = getLca(root->left, p, q);
	TreeNode* right = getLca(root->right, p, q);

	if(left && right) {
		return root;
	} else if(left) {
		return left;
	} else {
		return right;
	}
}

bool areTreesSame(TreeNode* p, TreeNode* q) {
	if(!p && !q) return true;
	if(!p || !q) return false;

	if(p->val != q->val) return false;

	return areTreesSame(p->left, q->left) && areTreesSame(p->right, q->right);
}

vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
	if(!root) return {};

	queue<TreeNode*> que;
	que.push(root);

	vector<vector<int>> ans;
	bool flag = true;
	while(que.size()) {
		int size = que.size();

		vector<int> row(size);
		for(int i = 0; i < size; i++) {
			TreeNode* node = que.front();
			que.pop();
			
			int idx = flag ? i : size-1-i;
			row[idx] = node->val;

			if(node->left) que.push(node->left);
			if(node->right) que.push(node->right);
		}
		flag = !flag;
		ans.push_back(row);
	}

	return ans;
}

bool isLeafNode(TreeNode* root) {
	return !root->left && !root->right;
}

void addleftBoundary(TreeNode* root, vector<int>& ans) {
	TreeNode* curr = root->left;

	while(curr) {
		if(!isLeafNode(curr)) ans.push_back(curr->val);
		if(curr->left) {
			curr = curr->left;
		} else {
			curr = curr->right;
		}
	}
}

void addrightBoundary(TreeNode* root, vector<int>& ans) {
	TreeNode* curr = root->right;

	vector<int> temp;
	while(curr) {
		if(!isLeafNode(curr)) temp.push_back(curr->val);
		if(curr->right) {
			curr = curr->right;
		} else {
			curr = curr->left;
		}
	}

	for(int i = temp.size()-1; i >= 0; i--) {
		ans.push_back(temp[i]);
	}
}

void addLeaves(TreeNode* root, vector<int>& ans) {
	if(!root) return;

	if(isLeafNode(root)) {
		ans.push_back(root->val);
		return;
	}

	addLeaves(root->left, ans);
	addLeaves(root->right, ans);
}

vector<int> boundaryTraversal(TreeNode* root) {
	if(!root) return {};

	vector<int> ans;
	if(!isLeafNode(root)) ans.push_back(root->val);
	addleftBoundary(root, ans);
	addLeaves(root, ans);
	addrightBoundary(root, ans);
	return ans;
}

int getMaxPathSumHelper(TreeNode* root, int& max_) {
	if(!root) return 0;

	int lsum = max(0, getMaxPathSumHelper(root->left, max_));
	int rsum = max(0, getMaxPathSumHelper(root->right, max_));
	max_ = max(max_, root->val + lsum + rsum);

	return root->val + max(lsum , rsum);
}

int getMaxPathSum(TreeNode* root) {
	int max_ = INT_MIN;
	getMaxPathSumHelper(root, max_);
	return max_;
}

TreeNode* buildTreeFromPreAndInHelper(vector<int>& preorder, vector<int>& inorder, int inSt, int inEnd, int preSt, unordered_map<int, int>& mp) {
	if(inSt > inEnd) {
		return NULL;
	}

	TreeNode* root = new TreeNode(preorder[preSt]);
	int idx = mp[preorder[preSt]];
	root->left = buildTreeFromPreAndInHelper(preorder, inorder, inSt, idx-1, preSt+1, mp);
	root->right = buildTreeFromPreAndInHelper(preorder, inorder, idx+1, inEnd, preSt+(idx-inSt)+1, mp);
	return root;
}

TreeNode* buildTreeFromPreAndIn(vector<int>& preorder, vector<int>& inorder) {
    unordered_map<int, int> mp;
	for (int i = 0; i < inorder.size(); i++) {
		mp[inorder[i]] = i;
	}

	return buildTreeFromPreAndInHelper(preorder, inorder, 0, preorder.size()-1, 0, mp);
}

TreeNode* buildTreeFromPostAndInHelper(vector<int>& postorder, vector<int>& inorder, int inSt, int inEnd, int postSt, int postEnd, unordered_map<int, int>& mp) {
	if(inSt > inEnd) {
		return NULL;
	}
	
	// cout<<"postEnd-> "<<postEnd<<" && inSt -> "<<inSt<<" && inEnd-> "<<inEnd<<endl;
	TreeNode* root = new TreeNode(postorder[postEnd]);
	int idx = mp[postorder[postEnd]];
	
	root->left = buildTreeFromPostAndInHelper(postorder, inorder, inSt, idx-1, postSt, postEnd-(inEnd-idx)-1, mp);
	root->right = buildTreeFromPostAndInHelper(postorder, inorder, idx+1, inEnd, postEnd-(inEnd-idx), postEnd-1, mp);
	return root;
}

TreeNode* buildTreeFromPostAndIn(vector<int>& postorder, vector<int>& inorder) {
	int n = inorder.size();
	unordered_map<int, int> mp;
	for (int i = 0; i < n; i++) {
		mp[inorder[i]] = i;
	}

	TreeNode* node = buildTreeFromPostAndInHelper(postorder, inorder, 0, n-1, 0, n-1, mp);
	// cout<<"node->val : "<<node->val<<endl;
	// printv(getlevelOrderTraversal(node));
	return node;
}

TreeNode* mirror(TreeNode* root) {
	if(!root) return NULL;

	TreeNode* l = mirror(root->left);
	TreeNode* r = mirror(root->right);
	root->right = l;
	root->left = r;

	return root;
}

TreeNode* mirror2(TreeNode* root) {
	if(!root) return root;

	queue<TreeNode*> que;
	que.push(root);
	while(que.size()) {
		TreeNode* node = que.front();
		que.pop();

		swap(root->left, root->right);
		if(root->left) que.push(root->left);
		if(root->right) que.push(root->right);
	}

	return root;
}

bool isSameTree(TreeNode* root1, TreeNode* root2) {
	if(!root1 && !root2) return true;
	if(!root1 || !root2) return false;

	return root1->val == root2->val && isSameTree(root1->left, root2->right) && isSameTree(root1->right, root2->left);
}

bool isTreeSymmetric(TreeNode* root) {
	if(!root) return true;
	return isSameTree(root->left, root->right);
}


TreeNode* prevNode = NULL;
void flattenBinaryTree(TreeNode* root) {
	if(!root) return;

	flattenBinaryTree(root->right);
	flattenBinaryTree(root->left);

	root->left = NULL;
	root->right = prevNode;
	prevNode = root;
}

void flattenBinaryTree2(TreeNode* root) {
	if(!root) return;

	while(root) {
		TreeNode* curr = root->left;
		if(curr) {
			while(curr->right) curr = curr->right;
			curr->right = root->right;
			root->right = root->left;
			root->left = NULL;
		}
		root = root->right;
	}
}

void printFlattenTree(TreeNode* root) {
	while(root) {
		cout<<root->val<<" ";
		root = root->right;
	}

	cout<<endl;
}

void changeTreeToChildrenSumPropertyHelper(TreeNode* root, int &diff) {
	if(!root) return;

	root->val += diff;
	if(root->left)
		changeTreeToChildrenSumPropertyHelper(root->left, diff);
	else 
		changeTreeToChildrenSumPropertyHelper(root->right, diff);
}

void changeTreeToChildrenSumProperty(TreeNode* root) {
	if(!root) return;

	changeTreeToChildrenSumProperty(root->left);
	changeTreeToChildrenSumProperty(root->right);

	int diff = root->val;
	if(root->left) diff -= root->left->val;
	if(root->right) diff -= root->right->val;
	if(diff > 0) {
		if(root->left) changeTreeToChildrenSumPropertyHelper(root->left, diff);
		else changeTreeToChildrenSumPropertyHelper(root->right, diff);
	} else if(diff < 0) {
		root->val -= diff;
	}
}

void solve() {
	string str;

	ifstream fs;
	fs.open("input.txt");
	string word;
	while(fs>>word) {
		str += word;
	}
	fs.close();

	TreeNode* root = buildTree(str);

	vector<int> inOrder = inorderTraversal(root);
	cout<<"inOrder -> ";
	printv(inOrder);

	vector<int> preOrder = preorderTraversal(root);
	cout<<"preOrder ->";
	printv(preOrder);
	
	vector<int> postOrder = postorderTraversal(root);
	cout<<"postOrder ->";
	printv(postOrder);
	
	vector<int> bottomView = getbottomView(root);
	cout<<"bottomView ->";
	printv(bottomView);
	
	vector<int> topView = gettopView(root);
	cout<<"topView ->";
	printv(topView);

	vector<vector<int>> preInPost = getPreInPost(root);
	printv(preInPost);

	cout<<"maxWidth -> "<<getMaxWidth(root)<<endl;

	TreeNode* curr = buildTree("[1,2,3,4,6,5,7]");
	vector<vector<int>> verticalOrderTraversal = getVerticalOrderTraversal(curr);
	cout<<"verticalOrder"<<endl;
	printv(verticalOrderTraversal);

	vector<vector<int>> levelOrder = getlevelOrderTraversal(root);
	cout<<"levelOrder traversal: "<<endl;
	printv(levelOrder);

	cout<<"height -> "<<height(root)<<endl;
	cout<<"diameter -> "<<diameterOfBinaryTree(root)<<endl;

	cout<<"lca for 4 and 5 is : "<<getLca(root, 4, 5)->val<<endl;

	TreeNode* p = buildTree("[1,2,3]");
	TreeNode* q = buildTree("[1,2,3,4]");
	cout<<(areTreesSame(p, q) ? "The Two trees are same" : "The two trees are different")<<endl;

	vector<vector<int>> zigzagTraversal = zigzagLevelOrder(root);
	cout<<"zigzagTraversal : "<<endl;
	printv(zigzagTraversal);

	vector<int> bt = boundaryTraversal(root);
	cout<<"boundaryTraversal: ";
	printv(bt);


	vector<int> inorder{9,3,15,20,7};

	cout<<endl;
	vector<int> preorder{3,9,20,15,7};
	TreeNode* treeFromPreAndIn = buildTreeFromPreAndIn(preorder, inorder);
	cout<<treeFromPreAndIn->val<<endl;
	cout<<"Level order traversal of treeFromPreAndIn:"<<endl;
	printv(getlevelOrderTraversal(treeFromPreAndIn));

	cout<<endl;
	vector<int> postorder{9,15,7,20,3};
	TreeNode* treeFromPostAndIn = buildTreeFromPostAndIn(postorder, inorder);
	cout<<"Level order traversal of treeFromPostAndIn:"<<endl;
	printv(getlevelOrderTraversal(treeFromPostAndIn));

	cout<<endl;
	cout<<"Mirror -> "<<endl;
	cout<<"Old tree: "<<endl;
	printv(getVerticalOrderTraversal(root));
	cout<<"Mirrored tree: "<<endl;
	printv(getVerticalOrderTraversal(mirror(root)));

	cout<<endl;
	TreeNode* symmetric = buildTree("[1,2,2,3,4,4,3]");
	bool isSymmetric = isTreeSymmetric(symmetric);
	cout<<(isSymmetric ? "Tree is symmetric" : "Tree is not symmetric")<<endl;

	cout<<endl;
	TreeNode* flatten = buildTree("[1,2,5,3,4,null,6]");
	flattenBinaryTree2(flatten);
	cout<<"flattened binary tree -> ";
	printFlattenTree(flatten);

	cout<<endl;
	TreeNode* maxPathSum = buildTree("[-10,9,20,null,null,15,7]");
	cout<<"max Path sum is -> "<<getMaxPathSum(maxPathSum);

	cout<<endl;
	TreeNode* changeTree = buildTree("[50,7,2,3,5,1,30]");
	cout<<"Change tree to children sum property:"<<endl;
	cout<<"before changing -> "<<endl;
	printv(getlevelOrderTraversal(changeTree));
	changeTreeToChildrenSumProperty(changeTree);
	cout<<"after change -> "<<endl;
	printv(getlevelOrderTraversal(changeTree));
}


int main() {
	solve();
	return 0;
}