#include "Bst.h"

// Constructor of AVL tree
Bst::Bst() {
	total = 0;
	dataSize = 1;
	root = NULL;
	key = 4;
}

Bst::Bst(int iDataSize) {
	total = 0;
	dataSize = iDataSize;
	root = NULL;
	key = 15;
}

// Destructor of AVL tree
Bst::~Bst() {
	makeEmpty(root);
}

// Insert data to AVL tree
void Bst::insert(string* iData) {
	iData[11] = toNumber(iData[11]);
	root = insert(iData, root);
}

BstNode* Bst::insert(string* iData, BstNode* t) {
	if (t == NULL) {													// Case 1. BstNode is empty, insert new BstNode under root
		t = new BstNode;
		t->height = 0;
		t->left = t->right = NULL;
		string* newData = new string[dataSize];
		for (int i = 0; i < dataSize; i++)
			newData[i] = iData[i];
		t->data = newData;
		//cout << iData << " " << *iData << " " << &iData << endl;
		//cout << t->data << " " << *t->data << " " << &t->data << endl << endl;
	} else if (iData[key] < t->data[key]) {								// Case 2. if iData < BstNode
		t->left = insert(iData, t->left);
		if (height(t->left) - height(t->right) == 2) {
			if (iData[key] < t->left->data[key])
				t = singleRightRotate(t);
			else
				t = doubleRightRotate(t);
		}
	} else if (iData[key] > t->data[key]) {								// Case 3. if iData > BstNode
		t->right = insert(iData, t->right);
		if (height(t->right) - height(t->left) == 2) {
			if (iData[key] > t->right->data[key])
				t = singleLeftRotate(t);
			else
				t = doubleLeftRotate(t);
		}
	}																	// Case 4. if x == iData, skip it

	t->height = max(height(t->left), height(t->right)) + 1;
	return t;
}

// Remove data at AVL tree
void Bst::remove(string x) {
	root = remove(x, root);
}

BstNode* Bst::remove(string x, BstNode* t) {
	BstNode* temp;

	if (t == NULL)														// Element not found
		return NULL;

	else if (x < t->data[key])											// Searching for element
		t->left = remove(x, t->left);
	else if (x > t->data[key])
		t->right = remove(x, t->right);

	else if (t->left && t->right) {										// Element found: With 2 children
		temp = findMin(t->right);
		t->data[key] = temp->data[key];
		t->right = remove(t->data[key], t->right);
	} else {															// With one or zero child
		temp = t;
		if (t->left == NULL)
			t = t->right;
		else if (t->right == NULL)
			t = t->left;
		delete temp;
	}

	if (t == NULL)
		return t;

	t->height = max(height(t->left), height(t->right)) + 1;

	if (height(t->left) - height(t->right) == 2) {						// If BstNode is unbalanced: If left BstNode is deleted, right case
		if (height(t->left->left) - height(t->left->right) == 1)		// Right right case
			return singleLeftRotate(t);
		//return singleRightRotate(t);
		else															// Right left case
			return doubleLeftRotate(t);
		//return doubleRightRotate(t);
	}
	else if (height(t->right) - height(t->left) == 2) {					// If right BstNode is deleted, left case

		if (height(t->right->right) - height(t->right->left) == 1)		// Left left case
			return singleRightRotate(t);
		//return singleLeftRotate(t);
		else															// Left right case
			return doubleRightRotate(t);
		//return doubleLeftRotate(t);
	}
	return t;
}

// Search Node by key, return the Node when the Node->data[key] exactly equal key
BstNode* Bst::search(string x) {
	return search(x, root);
}

BstNode* Bst::search(string s, BstNode* t) {
	if (t == NULL)
		return NULL;
	else if (!s.compare(t->data[key]))
		return t;
	else if (s < t->data[key])
		return search(s, t->left);
	else if (s > t->data[key])
		return search(s, t->right);
	return NULL;
}

// Search data with fist given string
BstNode* Bst::searchHalf(string x) {
	return searchHalf(x, root);
}

