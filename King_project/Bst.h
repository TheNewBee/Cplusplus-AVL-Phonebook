#ifndef BST_H
#define BST_H

#include "BstNode.h"
#include <algorithm>
#include <iostream>

class Bst {
	private:
		int total;
		int dataSize;
		BstNode* root;

	public:
		Bst();
		Bst(int iDataSize);
		~Bst();
		int key;

		void insert(string* iData);
		BstNode* insert(string* iData, BstNode* t);

		void remove(string x);
		BstNode* remove(string x, BstNode* t);

		BstNode* search(string x);
		BstNode* search(string s, BstNode* t);
		BstNode* searchHalf(string x);
		BstNode* searchHalf(string s, BstNode* t);

		void display();
		void makeEmpty();						//delete passed BstNode and it children
		void makeEmpty(BstNode* t);				//delete passed BstNode and it children

		void changeKey(int iKey);

		BstNode* singleLeftRotate(BstNode* &t);
		BstNode* singleRightRotate(BstNode* &t);
		BstNode* doubleLeftRotate(BstNode* &t);
		BstNode* doubleRightRotate(BstNode* &t);
		BstNode* findMin(BstNode* t);					//return Min data BstNode
		BstNode* findMax(BstNode* t);					//return Max data BstNode

		int height(BstNode* t);					//get BstNode height
		int getBalance(BstNode* t);				//determine BstNode children is is balance
		void inorder(BstNode* t);					//LVR: retern value asscending
		bool isEmpty();							//return the tree empty or not
		string toNumber(string str);
};

#endif
