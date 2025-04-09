#include "Algoritms.hpp"

void deleteRecord(dataBase& DB) {
	int index = findRecord(DB);
	if (index < 0) { return; }
	DB.data[index] = DB.data[DB.count - 1];
	--DB.count;
}

int findRecord(const dataBase& DB) {
	short int tmp;
	std::cin >> tmp;
	for (int i = 0; i < DB.count; ++i) {
		if (DB.data[i].ID == tmp) { return i; }
	}
	//std::cout << "Unknown command: " << tmp;
	return -1;
}

void printDB(const dataBase& DB) {
	for (int i = 0; i < DB.count; ++i) {
		std::cout << DB.data[i] << std::endl;
	}
}

void domTitle(const dataBase& DB, const char* title) {
	//copy base and search necessary ticket

	dataBase newDB = DB;
	//short int newCount = DB.count;

	for (int i = DB.count - 1; i >= 0; --i) {
		if (strcmpM(newDB.data[i].title, title) || newDB.data[i].count <= 0) {
			newDB.data[i] = newDB.data[newDB.count - 1];
			--newDB.count;
		}
	}

	//first sorting =D
	//quickSort(newDB.data, 0, newDB.count - 1, compByPrice, compByPriceR);
	choosesortM(newDB.data, 0, newDB.count, compByPriceUP);

	//second sorting ;|
	/*printDB(newDB);
	std::cout << std::endl;*/
	for (int i = 0; i < newDB.count; ++i) {
		double compair = newDB.data[i].price;
		int itr = 1;
		int begin = i;
		double certain = newDB.data[i + 1].price;
		while (compair == certain && (i < newDB.count - 1)) {
			++itr;
			++i;
			certain = newDB.data[i + 1].price;
		}
		if (itr > 1) { sortByStatus(newDB, begin, begin + itr); }
	}

	//third sorting ;(
	//printDB(newDB);
	//std::cout << std::endl;
	for (int i = 0; i < newDB.count; ++i) {
		//bool compair = newDB.data[i].status[0] == 'b' ? compair = 1 : compair = 0;
		int compair{};
		if (newDB.data[i].status[0] == 'b') {
			compair = 1;
		}
		else {
			compair = 0;
		}
		double compairP = newDB.data[i].price;
		int itr = 1;
		int begin = i;
		//bool certain = newDB.data[i + 1].status[0] == 'b' ? certain = 1 : certain = 0;
		int certain{};
		if (newDB.data[i + 1].status[0] == 'b') {
			certain = 1;
		}
		else {
			certain = 0;
		}
		double certainP = newDB.data[i + 1].price;
		while (compair == certain && (i < newDB.count - 1) && compairP == certainP) {
			++itr;
			++i;
			newDB.data[i + 1].status[0] == 'b' ? certain = 1 : certain = 0;
			certainP = newDB.data[i + 1].price;
		}
		//if (itr > 1 && compair) { quickSort(newDB.data, begin, begin + itr - 1, compByDate, compByDateR); }
		if (itr > 1 && compair==1) { choosesortM(newDB.data, begin, begin + itr, compByDateDW); }
		//if (itr > 1 && !compair) { quickSort(newDB.data, begin, begin + itr - 1, compByDateUp, compByDateUpR); }
		if (itr > 1 && compair==0) { choosesortM(newDB.data, begin, begin + itr, compByDateUP); }
		//printDB(newDB);
		//std::cout << std::endl;
	}
	/*if (newDB.data) {
		delete[] newDB.data;
	}*/
	//new type of out :/
	for (int i = 0; i < newDB.count; ++i) {
		std::cout << newDB.data[i].status << " " << std::fixed << std::setprecision(2) << newDB.data[i].price << ", ";
		std::cout << newDB.data[i].count << ", ";
		std::cout << newDB.data[i].date[6] << newDB.data[i].date[7] << newDB.data[i].date[8] << newDB.data[i].date[9] << '.';
		std::cout << newDB.data[i].date[3] << newDB.data[i].date[4] << '.';
		std::cout << newDB.data[i].date[0] << newDB.data[i].date[1] << " ";
		short j = 0;
		while (newDB.data[i].time[j] != ',') {
			std::cout << newDB.data[i].time[j];
			++j;
		}
		std::cout << std::endl;
	}
}

void sortByStatus(dataBase& DB, int first, int last) {
	order* sd = new order[DB.count];
	order* ft = new order[DB.count];
	int s = 0;
	int f = 0;
	for (int cfrom = first; cfrom < last; ++cfrom) {
		if (DB.data[cfrom].status[0] == 'b') {
			ft[f] = DB.data[cfrom];
			++f;
		}
		else {
			sd[s] = DB.data[cfrom];
			++s;
		}
	}
	short int i = 0;
	i = 0;
	while (s != 0) {
		DB.data[first] = sd[i];
		--s;
		++i;
		++first;
	}
	while (f > 0) {
		DB.data[first] = ft[i];
		--f;
		++i;
		++first;
	}
	delete[] sd;
	delete[] ft;
}

void doubleTimeSort(const dataBase& newDB) {
	for (int i = 0; i < newDB.count; ++i) {
		long long compair = newDB.data[i].oTime;
		int itr = 1;
		int begin = i;
		long long certain = newDB.data[i + 1].oTime;
		while (compair == certain && (i < newDB.count)) {
			++itr;
			++i;
			certain = newDB.data[i + 1].oTime;
		}
		if (itr > 1) { choosesortM(newDB.data, begin, begin + itr, compByIdUP); }
	}
}

//lowwer to hegger 
bool compByPriceDW(const order& X, const order& Y) {
	return X.price < Y.price;
}
bool compByDateDW(const order& X, const order& Y) {
	return X.oTime < Y.oTime;
}
//higger to lower
bool compByPriceUP(const order& X, const order& Y) {
	return X.price > Y.price;
}
bool compByDateUP(const order& X, const order& Y) {
	return X.oTime > Y.oTime;
}
bool compByIdUP(const order& X, const order& Y) {
	return X.ID < Y.ID;
}
