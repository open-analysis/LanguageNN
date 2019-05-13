#include "GRUNeuron.h"

GRUNeuron::GRUNeuron() {
	z.clear(); 
	r.clear();
	h.clear();
	s.clear();
}

void GRUNeuron::create() {
	// init all the stuff
	//z = r = h = s = 0;
	input.clear();
	input.shrink_to_fit();
	for (int i = 0; i < 3; i++) {
		U[i] = weightInit(); 
		W[i] = weightInit();
	}
}

double GRUNeuron::weightInit() {
	std::random_device rd;
	std::normal_distribution <double> dist(-.05, .05);
	return dist(rd);
}