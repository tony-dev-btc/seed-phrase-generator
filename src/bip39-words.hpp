#pragma once

#include <string>
#include <vector>
#include <random>
#include <fstream>


std::vector<std::string> bip39_words;

bool load_bip39_words()
{
	std::string file_path = "bip39-words.txt";
	std::ifstream file(file_path);;
	if (!file.is_open())
		return false;

	std::string line;
	while (std::getline(file, line)) {
		bip39_words.push_back(line);
	}

	return true;
}

std::string generate_mnemonic(int length)
{
	std::string mnemonic = "";
	std::random_device rd;

	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(0, bip39_words.size() - 1);

	for (int i = 0; i < 12; ++i) {
		int index = dis(gen);
		mnemonic += bip39_words[index];
		if (i < 11) {
			mnemonic += " ";
		}
	}
	return mnemonic;
}
