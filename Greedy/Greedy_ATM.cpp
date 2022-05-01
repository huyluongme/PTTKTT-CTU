#include <iostream>
#include <fstream>
#include <vector>

typedef struct {
	char money_name[25];
	int denomination, plan;
}Money;

void read_data(const char filename[], std::vector<Money> *money_list) {
	std::ifstream input(filename);
	if (input.fail()) {
		std::cout << "Cannot open file!!" << std::endl;
		input.close();
		return;
	}
	while (!input.eof()) {
		Money tmp;
		input >> tmp.denomination;
		input.getline(tmp.money_name, 25);
		tmp.plan = 0;
		money_list->push_back(tmp);
	}
	input.close();
}

void print_data(std::vector<Money> money_list, int money_withdraw) {
	int total_payment = 0, n = money_list.size();
	int stt = 1;
	printf("|---|-------------------------|---------|---------|----------|\n");
	printf("|%-3s|%-25s|%-9s|%-9s|%-10s|\n", "STT", "     Loai tien   ", "Menh Gia", "So to", "Thanh tien");
	printf("|---|-------------------------|---------|---------|----------|\n");
	for (int i = 0; i < n; i++) {
		if (money_list.at(i).plan > 0) {
			printf("|%-3d", stt);
			printf("|%-25s", money_list.at(i).money_name);
			printf("|%-9d", money_list.at(i).denomination);
			printf("|%-9d", money_list.at(i).plan);
			printf("|%-10d|\n", money_list.at(i).denomination * money_list.at(i).plan);
			total_payment = total_payment + money_list.at(i).plan * money_list.at(i).denomination;
			stt++;
		}
	}
	printf("|---|-------------------------|---------|---------|----------|\n");
	printf("So tien can rut= %9d\n", money_withdraw);
	printf("So tien da tra= %9d\n", total_payment);
	printf("So tien chua tra= %9d\n", money_withdraw - total_payment);
}

void BubbleSort(std::vector<Money>* money_list) {
	int n = money_list->size();
	for (int i = 0; i < n - 1; i++)
		for (int j = n - 1; j > i; j--)
			if (money_list->at(j).denomination > money_list->at(j - 1).denomination)
				std::swap(money_list->at(j), money_list->at(j - 1));
}

void Greedy(std::vector<Money>* money_list, int money_withdraw) {
	int i = 0, n= money_list->size();
	while (i < n && money_withdraw > 0) {
		money_list->at(i).plan = money_withdraw / money_list->at(i).denomination;
		money_withdraw = money_withdraw - money_list->at(i).denomination * money_list->at(i).plan;
		i++;
	}
}

int main() {
	std::vector<Money> money_list;
	read_data("ATM.txt", &money_list);
	int money_withdraw;
	std::cout << "Nhap so tien can rut: ";
	std::cin >> money_withdraw;
	BubbleSort(&money_list);
	Greedy(&money_list, money_withdraw);
	print_data(money_list, money_withdraw);
	return 0;
}
