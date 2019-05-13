#pragma once

#include <random>
#include <vector>

struct GRUNeuron {
	std::vector <double> z, r, h, s;
	std::vector <double> input;
	double U[3], W[3];

	void create();

	double weightInit();

	GRUNeuron();
	//~GRUNeuron();
};