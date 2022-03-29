#ifndef MENU_H
#define MENU_H

#include "Bst.h"
#include "SinglyList.h"
#include <ctime>
#include <fstream>

class Menu {
	private:
		Bst* bstData;
		double runTime;
		int columnL;
		string columns[16];
		string mainMenuItems[9];

	public:
		Menu();						// Build main menu
		~Menu();					// Desturcter
		void insertAllData();		// Insert all data from contacts.txt
		void insertData();			// Insert one data
		void insertLots();			// Input a path of txt to insert a batch of data
		void modifyData();			// Modify Data
		void deleteData();			// Delete Node by user input key
		void searchData();			// Search data by user input key (prefix search)
		void printData();			// Print out all of Data
		void changeKey();			// Cnange the key and rebuild the tree
		void restoreData();			// Rewrite to default data
		void aboutThis();			// About our development team
		void showHeader(string title);	// Display a header
		void inOrderToFindNode(string findKey, BstNode* t, SinglyList* resultNode);				// Save the equal Node at single list
		int selectItem(string* data, int length, string title, string lastItemName, string headerTitle);	// Static function that show the menu
};

#endif
