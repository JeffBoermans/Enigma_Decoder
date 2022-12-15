//
// Created by Jeff Boermans on 06/12/2022.
//

#ifndef SPEEDY_ENIGMA_ENIGMA_H
#define SPEEDY_ENIGMA_ENIGMA_H


#include <string>
#include <vector>

#include "Graph.h"

class Enigma {
private:
    std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string crib;
    std::string ciphertext;
    std::vector<std::string> rotor_combinations;
    std::vector<std::vector<std::string>> cycle_rCombinations;
    std::vector<std::string> cycle_reflector;


    void createRotorCombinations();
    Graph* createCribGraph();
    void updateAdvancedGraph(Graph* advancedGraph, Graph *cribgraph, int k_val, std::tuple<int,int,int> rotor_composition);
    Graph* createInitialAdvancedGraph();

    void advancedTuringBombe(Graph* crib_graph);
    char encryptChar(char toEncrypt, int k_val , std::tuple<int,int,int> rotor_composition);
    char encryptCharTest();
    char CharSum(const char& c1, const char& c2);
    char CharSub(const char& c1, const char& c2);

public:
    Enigma(std::string _crib, std::string _ciphertext, std::vector<std::string> reflector,
           std::vector<std::vector<std::string>> rotors);

    void decrypt();
    ~Enigma() = default;
};


#endif //SPEEDY_ENIGMA_ENIGMA_H
