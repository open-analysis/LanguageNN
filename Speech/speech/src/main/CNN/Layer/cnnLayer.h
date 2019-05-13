#pragma once
#include "Node\Node.h"
struct Layer
{
	std::vector <Node> nodes;
	
	Layer(unsigned numNodes);
};