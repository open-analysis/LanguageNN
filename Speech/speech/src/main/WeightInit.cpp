#pragma once

#include <random>
#include <ctime>

// generates random number from -1 to 1
double weightInit() {
	//Type of random number distribution
	std::uniform_real_distribution<double> dist(-1.000, 1.000);  //(min, max)

	//Mersenne Twister: Good quality random number generator
	std::mt19937 rng;
	//Initialize with non-deterministic seeds
	rng.seed(std::random_device{}());

	return dist(rng);
}