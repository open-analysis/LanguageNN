#include "cnnNetwork.h"

Network::Network(unsigned numLayers, unsigned numNodes) {
	layers.clear();
	for (unsigned i = 0; i < numLayers; i++) {
		layers.emplace_back(numNodes);
	}
	// adds the output layer with the # of output nodes
	layers.emplace_back(NUM_OUPUTS);
}