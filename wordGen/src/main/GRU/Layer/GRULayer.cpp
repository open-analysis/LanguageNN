#include "GRULayer.h"

GRULayer::GRULayer() {
	neurons.clear();
}
/*
GRULayer::~GRULayer() {
printf("MOTHERFUCKER");
if (multiNeuron) {
for (int i = 0; i < neurons.size(); i++)
neurons[i].~GRUNeuron();

neurons.clear();
neurons.shrink_to_fit();
}
else
neuron.~GRUNeuron();
}*/

void GRULayer::create(int numNeurons) {
	multiNeuron = true;
	neurons.resize(numNeurons);
	for (int i = 0; i < numNeurons; i++) {
		n = GRUNeuron();
		n.create();
		neurons[i] = n;
	}
}

void GRULayer::create() {
	multiNeuron = false;
	neuron = GRUNeuron();
	neuron.create();
}

void GRULayer::calculate() {
	if (!multiNeuron) {
		neuron.s.push_back(0);
		neuron.z.resize(483);
		for (int t = 0; t < neuron.input.size(); t++) {
			if (t == 0) {
				neuron.z.push_back((neuron.input[t] * neuron.U[0]));
				neuron.z[t] = 1.0 / (1.0 + exp(-neuron.z[t]));

				neuron.r.push_back((neuron.input[t] * neuron.U[1]));
				neuron.r[t] = 1.0 / (1.0 + exp(-neuron.r[t]));

				neuron.h.push_back((neuron.input[t] * neuron.U[2]));
				neuron.h[t] = 1.0 / (1.0 + exp(-neuron.h[t]));
			}
			else {
				neuron.z.push_back((neuron.input[t] * neuron.U[0]) + (neuron.s[t - 1] * neuron.W[0]));
				neuron.z[t] = 1.0 / (1.0 + exp(-neuron.z[t]));

				neuron.r.push_back((neuron.input[t] * neuron.U[1]) + (neuron.s[t - 1] * neuron.W[1]));
				neuron.r[t] = 1.0 / (1.0 + exp(-neuron.r[t]));

				neuron.h.push_back((neuron.input[t] * neuron.U[2]) + ((neuron.s[t - 1] * neuron.r[t]) * neuron.W[2]));
				neuron.h[t] = 1.0 / (1.0 + exp(-neuron.h[t]));
			}
			if (neuron.s[0] == 0)
				neuron.s.push_back(((1 - neuron.z.back()) * neuron.h.back() + neuron.z.back() * 0));
			else
				neuron.s.push_back(((1 - neuron.z.back()) * neuron.h.back() + neuron.z.back() * neuron.s[t - 1]));
			layerSum += neuron.s[t];
		}
	}
	else {
		for (int n = 0; n < neurons.size(); n++) {
			neurons[n].s.push_back(0);
			for (int t = 0; t < neurons[n].input.size(); t++) {
				if (t == 0) {
					neurons[n].z.push_back((neurons[n].input[t] * neurons[n].U[0]));
					neurons[n].z[t] = 1.0 / (1.0 + exp(-neurons[n].z[t]));

					neurons[n].r.push_back((neurons[n].input[t] * neurons[n].U[1]));
					neurons[n].r[t] = 1.0 / (1.0 + exp(-neurons[n].r[t]));

					neurons[n].h.push_back((neurons[n].input[t] * neurons[n].U[2]));
					neurons[n].h[t] = 1.0 / (1.0 + exp(-neurons[n].h[t]));
				}
				else {
					if (t == 2)
						printf("");
					neurons[n].z.push_back((neurons[n].input[t] * neurons[n].U[0]) + (neurons[n].s[t - 1] * neurons[n].W[0]));
					neurons[n].z[t] = 1.0 / (1.0 + exp(-neurons[n].z[t]));

					neurons[n].r.push_back((neurons[n].input[t] * neurons[n].U[1]) + (neurons[n].s[t - 1] * neurons[n].W[1]));
					neurons[n].r[t] = 1.0 / (1.0 + exp(-neurons[n].r[t]));

					neurons[n].h.push_back((neurons[n].input[t] * neurons[n].U[2]) + ((neurons[n].s[t - 1] * neurons[n].r[t]) * neurons[n].W[2]));
					neurons[n].h[t] = 1.0 / (1.0 + exp(-neurons[n].h[t]));
				}
				//if (neurons[n].s[0] == 0)
				if (t == 0)
					neurons[n].s[t] = (1 - neurons[n].z[t]) * neurons[n].h[t]/* + neurons[n].z[t] * 0*/;
				else if (t == 1)
					neurons[n].s.back() = (1 - neurons[n].z[t]) * neurons[n].h[t] + neurons[n].z[t] * neurons[n].s.back();
				else
					neurons[n].s[t] = (1 - neurons[n].z[t]) * neurons[n].h[t] + neurons[n].z[t] * neurons[n].s[t - 1];
				layerSum += neurons[n].s.back();
				neurons[n].s.push_back(0);
			}
		}
	}
}

// Cross Entropy Error
void GRULayer::CE(std::vector <bool> target) {
	if (multiNeuron) {
		for (int t = 0; t < target.size(); t++) {
			errsO.push_back(0);
			for (int i = 0; i < neurons[t].s.size(); i++)
				errsO[t] += (target[t] - neurons[t].s[i]);
			neurons[t].W[0] += learningRate * neurons[t].s[t] * errsO[t];
			neurons[t].W[1] = neurons[t].W[0] + learningRate * neurons[t].s[t + 1] * errsO[t];
			neurons[t].W[2] = neurons[t].W[1] + learningRate * neurons[t].s[t + 1] * errsO[t];

			errsH.push_back(neuron.h[t] * (errorO[t] * neurons[t].W[t]));
			neurons[t].U[0] += learningRate * neurons[t].s[t - 1] * errsH[t];
			neurons[t].U[1] = neurons[t].U[0] + learningRate * neurons[t].s[t] * errsH[t];
			neurons[t].U[2] = neurons[t].U[1] + learningRate * neurons[t].s[t] * errsH[t];
		}
	}
	else {
		for (int t = 0; t < target.size(); t++) {
			errorO.push_back(0);
			for (int i = 1; i < neuron.s.size(); i++)
				errorO[t] += (target[t] - neuron.s[i]);
			neuron.W[0] += learningRate * neuron.s[t + 1] * errorO[t];
			neuron.W[1] = neuron.W[0] + learningRate * neuron.s[t + 1] * errorO[t];
			neuron.W[2] = neuron.W[1] + learningRate * neuron.s[t + 1] * errorO[t];

			errorH.push_back(neuron.h[t] * (errorO[t] * neuron.W[t]));
			neuron.U[0] += learningRate * neuron.s[t] * errorH[t];
			neuron.U[1] = neuron.U[0] + learningRate * neuron.s[t] * errorH[t];
			neuron.U[2] = neuron.U[1] + learningRate * neuron.s[t] * errorH[t];
		}
	}
}