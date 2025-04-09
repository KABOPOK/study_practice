#include "Algoritms.hpp"

short int id = 1;
bool problemOut = true;
namespace rew {
	std::ostream& operator<< (std::ostream& out, const order& ord) {
		out << ord.date[6] << ord.date[7] << ord.date[8] << ord.date[9] << '.';
		out << ord.date[3] << ord.date[4] << '.';
		out << ord.date[0] << ord.date[1];
		out << " " << ord.time << " " << ord.title << " " << ord.status << " " << ord.count << ", " << std::fixed << std::setprecision(2) << ord.price;
		//std::cout << " " << ord.time << " " << ord.title << " " << ord.status << " " << ord.count << ", " << std::fixed << std::setprecision(2) << ord.price;
		return out;
	}
}
//operator!!
std::istream& operator>> (std::istream& in, order& ord) {
	//ID
	ord.ID = id;

	//date and time
	in.ignore();
	in >> ord.date;
	in.ignore();
	in >> ord.time;
	ord.oTime = checkTime(ord.date, ord.time);
	in.ignore();
	if (ord.oTime == -1) { return in; }

	char ch{};

	//title
	for (int i = 0; ch != ','; ++i) {
		in.get(ch);
		ord.title[i] = ch;
	}
	in.get(ch);
	while (ch == ' ') {
		in.get(ch);
	}

	//status
	short i = 0;
	for (; ch != ','; ++i) { //NVIDIA, buy,110, 173
		ord.status[i] = ch;
		in.get(ch);
	}
	ord.status[i] = ',';
	if (in.peek() == ' ') {
		in.get(ch);
		while (in.peek() == ' ') { in.get(ch); }
	}

	//count of share
	in >> ord.count;
	in.ignore();

	//price of share
	in >> ord.price;

	if (Corrector(ord)) { ord.oTime = -1; }
	else { ++id; }
	return in;
}
std::ostream& operator<< (std::ostream& out, const order& ord) {
	out << ord.date << " " << ord.time << " " << ord.title << " " << ord.status << " " << ord.count << ", " << std::fixed << std::setprecision(2) << ord.price;
	return out;
}

bool strcmpM(const char* str1, const char* str2) {
	for (int i = 0; str1[i] != 0; ++i) {
		/*if (str1[i] >= 'A' && str1[i] <= 'z' && str2[i] >= 'A' && str2[i] <= 'z') {
			if (str1[i] != str2[i]) {
				if (str1[i] >= 65 && str1[i] <= 90) {
					if ((str1[i] + 35) != str2[i]){
						return 1;
					}
				}
				else {
					if ((str1[i] - 35) != str2[i]) {
						return 1;
					}
				}
			}
		}
		else {
			if (str1[i] != str2[i]) {
				return 1;
			}
		}*/
		if ( (((int)str1[i] - (int)str2[i]) % 32) !=0) {
			return true;
		}
	}
	return false;
}

int addRecord(dataBase& DB) {
	//memory allocation
	if (DB.count >= DB.maxsize) {
		DB.maxsize = DB.maxsize > 0 ? 2 * DB.maxsize : 1;
		order* tmp = new order[DB.maxsize];
		for (int i = 0; i < DB.count; ++i) { tmp[i] = DB.data[i]; }
		delete[] DB.data;
		DB.data = tmp;
	}
	std::cin >> DB.data[DB.count];
	++DB.count;
	if (DB.data[DB.count - 1].oTime == -1) {
		if (DB.count - 1 == 0) {
			--DB.count;
			//DB.data = nullptr;
			return DB.count;
		}
		DB.data[DB.count] = DB.data[DB.count - 1];
		--DB.count;
	}
	//sort by decrease
	/*quickSort(DB.data, 0, DB.count - 1, compByDate, compByDateR);
	printDB(DB);*/
	//order processing
	order buyer = DB.data[DB.count - 1];
	if (buyer.status[0] == 'b') {
		///quickSort(DB.data, 0, DB.count - 1, compByPrice, compByPriceR);
		choosesortM(DB.data, 0, DB.count, compByPriceDW);
		for (int i = 0; i < DB.count; ++i) {
			if (strcmp(buyer.title, DB.data[i].title)==0 && DB.data[i].status[0] == 's' && buyer.price >= DB.data[i].price && DB.data[i].count != 0 && buyer.count != 0) {
				if (buyer.count <= DB.data[i].count) {
					DB.data[i].count -= buyer.count;
					buyer.count = 0;
					//break;
				}
				else {
					buyer.count -= DB.data[i].count;
					DB.data[i].count = 0;
				}
			}
		}
	}
	if (buyer.status[0] == 's') {
		//quickSort(DB.data, 0, DB.count - 1, compByPriceR, compByPrice);
		choosesortM(DB.data, 0, DB.count, compByPriceUP);
		//printDB(DB);
		for (int i = 0; i < DB.count; ++i) {
			if (strcmp(buyer.title, DB.data[i].title) == 0 && DB.data[i].status[0] == 'b' && buyer.price <= DB.data[i].price && DB.data[i].count != 0 && buyer.count != 0) {
				if (buyer.count <= DB.data[i].count) {
					DB.data[i].count -= buyer.count;
					buyer.count = 0;
					//break;
				}
				else {
					buyer.count -= DB.data[i].count;
					DB.data[i].count = 0;
				}
			}
		}
	}
	for (int i = 0; i < DB.count; ++i) {
		if (DB.data[i].ID == buyer.ID) {
			DB.data[i].count = buyer.count;
			break;
		}
	}
	return DB.count;
}

