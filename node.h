#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <bits/stdc++.h>
#include <string>
using namespace std;


struct Node{
	string name;
	int depth;
	vector <string> words;
	Node* first_Node;
	Node* second_Node;
	Node* third_Node;
	Node* fourth_Node;
};

extern Node* root;

Node* getNewNode(string nameToGive, int level);
void addToVector(vector<string> &v, string toAdd);

#endif
