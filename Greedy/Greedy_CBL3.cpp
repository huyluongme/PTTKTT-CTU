#include <iostream>
#include <fstream>
#include <string>
#include <vector>

typedef struct {
	std::string TenDV;
	float TL, GT, DG;
	int PA;
}DoVat;

void read_data(const char filename[], std::vector<DoVat>* dsdv, float* W) {
	std::ifstream input(filename);
	if (input.fail()) {
		std::cout << "Cannot open file!!" << std::endl;
		input.close();
		return;
	}
	input >> *W;
	while (!input.eof()) {
		DoVat tmp;
		input >> tmp.TL >> tmp.GT;
		std::getline(input, tmp.TenDV);
		tmp.DG = tmp.GT / tmp.TL;
		tmp.PA = 0;
		dsdv->push_back(tmp);
	}
	input.close();
}

void print_data(std::vector<DoVat> dsdv, float W) {
	int i;
	float TongTL = 0.0, TongGT = 0.0;
	printf("\nPhuong an Cai Ba lo 1 dung thuat toan THAM AN nhu sau:\n");
	printf("\nTrong luong cua ba lo = %-9.2f\n", W);
	printf("|---|------------------|---------|---------|---------|-----------|\n");
	printf("|STT|     Ten Do Vat   | T Luong | Gia Tri | Don Gia | Phuong an |\n");
	printf("|---|------------------|---------|---------|---------|-----------|\n");
	for (i = 0; i < dsdv.size(); i++) {
		printf("|%2d |%-18s|%9.2f|%9.2f|%9.2f|%6d     |\n",
			i + 1, dsdv[i].TenDV.c_str(), dsdv[i].TL, dsdv[i].GT, dsdv[i].DG, dsdv[i].PA);
		TongTL = TongTL + dsdv[i].PA * dsdv[i].TL;
		TongGT = TongGT + dsdv[i].PA * dsdv[i].GT;
	}
	printf("|---|------------------|---------|---------|---------|-----------|\n");
	printf("Phuong an (theo thu tu DG giam dan): X(");
	for (i = 0; i < dsdv.size() - 1; i++) {
		printf("%d,", dsdv[i].PA);
	}
	printf("%d)", dsdv[dsdv.size() - 1].PA);
	printf("\nTong trong luong = %-9.2f\n", TongTL);
	printf("Tong gia tri = %-9.2f\n", TongGT);
}

void BubbleSort(std::vector<DoVat>* dsdv) {
	int n = dsdv->size();
	for (int i = 0; i < n - 1; i++)
		for (int j = n - 1; j > i; j--)
			if (dsdv->at(j).DG > dsdv->at(j - 1).DG)
				std::swap(dsdv->at(j), dsdv->at(j - 1));
}

void Greedy(std::vector<DoVat>* dsdv, float W) {
	for (int i = 0; i < dsdv->size(); i++) {
		dsdv->at(i).PA = std::min((int)(W / dsdv->at(i).TL), 1);
		W = W - dsdv->at(i).TL * dsdv->at(i).PA;
	}
}

int main() {
	float W;
	std::vector<DoVat> dsdv;
	read_data("CaiBalo3.txt", &dsdv, &W);
	BubbleSort(&dsdv);
	Greedy(&dsdv, W);
	print_data(dsdv, W);
	return 0;
}

