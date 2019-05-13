#pragma once

#include <vector>
#include "../../../WeightInit.cpp"

struct Node 
{
	std::vector <double> z, r, h, s;
	double U[3], V[3];
	
	Node();
};