void exportDB(const dataBase& DB, const char filename[]) {
	std::ofstream outFile(filename);
	if (!outFile.is_open()) {
		std::cout << "> Can not write to file: " << std::endl;
		return;
	}
	for (int i = 0; i < DB.count; ++i) {
		//outFile << DB.data[i] << std::endl;
		rew::operator<<(outFile, DB.data[i]) << std::endl;
	}
	outFile.close();
}

int load(dataBase& DB, const char filename[]) {
	//open base
	//char r{};
	std::ifstream inFile(filename, std::ios_base::binary);
	if (!inFile.is_open()) {
		if (problemOut) { std::cout << "> Can not open file: " << filename << std::endl; }
		return 0;
	}
	DB.count = 0;
	while (static_cast<signed char>(inFile.peek()) != EOF) {
		//create place for order
		if (DB.count >= DB.maxsize) {
			DB.maxsize = DB.maxsize > 0 ? 2 * DB.maxsize : 1;
			order* tmp = new order[DB.maxsize];
			for (int i = 0; i < DB.count; ++i) { tmp[i] = DB.data[i]; }
			delete[] DB.data;
			DB.data = tmp;
		}
		//load data to empty order
		DB.data[DB.count].ID = id;
		inFile >> DB.data[DB.count].oTime;
		inFile.ignore();
		inFile.read(DB.data[DB.count].date, 10);
		inFile.ignore();
		inFile.read(DB.data[DB.count].time, 9);
		inFile.ignore();
		char ch{};
		for (int i = 0; ch != ' '; ++i) {
			inFile.get(ch);
			if (ch != ' ') {
				DB.data[DB.count].title[i] = ch;
			}
		}
		ch = 0;
		for (int i = 0; ; ++i) {
			inFile.get(ch);
			if (ch == ' ') { break; }
			DB.data[DB.count].status[i] = ch;
		}
		inFile >> DB.data[DB.count].count;
		inFile.ignore();
		inFile >> DB.data[DB.count].price;
		/*inFile.ignore();
		inFile >> DB.data[DB.count].oTime;*/
		++DB.count;
		++id;
		//if (DB.data[DB.count - 1].oTime == -1) {
		//	if (DB.count - 1 == 0) {
		//		--DB.count;
		//		DB.data = nullptr;
		//		return DB.count;
		//	}
		//	DB.data[DB.count] = DB.data[DB.count - 1];
		//	--DB.count;
		//}
	}
	inFile.close();
	return DB.count;
}

void save(const dataBase& DB, const char filename[]) {
	std::ofstream outFile(filename);
	if (!outFile.is_open()) {
		std::cout << "> Can not write to file: " << std::endl;
		return;
	}
	for (int i = 0; i < DB.count; ++i) {
		outFile << DB.data[i].oTime << " ";
		if (i + 1 == DB.count) { outFile << DB.data[i]; }
		else { outFile << DB.data[i] << std::endl; }
	}
	outFile.close();
}
//add 12.02.2023 10:02:01, Intel, buy, 35, 32.1

void clear(dataBase& DB) {
	int n = DB.count;
	for (int i = n - 1; i >= 0; --i) {
		if (DB.data[i].count == 0) {
			DB.data[i] = DB.data[DB.count - 1];
			--DB.count;
		}
	}
}




