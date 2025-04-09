#include <cmath>
#include <cstring>
#include <iostream>
#include <fstream>
#include <iomanip>
#ifndef __MY__FUNCTION__
#define __MY__FUNCTION__

struct order {
	//unique ID
	short int ID{};
	//own time
	long long oTime{};

	//date
	char date[16]{};

	//time
	char time[16]{};

	//title 
	char title[16]{};

	//type of share
	char status[8]{};

	//count of share
	int count{};

	//price of share
	double price{};
};
struct dataBase {
	int count{};
	int maxsize{};
	order* data = nullptr;
};

//Errors processing
long long checkTime(const char* first, const char* last);
int monthCount(int first, int last);
bool Corrector(order& ord);
void timeInpit(const char* time);
void timeInpitFormat(const char* time);
void dateInpitFormat(const char* date);

//File processing
void exportDB(const dataBase& DB, const char filename[]);
void save(const dataBase& DB, const char filename[]);
int load(dataBase& DB, const char filename[]);
//int loadTxt(dataBase& DB, const char filename[]);
bool strcmpM(const char* str1, const char* str2);

//Work with base
void printDB(const dataBase& DB);
int addRecord(dataBase& DB);
void deleteRecord(dataBase& DB);
void clear(dataBase& DB);
void domTitle(const dataBase& DB, const char* title);

//Algoritms
int findRecord(const dataBase& DB);
void sortByStatus(dataBase& DB, int first, int last);
bool compByDateUP(const order& X, const order& Y);
bool compByPriceUP(const order& X, const order& Y);
bool compByDateDW(const order& X, const order& Y);
bool compByPriceDW(const order& X, const order& Y);
bool compByIdUP(const order& X, const order& Y);
void doubleTimeSort(const dataBase& newDB);

std::ostream& operator<< (std::ostream& out, const order& ord);
std::istream& operator>> (std::istream& in, order& ord);

template <typename t>
void choosesort(t* m, int f, int n, bool (*comparator)(const t&, const t&)) {
	for (int step = f + 1; step < n - 1; ++step) {
		int minimumindex = step;
		for (int i = minimumindex + 1; i < n; ++i) {
			if (comparator(m[i], m[minimumindex]))
				minimumindex = i;
		}
		if (step < minimumindex) {
			std::swap(m[step], m[minimumindex]);
		}
	}
}

template <typename t>
void choosesortM(t* m, int f, int n, bool (*comparator)(const t&, const t&)) {
	for (int step = f; step < n; ++step) {
		int minimumindex = step;
		for (int i = minimumindex; i < n; ++i) {
			//if (m[i].oTime < m[minimumindex].oTime) { minimumindex = i; }
			if (comparator(m[i], m[minimumindex])) { minimumindex = i; }
		}
		if (step < minimumindex) {
			std::swap(m[step], m[minimumindex]);
		}
	}
}

template <typename t>
void quickSort(t* base, int first, int last, bool (*comparator)(const t&, const t&))
{
	if (first < last) {
		int left = first;
		int right = last - 1;
		int middle = left + (right - left) / 2;
		do {
			//comparator(base.data[left], base.data[left + (right - left) / 2])
			while (comparator(base[left], base[middle])) {
				++left;
			}
			while (comparator(base[middle], base[right])) {
				--right;
			}
			if (left <= right) {
				std::swap(base[left], base[right]);
				++left;
				--right;
			}
		} while (left < right);
		quickSort(base, first, right, comparator);
		quickSort(base, left, last, comparator);
	}
}
#endif
