#include "GRU.h"

// NN
GRU::GRU() {
	_layers.clear();
}

GRU::~GRU() {
	printf("\n\nDeconstructing GRU\n\n");
	for (int i = 0; i < _layers.size(); i++)
		_layers[i].~GRULayer();
	_layers.clear();
	_layers.shrink_to_fit();
}

void GRU::create(int numLayers, int numNeurons) {
	_layers.resize(numLayers);
	for (int i = 0; i < _layers.size(); i++) {
		l = GRULayer();
		l.create(numNeurons);
		_layers[i] = l;
	}
	//batch_size = _layers.size();
}

void GRU::create(int numLayers) {
	_layers.resize(numLayers);
	for (int i = 0; i < _layers.size(); i++) {
		l = GRULayer();
		l.create();
		_layers[i] = l;
	}
	//batch_size = _layers.size();
}

//void inline GRU::setText(int epoch, int text_iter) {
//	if (pp.getText(_text, epoch, batch_iter, text_iter) == 0) batch_iter = 0;
//	_target = _text;
//}

void GRU::setBatchSize() {
	batch_size = pp.getBatchSize();
	batch_count = _target.size() / batch_size;
}

void GRU::train(double error_threshold, int num_epochs) {
	printf("Training\n");
	std::vector <double> doubles;
	// using multiple sources
	if (multiSource) {
		for (int epoch = 0; epoch <= num_epochs; epoch++) {
			for (int text_iter = 0; text_iter < pp.totalFiles; text_iter++) {
				double errorTotal = 0;
				setText(epoch);
				printf("Text Set\n");
				// propagate
				getDoubleFromOneHot(_text, doubles);
				propagate(doubles);
				printf("Propagated\n");
				// need to fix this so that way it goes through the entire text for each epoch

				// going thru each individual vector point in the text vector
				std::cout << "Layer Size: " << _layers.size() << "\n";
				for (int i = 0; i < _text.size(); i++, batch_iter++) {
					predictNext();
					/*for (GRULayer lay : _layers)
						lay.calculate();
					*/
					// bp
					// SGD (probably)
					printf("Calculating: ");
					std::cout << i << "\n";
					for (int i = 0; i < _layers.size(); i++)
						_layers[i].CE(_target[i]);
					for (int i = 0; i < _layers.size(); i++) {
						if (!_layers[i].multiNeuron) {
							for (double err : _layers[i].errorO) {
								errorTotal += err;
							}
						}
						else {
							for (double err : _layers[i].errsO) {
								errorTotal += err;
							}
						}
					}
				}
				std::cout << "\n=================================================\n";
				std::cout << "Epoch: " << epoch + 1 << "\n" << "Error: " << errorTotal << "\n";
				std::cout << "=================================================\n";
				if (errorTotal < error_threshold) {
					printf("\n\nError Under Threshold! Holy SHit\n\n");
					saveWeights();
					break;
				}
			}
		}
	}
	// using a single source
	else {
		for (int epoch = 0; epoch <= num_epochs; epoch++) {
			double errorTotal = 0;
			setText(epoch);
			printf("Text Set\n");
			// propagate
			getDoubleFromOneHot(_text, doubles);
			propagate(doubles);
			printf("Propagated\n");
			// need to fix this so that way it goes through the entire text for each epoch

			// going thru each individual vector point in the text vector
			for (int i = 0; i < _text.size(); i++, batch_iter++) {
				predictNext();
				/*for (GRULayer lay : _layers)
				lay.calculate();
				*/
				// bp
				// SGD (probably)
				printf("Calculating: ");
				std::cout << i << "\n";
				for (int i = 0; i < _layers.size(); i++)
					_layers[i].CE(_target[i]);
				for (int i = 0; i < _layers.size(); i++) {
					if (!_layers[i].multiNeuron) {
						for (double err : _layers[i].errorO) {
							errorTotal += err;
						}
					}
					else {
						for (double err : _layers[i].errsO) {
							errorTotal += err;
						}
					}
				}
			}
			std::cout << "\n=================================================\n";
			std::cout << "Epoch: " << epoch + 1 << "\n" << "Error: " << errorTotal << "\n";
			std::cout << "=================================================\n";
			if (errorTotal < error_threshold) {
				printf("\n\nError Under Threshold! Holy SHit\n\n");
				saveWeights();
				break;
			}
		}
	}
}

void GRU::shuffle(std::vector <std::vector <double>> &input) {
	int num;
	std::vector <std::vector <double>> tmp;
	std::random_device rd;
	std::uniform_int_distribution <int> dist(0, input.size());
	tmp.resize(input.size());
	for (int i = 0; i < input.size(); i++) {
		num = dist(rd);
		tmp.push_back(input[i]);
	}
	input.swap(tmp);
}