///
//int loadTxt(dataBase& DB, const char filename[]) {
//	//open base
//	char r{};
//	std::ifstream inFile(filename, std::ios_base::binary);
//	if (!inFile.is_open()) {
//		if (problemOut) { std::cout << "> Can not open file: " << filename << std::endl; }
//		return 0;
//	}
//	//DB.count = 0;
//	while ((r = inFile.peek()) != EOF) {
//		//create place for order
//		if (DB.count >= DB.maxsize) {
//			DB.maxsize = DB.maxsize > 0 ? 2 * DB.maxsize : 1;
//			order* tmp = new order[DB.maxsize];
//			for (int i = 0; i < DB.count; ++i) { tmp[i] = DB.data[i]; }
//			if (DB.data) { delete[] DB.data; }
//			DB.data = tmp;
//		}
//
//		//load data to empty order
//		inFile.ignore();
//		inFile.ignore();
//		inFile.ignore();
//		DB.data[DB.count].ID = id;
//		//inFile >> DB.data[DB.count].oTime;
//		inFile.ignore();
//		inFile.read(DB.data[DB.count].date, 10);
//		inFile.ignore();
//		inFile.read(DB.data[DB.count].time, 9);
//		inFile.ignore();
//		DB.data[DB.count].oTime = checkTime(DB.data[DB.count].date, DB.data[DB.count].time);
//		char ch{};
//
//		//title
//		for (int i = 0; ch != ','; ++i) {
//			inFile.get(ch);
//			DB.data[DB.count].title[i] = ch;
//		}
//		inFile.get(ch);
//		while (ch == ' ') {
//			inFile.get(ch);
//		}
//
//		//status
//		short i = 0;
//		for (i; ch != ','; ++i) { //NVIDIA, buy,110, 173
//			DB.data[DB.count].status[i] = ch;
//			inFile.get(ch);
//		}
//		DB.data[DB.count].status[i] = ',';
//		if (inFile.peek() == ' ') {
//			inFile.get(ch);
//			while (inFile.peek() == ' ') { inFile.get(ch); }
//		}
//
//		//count of share
//		inFile >> DB.data[DB.count].count;
//		inFile.ignore();
//
//		//price of share
//		inFile >> DB.data[DB.count].price;
//		inFile.ignore();
//		inFile.ignore();
//		++DB.count;
//		++id;
//
//		//initialization
//		order buyer = DB.data[DB.count - 1];
//		if (buyer.status[0] == 'b') {
//			//quickSort(DB.data, 0, DB.count - 1, compByPrice, compByPriceR);
//			choosesort(DB.data, 0, DB.count, compByPriceDW);
//			for (int i = 0; i < DB.count; ++i) {
//				if (!strcmp(buyer.title, DB.data[i].title) && DB.data[i].status[0] == 's' && buyer.price >= DB.data[i].price && DB.data[i].count != 0 && buyer.count != 0) {
//					if (buyer.count <= DB.data[i].count) {
//						DB.data[i].count -= buyer.count;
//						buyer.count = 0;
//						break;
//					}
//					else {
//						buyer.count -= DB.data[i].count;
//						DB.data[i].count = 0;
//					}
//				}
//			}
//		}
//		if (buyer.status[0] == 's') {
//			choosesort(DB.data, 0, DB.count, compByPriceUP);
//			//quickSort(DB.data, 0, DB.count - 1, compByPriceR, compByPrice);
//			//printDB(DB);
//			for (int i = 0; i < DB.count; ++i) {
//				if (!strcmp(buyer.title, DB.data[i].title) && DB.data[i].status[0] == 'b' && buyer.price <= DB.data[i].price && DB.data[i].count != 0 && buyer.count != 0) {
//					if (buyer.count <= DB.data[i].count) {
//						DB.data[i].count -= buyer.count;
//						buyer.count = 0;
//						break;
//					}
//					else {
//						buyer.count -= DB.data[i].count;
//						DB.data[i].count = 0;
//					}
//				}
//			}
//		}
//		for (int i = 0; i < DB.count; ++i) {
//			if (DB.data[i].ID == buyer.ID) {
//				DB.data[i].count = buyer.count;
//				break;
//			}
//		}
//	}
//	inFile.close();
//	return DB.count;
//}
