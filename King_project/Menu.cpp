#include "Menu.h"

// Build main menu
Menu::Menu() {
	clock_t startTime = clock();		// Set start time
	runTime = 0.0;
	bool loop = true;
	int mainMenuItemL = 9;
	string copyColumns[16] = { 
		"Title", "Surname", "Given Name", "Gender", "Birthday",
		"Street Address", "City", "State Full", "Zip Code", "Country Full",
		"Telephone Country Code", "Telephone Number", "Email Address", "Occupation", "Company", "Full Name" };
	string copyMainMenuItems[9] = { 
		"Insert a record", "Insert lots of records", "Modify record", "Delete record", 
		"Search record", "Print records", "Change search key", "[*!!*]Restore to default data", "About this" };

	columnL = 16;
	bstData = new Bst(columnL);
	for (int i = 0; i < columnL; i++)
		columns[i] = copyColumns[i];
	for (int i = 0; i < mainMenuItemL; i++)

		mainMenuItems[i] = copyMainMenuItems[i];

	cout << "System is preparing, please wait..." << endl;
	insertAllData();		// insert all data form txt
	while(loop) {
		showHeader("Main Menu");
		int choice = selectItem(mainMenuItems, mainMenuItemL, "function", "Exit", "Main Menu");
		system("cls");
		switch(choice) {
			case 0: showHeader("Good Bye!");
				cout << "Thanks for using! Hope to see you again!" << endl;
				loop = false;
				break;
			case 1: insertData();
				break;
			case 2: insertLots();
				break;
			case 3: modifyData();
				break;
			case 4: deleteData();
				break;
			case 5: searchData();
				break;
			case 6: printData();
				break;
			case 7: changeKey();
				break;
			case 8: restoreData();
				break;
			case 9: aboutThis();
				break;
		}
		system("pause");
	}
	clock_t endTime = clock();		// Set end time
	runTime = (double)(endTime - startTime) / CLOCKS_PER_SEC;	// Saving the different time
}

Menu::~Menu() {
	bstData->makeEmpty();
	delete bstData;
}

void Menu::insertAllData() {
	clock_t startTime = clock();
	int dataL = 150000, columnL = 16;
	ifstream inputFile("Contacts.txt");

	int stop = 0;
	while (!inputFile.eof() && stop++ < dataL) {
		int i = 0;									// Assign data the string until the source empty
		string strLine = "", strData = "";
		string* columns = new string[columnL];
		getline(inputFile, strLine);

		for (char& c : strLine) {
			if (c == '\t') {
				columns[i++] = strData;
				strData = "";
			}
			else
				strData += c;
		}
		columns[14] = strData;
		columns[15] = columns[2] + "_" + columns[1];		// Full_name
		bstData->insert(columns);
		delete[] columns;
	}
	inputFile.close();
	clock_t endTime = clock();
	runTime = (double)(endTime - startTime) / CLOCKS_PER_SEC;
}

/*void Menu::insertData() {
	cout << "Please insert the following details in order (Use BACKSPACE to separate them): " << endl
		<< "[Title, Surname, Given Name, Gender, Birthday, Street Address, City, State Full, Zip Code, Country Full, Telephone Country Code, Telephone, Email Address, Occupation, Company]" << endl << endl;

	string* columns = new string[15];
	for (int i = 0; i < 15; i++) {
		cin >> columns[i];
	}
	bstData->insert(columns[11], columns[0], columns[1], columns[2], columns[3], columns[4], columns[5], columns[6], columns[7], atoi(columns[8].c_str()), columns[9], atoi(columns[10].c_str()), columns[12], columns[13], columns[14]);
	delete[] columns;
	bstData->display();
}*/

