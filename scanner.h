
#ifndef SCANNER_H
#define SCANNER_H

#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string>

using namespace std;

void continueID(string str, int i);
void continueDigit(string str, int i);
void incrementTKIndexIfDone(string str, int i);
int assignPossibleKW(string str, int i);
void interpretString(string str);
void assignDelim(char c);
string getNumberFromString(string str, int i);

const int MAX = 1000;

int tkns[MAX] = {};
int tknIndex = 0;
bool isStart = 0;
bool isNumber = 0;
bool error = 0;

#endif
