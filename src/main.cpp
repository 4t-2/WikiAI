#include "../lib/IntNet/intnet.hpp"

#include "../inc/TextPredictor.hpp"

#include <fstream>
#include <string>

int main()
{
	std::fstream fs("text.txt", std::ios::in);
	std::string	 text;

	for (int i = 0; i < CHARBUFFERSIZE; i++)
	{
		text = '\0' + text;
	}

	std::cout << "Reading training data" << '\n';

	while (fs.eof() == false)
	{
		std::string line;
		std::getline(fs, line);

		text += line + '\n';
	}

	std::cout << "Training network" << '\n';

	TextPredictor tp;

	for (int i = 0; i < text.length() - 10; i++)
	{
		tp.train(text.substr(i, CHARBUFFERSIZE), text[CHARBUFFERSIZE + i]);
		std::cout << i << " / " << text.length() - 10 << '\n' << '\n';
	}

	tp.predict("th");
}
