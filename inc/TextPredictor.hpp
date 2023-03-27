#pragma once

#include "../lib/IntNet/intnet.hpp"

#define WORDBUFFERSIZE 1

class TextPredictor
{
	private:
		in::NetworkStructure netstruct; // hot encoded words, const 1
		in::NeuralNetwork	*network;
		int indexedWords = 0;
		int embeddingDimension = 0;

	public:
		TextPredictor(int indexedWords, int embeddingDimension);

		void train(std::vector<int> index, int target);

		int predict(std::vector<int> index);

		~TextPredictor();
};
