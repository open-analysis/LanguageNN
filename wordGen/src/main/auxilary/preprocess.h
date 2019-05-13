#pragma once

#define _CRT_SECURE_NO_WARNINGS

//#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <ctime>
#include <iostream>

class Preprocess {
// variables & shiz
private:
	std::vector <std::string> filepathways;
	std::vector <std::string> text;
	std::vector <std::string> target;
	std::vector <std::string> dict;
	std::vector <std::string> dictTarget;
	std::vector <int> dictCount;
	std::vector <int> dictTargetCount;
	std::vector <std::string> vocab;
	std::vector <std::string> vocabTarget;
	std::vector <char> alphabet;
	std::vector <char> alphabetTarget;
	std::vector <char> lowerCase;
	std::vector <char> lowerCaseTarget;
	// one-hot array
	std::vector <std::vector <bool>> lexicon;
	std::vector <std::vector <bool>> lexiconTarget;
	bool _usingVocab = false;
	bool _usingLowerCase = true;

	int fileLength = 0;
	int numTextIters = 0;
	int timesThru = 1;
	int timesThruTest = 0;

	int vocab_MIN = 500;
	int vocab_MAX = 0;

	std::fstream f;
	std::string m_TextPathWay;
	std::string m_TargetPathWay;

	int batch_size;
	int batch_iter = 0;
	int batch_count = 0;
	int batch_count_target = 0;
	bool batch_set = false;

public:
	int totalFiles;
	std::vector <std::string> practice;
	std::vector <std::string> test;

	std::vector <std::string> practiceTarget;
	std::vector <std::string> testTarget;
// functions & methods & shiz	
private:
	void getOneHotText(std::vector <std::vector <bool>> &te, int epoch, int iter);
	void toLower(char &word);

public:
	Preprocess();
												
	void setUseVocab(bool f) { _usingVocab = f; }
	void setLowerCase(bool f) { _usingLowerCase = f; }
	void setBatchSize(int size) { batch_size = size; batch_set = true; }
	void setGroup() { setGroup(0); }
	void setGroup(std::vector <std::string> files);
	void setGroup(unsigned);
	void setText(std::string path) { m_TextPathWay = path; }
	void setTarget(std::string path) { m_TargetPathWay = path; }
	void setVocabMin(int min) { vocab_MIN = min; }
	void setVocabMax(int max) { vocab_MAX = max; }

	bool getUsingLexicon() { return _usingVocab; }
	std::vector <std::vector <bool>> getLexicon() { return lexicon; }
	std::vector <char> getAlphabet() { return alphabet; }
	std::vector <std::string> getVocab() { return vocab; }
	void getText(std::vector <std::vector <bool>> &te, int epoch, int iter) { getOneHotText(te, epoch, iter); }
	//int getText(std::vector <std::vector <bool>> &te, int epoch, int iter, int text_iter);
	int getBatchSize() { return batch_size; }
	bool getBatchSet() { return batch_set; }

	void read();
};
