#pragma once
#include "Network.h"

// look at RNN for comments, processes are basically the same
struct Calc
{
	static Network net;
	std::vector <double> target;
	std::vector <double> errO, errH;
	
	Calc(Network &p_net, std::vector <double> p_target);
	
	void train(unsigned numEpochs, float threshold);
	void calcErr();
	void shuffle();
};