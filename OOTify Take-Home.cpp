// OOTify Take-Home.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <vector>
#include <string>
#include <random>
#include "Program.h"
#include "CareGiver.h"
#include <iostream>

int main()
{
    std::vector<std::string> questions = {
        "I struggle with loneliness/depression.",
        "I always feel stressed/anxious.",
        "I drink too much alcohol.",
        "I have trouble sleeping.",
        "I have problems eating too much/too little."
    };

    std::vector<std::string> categories = {
        "Depression",
        "Anxiety",
        "Substance Abuse",
        "Sleep",
        "Eating Disorders"
    };

    std::vector<std::string> therapistNames = {
        "Henry",
        "Linda",
        "Rachel",
        "Paul",
        "Sandra",
        "Jeremy",
        "Chris",
        "Rebecca",
        "David",
        "James",
        "Spencer",
        "Brad",
        "Sarah",
        "Lisa",
        "Matthew",
    };

    std::vector<Therapist> careGivers = std::vector<Therapist>();

    for (auto name : therapistNames) {
        std::vector<uint8_t> experience = std::vector<uint8_t>();
        for (int i = 0; i < 5; i++) {
            int num = (rand() % 100) / 17;
            experience.push_back(num);
            
        }
        Therapist therapist = Therapist(name, experience);
        careGivers.push_back(therapist);
    }

    Program program = Program(questions, categories, careGivers);
    program.start();
}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
