#include <iostream>
#include <fstream>
#include <vector>

typedef struct {
	int from, to;
	float distance;
}Edge;

void read_data(const char filename[], std::vector<Edge> *edge_list, int *n) {
	std::ifstream input(filename);
	if (input.fail()) {
		std::cout << "Cannot open file!!" << std::endl;
		input.close();
		return;
	}
	int i = 0, j;
	float tmp;
	input >> *n;
	while (i < *n)
	{
		for (j = 0; j <= i; j++) input >> tmp;
		for (j = i + 1; j < *n; j++) {
			Edge edge_tmp;
			input >> edge_tmp.distance;
			edge_tmp.from = i;
			edge_tmp.to = j;
			edge_list->push_back(edge_tmp);
		}
		i++;
	}
	input.close();
}

void print_data(std::vector<Edge> edge_list, int is_plan) {
	float sum = 0.0, n = edge_list.size();
	for (int i = 0; i < n; i++) {
		printf("%3d %c%c=%8.2f\n", i + 1, edge_list.at(i).from + 97, edge_list.at(i).to + 97, edge_list.at(i).distance);
		if (is_plan)
			sum += edge_list.at(i).distance;
	}
	if (is_plan)
		printf("Tong do dai cac canh: %5.2f", sum);
}

void BubbleSort(std::vector<Edge>* edge_list) {
	int n = edge_list->size();
	for (int i = 0; i < n - 1; i++)
		for (int j = n - 1; j > i; j--)
			if (edge_list->at(j).distance < edge_list->at(j - 1).distance)
				std::swap(edge_list->at(j), edge_list->at(j - 1));
}

int is_vertex_level_3(std::vector<Edge> *result, Edge edge_new) {
	int count = 1;
	for (int i = 0; i < result->size(); i++) {
		if (count == 3) break;
		if (edge_new.from == result->at(i).from || edge_new.from == result->at(i).to)
			count++;
	}

	if(count == 3) return 1;

	count = 1;
	for (int i = 0; i < result->size(); i++) {
		if (count == 3) break;
		if (edge_new.to == result->at(i).from || edge_new.to == result->at(i).to)
			count++;
	}
	return count == 3;
}

void init_forest(std::vector<int>* parent, int n) {
	for (int i = 0; i < n; i++)
		parent->push_back(i);
}

int find_root(std::vector<int> parent, int u) {
	while (u != parent.at(u))
		u = parent.at(u);
	return u;
}

int is_circle(int from_root, int to_root) {
	return from_root == to_root;
}

void update_forest(std::vector<int>* parent, int r1, int r2) {
	parent->at(r2) = r1;
}

void Greedy(std::vector<Edge>* edge_list, std::vector<Edge> *result, int n) {
	std::vector<int> parent;
	init_forest(&parent, n);
	int from_root, to_root;
	int i;
	for (i = 0; i < n * (n - 1) / 2 && result->size() < n-1; i++) {

		from_root = find_root(parent, edge_list->at(i).from);
		to_root = find_root(parent, edge_list->at(i).to);
		if (!is_vertex_level_3(result, edge_list->at(i)) && !is_circle(from_root, to_root)) {
			result->push_back(edge_list->at(i));
			update_forest(&parent, from_root, to_root);
		}
	}
	for (; i < n * (n - 1) / 2; i++) {
		from_root = find_root(parent, edge_list->at(i).from);
		to_root = find_root(parent, edge_list->at(i).to);
		if (!is_vertex_level_3(result, edge_list->at(i)) && is_circle(from_root, to_root)) {
			result->push_back(edge_list->at(i));
			break;
		}
	}

}

int main() {
	int n;
	std::vector<Edge> edge_list, result;
	printf("Phuong an TSP dung thuat toan THAM AN:\n");
	read_data("TSP1.txt", &edge_list, &n);
	printf("Danh sach cac canh cua do thi:\n");
	print_data(edge_list, 0);
	BubbleSort(&edge_list);
	printf("Danh sach cac canh cua do thi da SAP XEP:\n");
	print_data(edge_list, 0);
	Greedy(&edge_list, &result, n);
	printf("PHUONG AN:\n");
	print_data(result, 1);
	return 0;
}
