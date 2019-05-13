#pragma once
#include "Layer\Layer.h"

#define NUM_OUPUTS 3

struct Network
{
	// static in hopes that it won't purge the layers & nodes from memory
	static std::vector <Layer> layers;

	Network(unsigned numLayers, unsigned numNeurons);
};