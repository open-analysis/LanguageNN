#pragma once
#include "Layer\Layer.h"

#define NUM_OUPUTS 3

struct Network
{
	std::vector <Layer> layers;

	Network(unsigned numLayers, unsigned numNeurons);
};