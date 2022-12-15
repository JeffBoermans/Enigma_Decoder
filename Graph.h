//
// Created by Jeff Boermans on 06/12/2022.
//

#ifndef SPEEDY_ENIGMA_GRAPH_H
#define SPEEDY_ENIGMA_GRAPH_H

#include <vector>
#include <map>
#include <string>
#include <fstream>

class Node{
private:
    std::vector<std::pair<Node* , int>> pointers;
    std::string name;

public:
    std::string getName();
    std::vector<std::pair<Node*, int>> getPointers();
    explicit Node(std::string _name);
    explicit Node(char _name);
    Node(char name1, char name2);
    void createPointer(Node* node, int value);
    void resetPointers();
};



class Graph {
private:
    std::map<std::string, Node*> nodes;
public:
    Graph() = default;
    ~Graph();

    void addNode(Node* node);
//    int returnValue(std::string node_name1, std::string node_name2);
    const int returnValue(char node_name1, char node_name2);
    void setPotential(Node* node);
    bool checkValidEndGraph();
    void removePotential();
    std::vector<Node*> potential_nodes;
    std::map<std::string, Node*> getNodes();
    std::vector<Node*> getNodes(char name);
    Node* getNode(char L1, char L2);
    Node* getNode(char L1);
    void resetNodes();
    void print();
};




#endif //SPEEDY_ENIGMA_GRAPH_H
