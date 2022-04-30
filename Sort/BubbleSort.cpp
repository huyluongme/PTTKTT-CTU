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

void BubbleSort(std::vector<recordtype>* data) {
	for (int i = 0; i < data->size() - 1; i++)
		for (int j = data->size() - 1; j > i; j--) {
			if (data->at(j).key < data->at(j - 1).key)
				std::swap(data->at(j), data->at(j - 1));
		}
}

int main() {
	std::vector<recordtype> data;
	read_data("data.txt", &data);
	std::cout << "Du lieu truoc khi sap xep:" << std::endl;
	print_data(data);
	BubbleSort(&data);
	std::cout << "Du lieu sau khi sap xep:" << std::endl;
	print_data(data);
	return 0;
}