BstNode* Bst::searchHalf(string s, BstNode* t) {
	if (t == NULL)
		return NULL;
	else if (!t->data[key].compare(0, s.size(), s))
		return t;
	else if (s < t->data[key])
		return searchHalf(s, t->left);
	else if (s > t->data[key])
		return searchHalf(s, t->right);
	return NULL;
}

// Inorder to display all data
void Bst::display() {
	inorder(root);
	cout << endl << endl << "Total: " << total << " records" << endl;
	total = 0;
}

// Remove whole tree
void Bst::makeEmpty() {
	makeEmpty(root);
	root = NULL;
	total = 0;
}

// Delete passed BstNode and it children
void Bst::makeEmpty(BstNode* t) {											// Delete passed BstNode and it children
	if (t != NULL) {
		makeEmpty(t->left);
		makeEmpty(t->right);
		if (t->data != NULL)
			delete[] t->data;
		delete t;
		t = NULL;
	}
}

// Change the key of tree
void Bst::changeKey(int iKey) {
	makeEmpty();
	key = iKey;
}

// Rotate left sub tree
BstNode* Bst::singleLeftRotate(BstNode* &t) {
	BstNode* u = t->right;
	t->right = u->left;
	u->left = t;
	t->height = max(height(t->left), height(t->right)) + 1;
	u->height = max(height(t->right), t->height) + 1;
	return u;
}

// Rotate right sub tree
BstNode* Bst::singleRightRotate(BstNode* &t) {
	BstNode* u = t->left;
	t->left = u->right;
	u->right = t;
	t->height = max(height(t->left), height(t->right)) + 1;
	u->height = max(height(u->left), t->height) + 1;
	return u;
}

// Rotate right sub tree, and then left
BstNode* Bst::doubleLeftRotate(BstNode* &t)
{
	t->right = singleRightRotate(t->right);
	return singleLeftRotate(t);
}

// Rotate left sub tree, and then right
BstNode* Bst::doubleRightRotate(BstNode* &t) {
	t->left = singleLeftRotate(t->left);
	return singleRightRotate(t);
}

// Find Minimum value from Node and it children
BstNode* Bst::findMin(BstNode* t) {											// Return Min telephoneNumber BstNode
	if (t == NULL)
		return NULL;
	else if (t->left == NULL)
		return t;
	else
		return findMin(t->left);
}

// Find Maximum value from Node and it children
BstNode* Bst::findMax(BstNode* t) {											// Return Max telephoneNumber BstNode
	if (t == NULL)
		return NULL;
	else if (t->right == NULL)
		return t;
	else
		return findMax(t->right);
}

// Return height of Node
int Bst::height(BstNode* t) {												// Get BstNode height
	return (t == NULL ? -1 : t->height);
}

// Detect Balance of Node
int Bst::getBalance(BstNode* t) {											// Determine BstNode children is is balance
	if (t == NULL)
		return 0;
	else
		return height(t->left) - height(t->right);
}

// Visit to Node inorder
void Bst::inorder(BstNode* t) {											// LVR: retern value asscending
	if (t != NULL) {
		inorder(t->left);
		//cout << t->data[key] << " ";
		//total++;
		cout << "----------------------------------------------------------------------------------------------------" << endl <<
			++total << ".\n" << t->data[0] << " " << t->data[2] << " " << t->data[1] << " (" << t->data[3] << ")" << "\nBirthday: " << t->data[4] << endl <<
			"Address: " << t->data[5] << ", " << t->data[6] << ", " << t->data[7] << ", " << t->data[9] << " (Zip Code: " << t->data[8] << ")" << endl <<
			"Telephone: " << t->data[10] << "-" << t->data[11] << "\nEmail: " << t->data[12] << "\nCompany: " << t->data[14] << " (" << t->data[13] << ")" << endl <<
			"----------------------------------------------------------------------------------------------------" << endl;
		if (total % 10 == 0)
			cout << "====================================================================================================" << endl;
		inorder(t->right);
	}
}

// Return the tree empty or not
bool Bst::isEmpty() {
	return root == NULL;
}

// Remove symbol to string number
string Bst::toNumber(string str) {
	string strNum = "";
	for (char& c : str)
		switch (c)
			case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
				strNum += c;

	return strNum;
}
