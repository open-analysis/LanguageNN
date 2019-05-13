#pragma once

#include <fstream>
#include <vector>
#include "../WeightInit.cpp"

// creates a word2vec
struct word2Vec {

	// all of the words that will be put into the lexicon
	std::vector <std::string > words;
	// one hot lexicon
	static std::vector <std::vector <double>> lex;

	std::ifstream text;
	// characters that are ends of words (spaces, periods, commas, etc.)
	char endChrs[6] = { 0x20, 0x21, 0x3f, 0x2c, 0x2e, 0x0a };

	word2Vec(std::string);
	void addToLex();
	void make1Hot();
	void measureProb();
	bool checkSpcChrs(char);
};