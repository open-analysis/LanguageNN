#include <iostream>
#include "main/GRU/GRU.h"
#include "main/auxilary/preprocess.h"
#include <vector>
#include <fstream>

/*
TODO:
	- have to add additional language alphabet (Spanish ftm)
	- add some sort of database or something later with multiple alphabets
	- get rid of the "vocab" portions of code, probably unnecessary
		v probably done?
	- make sure the target gets set
	- make sure the get/setText functions apply to the target as well
*/

void readIn(std::vector <std::string> &, std::string);

int main() {
	std::vector <std::string> vec;
	GRU g;
	g.pp.setUseVocab(0);
	g.pp.setLowerCase(1);
	g.pp.setBatchSize(10000);
	g.pp.setVocabMin(1);
	g.pp.setText("C:/Users/Josh Chica/Desktop/SherlockHolmes/AStudyInScarlet.txt");
	g.pp.setTarget("C:/Users/Josh Chica/Desktop/SherlockHolmes/AStudyInScarlet.txt");
	g.pp.read();
	
	g.create(g.pp.getLexicon().size(), 50);
	g.train(.001, 2);
	g.saveWeights();
	printf("Done\n");
	std::cin.get();
	return 0;
} 

void readIn(std::vector <std::string> &vec, std::string path) {
	std::ifstream f;
	std::string line;
	f.open(path, std::ios::beg);
	if (f.is_open()) {
		while (!f.eof()) {
			while (std::getline(f, line)) {
				vec.push_back(line);
			}
		}
	}
	else {
		printf("fuck");
	}
}