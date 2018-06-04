
#ifndef SEMANTICS_H
#define SEMANTICS_H
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <bits/stdc++.h>
#include <string>
#include "tree.h"
#include "semantics.h"

using namespace std;

void verify(string myStr);
void verifyThisIDTokenExists(string currentWord);
void semanticCheck(Node *root);
void addVarFromVarTknToVars(string name, string value);
void addVarFromColonTknToVars(string name);
void addTempVar(string name);
void addTempIdVar(string name);

#endif