void Menu::insertData() {
	clock_t startTime = clock();
	showHeader(mainMenuItems[0]);
	string *stores = new string[16];

	cout << "Please insert the following details: " << endl;
	for (int i = 0; i < 15; i++) {
		cout << endl << columns[i] << ": ";
		cin >> stores[i];
	}
	stores[15] = stores[2] + "_" + stores[1];

	bstData->insert(stores);
	//delete[] stores;
	//bstData->display();
	clock_t endTime = clock();
	runTime = (double)(endTime - startTime) / CLOCKS_PER_SEC;
}

// Input a path of txt to insert a batch of data 
void Menu::insertLots() {
	clock_t startTime = clock();
	showHeader(mainMenuItems[1]);
	int columnL = 16;
	string path;
	cout << "Input the path of the file: ";
	cin.ignore();
	getline(cin, path);
	ifstream inputFile(path);

	if (inputFile) {
		while (!inputFile.eof()) {
			int i = 0;
			string strLine = "", strData = "";
			string* inputData = new string[columnL];
			getline(inputFile, strLine);

			for (char& c : strLine) {
				if (c == '\t') {
					inputData[i++] = strData;
					strData = "";
				}
				else
					strData += c;
			}
			columns[14] = strData;
			columns[15] = columns[2] + "_" + columns[1];
			bstData->insert(inputData);
			//delete[] inputData;
		}
	} else
		cout << "Fatal Error! Please input a correct format file with a correct path." << endl;
	
	//bstData->display();
	clock_t endTime = clock();
	runTime = (double)(endTime - startTime) / CLOCKS_PER_SEC;
}

// Modify Data
void Menu::modifyData() {
	clock_t startTime = clock();
	showHeader(mainMenuItems[2]);
	int choice = 0;
	string key = "", tempString = "";
	BstNode* modifyNode = NULL;

	// Search data by key
	while (key.compare("-1")) {
		showHeader(mainMenuItems[2]);
		cout << "Please input a " << columns[bstData->key] << " that you want to modify (input -1 to exit): " << endl;
		cin >> key;

		if (modifyNode = bstData->search(key)) {
			showHeader(mainMenuItems[2]);
			choice = selectItem(columns, columnL, ("a data that you want to change of " + key), "Exit", mainMenuItems[2]);
			if (choice > 0 && choice <= columnL) {
				showHeader(mainMenuItems[2]);
				cout << "Input new value of " << key << ": ";
				cin >> tempString;
				if (choice - 1 == bstData->key && tempString.compare(modifyNode->data[bstData->key])) {		// If modify key value, remove node then insert new node
					string* data = new string[columnL];
					data[bstData->key] = tempString;
					for (int i = 0; i < columnL; i++)
						if (i != bstData->key)
							data[i] = modifyNode->data[i];
					bstData->insert(data);
					bstData->remove(key);
				}
				else if (choice - 1 != bstData->key)					// Change the Node value
					modifyNode->data[choice - 1] = tempString;

				cout << endl << columns[choice - 1] << " of " << key << " changed to \"" << tempString << "\"!" << endl;
			}
		}
		else if (key == "-1")
			cout << "Return to main menu!" << endl;
		else
			cout << "Record not found! Please insert again." << endl;
	}
	clock_t endTime = clock();
	runTime = (double)(endTime - startTime) / CLOCKS_PER_SEC;
}

// Delete Node by user input key
void Menu::deleteData() {
	clock_t startTime = clock();
	showHeader(mainMenuItems[3]);
	string searchKey;
	cout << "Please input a " << columns[bstData->key] << " that you want to modify (input -1 to exit): ";
	cin >> searchKey;
	if (searchKey.compare("-1")) {
		bstData->remove(searchKey);
		cout << endl << "Deleted \"" << searchKey << "\" if had this record!" << endl;
	} else
		cout << "Return to main menu!" << endl;
	clock_t endTime = clock();
	runTime = (double)(endTime - startTime) / CLOCKS_PER_SEC;
}

