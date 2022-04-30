#include <iostream>
#include <fstream>
#include <vector>

typedef int keytype;
typedef float othertype;

typedef struct {
	keytype key;
	othertype otherfields;
}recordtype;

void read_data(const char filename[], std::vector<recordtype>* data) {
	std::ifstream input(filename);
	if (input.fail()) {
		std::cout << "Cannot open file!!" << std::endl;
		return;
	}
	while (!input.eof()) {
		recordtype tmp;
		input >> tmp.key >> tmp.otherfields;
		data->push_back(tmp);
	}
}

void print_data(std::vector<recordtype> data) {
	for (int i = 0; i < data.size(); i++)
		printf("%3d%5d%8.2f\n", i + 1, data.at(i).key, data.at(i).otherfields);
}

int find_pivot(std::vector<recordtype>* data, int start, int end) {
	keytype f_key = data->at(start).key;
	int i = start + 1;
	while (i <= end && data->at(i).key == f_key) i++;
	if (i > end) return -1;
	else
		if (data->at(i).key < f_key) return i;
		else return start;
}

int partition(std::vector<recordtype>* data, int start, int end, keytype pivot) {
	int L = start, R = end;
	while (L < R) {
		while (data->at(L).key <= pivot) L++;
		while (data->at(R).key > pivot) R--;
		if (L < R) std::swap(data->at(L), data->at(R));
	}
	return L;
}

void QuickSort_bienthe(std::vector<recordtype>* data, int start, int end) {
	int pivotindex = find_pivot(data, start, end);
	if (pivotindex != -1) {
		keytype pivot = data->at(pivotindex).key;
		int mid = partition(data, start, end, pivot);
		QuickSort_bienthe(data, start, mid - 1);
		QuickSort_bienthe(data, mid, end);
	}
}


int main() {
	std::vector<recordtype> data;
	read_data("data.txt", &data);
	std::cout << "Du lieu truoc khi sap xep:" << std::endl;
	print_data(data);
	QuickSort_bienthe(&data, 0, data.size()- 1);
	std::cout << "Du lieu sau khi sap xep:" << std::endl;
	print_data(data);
	return 0;
}
