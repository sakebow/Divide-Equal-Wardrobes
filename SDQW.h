#include <iostream>
#include <stack>
#include <vector>
using namespace std;

typedef struct node {
	int data;
	struct node* son, * bro;
} Node;
Node* start(int* a,int n); 
vector<int> showNode(Node* node);
Node* createson( int* a, int n);
Node* createbro( int* a, int n, int j);