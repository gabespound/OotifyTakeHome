#pragma once
#include <string>
#include <vector>
#include "Utils.h"

class Therapist {
public:
	Therapist(std::string, std::vector<uint8_t>);
	std::string getName();
	std::vector<Experience> getExperience();
	void adjustScore(uint8_t);
	uint8_t getScore();
	void setText(std::string);
	std::string getText();

private:
	std::string name;
	std::vector<Experience> experience;
	uint8_t score;
	std::string outputText;
};