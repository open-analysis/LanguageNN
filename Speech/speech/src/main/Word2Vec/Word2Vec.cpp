#include <iostream>
#include "Word2Vec.h"

word2Vec::word2Vec(std::string loc) {
	
	text.open(loc, std::ios::ate);

	addToLex();
	measureProb();
}

void word2Vec::addToLex() {
	
	char *input = NULL;
	std::string word = NULL;
	unsigned length = 0;
	
	if (!text.is_open()) return;
	//text.seekg(0, std::ios::end);
	length = text.tellg();
	text.seekg(0, std::ios::beg);
	while (std::cin.getline(input, length) && !text.eof){
		// adds characters that fit criteria to "word" then when it reaches an endChr adds "word" to "words" vector
		for (unsigned int i = 0; i < length; i++) {
			if (!checkSpcChrs(input[i])) {
				if ((input[i] >= 0x41 && input[i] <= 0x5a) || (input[i] >= 0x61 && input[i] <= 0x7a)) {
					word += input[i];
				}
				else {
					if (word != "")
						words.push_back(word);
					word = "";
				}
			}
			else {
				if (word != "")
					words.push_back(word);
				word = "";
			}
		}
	}
	text.close();
	make1Hot();
}

// checks if parameter is equal to endChrs
bool word2Vec::checkSpcChrs(char c) {
	for (char s : endChrs) {
		if (c == s) return true;
	}
	return false;
}

// makes "words" vector into a one-hot "lex"
void word2Vec::make1Hot() {
	unsigned len = words.size();
	unsigned /*short*/ pos = 0;
	lex.resize(len);
	for (std::string w : words) {
		for (unsigned i = 0; i < len; i++) {
			if (i = pos) w.back() = 1.0;
			else w.push_back(0.0);
		}
		pos++;
	}
}

// acts like a NN that will guess prob of a word being near another one 
void word2Vec::measureProb() {
	unsigned short numEpochs = 10;
	unsigned numOutput = lex.size();
	// window of words around center word (e.g. 5 words to the left, 5 to the right)
	unsigned short windowSize = 5;
	unsigned sum = 0;
	std::vector <std::vector <unsigned>> lookUp, output;
	lookUp.resize(numOutput);
	// init'ing "lookUp" vector & then "output" afterwards
	for (unsigned i = 0; i < lookUp.size(); i++) {
		lookUp[i].resize(300);
		for (unsigned short j = 0; j < 300; j++) {
			lookUp[i][j] = weightInit();
		}
	}
	output = lookUp;

	// NN to determine probabilities
	for (unsigned e = 0; e < numEpochs; e++) {

	}
}