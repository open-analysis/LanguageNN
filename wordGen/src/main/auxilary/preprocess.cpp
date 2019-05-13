#include "preprocess.h"

Preprocess::Preprocess() {
	vocab.clear();
	alphabet = {
		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
		'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k','l','m', 'n',	'o', 'p', 'q', 'r', 's', 't', 'u', 'v',	'w', 'x', 'y', 'z',
		'.', ',', '!', '?', '-', '_', '$', '\'', '\'', '#', '@', '%', '^', '&', '*', '(', ')', '+', '=', '[', ']', '{', '}', '|', '\\',
		':', ';', '<', '>', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '~', '`'
	};
	lowerCase = {
		'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k','l','m', 'n',	'o', 'p', 'q', 'r', 's', 't', 'u', 'v',	'w', 'x', 'y', 'z',
		'.', ',', '!', '?', '-', '_', '$', '\'', '\'', '#', '@', '%', '^', '&', '*', '(', ')', '+', '=', '[', ']', '{', '}', '|', '\\',
		':', ';', '<', '>', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '~', '`'
	};
	alphabetTarget = {
		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
		'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k','l','m', 'n',	'o', 'p', 'q', 'r', 's', 't', 'u', 'v',	'w', 'x', 'y', 'z',
		'.', ',', '!', '?', '-', '_', '$', '\'', '\'', '#', '@', '%', '^', '&', '*', '(', ')', '+', '=', '[', ']', '{', '}', '|', '\\',
		':', ';', '<', '>', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '~', '`'
	};
	lowerCaseTarget = {
		'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k','l','m', 'n',	'o', 'p', 'q', 'r', 's', 't', 'u', 'v',	'w', 'x', 'y', 'z',
		'.', ',', '!', '?', '-', '_', '$', '\'', '\'', '#', '@', '%', '^', '&', '*', '(', ')', '+', '=', '[', ']', '{', '}', '|', '\\',
		':', ';', '<', '>', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '~', '`'
	};
}

void Preprocess::setGroup(std::vector <std::string> files) {
	filepathways = files;
	totalFiles = filepathways.size();
	int testSize = filepathways.size() * .2;
	if (testSize <= 0) testSize = 1;
	for (int i = 0; i < test.size(); i++) {
		test.push_back(filepathways.back());
		filepathways.pop_back();
	}
	for (int i = 0; i < filepathways.size(); i++) {
		practice.push_back(filepathways.back());
		filepathways.pop_back();
	}
	filepathways.clear();
	filepathways.shrink_to_fit();
}

void Preprocess::setGroup(unsigned numTexts) {
	filepathways.resize(numTexts);
	if (numTexts == 0) {
		std::string path;
		while (true) {
			printf("Enter the filepath:\n");
			std::cin >> path;
			if (path == "") break;
			filepathways.push_back(path);
		}
	}
	else {
		totalFiles = filepathways.size();
		for (int i = 0; i < numTexts * 2; i++) {
			printf("Enter the filepath:\n");
			std::cin >> filepathways[i / 2];
		}
	}
	int testSize = filepathways.size() * .2;
	if (testSize <= 0) testSize = 1;
	for (int i = 0; i < test.size(); i++) {
		test.push_back(filepathways.back());
		filepathways.pop_back();
	}
	for (int i = 0; i < filepathways.size(); i++) {
		practice.push_back(filepathways.back());
		filepathways.pop_back();
	}
	filepathways.clear();
	filepathways.shrink_to_fit();
}

