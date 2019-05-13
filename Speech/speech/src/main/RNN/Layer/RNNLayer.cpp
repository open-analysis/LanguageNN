#include "RNNLayer.h"

Layer::Layer(unsigned numNodes) {
	nodes.clear();
	// inits the nodes for this layer
	for (unsigned i = 0; i < numNodes; i++) {
		nodes.emplace_back();
	}
}