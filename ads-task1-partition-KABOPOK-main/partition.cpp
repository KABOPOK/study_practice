#include <iostream>

long long partition(int n, int k);

int main() {
	int n = 0;
	int k = 0;
	std::cin >> n >> k;
	std::cout << partition(n, k);
	return 0;
}

long long partition(int n, int k) {
	long long* table = new long long[n] {0};
	long long answer = (long long)0;
	long long partLast = (long long)1;
	for (int i = 0; i < k; ++i) {
		for (int j = 0; j < n; ++j) {
			if (j < i) { table[j] = 0; /*std::cout << table[j] << " "; */ continue; }
			if (j - 1 == i || i == j || i == 0) {
				partLast = table[j];
				table[j] = (long long)1;
			}
			else {
				std::swap(partLast, table[j]);
				if (j - i > 0) {
					table[j] += table[j - (i+1)];
				}
			}
			//std::cout << table[j] << " ";
		}
		//std::cout << '\n';
	}
	answer = table[n - 1];
	delete[] table;
	return answer;
}

