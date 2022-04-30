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

void SelectionSort(std::vector<recordtype>* data) {
	int lowindex;
	keytype lowkey;

	for (int i = 0; i < data->size() - 1; i++) {
		lowkey = data->at(i).key;
		lowindex = i;
		for (int j = i + 1; j < data->size(); j++) {
			if (data->at(j).key < lowkey) {
				lowkey = data->at(j).key;
				lowindex = j;
			}
		}
		std::swap(data->at(i), data->at(lowindex));
	}
}

int main() {
	std::vector<recordtype> data;
	read_data("data.txt", &data);
	std::cout << "Du lieu truoc khi sap xep:" << std::endl;
	print_data(data);
	SelectionSort(&data);
	std::cout << "Du lieu sau khi sap xep:" << std::endl;
	print_data(data);
	return 0;
}