// Search data by user input key
void Menu::searchData() {
	clock_t startTime = clock();
	showHeader(mainMenuItems[4]);
	string key;
	cout << "Input your search key (input -1 to exit): ";
	cin >> key;

	if (key.compare("-1")) {									// Find out the prefix equal Node heightest valte at tree and save to fistNode
		cout << endl << "Please wait..." << endl;
		BstNode* fistNode = bstData->searchHalf(key);
		if (fistNode != NULL) {
			SinglyList* resultNode = new SinglyList;		// Find out the prefix equal Node under fistNode, save to single list and print out
			inOrderToFindNode(key, fistNode, resultNode);

			int num = 0;
			LLNode* currNode = resultNode->getHead();
			showHeader(mainMenuItems[4]);
			cout << "Search result of " << key << " :" << endl;
			while (currNode != NULL) {
				cout << currNode->data->data[bstData->key] << endl;
				currNode = currNode->next;
				num++;
			}
			cout << endl << "Total: " << num << " records" << endl;

			cout << "Please type a " << columns[bstData->key] << " to get more details (input -1 to exit): ";
			cin >> key;
			if (key.compare("-1")) {
				currNode = resultNode->getHead();
				while (currNode != NULL) {
					if (currNode->data->data[bstData->key] == key)
						cout << "====================================================================================================" << endl <<
							currNode->data->data[0] << " " << currNode->data->data[2] << "	" << currNode->data->data[1] << "\n(" << currNode->data->data[3] << ")" << "\nBirthday: " << currNode->data->data[4] << endl <<
							"Address: " << currNode->data->data[5] << ", " << currNode->data->data[6] << ", " << currNode->data->data[7] << ", " << currNode->data->data[9] << " (Zip Code: " << currNode->data->data[8] << ")" << endl <<
							"Telephone: " << currNode->data->data[10] << "-" << currNode->data->data[11] << "\nEmail: " << currNode->data->data[12] << "\nCompany: " << currNode->data->data[14] << " (" << currNode->data->data[13] << ")" << endl <<
							"====================================================================================================" << endl;
					currNode = currNode->next;
				}
			}
			delete resultNode;
		}
		else
			cout << "No record found!" << endl;					// Case : not find
	} else
		cout << "Return to main menu!" << endl;
	clock_t endTime = clock();
	runTime = (double)(endTime - startTime) / CLOCKS_PER_SEC;
}

// Save the equal Node at single list
void Menu::inOrderToFindNode(string findKey, BstNode* t, SinglyList* singlyList) {
	if (t == NULL)
		return;
	inOrderToFindNode(findKey, t->right, singlyList);
	if (!t->data[bstData->key].compare(0, findKey.size(), findKey))
		singlyList->insertNode(0, t);
	inOrderToFindNode(findKey, t->left, singlyList);
}

// Print out all of Data
void Menu::printData() {
	clock_t startTime = clock();
	showHeader(mainMenuItems[5]);
	bstData->display();
	clock_t endTime = clock();
	runTime = (double)(endTime - startTime) / CLOCKS_PER_SEC;
}

// Cnange the key and rebuild the tree
void Menu::changeKey() {
	clock_t startTime = clock();
	showHeader(mainMenuItems[6]);
	int choice = selectItem(columns, columnL, "key", "Exit", mainMenuItems[6]);
	if (choice > 0 && choice <= columnL) {
		showHeader(mainMenuItems[6]);
		cout << "Please wait..." << endl;
		bstData->changeKey(choice - 1);
		//system("pause");
		insertAllData();

		cout << endl << "Change key to " << columns[choice - 1] << " success!" << endl;
	}
	clock_t endTime = clock();
	runTime = (double)(endTime - startTime) / CLOCKS_PER_SEC;
}

// Rewrite to default data
void Menu::restoreData() {
	clock_t startTime = clock();
	string action[2] = { "Yes", "No" };
	showHeader(mainMenuItems[7]);
	if (selectItem(action, 2, "action\nAre you want to restore all records?", "Exit", mainMenuItems[7]) == 1) {
		showHeader(mainMenuItems[7]);
		cout << "Please wait..." << endl;
		bstData->makeEmpty();
		insertAllData();
		cout << "Restore to default data success!" << endl;
	} else {
		showHeader(mainMenuItems[7]);
		cout << "Restore to default data failed!" << endl;
	}
	clock_t endTime = clock();
	runTime = (double)(endTime - startTime) / CLOCKS_PER_SEC;
}

