#include "CareGiver.h"
#include <math.h>
#include <vector>

Therapist::Therapist(std::string name, std::vector<uint8_t> effectiveness) {
		this->name = name;
		this->score = 0;
		this->outputText = "";
		this->experience = std::vector<Experience>();
		for (int i = 0; i < effectiveness.size(); i++) {
			if (effectiveness[i] >= 0 && effectiveness[i] <= 5) {
				experience.push_back((Experience) effectiveness[i]);
			}
			else {
				EXIT_FAILURE;
			}
		}
}

std::string Therapist::getName() {
	return this->name;
}

std::vector<Experience> Therapist::getExperience() {
	return this->experience;
}

void Therapist::adjustScore(uint8_t score) {
	this->score += score;
}

uint8_t Therapist::getScore() {
	return this->score;
}

void Therapist::setText(std::string text) {
	this->outputText = text;
}

std::string Therapist::getText() {
	return this->outputText;
}