std::string GRU::generate(int length) {
	std::vector <std::vector <bool>> tmp;
	std::vector <std::string> vocab;
	std::string result;
	if (pp.getUsingLexicon()) {
		vocab = pp.getVocab();
		int loc = 0;
		for (int i = 0; i < length; i++) {
			tmp[i] = predictNext();
			for (int j = 0; j < tmp[i].size(); j++) {
				if (j == 0) continue;
				if (tmp[i][j] == 0) continue;
				else {
					loc = j;
					break;
				}
			}
			result += vocab[loc];
		}
	}
	else {
		//vocab = pp.getAlphabet();
		int loc = 0;
		for (int i = 0; i < length; i++) {
			tmp[i] = predictNext();
			for (int j = 0; j < tmp[i].size(); j++) {
				if (j == 0) continue;
				if (tmp[i][j] == 0) continue;
				else {
					loc = j;
					break;
				}
			}
			result += vocab[loc];
		}
	}
	return result;
}

std::vector <bool> GRU::predictNext() {
	std::vector <double> tmp;
	std::vector <bool> result;
	tmp.resize(pp.getLexicon().size());
	result.resize(tmp.size());
	int mostConfident = 0;
	for (int i = 0; i < _layers.size(); i++) {
		_layers[i].calculate();
		tmp[i] = _layers[i].layerSum;
	}
	/*for (int i = 0; i < tmp.size(); i++)
		std::cout << tmp[i] << std::endl; */
	for (int i = 1; i < tmp.size(); i++) 
		if (tmp[mostConfident] < tmp[i]) mostConfident = i;
	for (bool b : result) b = 0;
	result.at(mostConfident) = 1;
	tmp.erase(tmp.begin(), tmp.end());
	return result;
}

void GRU::getDoubleFromOneHot(std::vector <std::vector <bool>> const tmp, std::vector <double> &result) {
	result.resize(tmp.size());
	for (int i = 0; i < tmp.size(); i++) {
		for (int j = 0; j < tmp[i].size(); j++) {
			if (tmp[i][j] == 1) {
				result[i] = j;
				break;
			}
		}
		//printf("Results:\n");
		//std::cout << result[i] << "\n\n";
	}
}

void GRU::propagate(std::vector <double> Inputs) {
	for (int i = 0; i < _layers.size(); i++) {
		if (_layers[i].multiNeuron)
			for (int j = 0; j < _layers[i].neurons.size(); j++)
				_layers[i].neurons[j].input = Inputs;
		else 
			_layers[i].neuron.input = Inputs;
	}
	/*for (GRULayer la : _layers)
		if (la.multiNeuron)
			for (GRUNeuron ne : la.neurons)
				std::cout << ne.input.size() << std::endl;
		else
			std::cout << la.neuron.input.size() << std::endl;*/
}

void GRU::saveWeights() {
	std::fstream f;
	time_t now = time(0);
	tm *time = localtime(&now);
	std::string path = "/weights/";
#if 1
	path += 1900 + time->tm_year;
	path += "/";
	path += 1 + time->tm_mon;
	path += "/";
	path += time->tm_mday;
	path += "/";
	path += "weights.wght";
#else
	path += 1900 + time->tm_year;
	path += "-";
	path += 1 + time->tm_mon;
	path += "-";
	path += time->tm_mday;
	path += "-";
	path += "weights.wght";
#endif
	f.open(path, std::ios::out | std::ios::trunc);
	if (f.is_open()) {
		for (int i = 0; i < _layers.size(); i++) {
			if (_layers[i].multiNeuron) {
				f << "LAYER";
				for (int j = 0; j < _layers[i].neurons.size(); j++) {
					f << "NEURON";
					f << _layers[i].neurons[j].U[0];
					f << "\n";
					f << _layers[i].neurons[j].U[1];
					f << "\n";
					f << _layers[i].neurons[j].U[2];
					f << "\n";

					f << _layers[i].neurons[j].W[0];
					f << "\n";
					f << _layers[i].neurons[j].W[1];
					f << "\n";
					f << _layers[i].neurons[j].W[2];
					f << "\n";
					f << "\n";
				}
			}
			else {
				f << "LAYER";
				f << _layers[i].neuron.U[0];
				f << "\n";
				f << _layers[i].neuron.U[1];
				f << "\n";
				f << _layers[i].neuron.U[2];
				f << "\n";

				f << _layers[i].neuron.W[0];
				f << "\n";
				f << _layers[i].neuron.W[1];
				f << "\n";
				f << _layers[i].neuron.W[2];
				f << "\n";
				f << "\n";
			}
		}
	}
	f.close();
}

void loadWeights(std::string pathway) {
	std::fstream f;
	std::string path = pathway;

	f.open(path, std::ios::in);
}

void GRU::loadWeights() {
	std::fstream f;
	time_t now = time(0);
	tm *time = localtime(&now);
	std::string path = "/weights/";
}