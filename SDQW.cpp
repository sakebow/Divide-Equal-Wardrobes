#include "SDQW.h"
/**
 * time:			2022.11.16
 * author: 		sakebow
 * function:	create a multifurcating tree for storing every possibility
 * params:
 * 	shelves status array(>>> input zs <<<) -> a
 * 	depth of the tree(>>> input n <<<) -> n
 * 	current depth -> j
 * return created node -> s
*/
Node* createbro(int * a, int n, int j) {
	// create a node object
	Node * s = new Node;
	// initialize
	s->data = 0;
	s->bro = s->son = NULL;
	// from depth = j, consider all conditions
	for (; j <= n; ++j) {
		// check the shelves if movable
		if (a[j + 1] > (2000 / (n + 1) * j) && a[j] < (2000 / (n + 1) * j)) {
			// why 15? 'cause n in the examples is less than 5. should be dynamic, but never mind
			// extra cost for new & del isn't calculable somewhat
			// Anyway, set flag for every shelves
			int b[15] = { 0 };
			// if lower, stay; else, move
			for (int i = 0; i < n + 2; ++i)  b[i] = a[i];
			// I know where it should be, so set it
			b[j] = (2000 / (n + 1) * j);
			// check the next
			s->data = j;
			// move to the next depth
			s->son = createson( b, n);
			// until the last depth
			if (j == n) return s;
			// recursion for every shelf
			s->bro = createbro(a, n, j + 1);
			return s;
		}
	}
	// s for return means root node, even if s isn't root in loops
	return s;
}
 
/**
 * time:			2022.11.16
 * author: 		sakebow
 * function:	move to the next depth of recursion
 * params:
 * 	shelves status array(>>> input zs <<<) -> a
 * 	depth of the tree(>>> input n <<<) -> n
*/
Node* createson( int* a, int n) {
	// create a node object
	Node* s = new Node;
	// initialize
	s->data = 0;
	s->bro = s->son = NULL;
	// for every shelf in recursion
	for (int j = 1; j <= n; ++j)
		// check the shelves if movable
		if (a[j + 1] > (2000 / (n + 1) * j) && a[j] < (2000 / (n + 1) * j)) {
			// same
			int b[15] = { 0 };
			for (int i = 0; i < n + 2; ++i)  b[i] = a[i];
			b[j] = (2000 / (n + 1) * j);
			s->data = j;
			s->son = createson( b, n);
			if (j == n) return s;
			s->bro = createbro(a, n, j + 1);
			// this is a function of an epoch, not episode, so just break, not return
			break;
		}
	return s;
}

/**
 * time:			2022.11.16
 * author: 		sakebow
 * function:	use createbro & createson to struct a whole multifurcating tree
 * params:
 * 	shelves status array(>>> input zs <<<) -> a
 * 	depth of the tree(>>> input n <<<) -> n
 * extra:
 * 	to be serious, this should be the entrance of the whole program
*/
Node* start(int* a, int n) {
	// create the very start node
	// >>> TAKE CARE <<<
	// the root do not get any function but is just a signal of the very beginning
	Node * root = new Node;
	// initialize
	root->data = 0;
	// then the next depth of the multifurcating tree
	Node * p = new Node;
	root->son = p;
	p->bro = p->son = NULL;
	//n为多叉树的层数
	for (int j = 1; j <= n; ++j)
		// same
		if (a[j + 1] > (2000 / (n + 1) * j) && a[j] < (2000 / (n + 1) * j)) {
			int b[15] = { 0 };
			for (int i = 0; i < n+2; ++i) b[i] = a[i];
			b[j] = (2000 / (n + 1) * j);
			p->data = j;
			p->son = createson(b, n);
			if (j == n) break;
			p->bro = createbro(a, n, j + 1);
			break;
		}
		return root;
}

/**
 * time:			2022.11.16
 * author: 		sakebow
 * function:	use DFS to search the multifurcating tree for correct answers
 * params:
 * 	the node after the very start node -> node
 * returns:
 * 	solutions -> vector<int>
*/
vector<int> showNode(Node* node) {
	vector<int> v;
	stack<Node*> s, s2;
	// take the 2nd floor as beginning
	s.push(node);
	// start searching
	while (!s.empty()) {
		// get the top element of the stack
		Node * treeNode = s.top();
		// if not NULL or non-positive, lower leaves first
		if (treeNode->son->data) s.push(treeNode->son);
		// if NULL, start checking
		else {
			// invert twice for losslessly data gathering
			while (!s.empty()) { s2.push(s.top()); s.pop();	}
			while (!s2.empty()) {
				v.push_back(s2.top()->data);
				s.push(s2.top());
				s2.pop();
			}
			// check the brother nodes
			while (!treeNode->bro->data) {
				// the last node is tail, no data here. pop it out 
				s.pop();
				// get the next floor
				treeNode = s.top();
				// until all the floors get checked, clean the stack
				if (treeNode->bro == NULL) { s.pop();	break; }
			}
			// if there's element in stack, get the next floor
			if (!s.empty()) {
				treeNode = s.top();
				s.pop();
				// push the start node of the next floor
				s.push(treeNode->bro);
			}
		}
	}
	// return solutions
	return v;
}

/**
 * time:			2022.11.16
 * author: 		sakebow
 * function:	main entrance of the whole program
 * params:		NULL
 * returns:		status code for program
 * 	0 for normal exit
 * -1 for abnormal
*/
int main()
{
	// >>> example 1 <<<
	// zs = {bottom, zs, top}
	// int n = 3;
	// int zs[n + 2] = { 0,50,60,1000,2000 };

	// >>> example 2 <<<
	// a = {bottom, zs, top}
	int n = 4;
	int zs[n + 2] = { 0,50,600,700,1000,2000 };
	
	Node *root = start(zs, n);
	vector <int>  v = showNode(root->son);
	// output solution
	int q = 0;
	for (int i = 0; i < v.size(); ++i) {
		cout << v[i];
		++q;
		if (q == n) { cout << endl; q = 0; }
		else cout << ", ";
	}
	return 0;
}