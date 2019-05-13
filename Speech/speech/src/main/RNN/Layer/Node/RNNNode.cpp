#include "RNNNode.h"

Node::Node() {
	// init node, sets weights "U" & "V" to random doubles from -1 to 1
	for (unsigned short i = 0; i < 3; i++) {
		U[i] = weightInit();
		V[i] = weightInit();
	}
	// empties these weights
	z.clear();
	r.clear();
	h.clear();
	s.clear();
}