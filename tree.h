#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <bits/stdc++.h>
#include <string>
#include "node.h"
using namespace std;

static FILE * pFile;

void traversePreorder(Node *root);
void printLineToFile(Node *root);

#endif
