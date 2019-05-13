#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <fstream>
#include <ctime>
#include <iostream>
#include <vector>
#include "Layer\GRULayer.h"
#include "../auxilary/preprocess.h"

class GRU {
	std::vector <GRULayer> _layers;
	// first vector is the size of the sentence & the second/inner vector is the size of the lexicon that's being used
	std::vector <std::vector <bool>> _text;
	// the whole point of this is guessing the next word/character thus target is really just text at one index greater
	std::vector <std::vector<bool>> _target;

	GRULayer l;

	bool multiSource = false;
	bool underThreshold = false;

	int batch_size;
	int batch_count;
	int batch_iter = 0;
	
//	void setText(int, int);
	void setText(int n) { pp.getText(_text, n, batch_iter); _target = _text; }
	std::vector <bool> predictNext();
	void getDoubleFromOneHot(std::vector <std::vector <bool>> tmp, std::vector <double> &result);
	void GRU::propagate(std::vector <double> input);
public:
	Preprocess pp;

	// the number of layers is defined by the number of elements in the lexicon
	void create(int numLayers, int numNeurons);
	void create(int numLayers);

	void train(double error_threshold, int num_epochs);

	void setBatchSize();
	void setMultiSource(bool f) { multiSource = f; }

	void shuffle(std::vector <std::vector <double>> &input);

	std::string generate(int length);

	void saveWeights();
	void loadWeights(std::string pathway);
	void loadWeights();

	GRU();
	~GRU();
};