//int Preprocess::getText(std::vector <std::vector <bool>> &te, int epoch, int iter, int text_iter) {
//	if (text_iter != 0){
//		if (numTextIters == text_iter) {
//			if (timesThru > practice.size()) {
//				if (timesThruTest > test.size()) {
//					timesThruTest = 0;
//					timesThru = 0;
//					setText(practice[timesThru]);
//					timesThru++;
//					printf("Reading...");
//					read();
//					getOneHotText(te, epoch, 0);
//					std::cout << practice[timesThru] << std::endl;
//					return 0;
//				}
//				setText(test[timesThruTest]);
//				timesThruTest++;
//				printf("Reading...");
//				read();
//				getOneHotText(te, epoch, 0);
//				std::cout << test[timesThruTest] << std::endl;
//				return 0;
//			}
//			setText(practice[timesThru]);
//			timesThru++;
//			printf("Reading...");
//			read();
//			getOneHotText(te, epoch, 0);
//			std::cout << practice[timesThru] << std::endl;
//			return 0;
//		}
//	}
//	else {
//		getOneHotText(te, epoch, iter);
//		return 1;
//	}
//}

void Preprocess::toLower(char &word) {
	if (word == 'A') word = 'a';
	else if (word == 'B') word = 'b';
	else if (word == 'C') word = 'c';
	else if (word == 'D') word = 'd';
	else if (word == 'E') word = 'e';
	else if (word == 'F') word = 'f';
	else if (word == 'G') word = 'g';
	else if (word == 'H') word = 'h';
	else if (word == 'I') word = 'i';
	else if (word == 'J') word = 'j';
	else if (word == 'K') word = 'k';
	else if (word == 'L') word = 'l';
	else if (word == 'M') word = 'm';
	else if (word == 'N') word = 'n';
	else if (word == 'O') word = 'o';
	else if (word == 'P') word = 'p';
	else if (word == 'Q') word = 'q';
	else if (word == 'R') word = 'r';
	else if (word == 'S') word = 's';
	else if (word == 'T') word = 't';
	else if (word == 'U') word = 'u';
	else if (word == 'V') word = 'v';
	else if (word == 'W') word = 'w';
	else if (word == 'X') word = 'x';
	else if (word == 'Y') word = 'y';
	else if (word == 'Z') word = 'z';
}

void Preprocess::getOneHotText(std::vector <std::vector <bool>> &te, int epoch, int iter) {
	te.resize(text.size());
	for ( int i = 0; i < text.size(); i++) 
		te[i].resize(lexicon.size());
	for (int i = 0; i < text.size(); i++, iter++) {
		// using full words
		if (_usingVocab) {
			for (int j = 0; j < vocab.size(); j++)
				// this isn't quite right
				if (text[iter] == vocab[j]) {
					te[i][j] = 1;
					continue;
				}
		}
		// using characters
		else {
			// using uppercase letters 
			if (!_usingLowerCase) {
				for (int j = 0; j < alphabet.size(); j++)
					if (text[epoch][iter] == alphabet[j]) {
						te[i][j] = 1;
						break;
					}
			}
			// using only lowercase
			else {
				// making sure it's lowercase
				if (iter >= text[epoch].size())
					break;
				toLower(text[epoch][iter]);
				for (int j = 0; j < lowerCase.size(); j++)
					if (text[epoch][iter] == lowerCase[j]) {
						//std::cout << i << " " << j << "\n";
						te[i][j] = 1;
						break;
					}
			}
		}
	}
}

