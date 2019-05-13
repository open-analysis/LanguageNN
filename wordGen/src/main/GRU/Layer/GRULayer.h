#pragma once

#include <vector>
#include "../Neuron/GRUNeuron.h"

struct GRULayer {
	std::vector <GRUNeuron> neurons;
	GRUNeuron n;
	std::vector <double> errsO;
	std::vector <double> errsH;

	double learningRate = 0.01;

	// v is probably useless
	bool multiNeuron;
	GRUNeuron neuron;
	std::vector <double> errorO;
	std::vector <double> errorH;

	double layerSum = 0.0;

	GRULayer();
//	~GRULayer();

	void create(int numNeurons);
	void create();

	void calculate();
	// void calculate2();

	void CE(std::vector <bool> target);
};