#pragma once

#include "Network.h"
#include "../Word2Vec/Word2Vec.h"

// dios mio, no se
struct Calc
{
	// static in hopes that network, layers, & nodes won't be purged from memory
	static Network net;
	word2Vec input;
	std::vector <double> target;
	std::vector <double> errO, errH;
	
	Calc(Network &p_net, word2Vec p_input, std::vector <double> p_target);
	
	void train(unsigned numEpochs, float threshold);
	void calcWeights();
	void calcErr();
	void shuffle();
};