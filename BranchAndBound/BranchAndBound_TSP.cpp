#include <iostream>
#include <fstream>

using namespace std;

#define size 30

typedef struct {
	float distance;
	int from, to;
	bool used;
}Edge;

void read_data(const char filename[], Edge edge_list[][size], int* n) {
	ifstream input(filename);
	if (input.fail()) {
		cout << "Cannot open file!!!" << endl;
		return;
	}
	input >> *n;
	for (int i = 0; i < *n; i++) {
		for (int j = 0; j < *n; j++) {
			Edge tmp;
			input >> edge_list[i][j].distance;
			edge_list[i][j].from = i;
			edge_list[i][j].to = j;
			edge_list[i][j].used = false;
		}
	}
	input.close();
}

void print_data(Edge edge_list[][size], int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			printf("   %c%c = %5.2f   ", edge_list[i][j].from + 97, edge_list[i][j].to + 97, edge_list[i][j].distance);
		printf("\n");
	}
}

void print_result(Edge result[], int n) {
	float sum = 0.0;
	printf("\nPHUONG AN TIM DUOC:\n");
	for (int i = 0; i < n; i++) {
		sum += result[i].distance;
		printf(" Canh %c%c = %5.2f\n", result[i].from + 97, result[i].to + 97, result[i].distance);
	}
	printf("CHU TRINH : ");
	for (int i = 0; i < n; i++) {
		printf("%c", result[i].from + 97);
		printf("-> ");
	}
	printf("%c", result[0].from + 97);
	printf("\nTong do dai cac canh cua chu trinh = %5.2f\n", sum);
}

float min_edge(Edge edge_list[][size], int n) {
	float min = 3.40282e+38;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (i != j && !edge_list[i][j].used && edge_list[i][j].distance < min)
				min = edge_list[i][j].distance;
	return min;
}

float lower_Bound(Edge edge_list[][size], float total_cost, int n, int i) {
	return total_cost + (n - i) * min_edge(edge_list, n);
}

bool has_circle(Edge x[], int k, int next) {
	int i = 0;
	while (i < k)
		if (x[i].from == next) return true;
		else i++;
	return false;
}

void update_tmp_solution(Edge edge_list[][size], int n, float total_cost, float* min_cost_tmp, Edge x[], Edge result[]) {

	int i;
	x[n - 1] = edge_list[x[n - 2].to][x[0].from];
	total_cost = total_cost + x[n - 1].distance;
	if (*min_cost_tmp > total_cost) {
		*min_cost_tmp = total_cost;
		for (i = 0; i < n; i++)
			result[i] = x[i];
	}
}

void Branch_and_Bound(Edge edge_list[][size], int n, int i, int from, float* total_cost, float* lowerbound, float* min_cost_tmp, Edge x[], Edge result[]) {

	for (int j = 0; j < n; j++)
		if (from != j && !edge_list[from][j].used && !has_circle(x, i, j)) {

			*total_cost = *total_cost + edge_list[from][j].distance;
			*lowerbound = lower_Bound(edge_list, *total_cost, n, i + 1);
			if (*lowerbound < *min_cost_tmp) {

				x[i] = edge_list[from][j];
				edge_list[from][j].used = true;
				edge_list[j][from].used = true;

				if (i == n - 2) {
					update_tmp_solution(edge_list, n, *total_cost, min_cost_tmp, x, result);
				}
				else
					Branch_and_Bound(edge_list, n, i + 1, j, total_cost, lowerbound, min_cost_tmp, x, result);
			}
			*total_cost = *total_cost - edge_list[from][j].distance;
			edge_list[from][j].used = false;
			edge_list[j][from].used = false;
		}
}

void reset(Edge edge_list[][size], int n) {
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			edge_list[i][j].used = false;

}

int main() {
	Edge edge_list[size][size];
	Edge x[size], result[size];
	int n;
	read_data("TSP1.txt", edge_list, &n);
	printf("\nPhuong an TSP dung thuat toan NHANH CAN:\n");
	char start, select;
	while (1) {
		print_data(edge_list, n);
		float total_cost = 0.0, lowerbound = 0.0, min_cost_tmp = 3.40282e+38;
		printf("\nXuat phat tu thanh pho nao? ");
		printf("\n Nhap mot trong cac thanh pho tu a den %c: ", n - 1 + 97);
		cin >> start;
		Branch_and_Bound(edge_list, n, 0, start - 97, &total_cost, &lowerbound, &min_cost_tmp, x, result);
		print_result(result, n);
		printf("\nTiep tuc Y/N? ");
		cin >> select;
		if (select == 'N' || select == 'n')
			break;
		reset(edge_list, n);
	}
	return 0;
}
