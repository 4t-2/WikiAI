#include "../lib/IntNet/intnet.hpp"

#include "../inc/TextPredictor.hpp"

#include <fstream>
#include <string>

int main()
{
	std::fstream fs("text.txt", std::ios::in);
	std::string	 text;
	std::string	 newText;

	for (int i = 0; i < CHARBUFFERSIZE; i++)
	{
		text = (char)1 + text;
	}

	newText = text;

	std::cout << "Reading training data" << '\n';

	while (fs.eof() == false)
	{
		std::string line;
		std::getline(fs, line);

		text += line + '\n';
	}

	std::cout << "Training network" << '\n';
	
	// std::srand(time(NULL));

	TextPredictor tp;

	for (int i = 0; i < text.length()-(CHARBUFFERSIZE-1); i++)
	{
		tp.train(text.substr(i, CHARBUFFERSIZE), text[CHARBUFFERSIZE + i]);
		std::cout << i << " / " << text.length() - 10 << '\n' << '\n';
	}

	newText += tp.predict(newText.substr(newText.length() - CHARBUFFERSIZE, CHARBUFFERSIZE));
	for (int i = 0; i < 500 && newText[newText.length() - 1] != 0; i++)
	{
		newText += tp.predict(newText.substr(newText.length() - CHARBUFFERSIZE, CHARBUFFERSIZE));
	}
	std::cout << newText << '\n';
}
