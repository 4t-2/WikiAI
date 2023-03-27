#include "../lib/IntNet/intnet.hpp"

#include "../inc/TextPredictor.hpp"

#include <fstream>
#include <string>

int getWordIndex(std::vector<std::string> indexedWords, std::string word)
{
	for (int i = 0; i < indexedWords.size(); i++)
	{
		if (word == indexedWords[i])
		{
			return i;
		}
	}

	return -1;
}

int main()
{
	std::fstream			 fs("text.txt", std::ios::in);
	std::string				 newText;
	std::vector<std::string> indexedWords;
	std::vector<std::string> trainingData;

	std::cout << "Reading training data" << '\n';

	while (fs.eof() == false)
	{
		std::string element;
		std::getline(fs, element, ' ');

		trainingData.emplace_back(element);

		bool found = false;

		for (std::string &el : indexedWords)
		{
			if (el == element)
			{
				found = true;
				break;
			}
		}

		if (!found)
		{
			indexedWords.emplace_back(element);
		}
	}

	std::cout << "Building network" << '\n';

	// std::srand(time(NULL));
	TextPredictor tp(indexedWords.size(), 1);

	std::cout << "Training network" << '\n';

	for (int y = 0; y < 5; y++)
	{
		for (int i = 0; i < trainingData.size() - WORDBUFFERSIZE; i++)
		{
			std::vector<int> index;

			for (int x = 0; x < WORDBUFFERSIZE; x++)
			{
				index.emplace_back(getWordIndex(indexedWords, trainingData[i + x]));
			}

			int target = getWordIndex(indexedWords, trainingData[i + WORDBUFFERSIZE]);

			std::cout << i << " / " << trainingData.size() - (WORDBUFFERSIZE - 1) << '\n';
			tp.train(index, target);
		}
	}
	// int bs = 10;
	// std::cout << "structure" << '\n';
	// in::NetworkStructure ns(1 + (bs * 29), { (bs * 29)}, 29);
	//
	// std::cout << "network" << '\n';
	// in::NeuralNetwork nn(ns);
	//
	// std::cout << "writing" << '\n';
	// std::fstream fs1("modelstruct", std::ios::out);
	// std::fstream fs2("modelnetwor", std::ios::out);

	// fs1 << ns.serialize();
	// fs2 << nn.serialize();
	//
	// fs1.close();
	// fs2.close();

	// in::NeuralNetwork test((unsigned char*)nn.serialize().c_str(), (unsigned
	// char*)ns.serialize().c_str());
	//
	// std::cout << "done" << '\n';
	//
	// nn.destroy();
	// test.destroy();
}
