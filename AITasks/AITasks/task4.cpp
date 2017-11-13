#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <bitset>
#include <algorithm>

/*
	Genetic algorithm solution for the Backpack problem
*/

const std::vector<std::string> item_names = { "map", "compass", "water", "sandwich", "glucose", "tin", "banana", "apple",
"cheese", "beer", "suntan creem", "camera", "T-shirt", "trousers", "umbrella", "waterproof trousers", "waterproof overclothes",
"note-case", "sunglasses", "towel", "socks", "book", "notebook", "tent" };

const std::vector<int> weights = { 90,130, 1530, 500, 150, 680, 270, 390, 230, 520, 110, 320, 240, 480, 730, 420, 430, 220, 70, 180, 
40, 300, 900, 2000 };

const std::vector<int> values = { 150,35,200,160,60,45,60,40,30,10,70,30,15,10,40,70,75,80,20,12,50,10,1,150 };

// hyper-parameters
#define ITEMS_COUNT 24
#define TARGET_WEIGHT 5000
#define GENERATIONS_COUNT 10000
#define GENERATION_SIZE 40
#define CROSSOVER_SIZE 15
#define CROSSOVER_MASK "110111000000000111101000"
#define MUTATION_COEFF 4
#define MUTATION_MASK "001000010010100000000000"


typedef std::bitset<ITEMS_COUNT> Individual;
typedef std::vector<Individual> Generation;

int calc_weight(const Individual& a) {
	int weight = 0;
	for (int i = 0; i < ITEMS_COUNT; i++) {
		weight += a[i] * weights[i];
	}
	return weight;
}

int calc_value(const Individual& a) {
	int value = 0;
	for (int i = 0; i < ITEMS_COUNT; i++) {
		value += a[i] * values[i];
	}
	return value;
}

const auto INDIVIDUALS_ORDERING = [](const Individual& a, const Individual& b) {
	if (calc_weight(a) > TARGET_WEIGHT) {
		if (calc_weight(b) > TARGET_WEIGHT) return calc_value(a) > calc_value(b);
		else return false;
	}
	else if (calc_weight(b) > TARGET_WEIGHT) return true;
	else {
		return calc_value(a) > calc_value(b);
	}
};

void swap_bit_values(std::bitset<ITEMS_COUNT>::reference & a, std::bitset<ITEMS_COUNT>::reference & b) {
	if (a && !b) {
		a = false;
		b = true;
	}
	else if (!a && b) {
		a = true;
		b = false;
	}
}

Generation crossover(Generation& gen) {
	Generation crossovered = Generation(gen.begin(), gen.begin() + CROSSOVER_SIZE);
	for (int i = 0; i < CROSSOVER_SIZE - 1; i+=2) {
		for (int j = 0; j < ITEMS_COUNT; j++) {
			if (CROSSOVER_MASK[j] == '1') {
				swap_bit_values(crossovered[i][j], crossovered[i + 1][j]);
			};
		}
	}
	return crossovered;
}

void mutate(Generation& gen) {
	for (int i = 0; i < gen.size(); i++) {
		if (rand() % (int)(gen.size() / MUTATION_COEFF) == 0) {
			for (int j = 0; j < ITEMS_COUNT; j++) {
				if (MUTATION_MASK[j] == '1') gen[i][j] = gen[i][j] ? false : true;
			}
		}
	}
}

void merge_crossovered_generation(Generation& crossovered, Generation& gen) {
	Generation result;
	for (auto i : crossovered) {
		if (!std::binary_search(gen.begin(), gen.end(), i, INDIVIDUALS_ORDERING)) {
			result.push_back(i);
		}
	}

	for (int i = 0; result.size() < gen.size(); i++) {
		result.push_back(gen[i]);
	}
	gen = result;
}

void print_gen(Generation& gen) {
	std::cout << "value  weight\n";
	for (int i = 0; i < gen.size(); i++) {
		std::cout << calc_value(gen[i]) << "   " << calc_weight(gen[i]) << "\n";
	}
	std::cout << "\n\n\n";
}

void print_best_individual(Generation& gen) {
	std::cout << "Best individual from generation:\nScore = " << calc_value(gen[0]) << ", Weight = " << calc_weight(gen[0]) << "\nItems = ";
	for (int i = 0; i < ITEMS_COUNT; i++) {
		if (gen[0][i]) std::cout << item_names[i] << " | ";
	}
	std::cout << "\n\n\n";
}

void genetic_backpack() {
	srand(time(0));
	Generation gen;

	for (int i = 0; i < GENERATION_SIZE; i++) {
		gen.push_back(Individual(rand() % (unsigned long)pow(2, 24)));
	}

	std::sort(gen.begin(), gen.end(), INDIVIDUALS_ORDERING);
	//print_gen(gen);
	std::cout << "First generation\n";
	print_best_individual(gen);

	for (int i = 0; i < GENERATIONS_COUNT - 1; i++) {
		auto c = crossover(gen);
		mutate(c);
		merge_crossovered_generation(c, gen);
		std::sort(gen.begin(), gen.end(), INDIVIDUALS_ORDERING);
	}

	std::cout << "Last generation\n";
	//print_gen(gen);
	print_best_individual(gen);
}

//int main() {
//	genetic_backpack();
//	return 0;
//}
