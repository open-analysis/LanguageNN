#include "cnnNode.h"

// init the weight to a random double
Node::Node() {
	W = weightInit();
}