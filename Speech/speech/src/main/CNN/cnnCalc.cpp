#include "Calc.h"

Calc::Calc(Network &p_net, std::vector<double> p_target) {
	net = p_net;
	target = p_target;
}

// using CUDA
void Calc::train(unsigned numEpochs, float threshold) {
	for (unsigned e = 0; e < numEpochs; e++) {
		
		calcErr << 8, 256 >> ();
	}
}

__global__
void Calc::calcErr() {

}