void Preprocess::read() {
	// reading in
	if (_usingLowerCase) {
		alphabet.clear();
		alphabet.shrink_to_fit();
	}
	else {
		lowerCase.clear();
		lowerCase.shrink_to_fit();
	}
	// reading in the text
	f.open(m_TextPathWay, std::ios::in | std::ios::beg);
	if (f.is_open()) {
		std::string line;
		std::string index;
		char curr_char;
		// making sure the batch has a set amount, if not using the size size of the file as the batch length (probs not the best idea tbh)
		if (!batch_set) {
			f.seekg(0, std::ios::end);
			fileLength = f.tellg();
			f.seekg(0, std::ios::beg);
			batch_size = fileLength;
			numTextIters = batch_iter = fileLength / batch_size;
			//text.resize(batch_iter);
			batch_set = true;
		}
		// read thru the file
		while (!f.eof()) {
			// going thru in the batch sizes
			for (int i = 0; i <= batch_iter; i++) {
				f.seekg(batch_count * batch_size, std::ios::beg);
				while (std::getline(f, line)) {
					if (text.size() == batch_size) {
						batch_count++;
						break;
					}
					text.push_back(line);
				}
			}
		}
		
		// use vocab vector
		if (_usingVocab) {
			// where the words/characters begin to be processed to be put into vocab
			for (int i = 0; i < line.size(); i++)
				curr_char = line[i];
			if (curr_char != ',' || curr_char != '.' || curr_char != '!' || curr_char != '?')
				index += curr_char;
			// needs to be the root word (e.g. knowing -> know, gained -> gain)
			// does it? vastly increases lexicon size but having verb tense is useful...
			// there are far too many charspecial cases" (i.e. fought -> fight & bought -> buy & knew -> know) to bother
#if 0
			// remove "ing"
				if (index[index.back() - 2] == 'i')
					if (index[index.back() - 1] == 'n')
						if (index[index.back()] == 'g') {
							index.pop_back();
							index.pop_back();
							index.pop_back();
						}
				// remove "ed"
				if (index[index.back() - 1] == 'e')
					if (index[index.back()] == 'd') {
						index.pop_back();
						index.pop_back();
					}
#endif
			for (int i = 0; i < dict.size(); i++) {
				if (dict[i] == index) {
					dictCount[i]++;
					index = "";
					break;
				}
			}
			if (index != "") {
				dict.push_back(index);
				dictCount.push_back(1);
				index = "";
			}
			for (int i = 0; i < dict.size(); i++) {
				if (dictCount[i] >= vocab_MIN) {
					if (vocab_MAX != 0) {
						if (dictCount[i] <= vocab_MAX) {
							vocab.push_back(dict[i]);
						}
					}
					else {
						vocab.push_back(dict[i]);
					}
				}
			}
			// setting up the lexicon to use the vocab vector
			lexicon.resize(vocab.size());
			for (std::vector <bool> bo : lexicon) {
				bo.resize(lexicon.size());
				for (bool b : bo)
					b = 0;
			}
			for (int i = 0; i < lexicon.size(); i++) {
				lexicon[i][i] = 1;
			}
		}
		// setting up the lexicon for using the alphabet vector
		else {
			// using full (capital) alphabet 
			if (!_usingLowerCase) {
				lexicon.resize(alphabet.size());
				for (std::vector <bool> d : lexicon) {
					d.resize(alphabet.size());
					for (bool b : d)
						b = 0;
				}
				for (int i = 0; i < lexicon.size(); i++)
					for (int j = 0; j < lexicon[i].size(); j++)
						lexicon[i][j] = 1;
			}
			// using just the lowercase portion
			else {
				lexicon.resize(lowerCase.size());
				for (std::vector <bool> d : lexicon) {
					d.resize(lowerCase.size());
					for (bool b : d)
						b = 0;
				}
				for (int i = 0; i < lexicon.size(); i++)
					for (int j = 0; j < lexicon[i].size(); j++)
						lexicon[i][j] = 1;
			}
		}
		f.close();

		// reading in the target
		f.open(m_TargetPathWay, std::ios::in | std::ios::beg);
		if (f.is_open()) {
			std::string line;
			std::string index;
			char curr_char;
			// making sure the batch has a set amount, if not using the size size of the file as the batch length (probs not the best idea tbh)
			if (!batch_set) {
				f.seekg(0, std::ios::end);
				fileLength = f.tellg();
				f.seekg(0, std::ios::beg);
				batch_size = fileLength;
				numTextIters = batch_iter = fileLength / batch_size;
				//text.resize(batch_iter);
				batch_set = true;
			}
			// read thru the file
			while (!f.eof()) {
				// going thru in the batch sizes
				for (int i = 0; i <= batch_iter; i++) {
					f.seekg(batch_count * batch_size, std::ios::beg);
					while (std::getline(f, line)) {
						if (text.size() == batch_size) {
							batch_count_target++;
							break;
						}
						text.push_back(line);
					}
				}
			}

			// use vocab vector
			if (_usingVocab) {
				// where the words/characters begin to be processed to be put into vocab
				for (int i = 0; i < line.size(); i++)
					curr_char = line[i];
				if (curr_char != ',' || curr_char != '.' || curr_char != '!' || curr_char != '?')
					index += curr_char;
				// needs to be the root word (e.g. knowing -> know, gained -> gain)
				// does it? vastly increases lexicon size but having verb tense is useful...
				// there are far too many charspecial cases" (i.e. fought -> fight & bought -> buy & knew -> know) to bother
#if 0
				// remove "ing"
				if (index[index.back() - 2] == 'i')
					if (index[index.back() - 1] == 'n')
						if (index[index.back()] == 'g') {
							index.pop_back();
							index.pop_back();
							index.pop_back();
						}
				// remove "ed"
				if (index[index.back() - 1] == 'e')
					if (index[index.back()] == 'd') {
						index.pop_back();
						index.pop_back();
					}
#endif
				for (int i = 0; i < dict.size(); i++) {
					if (dictTarget[i] == index) {
						dictTargetCount[i]++;
						index = "";
						break;
					}
				}
				if (index != "") {
					dictTarget.push_back(index);
					dictTargetCount.push_back(1);
					index = "";
				}
				for (int i = 0; i < dict.size(); i++) {
					if (dictTargetCount[i] >= vocab_MIN) {
						if (vocab_MAX != 0) {
							if (dictTargetCount[i] <= vocab_MAX) {
								vocabTarget.push_back(dict[i]);
							}
						}
						else {
							vocabTarget.push_back(dict[i]);
						}
					}
				}
				// setting up the lexicon to use the vocab vector
				lexiconTarget.resize(vocab.size());
				for (std::vector <bool> bo : lexiconTarget) {
					bo.resize(lexiconTarget.size());
					for (bool b : bo)
						b = 0;
				}
				for (int i = 0; i < lexiconTarget.size(); i++) {
					lexiconTarget[i][i] = 1;
				}
			}
			// setting up the lexicon for using the alphabet vector
			else {
				// using full (w/ capital[ist]s) alphabet 
				if (!_usingLowerCase) {
					lexiconTarget.resize(alphabetTarget.size());
					for (std::vector <bool> d : lexiconTarget) {
						d.resize(alphabetTarget.size());
						for (bool b : d)
							b = 0;
					}
					for (int i = 0; i < lexiconTarget.size(); i++)
						for (int j = 0; j < lexiconTarget[i].size(); j++)
							lexiconTarget[i][j] = 1;
				}
				// using just the lowercase portion
				else {
					lexiconTarget.resize(lowerCaseTarget.size());
					for (std::vector <bool> d : lexiconTarget) {
						d.resize(lowerCaseTarget.size());
						for (bool b : d)
							b = 0;
					}
					for (int i = 0; i < lexiconTarget.size(); i++)
						for (int j = 0; j < lexiconTarget[i].size(); j++)
							lexiconTarget[i][j] = 1;
				}
			}
		}
		f.close();

		// writing out the vocab
		if (_usingVocab) {
			time_t now = time(0);
			tm *time = localtime(&now);
			std::string path = "/vocab/";
#if 0
			path += 1900 + time->tm_year;
			path += "/";
			path += 1 + time->tm_mon;
			path += "/";
			path += time->tm_mday;
			path += "/";
			path += "vocab.txt";
#else
			path += 1900 + time->tm_year;
			path += "-";
			path += 1 + time->tm_mon;
			path += "-";
			path += time->tm_mday;
			path += "-";
			path += "vocab.txt";
#endif
			f.open(path, std::ios::out | std::ios::trunc);
			if (f.is_open()) {
				for (int i = 0; i < vocab.size(); i++) {
					if (10 % i == 0) f << "\n";
					f << vocab[i];
					f << "\t";
				}
				f.close();
			}
		}

		// releasing the memory
		// hopefully
		dict.clear();
		dict.shrink_to_fit();
		dictCount.clear();
		dictCount.shrink_to_fit();
		dictTarget.clear();
		dictTarget.shrink_to_fit();
		dictTargetCount.clear();
		dictTargetCount.shrink_to_fit();
	}
}
