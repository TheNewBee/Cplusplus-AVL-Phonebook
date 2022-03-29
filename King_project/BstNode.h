#ifndef BST_NODE_H
#define BST_NODE_H

#include <string>
using namespace std;

class BstNode {
	public:
		BstNode* left;
		BstNode* right;
		string* data;		// An array to save to data
		int height;
};

#endif
