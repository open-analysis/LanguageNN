#include "cnnLayer.h"

Layer::Layer(unsigned numNodes) {
	nodes.clear();

	for (unsigned i = 0; i < numNodes; i++) {
		nodes.emplace_back();
	}
}