#pragma once
#ifndef WORDREADER_H
#define WORDREADER_H

#include <fstream>
#include <vector>
#include <string>

class WordReader {
public:
	/// <summary>
	/// This is my WordReader Constructor.
	/// </summary>
	/// <param name="filename"></param>
	WordReader(const std::string& filename);

	/// <summary>
	/// This is my WordReader Destructor.
	/// </summary>
	~WordReader();
	std::string getRandomWord();

private:
	std::vector<std::string> words;
};

#endif