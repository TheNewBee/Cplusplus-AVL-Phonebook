#ifndef SINGLYLIST_H
#define SINGLYLIST_H

#include "LLNode.h"

class SinglyList {
	private:
		LLNode* head; // a pointer to the first node in the list

	public:
		SinglyList();	// constructor
		~SinglyList();	// destructor
						// isEmpty determines whether the list is empty or not
		bool isEmpty();
		// insertNode inserts a new node at position "index"
		LLNode* insertNode(int index, BstNode* x);
		// findNode finds the position of the node with a given value
		int findNode(BstNode* x);
		// deleteNode deletes a node with a given value
		BstNode* deleteNode(BstNode* x);
		// displayList prints all the nodes in the list
		void displayList();

		// set head node
		void setHead(LLNode*);
		// get head node
		LLNode* getHead();
};

#endif