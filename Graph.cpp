#include "Graph.h"

#include <utility>
#include <iostream>

void Graph::addNode(Node* node) {
    this->nodes[node->getName()] = (node);
}


std::map<std::string, Node *> Graph::getNodes() {
    return this->nodes;
}

const int Graph::returnValue(char node_name1, char node_name2) {
    Node* possible_node = getNode(node_name1);
    if(possible_node == nullptr){
        return -1;
    }
    for(auto&& itr: possible_node->getPointers()){
        if(itr.first->getName()[0] == node_name2){
            return itr.second;
        }
    }
return -1;}

void Graph::setPotential(Node *node) {
    if(this->potential_nodes.size() >= 40){
        return;
    }
    if(std::count(potential_nodes.begin(), potential_nodes.end(), node)){
        return;
    }
    potential_nodes.push_back(node);
    for(std::pair<Node*,int> itr : node->getPointers()){
        this->setPotential(itr.first);
    }
}

bool Graph::checkValidEndGraph() {
    if(potential_nodes.size() <= 26){
        return true;
    }
    return false;
}

void Graph::removePotential() {
    this->potential_nodes.clear();
}

std::vector<Node*> Graph::getNodes(char node_char) {
    std::vector<Node*> possible_nodes;
    std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for(char c : alphabet){
        std::string name = "{";
        name += node_char;
        name += ",";
        name += c;
        name += "}";
        Node* possible_node = this->nodes[name];
        if(possible_node != nullptr){
            possible_nodes.push_back(possible_node);
        }
    }
return possible_nodes;}

Node *Graph::getNode(char L1, char L2) {
    std::string name = "{";
    name += L1;
    name += ',';
    name += L2;
    name += "}";
    return this->nodes[name];
}

Node *Graph::getNode(char L1) {
    std::string temp_str;
    temp_str += L1;
    return this->nodes[temp_str];
}

Graph::~Graph() {
    for(const auto& n : this->nodes){
        delete n.second;
    }
}

void Graph::resetNodes() {
    for(const auto& itr : this->nodes){
        itr.second->resetPointers();
    }
}

void Graph::print() {
    std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::cout << "   ";
    for(char c : alphabet){
        std::cout << " " << c << " ";
    }
    std::cout << std::endl;
    for(char c : alphabet){
        std::cout << " " << c << " ";
        std::vector<Node *> possible_nodes = this->getNodes(c);
        for(Node* n : possible_nodes){
            if(std::count(potential_nodes.begin(), potential_nodes.end(), n)){
                std::cout << " 1 ";
            }else{
                std::cout << " 0 ";
            }
        }
        std::cout << std::endl;
    }
}


void Node::createPointer(Node *node, int value) {
    this->pointers.emplace_back(node, value);
}

Node::Node(std::string _name) {
    this->name = std::move(_name);
}

std::string Node::getName() {
    return this->name;
}

std::vector<std::pair<Node *, int>> Node::getPointers() {
    return this->pointers;
}

Node::Node(char _name) {
    std::string str_name;
    str_name.push_back(_name);
    this->name = str_name;
}

Node::Node(char name1, char name2) {
    std::string _name = "{";
    _name += name1;
    _name += ",";
    _name += name2;
    _name += "}";
    this->name = _name;
}

void Node::resetPointers() {
    this->pointers.clear();
}





