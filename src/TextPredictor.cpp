#include "../inc/TextPredictor.hpp"

TextPredictor::TextPredictor(int indexedWords, int embeddingDimension)
	: netstruct(in::NetworkStructure((WORDBUFFERSIZE * indexedWords) + 1, {200, 200}, indexedWords))
{
	in::NetworkStructure::randomWeights(netstruct);

	network = new in::NeuralNetwork(netstruct);

	network->learningRate = 0.6;

	network->setInputNode(network->structure.totalInputNodes - 1, 1);

	this->indexedWords = indexedWords;
}

int TextPredictor::predict(std::vector<int> index)
{
	for (int i = 0; i < network->structure.totalInputNodes - 1; i++)
	{
		network->setInputNode(i, 0);
	}

	for (int i = 0; i < index.size(); i++)
	{
		network->setInputNode((i * indexedWords) + index[i], 1);
	}

	network->update();

	std::vector<float> outputVec;
	outputVec.resize(indexedWords);

	for (int i = 0; i < outputVec.size(); i++)
	{
		outputVec[i] = network->outputNode[i].value;
	}

	struct
	{
			int	  id;
			float val;
	} max;

	for (int i = 0; i < network->structure.totalOutputNodes; i++)
	{
		if (max.val < network->outputNode[i].value)
		{
			max.id = i;
		}
	}

	return max.id;
}

void TextPredictor::train(std::vector<int> index, int target)
{
	std::vector<float> targetValue;
	targetValue.resize(indexedWords);

	targetValue[target] = 1;

	int prediction = this->predict(index);

	std::cout << network->backpropagation(targetValue) << '\n';
}

TextPredictor::~TextPredictor()
{
	network->destroy();
	delete network;
}
