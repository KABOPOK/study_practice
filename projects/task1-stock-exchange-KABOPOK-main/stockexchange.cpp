#include "Algoritms.hpp"

int main() {
	char key[16]{};
	char mycop[64]{};
	//work whit data
	dataBase DB;
	char cash[32]{};
	while ((strcmp("quit", key) != 0)) {
		bool wrongStr = true;
		std::cout << "> ";
		std::cin >> key;
		//std::cin.ignore();

		if ((strcmp("add", key) == 0)) {
			addRecord(DB);
			wrongStr = false;
			std::cin.getline(mycop, 64);
		}

		if ((strcmp("load", key)) == 0) {
			wrongStr = false;
			std::cin.ignore();
			std::cin.getline(cash, 32);
			load(DB, cash);
		}

		if ((strcmp("save", key)) == 0) {
			wrongStr = false;
			std::cin.ignore();
			std::cin.getline(cash, 32);
			save(DB, cash);
		}

		if ((strcmp("delete", key)) == 0) {
			wrongStr = false;
			deleteRecord(DB);
		}

		if ((strcmp("clear", key)) == 0) {
			clear(DB);
			wrongStr = false;
		}

		if ((strcmp("print", key)) == 0) {
			/*choosesortM(DB.data, 0, DB.count, compByDateDW);
			printDB(DB);
			std::cout << '\n';
			doubleTimeSort(DB);*/
			printDB(DB);
			wrongStr = false;
		}

		if ((strcmp("dom", key)) == 0) {
			wrongStr = false;
			char inputTitle[16]{};
			std::cin.ignore();
			std::cin.getline(inputTitle, 15);
			//pitfail
			short int i = 0;
			for (; inputTitle[i] != 0; ++i) {}
			inputTitle[i] = ',';
			//
			domTitle(DB, inputTitle);
		}

		if ((strcmp("export", key)) == 0) {
			wrongStr = false;
			std::cin.ignore();
			char fileName[16]{};
			std::cin.getline(fileName, 16);
			//first sorting =D
			choosesortM(DB.data, 0, DB.count, compByDateDW);
			//second sorting :|
			doubleTimeSort(DB);
			exportDB(DB, fileName);
		}

		//just for myself
		/*if ((strcmp("txt", key)) == 0) {
			loadTxt(DB, "o.txt");
			wrongStr = false;
		}*/
		//

		if ((strcmp("quit", key)) == 0) { break; }

		if (wrongStr) {
			std::cout << "Unknown command: " << key << std::endl;
			std::cin.getline(mycop, 64);
		}
	}
	//delete[] key;
	delete[] DB.data;
	DB.data = nullptr;
	return 0;
}
