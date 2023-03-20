#pragma once

#include "../lib/IntNet/intnet.hpp"

#define CHARBUFFERSIZE 5

class TextPredictor
{
	private:
		in::NetworkStructure netstruct = in::NetworkStructure(1 + (CHARBUFFERSIZE * 29), {30, 30}, 29); // null, a-z, , \n
		in::NeuralNetwork	*network;

	public:
		TextPredictor();

		void train(std::string input, char target);

		char predict(std::string input);

		~TextPredictor();
};