// About our development team
void Menu::aboutThis() {
	clock_t startTime = clock();
	showHeader(mainMenuItems[8]);
	cout << "Crazy Search Just You" << endl << endl <<
		"C.S.J.Y are come from our names." << endl <<
		"C:Chan  S:Siu  J:John  Y:Yuen" << endl << endl <<
		"Made by:" << endl <<
		"Chan Chi Wah (Raymond) (SID:5478 5523)" << endl <<
		"Siu Chi Ho (King) (SID:5478 5479)" << endl <<
		"Yuen Chung Man (John) (SID:5478 5443)" << endl <<
		"Kwong Chun Yuen (Yuen) (SID:5478 5406)" << endl << endl;
	clock_t endTime = clock();
	runTime = (double)(endTime - startTime) / CLOCKS_PER_SEC;
}

// Display a header
void Menu::showHeader(string title) {
	clock_t startTime = clock();
	system("cls");
	int keySymbolCount = round((42 - columns[bstData->key].length()) / 2);
	int lastRunningTimeCount = round((28 - (log10(runTime) > 0 ? 6 : 5)) / 2);
	int titleSymbolCount = round((48 - title.length()) / 2);
	cout << "==================================================" << endl <<
		"========= (C)razy (S)earch  (J)ust (Y)ou =========" << endl <<
		"=========  C.S.J.Y. Address Book System  =========" << endl <<
		"==================================================" << endl;

	for (int i = 0; i < 42 - keySymbolCount - columns[bstData->key].length(); i++)
		cout << "=";
	cout << " Key : " << columns[bstData->key] << " ";
	for (int i = 0; i < keySymbolCount; i++)
		cout << "=";

	cout << endl;

	for (int i = 0; i < 28 - lastRunningTimeCount - (log10(runTime) > 0 ? 6 : 5); i++)
		cout << "=";
	cout << " Last Runing time : " << runTime << "s ";
	for (int i = 0; i < lastRunningTimeCount; i++)
		cout << "=";

	//cout << endl << "======================== Last Runing: " << runTime << "s" << (log10(runTime) > 0? "":"=") << endl <<
	cout << endl << "==================================================" << endl;
	
	for (int i = 0; i < 48 - titleSymbolCount - title.length(); i++)
		cout << "-";
	cout << " " << title << " ";
	for (int i = 0; i < titleSymbolCount; i++)
		cout << "-";
	cout << endl << endl;
}

//static function that show the menu
int Menu::selectItem(string* data, int length, string title, string nameOfExit, string headerTitle) {
	int choice, restItems, page;
	choice = restItems = page = 0;

	//show the data using a list
	while (choice >= 0 || choice <= length) {
		restItems = length - 8 * page;

		cout << "Select " << title << ": " << endl;
		cout << "----------------" << endl;
		for (int i = 0; i < (restItems > 8 ? 8 : restItems); i++)
			cout << i + 1 << ".) " << data[8 * page + i] << endl;
		
		//Paging the data
		if (restItems > 8)
			cout << "9.) Next " << endl;
		else
			for (int i = 0; i < 9 - (restItems > 8 ? 8 : restItems); i++)
				cout << endl;

		if (page > 0)
			cout << "0.) Back " << endl;
		else
			cout << "0.) " << nameOfExit << endl;

		//request the choice
		cout << endl;
		cout << "Please enter your choice: ";
		cin >> choice;

		//next page or before page
		if (choice >= 1 && choice <= 8)
			return (8 * page + choice);
		else if (choice == 9 && (restItems > 8))
			page++;
		else if (choice == 0 && page > 0)
			page--;
		else
			return 0;
		showHeader(headerTitle);
	}
	return 0;
}
