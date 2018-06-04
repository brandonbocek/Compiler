#include <iostream>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <bits/stdc++.h>
#include <string>
#include "tree.h"
using namespace std;

FILE * pFile;

void printLineToFile(Node* root){
	int i;

	for(i=0; i<root->depth; i++)
		fprintf(pFile, "  ");

	fprintf(pFile, "%d %s - ", root->depth, root->name.c_str());
	
	for(i = 0; i<root->words.size() ; i++){
		fprintf(pFile, "%s ", root->words[i].c_str());
	}
	if(root->first_Node != NULL)
		fprintf(pFile, "- %s ", root->first_Node->name.c_str());
	
	if(root->second_Node != NULL)
		fprintf(pFile, "%s ", root->second_Node->name.c_str());
	
	if(root->third_Node != NULL)
		fprintf(pFile, "%s ", root->third_Node->name.c_str());
	
	if(root->fourth_Node != NULL)
		fprintf(pFile, "%s ", root->fourth_Node->name.c_str());
	
	fprintf(pFile, "\n");

}

void traversePreorder(Node *root){
	int i;

	if(root == NULL) 
		return;

	printLineToFile(root);
	traversePreorder(root->first_Node);
	traversePreorder(root->second_Node);
	traversePreorder(root->third_Node);
	traversePreorder(root->fourth_Node);
}

//string previousWord = "", currentWord = "";
//vector<string> myIdTokens;
//int amtToLookBack;
//int sizeOfAmt = 0;
//bool semanticError = 0;
/*
void verify(string myStr){

	semanticError = 0;
	int j = 0;	
	for(int i=myIdTokens.size()-1; j < amtToLookBack; i--){
		j++;
//		cout << "Checking " << myStr << " against " << myIdTokens[i] << endl;
		if(myIdTokens[i] == myStr){
			semanticError = 1;
			cout << "Found a semantic error" << endl;
		}
	}

}

void verifyThisIDTokenExists(string currentWord){

	semanticError = 1;

	for(int i = 0; i < myIdTokens.size(); i++){
		if(myIdTokens[i] == currentWord){
			semanticError = 0;
			break;
		}
	}

	if(semanticError){
		cout << "Found an unidentified variable" << endl;
	}
}

void semanticCheck(Node *root){
	int i;

	if(root == NULL) 
		return;
	string name = root->name.c_str();
	if(name == "Program"){
		amtToLookBack = 0;
	}else if(name == "Vars"){
		for(i = 0; i<root->words.size() ; i++){
			currentWord = root->words[i].c_str();
			if(currentWord == "VAR_TKN"){
				//cout << "Var tkn id'ed " << (myIdTokens.size()-1) << " >= " << amtToLookBack << endl;
				verify(root->words[i+1].c_str());
				amtToLookBack++;
				myIdTokens.push_back(root->words[i+1].c_str());
			}
		}
	}else if(name == "mVars"){
		for(i = 0; i<root->words.size() ; i++){
			currentWord = root->words[i].c_str();
			if(currentWord == "COLON_TKN"){
				//cout << "Colon tkn id'ed " << (myIdTokens.size()-1) << " >= " << amtToLookBack << endl;
				verify(root->words[i+1].c_str());
				amtToLookBack++;
				myIdTokens.push_back(root->words[i+1].c_str());
			}
		}	
	}else if(name == "Block"){
		amtToLookBack = 0;
	}else if(name == "mStats"){
		amtToLookBack = 0;
	}

	for(i = 0; i<root->words.size() ; i++){
		previousWord = currentWord;
		currentWord = root->words[i].c_str();
		if((currentWord.substr(0,3) == "ID_") && (previousWord != "VAR_TKN") && (previousWord != "COLON_TKN")){
			verifyThisIDTokenExists(currentWord);	
		}
	}
	
	semanticCheck(root->first_Node);
	semanticCheck(root->second_Node);
	semanticCheck(root->third_Node);
	semanticCheck(root->fourth_Node);
}
*/
