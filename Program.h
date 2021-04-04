#pragma once
#include "Caregiver.h"
#include <vector>
#include <string>
#include "Utils.h"

class Program {
public:
	Program(std::vector<std::string>, std::vector<std::string>, std::vector<Therapist>);
	bool start(bool = false);

private:
	bool askQuestions();
	bool provideResults();
	bool scoreCareGivers();
	bool assignText();
	bool sortCareGivers();
	void printResults();
	std::string experienceToString(Experience);

	std::vector<std::string> questions;
	std::vector<std::string> conditions;
	std::vector<Therapist> careGivers;
	std::vector<uint8_t> patientResponse;
	std::vector<std::vector<uint8_t>> scoreMap;
};