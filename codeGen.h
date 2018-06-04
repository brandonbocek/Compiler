
#ifndef CODEGEN_H
#define CODEGEN_H
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <bits/stdc++.h>
#include <string>
#include "tree.h"

using namespace std;

void gen(Node *root);
string getVarNameFromIDTkn(string name);
string addPortToStack(int dep, bool addToStack);
string addIterToStack(int dep, bool addToStack);
string getCorrectOut();

#endif
