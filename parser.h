#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <bits/stdc++.h>
#include <string>
#include "node.h"
using namespace std;


string scanner();
Node* parser();
Node* program();
Node* block();
Node* vars();
Node* mvars();
Node* expr();
Node* M();
Node* R();
Node* stats();
Node* mStat();
Node* stat();
Node* in();
Node* out();
Node* iif();
Node* loop();
Node* assign();
Node* RO();

#endif
