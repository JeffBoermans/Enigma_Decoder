//
// Created by Jeff Boermans on 06/12/2022.
//

#include <iostream>
#include <utility>
#include "Enigma.h"


Enigma::Enigma(std::string _crib, std::string _ciphertext, std::vector<std::string> _reflector,
               std::vector<std::vector<std::string>> _rotors) {

    this->crib = std::move(_crib);
    this->ciphertext = std::move(_ciphertext);
    this->cycle_rCombinations = std::move(_rotors);
    this->cycle_reflector = std::move(_reflector);
}

void Enigma::decrypt() {
    this->createRotorCombinations();
    Graph* newGraph = this->createCribGraph();
    this->advancedTuringBombe(newGraph);
}

void Enigma::createRotorCombinations() {
    std::string init = "AAA";
    for(int i = 0 ; i < this->alphabet.size() + 1; i++){
        for(int j = 0 ; j < this->alphabet.size() + 1; j++){
            for(char k : this->alphabet){
                init[2] = k;
                this->rotor_combinations.push_back(init);
            }
            init[2] = 'A';
            if(j == 0){
                j++;
            }
            init[1] = this->alphabet[j];
        }
        init[1] = 'A';
        if (i == 0){
            i++;
        }
        init[0] = this->alphabet[i];
    }
}

Graph* Enigma::createCribGraph() {
    std::string encrypted_string = "LXCACYLPNSIZCOQMAZ";
    auto* g = new Graph();

    for(int i = 0 ; i < this->crib.size() ; i++){
        Node* node = new Node(this->crib[i]);
        Node* node1 = new Node(encrypted_string[i]);

        Node* node_check = g->getNode(node->getName()[0]);
        Node* node_check1 = g->getNode(node1->getName()[0]);

        if(node_check == nullptr and node_check1 == nullptr){
            node->createPointer(node1, i);
            node1->createPointer(node, i);
            g->addNode(node);
            g->addNode(node1);
        }
        else if(node_check == nullptr and node_check1 != nullptr){
            node->createPointer(node_check1, i);
            node_check1->createPointer(node, i);
            g->addNode(node);
        }
        else if(node_check != nullptr and node_check1 == nullptr) {
            node1->createPointer(node_check, i);
            node_check->createPointer(node1, i);
            g->addNode(node1);
        }
        else{
            node_check1->createPointer(node_check, i);
            node_check->createPointer(node_check1, i);
        }
    }
    return g;
}




// The place to be to decipher enigma, like specified in the print statements, manually fill in your character when
// the number of potential nodes is smaller or equal to 26.
void Enigma::advancedTuringBombe(Graph *crib_graph) {
    int counter = 0;
    std::vector<std::tuple<int,int,int>> rotor_compositions;
    for(int i = 0 ; i < 5 ; i++){
        for(int j = 0 ; j < 5 ; j++){
            for(int k = 0 ; k < 5 ; k++){
                if(i != j and j != k and i != k){
                    rotor_compositions.emplace_back(i, j, k);
                }
            }
        }
    }
    Graph* advancedGraph = this->createInitialAdvancedGraph();
    for(std::tuple<int,int,int> r_comp : rotor_compositions){
        for(int k_val = 0 ; k_val < this->rotor_combinations.size() ; k_val++){
            // reset graph
            // To check the hardcoded solution, set k_val = 3493 and rotor_compositions = {std::make_tuple(1,3,2)};
            this->updateAdvancedGraph(advancedGraph, crib_graph, k_val, r_comp);
            std::vector<Node*> possible_nodes = advancedGraph->getNodes('A');
            for (auto&& itr : possible_nodes){
                advancedGraph->setPotential(itr);
                if(advancedGraph->checkValidEndGraph()){
                    std::cout << "========================================================================================" << std::endl;
                    std::cout << "Rightful rotor combination found!" << std::endl;
                    std::cout << "If some nodes aren't having potential, manually put them in the possible_nodes vector." << std::endl;
                    std::cout << "This can be done through changing the character in 'advancedGraph->getNodes(CHAR_HERE)"
                                 << std::endl << "(Line 104 in Enigma.cpp)" << std::endl;
                    std::cout << "========================================================================================" << std::endl;
                    std::cout << "Rotor start-position (S-M-F) = "<<this->rotor_combinations[k_val] << std::endl;
                    std::cout << "Rotor combination (S-M-F) = (" << std::get<0>(r_comp) << "," << std::get<1>(r_comp)
                            << "," << std::get<2>(r_comp) << ")" <<  std::endl;
                    std::cout << "========================================================================================" << std::endl;
                    advancedGraph->print();
                    return;
                }
                advancedGraph->removePotential();
            }
            counter++;
            if(counter % 2000 == 1){
                double temp = float(counter) / float(17000);
                std::cout << "Current combination: (" << std::get<0>(r_comp) << "," << std::get<1>(r_comp)
                          << "," << std::get<2>(r_comp) << ") is " << (temp * 100) << "% Covered." <<  std::endl;
            }
        }
        std::cout << "Following composition has no matches: " << std::get<0>(r_comp) << ", " << std::get<1>(r_comp)
                << ", " << std::get<2>(r_comp) << std::endl;
        std::cout << "Now trying next composition, wish me luck..." << std::endl;
        counter = 0;
    }
}

