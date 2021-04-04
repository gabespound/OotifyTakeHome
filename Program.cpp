#include "Program.h"
#include <stdio.h>
#include <iostream>

Program::Program(std::vector<std::string> questions, std::vector<std::string> conditions, std::vector<Therapist> careGivers) {
	this->questions = questions;
	this->conditions = conditions;
	this->careGivers = careGivers;
	this->scoreMap = std::vector<std::vector<uint8_t>>();
	this->patientResponse = std::vector<uint8_t>();
	for (int i = 0; i < careGivers.size(); i++) {
		scoreMap.push_back(std::vector<uint8_t>());
	}
}

bool Program::start(bool testing) {
	printf("Welcome to Thera-pairer!\n\nPlease answer the following questions on a scale of 1 to 5.\n1 means \"I do not agree at all\" and 5 meaning \"I totally agree\".\n\n");
	if (testing) {
		this->patientResponse = { 0, 4, 2, 4, 1 };
		return this->provideResults();
	}
	else {
		return this->askQuestions();
	}
}

bool Program::askQuestions() {
	if (questions.size() < 1) { return false; }
	for (int i = 0; i < questions.size(); i++) {
		printf(questions[i].c_str());
		printf("\n");
		bool loop = true;
		uint8_t x;
		while (loop) {
			std::cin >> x;
			if (std::cin.fail()) {
				printf("Please enter an integer from 1-5.\n");
			}
			else {
				if (x >= 49 && x <= 53) {
					loop = false;
					this->patientResponse.push_back(x - 49);
				}
				else {
					printf("Please enter an integer from 1-5.\n");
				}
			}
		}
	}
	return this->provideResults();
}

bool Program::provideResults() {
	bool properScoring = this->scoreCareGivers();
	bool textAssignment = this->assignText();
	bool properSorting = this->sortCareGivers();
	this->printResults();
	return properScoring && textAssignment && properSorting;
}

bool Program::scoreCareGivers() {
	if (careGivers.size() < 3) {
		return false;
	}
	for (int i = 0; i < patientResponse.size(); i++) {
		for (int j = 0; j < careGivers.size(); j++) {
			uint8_t score = patientResponse[i] * careGivers[j].getExperience()[i];
			this->scoreMap[j].push_back(score);
			careGivers[j].adjustScore(score);
		}
	}
	return true;
}

bool Program::assignText() {
	if (conditions.size() != questions.size() || careGivers.size() < 3) {
		return false;
	}
	for (int i = 0; i < 5; i++) {
		std::vector<int> bestScoreIndices = { 0 };
		for (int j = 1; j < scoreMap.size(); j++) {
			if (scoreMap[j][i] > scoreMap[bestScoreIndices[0]][i]) {
				bestScoreIndices = { j };
			}
			else if (scoreMap[j][i] == scoreMap[bestScoreIndices[0]][i]) {
				bestScoreIndices.push_back(j);
			}
		}
		for (auto it : bestScoreIndices) {
			std::string text = "" + careGivers[it].getName() + " is the best at helping people with " + this->conditions[i];
			uint8_t secondBest = 0;
			uint8_t best = 0;
			bool set = false;
			for (uint8_t j = 0; j < 5; j++) {
				if (careGivers[it].getExperience()[j] > 0) {
					if (set) {
						if (careGivers[it].getExperience()[j] >= careGivers[it].getExperience()[secondBest]) {
							secondBest = best;
							best = j;
							set = true;
						}
					}
					else {
						secondBest = best;
						best = j;
						set = true;
					}
				}
			}
			if (set) {
				text += ", and is also good at helping people with " + this->conditions[secondBest];
			}
			careGivers[it].setText(text);
		}
		bool hasText = true;
		for (auto cg : careGivers) {
			hasText = hasText && (cg.getText() != "");
		}
		return hasText;
	}
	for (int i = 0; i < careGivers.size(); i++) {
		if (careGivers[i].getText() == "") {
			std::vector<int> bestTraitIndices = { 0 };
			std::vector<Experience> experience = careGivers[i].getExperience();
			for (int i = 1; i < experience.size(); i++) {
				if (experience[i] > experience[bestTraitIndices[0]]) {
					bestTraitIndices = { i };
				}
				else if (experience[i] == experience[bestTraitIndices[0]]) {
					bestTraitIndices.push_back(i);
				}
			}
			std::string text = "" + careGivers[i].getName() + " is " + experienceToString(experience[bestTraitIndices[0]]) +
				" at helping people with " + this->conditions[bestTraitIndices[0]];
			if (bestTraitIndices.size() > 1) {
				 text += " and " + this->conditions[bestTraitIndices[1]];
			}
			careGivers[i].setText(text);
		}
	}
}

bool Program::sortCareGivers() {
	if (careGivers.size() < 3) {
		return false;
	}
	std::vector<Therapist> sortedCareGivers = { careGivers[0] };
	for (int i = 1; i < careGivers.size(); i++) {
		bool inserted = false;
		int cSize = sortedCareGivers.size();
		for (int j = 0; j < cSize; j++) {
			if (careGivers[i].getScore() > sortedCareGivers[j].getScore()) {
				inserted = true;
				sortedCareGivers.insert(sortedCareGivers.begin() + j, careGivers[i]);
				j = cSize;
			}
		}
		if (!inserted) {
			sortedCareGivers.push_back(careGivers[i]);
		}
	}
	this->careGivers = sortedCareGivers;
	return careGivers.size() > 2;
}

void Program::printResults() {
	printf("\nOur top 3 recommended therapists in order are: \n");
	int i = 1;
	for (auto cg:careGivers) {
		printf("%d. %s \n", i + 1, cg.getText().c_str()); 
		i++;
	}
}

std::string Program::experienceToString(Experience exp) {
	switch (exp) {
	case none:
		return "not good";
	case little:
		return "ok";
	case normal:
		return "good";
	case proficient:
		return "very good";
	case expert:
		return "an expert at";
	case master:
		return "masterful";
	}
}