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
	for (int i = data.size() - 1; i >= 0; i--)
		printf("%3d%5d%8.2f\n", data.size() - i , data.at(i).key, data.at(i).otherfields);
}

void pushdown(std::vector<recordtype>* data, int first, int last) {
	int r = first;
	while (r <= (last - 1) / 2) {
		if (last == 2 * r + 1) {
			if (data->at(r).key > data->at(last).key)
				std::swap(data->at(r), data->at(last));
			r = last;
		}
		else if (data->at(r).key > data->at(r * 2 + 1).key && data->at(r * 2 + 1).key <= data->at(r * 2 + 2).key) {
			std::swap(data->at(r), data->at(r * 2 + 1));
			r = r * 2 + 1;
		}
		else if (data->at(r).key > data->at(r * 2 + 2).key && data->at(r * 2 + 2).key < data->at(r * 2 + 1).key) {
			std::swap(data->at(r), data->at(r * r + 2));
			r = r * 2 + 2;
		}
		else
			r = last;
	}
}

void HeapSort(std::vector<recordtype>* data) {
	int n = data->size();
	for (int i = (n - 2) / 2; i >= 0; i--)
		pushdown(data, i, n - 1);

	for (int i = n - 1; i >= 2; i--) {
		std::swap(data->at(0), data->at(i));
		pushdown(data, 0, i - 1);
	}
	std::swap(data->at(0), data->at(1));
}


int main() {
	std::vector<recordtype> data;
	read_data("data.txt", &data);
	std::cout << "Du lieu truoc khi sap xep:" << std::endl;
	print_data(data);
	HeapSort(&data);
	std::cout << "Du lieu sau khi sap xep:" << std::endl;
	print_data(data);
	return 0;
}
