#include "SinglyList.h"
#include <string>
#include <iostream>
using namespace std;

// Constructor
SinglyList::SinglyList() {
	head = NULL;
}

// Destructor
SinglyList::~SinglyList() {
	LLNode* currNode = head;
	LLNode* nextNode = NULL;
	while (currNode != NULL) {
		nextNode = currNode->next;
		delete currNode;
		currNode = nextNode;
	}
}

// isEmpty determines whether the list is empty or not
bool SinglyList::isEmpty() {
	return (head==NULL);
}

// findNode finds the position of the node with a given value
int SinglyList::findNode(BstNode* x) {
	LLNode* currNode = head;
	int currIndex = 1;
	while (currNode && currNode->data != x)
	{
		currNode = currNode->next;
		currIndex++;
	}
	if (currNode)
		return currIndex;
	return 0;
}

// insertNode inserts a new node at position "index"
LLNode* SinglyList::insertNode(int index, BstNode* x) {
	if (index < 0)
		return NULL;
	int currIndex = 1;
	LLNode* currNode = head;
	while (currNode && index > currIndex) {
		currNode = currNode->next;
		currIndex++;
	}
	if (index > 0 && currNode == NULL)
		return NULL;
	LLNode* newNode = new LLNode;
	newNode->data = x;
	if (index == 0) {
		newNode->next = head;
		head = newNode;
	}
	else {
		newNode->next = currNode->next;
		currNode->next = newNode;
	}
	return newNode;
}

// deleteNode deletes a node with a given value
BstNode* SinglyList::deleteNode(BstNode* x) {
	LLNode* prevNode = NULL;
	LLNode* currNode = head;
	BstNode* bstNode = NULL;
	while (currNode && currNode->data != x)
	{
		prevNode = currNode;
		currNode = currNode->next;
	}
	if (currNode) {
		if (prevNode) {
			bstNode = currNode->data;
			prevNode->next = currNode->next;
			delete currNode;
		}
		else {
			bstNode = currNode->data;
			head = currNode->next;
			delete currNode;
		}
		return bstNode;
	}
	return NULL;
}

// displayList prints all the nodes in the list
void SinglyList::displayList() {
	int num = 0;
	LLNode* currNode = head;
	while (currNode != NULL) {
		cout << currNode->data << endl;
		currNode = currNode->next;
		num++;
	}
	cout << "Number of nodes in the list: " << num << endl;
}

void SinglyList::setHead(LLNode* nodeIn) {
	head = nodeIn;
}

LLNode* SinglyList::getHead() {
	return head;
}

