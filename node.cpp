
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <bits/stdc++.h>
#include <string>
#include "node.h"
using namespace std;


Node* getNewNode(string nameToGive, int level) {
	Node* newNode = new Node();
	newNode->name = nameToGive;
	newNode->depth = level;
	newNode->first_Node = newNode->second_Node = NULL;
	newNode->third_Node = newNode->fourth_Node = NULL;
	return newNode;
}

void addToVector(vector<string> &v, string toAdd){
	bool isUnique = true;

	for(vector<string>::const_iterator i = v.begin(); i!=v.end(); ++i)
		if(*i == toAdd)
			isUnique = false;

	if(isUnique)
		v.push_back(toAdd);
}

