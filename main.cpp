/*
 * Brandon Bocek
 * CS 4280
 * 7 May 2018
 * Project 4
 */

#include <iostream>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <bits/stdc++.h>
#include <string>
#include <ctype.h>
#include "node.cpp" 
#include "tree.cpp"
#include "scanner.cpp"
#include "preliminary.cpp"
#include "printer.cpp"
#include "parser.cpp"
#include "semantics.cpp"
#include "codeGen.cpp"

using namespace std;


int main(int argc, char *argv[]){
	
	ofstream fileAsm("out.asm");
	string myVar;
	string totalStr;
	ifstream testFile;
	stringstream buffer;
	arraySize = 0;
	preFileName = "out.preorder";	
	string asmFileName = "out.asm";
	
	//text is given from the command line
	//or a file with "<"
	if (argc <= 1){
		do{	
			getline(cin, myVar);	
			if(myVar != ""){
				totalStr = totalStr + " " + myVar;
			}
		}while(myVar != "");

	//user gave a file name
	} else if(argc == 2) {

		string fileName(argv[1]);
		asmFileName = fileName + ".asm";
		fileName = fileName + ".sp18";
		preFileName = fileName + ".preorder";
		testFile.open(fileName.c_str());
		buffer << testFile.rdbuf();
		testFile.close();
		totalStr = buffer.str();
	}else {
		cout << "Too many arguments. I can't understand them all." << endl;
		cout << "If you want to type the words, execute ./P1 without arguments" << endl;
	}
	
	// removing comments and separating words
	// into array based on white spaces
	totalStr = removeComments(totalStr);
    	string *arr = breakIntoArray(totalStr);
	
	int i=0, j=0;

	// scanning the string into tokens
	while(arr[i] != "" && !error){
		interpretString(arr[i]);
		i++;
	}	
	
	// Adding EOF token
	tkns[tknIndex] = 300;

	// Filling true token array
	for(i=0; i < MAX; i++){
		if(tkns[i] == 0)
			break;
		trueTkns[i] = printToken(tkns[i]);	
		//cout << trueTkns[i] << endl;
	}
	
	//getting the tree from the parser	
	Node *root = parser();

	if(!errorFound){	
		//writing preorder to the file
		pFile = fopen(preFileName.c_str(), "w");
		traversePreorder(root);
		fclose(pFile);
		cout << "OK, preorder file is called \"" << preFileName << "\"" << endl;
		semanticCheck(root);
		if(!semanticError){	
			cout << "No semantic errors found" << endl;
			gen(root);
			
			ofstream fileAsm(asmFileName.c_str());
			cout << "asm file is called \"" << asmFileName << "\"" << endl;
			for(int i = 0; i < code.size(); i++) {
				fileAsm << code[i] << endl;
			}
			fileAsm << "STOP" << endl;
			for (int i = 0; i < codeVars.size(); i++) {
            			fileAsm << codeVars[i] << endl;
        		}
			fileAsm.close();	
		}
	}
	/*
	for(int i = 0; i < code.size(); i++) {
		cout << code[i] << endl;
	}
	for (int i = 0; i < codeVars.size(); i++) {
            cout << codeVars[i] << endl;
        }
	*/	
	return 0;
}