void Enigma::updateAdvancedGraph(Graph* advancedGraph, Graph *cribgraph, int k_val, std::tuple<int, int, int> rotor_composition) {
    // Step one : Reset graph
    // Step two : Add symmetric edges
    // Step three : Add transition rules
    // Full explanation of rules can be found in the course nodes (39 - 40)
    advancedGraph->resetNodes();
    for(char L1 : this->alphabet) {
        for(char L2 : this->alphabet){
            if(L1 != L2){
                Node* temp_node = advancedGraph->getNode(L1,L2);
                temp_node->createPointer(advancedGraph->getNode(L2,L1), 0);
            }
        }
    }

    for(std::pair<const std::string, Node *> node : cribgraph->getNodes()){
        for(std::pair<Node *, int> child : node.second->getPointers()){
            for(char c : this->alphabet){
                Node* temp = advancedGraph->getNode(node.first[0], c);
                char newVal = encryptChar(c, (k_val + child.second) % this->rotor_combinations.size() , rotor_composition);
                temp->createPointer(advancedGraph->getNode(child.first->getName()[0], newVal), 0);
            }
        }
    }
}

// Encrypts the character following the enigma rules, course notes (33)
char Enigma::encryptChar(char toEncrypt, int k_val, std::tuple<int,int,int> rotor_composition) {
    std::string rotor_comb = this->rotor_combinations[k_val];
    std::vector<int> rotor_comp = {std::get<0>(rotor_composition), std::get<1>(rotor_composition),
            std::get<2>(rotor_composition)};

    for(int i = 2 ; i >= 0 ; i--){
        toEncrypt = CharSum(toEncrypt, rotor_comb[i]);
        for(auto&& itr : this->cycle_rCombinations[rotor_comp[i]]) {
            if (std::count(itr.begin(), itr.end(), toEncrypt)) {
                toEncrypt = itr[((itr.find(toEncrypt) + 1) % itr.size())];
            }
        }
        toEncrypt = CharSub(toEncrypt, rotor_comb[i]);
    }
    for(auto&& itr : this->cycle_reflector){
        if (std::count(itr.begin(), itr.end(), toEncrypt)) {
            toEncrypt = itr[((itr.find(toEncrypt) + 1) % itr.size())];
            break;
        }
    }
    for(int i = 0 ; i <= 2 ; i++){
        toEncrypt = CharSum(toEncrypt, rotor_comb[i]);
        for(auto&& itr : this->cycle_rCombinations[rotor_comp[i]]) {
            if (std::count(itr.begin(), itr.end(), toEncrypt)) {
                int a = (((itr.find(toEncrypt) - 1) + itr.size()) % itr.size());
                toEncrypt = itr[a];
            }
        }
        toEncrypt = CharSub(toEncrypt, rotor_comb[i]);
    }
return toEncrypt;
}

Graph *Enigma::createInitialAdvancedGraph() {
    auto* advancedGraph = new Graph();
    for(char L1 : this->alphabet){
        for(char L2 : this->alphabet) {
            Node *node = new Node(L1, L2);
            advancedGraph->addNode(node);
        }
    }
return advancedGraph;
}

char Enigma::CharSum(const char &c1, const char &c2) {
    int sum = c1 + c2;
    return this->alphabet[(sum - 130) % 26];
}

char Enigma::CharSub(const char &c1, const char &c2) {
    int sub = c1 - c2;
    return this->alphabet[sub + 26 * (sub < 0)];
}

char Enigma::encryptCharTest() {
    for(char c : this->alphabet){
        char test = encryptChar(c,0,std::make_tuple(0,1,2));
        std::cout << c << " --> " << test << std::endl;
    }
}
