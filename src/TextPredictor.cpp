#include "../inc/TextPredictor.hpp"

TextPredictor::TextPredictor()
{
	in::NetworkStructure::randomWeights(netstruct);

	network = new in::NeuralNetwork(netstruct);

	network->setInputNode(0, 1);
}

int charToNode(char c)
{
	int ci = 0;

	if (c >= 97 && c <= 122)
	{
		ci = c - 96;
	}
	else if (c == 32)
	{
		ci = 27;
	}
	else if (c == 10)
	{
		ci = 28;
	}

	return ci;
}

char nodeToChar(int node)
{
	int ni = 0;

	if ((node + 96) >= 97 && (node + 96) <= 122)
	{
		ni = node + 96;
	}
	else if (node == 27)
	{
		ni = 32;
	}
	else if (node == 28)
	{
		ni = 10;
	}

	return node;
}

void TextPredictor::train(std::string input, char target)
{
	std::vector<float> targetValue;
	targetValue.resize(29);

	for (int i = 1; i < network->structure.totalInputNodes; i++)
	{
		network->setInputNode(i, 0);
	}

	for (int i = 0; i < CHARBUFFERSIZE; i++)
	{
		int ci = 0;

		if (input[i] >= 97 && input[i] <= 122)
		{
			ci = input[i] - 96;
		}
		else if (input[i] == 32)
		{
			ci = 27;
		}
		else if (input[i] == 10)
		{
			ci = 28;
		}

		network->setInputNode((i * CHARBUFFERSIZE) + ci + 1, 1);
		targetValue[ci] = 1;
	}

	network->update();

	network->backpropagation(targetValue);
}

char TextPredictor::predict(std::string input)
{
	for (int i = 1; i < network->structure.totalInputNodes; i++)
	{
		network->setInputNode(i, 0);
	}

	for (int i = 0; i < CHARBUFFERSIZE; i++)
	{
		int ci = 0;

		if (input[i] >= 97 && input[i] <= 122)
		{
			ci = input[i] - 96;
		}
		else if (input[i] == 32)
		{
			ci = 27;
		}
		else if (input[i] == 10)
		{
			ci = 28;
		}

		network->setInputNode((i * CHARBUFFERSIZE) + ci + 1, 1);
	}

	network->update();

	int max = network->structure.totalNodes - network->structure.totalOutputNodes;
	int val = 0;

	for(int i = network->structure.totalNodes - network->structure.totalOutputNodes; i < network->structure.totalNodes; i++)
	{
		if(network->node[i].value > val)
		{
			max = i;
		}
	}

	std::cout << (int)nodeToChar(max - (network->structure.totalNodes - network->structure.totalOutputNodes));

	return 0;
}

TextPredictor::~TextPredictor()
{
	network->destroy();
	delete network;
}
