#include "WordReader.h"
#include <iostream>

WordReader::WordReader(const std::string& filename) {
	std::ifstream file(filename);
	if (!file) {
		throw std::runtime_error("Error opening file!");
	}

	std::string word;
	while (std::getline(file, word)) {
		words.push_back(word);
	}

	std::srand(std::time(nullptr));
}

WordReader::~WordReader() {}

std::string WordReader::getRandomWord() {
	// If the file is empty return ""
	if (words.empty()) {
		return "";
	}
	// Choosing random index
	int randomIndex = std::rand() % words.size();
	return words[randomIndex];
}