#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <fstream>
#include <ctime>
#include <map>
#include <string>

typedef std::vector<float> Features;
typedef std::vector<Features> X;
typedef std::vector<std::string> Y;

double distance(const Features& data1, const Features& data2) {
	double res = 0;
	for (int i = 0; i < data1.size(); i++) {
		res += pow(data2[i] - data1[i], 2);
	}
	return sqrt(res / data1.size());
}

void train_test_split(
	X& x_train, Y& y_train, X& x_test, Y& y_test,
	X data, Y labels,
	int test_size = -1, int random_state = -1
) {
	if (test_size == -1) test_size = (int)(data.size() / 10);
	if (random_state == -1) srand(time(0));
	else srand(random_state);

	for (int i = 0; i < test_size; i++) {
		int index = rand() % data.size();
		std::swap(data[index], data.back());
		std::swap(labels[index], labels.back());
		x_test.push_back(data.back());
		y_test.push_back(labels.back());
		data.pop_back();
		labels.pop_back();
	}

	x_train = data;
	y_train = labels;
}

class kNNClassifier {
private:
	X data;
	Y labels;
public:
	int k;
	kNNClassifier(int k=1) {
		this->k = k;
	}

	kNNClassifier& fit(X& data, Y& labels) {
		this->data = data;
		this->labels = labels;
		return *this;
	}

	Y predict(const X& values) {
		Y res;
		for (const auto& example : values) {
			std::vector <std::pair<double, std::string>> k_nearest;
			for (int i = 0; i < data.size(); i++) {
				k_nearest.push_back({ distance(example, data[i]), labels[i] });
			}

			std::sort(k_nearest.begin(), k_nearest.end(), [](std::pair<double, std::string>& a, std::pair<double, std::string>& b) {
				return a.first == b.first ? a.second < b.second : a.first < b.first;
			});

			std::sort(k_nearest.begin(), k_nearest.begin() + k, [](std::pair<double, std::string>& a, std::pair<double, std::string>& b) {
				return a.second < b.second;
			});

			std::string max_label, current_label = k_nearest[0].second;
			int max_count = 0, i_started = 0;
			for (int i = 1; i < k; i++) {
				if (k_nearest[i].second != current_label) {
					if (i - i_started > max_count) {
						max_label = k_nearest[i].second;
						max_count = i - i_started;
					}

					i_started = i;
					current_label = k_nearest[i].second;
				}
			}

			if (k - 1 - i_started > max_count) {
				max_label = k_nearest[k-1].second;
				max_count = k - 1 - i_started;
			}

			res.push_back(max_label);
		}

		return res;
	}

	double score(const X& data, const Y& labels) {
		double correct = 0;
		auto predicted = predict(data);
		for (int i = 0; i < predicted.size(); i++) {
			if (predicted[i] == labels[i]) correct++;
		}

		return correct / labels.size();
	}
};

void read(const char* path, X& x, Y& y) {
	std::ifstream myfile(path);
	std::string line;

	if (!myfile.is_open()) {
		std::cerr << "Error opening file!\n";
		terminate();
	}

	std::getline(myfile, line);
	while (std::getline(myfile, line))
	{
		char label[20];
		Features f(4);
		sscanf(line.c_str(), "%*i,%f,%f,%f,%f,%s", &f[0], &f[1], &f[2], &f[3], label);
		x.push_back(f);
		y.push_back(std::string(label));
	}

	myfile.close();
}

int main(int argc, char **argv) {
	X iris_x, x_train, x_test;
	Y iris_y, y_train, y_test;

	read("iris.csv", iris_x, iris_y);
	train_test_split(x_train, y_train, x_test, y_test, iris_x, iris_y, 20, 0);

	kNNClassifier model = kNNClassifier(atoi(argv[1])).fit(x_train, y_train);

	std::cout << "Train score: " << model.score(x_train, y_train) << std::endl;
	std::cout << "Test score: " << model.score(x_test, y_test) << std::endl;
	return 0;
}