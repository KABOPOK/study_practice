#include <iostream>
#include <fstream>

struct Node {
	int first;
	int second;
	int weight;
};
int findVertices(int * V, int i) {
    while (i != V[i]) {
        i = V[i];
    }
    return i;
}
bool compWeight(Node& i, Node& j) {
	return i.weight <= j.weight;
}
void merge(Node*& M, Node*& tmp, int start1, int start2, int end, bool (*comp)(Node& i, Node& j)) {
    int index = start1;
    int i = start1;
    int j = start2;
    while (true) {
        if (comp(M[i], M[j])) {
            tmp[index++] = M[i++];
        }
        else {
            int c = 1;
            tmp[index++] = M[j++];
        }
        if (i == start2) {
            while (j < end) { tmp[index++] = M[j++]; }
            break;
        }
        if (j == end) {
            while (i < start2) { tmp[index++] = M[i++]; }
            break;
        }
    }
}
void MergeSort(Node*& M, int n, bool (*comp)(Node& i, Node& j)) {
    Node* tmp = new Node[n];
    int p = 1;
    bool tmpOrder = true;
    while (p < n) {
        int i = 0;
        if (tmpOrder) {
            while (i + 2 * p <= n) {
                merge(M, tmp, i, i + p, i + 2 * p, comp);
                i += 2 * p;
            }
            if (i + p < n) {
                merge(M, tmp, i, i + p, n, comp);
                i += p;
            }
            else {
                for (; i < n; ++i) {
                    tmp[i] = M[i];
                }
            }
        }
        else {
            while (i + 2 * p <= n) {
                merge(tmp, M, i, i + p, i + 2 * p, comp);
                i += 2 * p;
            }
            if (i + p < n) {
                merge(tmp, M, i, i + p, n, comp);
                i += p;
            }
            else {
                for (; i < n; ++i) {
                    M[i] = tmp[i];
                }
            }
        }
        tmpOrder = !tmpOrder;
        p <<= 1;

    }
    if (!tmpOrder) {
        std::swap(M, tmp);
    }
    delete[] tmp;
}
int main(int argc, const char* argv[]) {
	std::ifstream in(argv[1]);
	int edges = 0;
	int vertices = 0;
	in >> vertices;
	in >> edges;
	int i = 0;
	Node* M = new Node[edges];
	int* V = new int[vertices];
    int* rank = new int[vertices] {0};

    for (int i = 0; i < vertices; ++i) {
        V[i] = i;
    }

	for (int i = 0; i < edges; ++i) {
		in >> M[i].first;
		in >> M[i].second;
		in >> M[i].weight;
	}

    MergeSort(M, edges, compWeight);

    int answer=0;
    for (int i = 0; i < edges; ++i) {
        int first = findVertices(V, M[i].first);
        int second = findVertices(V, M[i].second);
        if (first != second) {
            if (rank[first] > rank[second]) {
                V[second] = first;
            }
            else {
                V[first] = second;
            }
            if (rank[first] == rank[second]) {
                ++rank[second];
            }
            {

            }
            answer += M[i].weight;
        }
    }
    std::cout << answer;
	delete[] M;
	delete[] V;
	delete[] rank;
	in.close();
}
