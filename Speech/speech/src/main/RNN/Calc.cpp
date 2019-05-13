#include "Calc.h"

// setting member variables to parameter ones
Calc::Calc(Network &p_net, word2Vec p_input, std::vector<double> p_target) {
	net = p_net;
	input = p_input;
	target = p_target;
}

// runs through the feed forward & then the backprop
// using CUDA
void Calc::train(unsigned numEpochs, float threshold) {
	for (unsigned e = 0; e < numEpochs; e++) {
		calcWeights /*<< 8, 256 >>*/ ();
		calcErr << 8, 256 >> ();
	}
}

// feed foward, calcs 
//__global__
void Calc::calcWeights() {
	for (Layer l : net.layers) {
		for (Node n : l.nodes) {
			n.s.push_back(0);
			for (unsigned i = 0; i < input.lex.size(); i++) {
				// doesn't quite work on the first run through, so it must be dealt with accordingly
				if (i = 0) {
					n.z.push_back(input[i] * n.U[0]);
					n.z[i] = 1.0 / (1.0 + exp(-n.z[i]));
					n.r.push_back(input[i] * n.U[1]);
					n.r[i] = 1.0 / (1.0 + exp(-n.r[i]));
					n.h.push_back(input[i] * n.U[2]);
					n.h[i] = 1.0 / (1.0 + exp(-n.h[i]));

					n.s[i] = (1 - n.z[i]) * n.h[i];
				} else {
					n.z.push_back((n.s[i-1] * n.U[0]) + (n.s[i-1] * n.V[0]));
					n.z[i] = 1.0 / (1.0 + exp(-n.z[i]));
					n.r.push_back((n.s[i - 1] * n.U[1]) + (n.s[i - 1] * n.V[1]));
					n.r[i] = 1.0 / (1.0 + exp(-n.r[i]));
					n.h.push_back((n.s[i - 1] * n.U[2]) + (n.s[i - 1] * n.V[2]));
					n.h[i] = 1.0 / (1.0 + exp(-n.h[i]));

					// this check shouldn't be necessary as they should do essentially the same thing, test later
					if (i == 1) {
						if (n.s.back() != 0)
							n.s.back() = (1 - n.z[i]) * n.h[i] + n.z[i] * n.s.back();
						else
							return;
					} else {
						n.s.back() = (1 - n.z[i]) * n.h[i] + n.z[i] * n.s[i - 1];
					}
				}
				n.s.push_back(1);
			}
		}
	}
}

// calculates the error 
__global__
void Calc::calcErr() {

}

// shuffles the training data
void Calc::shuffle() {

}