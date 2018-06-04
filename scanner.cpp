/*
 * Brandon Bocek
 * CS 4280
 * 17 March 2018
 * Project 1
 */

#include <iostream>
#include <sstream>
#include <fstream>
#include <stdio.h>
//#include <bits/stdc++.h>
#include <string>
#include <ctype.h>
#include "scanner.h"
using namespace std;

vector<string> ids;
vector<string> nums;

void interpretString(string str){
	int i = 0, amountToMove = 0;
	isStart = 1;
	while(str[i] != '\0' && !error){
		if(!isalpha(str[i]) && !isdigit(str[i])){
			assignDelim(str[i]);
		}else if(isStart){
			if(isdigit(str[i])){ //start of a number
				tkns[tknIndex] = 100;
				incrementTKIndexIfDone(str, i);
			}else if(isalpha(str[i])){
				if(!isupper(str[i])){
					amountToMove = assignPossibleKW(str, i);
					i += amountToMove;
					if(amountToMove == 0){ //start of an identifier
						tkns[tknIndex] = 200;
						incrementTKIndexIfDone(str, i);
					}
				}else{ //start of an identifier
					tkns[tknIndex] = 200;
					incrementTKIndexIfDone(str, i);
				}
			}else{ //Unknown Error
				tkns[tknIndex] = -1;
				error  = 1;
			}
		}else{ //continuing a number or identifier
			if(tkns[tknIndex] >= 200){
				continueID(str, i);
			}else if(tkns[tknIndex] >= 100){
				continueDigit(str, i);
			}else{
				tkns[tknIndex] = -1;
				error = 1;
			}
		}
		i++;
	}
}

void continueID(string str, int i){
	if(isalpha(str[i]) || isdigit(str[i])){
		tkns[tknIndex]++;
	}else{
		error = 1;
		return;
	}

	if(tkns[tknIndex] > 207){
		error = 1;
		return;
	}

	if(!isalpha(str[i+1]) && !isdigit(str[i+1])){
		//subtract 199 from tkns[tknIndex] will give length of id string
		int length = tkns[tknIndex] - 199;
		ids.push_back("ID_" + str.substr((i-length+1), length) + "_TKN");
		tkns[tknIndex] = 200;
		tknIndex++;
		isStart = 1;	
	}else{
		isStart = 0;
	}
}

void continueDigit(string str, int i){

	if(isdigit(str[i])){
		tkns[tknIndex]++;
	}else{
		error = 1;
		return;
	}

	if(tkns[tknIndex] > 107){
		error = 1;
		return;
	}

	if(!isdigit(str[i+1])){
		nums.push_back("NUM_" + str + "_ID");
		tkns[tknIndex] = 100;
		tknIndex++;
		isStart = 1;	
	}else{
		isStart = 0;
	}
}

void incrementTKIndexIfDone(string str, int i){
	
	if(!isalpha(str[i+1]) && !isdigit(str[i+1])){
		if(tkns[tknIndex] == 200){
			ids.push_back("ID_" + str.substr(i,1) + "_TKN");
		}else if(tkns[tknIndex] >= 100 && tkns[tknIndex] < 108){
			string s = "NUM_";
			s.append(str);
			s.append("_TKN");
			nums.push_back(s);
		}
		tknIndex++;
		isStart = 1;
	
	}else{
		isStart = 0;
	}
}

string getNumberFromString(string str, int i){
	int length = 1;
	while(isdigit(str[i])){
		i--;
		length++; 
	}
	int start = i+1;	
	return "NUM_" + str + "_TKN";
}

int assignPossibleKW(string str, int i){

	if(str[i] == 's'){
		if(str[i+1] == 't'){
			if(str[i+2] == 'a'){
				if(str[i+3] == 'r'){
					if(str[i+4] == 't'){
						if(!isalpha(str[i+5]) && !isdigit(str[i+5])){
							tkns[tknIndex] = 50;
							tknIndex++;
							return 4;
						}
					}
				}
			}else if(str[i+2] == 'o'){
				if(str[i+3] == 'p'){
					if(!isalpha(str[i+4]) && !isdigit(str[i+4])){
						tkns[tknIndex] = 51;
						tknIndex++;
						return 3;
					}
				}
			}
		}

	}else if(str[i] == 'i'){
		if(str[i+1] == 't'){
			if(str[i+2] == 'e'){
				if(str[i+3] == 'r'){
					if(!isalpha(str[i+4]) && !isdigit(str[i+4])){
						tkns[tknIndex] = 52;
						tknIndex++;
						return 3;
					}
				}
			}
		}else if(str[i+1] == 'f'){
			if(str[i+2] == 'f'){
				if(!isalpha(str[i+3]) && !isdigit(str[i+3])){
					tkns[tknIndex] = 53;
					tknIndex++;
					return 2;
				}
			}
		}

	}else if(str[i] == 'v'){
		if(str[i+1] == 'o'){
			if(str[i+2] == 'i'){
				if(str[i+3] == 'd'){	
					if(!isalpha(str[i+4]) && !isdigit(str[i+4])){
						tkns[tknIndex] = 54;
						tknIndex++;
						return 3;
					}
				}
			}
		}else if(str[i+1] == 'a'){
			if(str[i+2] == 'r'){
				if(!isalpha(str[i+3]) && !isdigit(str[i+3])){
					tkns[tknIndex] = 55;
					tknIndex++;
					return 2;
				}
			}
		}

	}else if(str[i] == 'r'){
		if(str[i+1] == 'e'){
			if(str[i+2] == 't'){
				if(str[i+3] == 'u'){
					if(str[i+4] == 'r'){
						if(str[i+5] == 'n'){
							if(!isalpha(str[i+6]) && !isdigit(str[i+6])){
								tkns[tknIndex] = 56;
								tknIndex++;
								return 5;
							}
						}
					}
				}
			}else if(str[i+2] == 'a'){
				if(str[i+3] == 'd'){
					if(!isalpha(str[i+4]) && !isdigit(str[i+4])){
						tkns[tknIndex] = 57;
						tknIndex++;
						return 3;
					}
				}
			}
		}
	}else if(str[i] == 'p'){
		if(str[i+1] == 'r'){
			if(str[i+2] == 'i'){
				if(str[i+3] == 'n'){
					if(str[i+4] == 't'){
						if(!isalpha(str[i+5]) && !isdigit(str[i+5])){
							tkns[tknIndex] = 58;
							tknIndex++;
							return 4;
						}
					}
				}
			}else if(str[i+2] == 'o'){
				if(str[i+3] == 'g'){
					if(str[i+4] == 'r'){
						if(str[i+5] == 'a'){
							if(str[i+6] == 'm'){
								if(!isalpha(str[i+7]) && !isdigit(str[i+7])){
									tkns[tknIndex] = 59;
									tknIndex++;
									return 6;
								}
							}
						}
					}
				}
			}
		}

	}else if(str[i] == 't'){
		if(str[i+1] == 'h'){
			if(str[i+2] == 'e'){
				if(str[i+3] == 'n'){	
					if(!isalpha(str[i+4]) && !isdigit(str[i+4])){
						tkns[tknIndex] = 60;
						tknIndex++;
						return 3;
					}
				}
			}
		}

	}else if(str[i] == 'l'){
		if(str[i+1] == 'e'){
			if(str[i+2] == 't'){
				if(!isalpha(str[i+3]) && !isdigit(str[i+3])){
					tkns[tknIndex] = 61;
					tknIndex++;
					return 2;
				}
			}
		}

	}

	return 0;
}

void assignDelim(char c){

	switch(c){
		case '=':
			tkns[tknIndex] = 1;
			tknIndex++;
			break;	
		case '<':
			tkns[tknIndex] = 2;
			tknIndex++;
			break;
		case '>':
			tkns[tknIndex] = 3;
			tknIndex++;
			break;	
		case ':':
			tkns[tknIndex] = 4;
			tknIndex++;
			break;	
		case '+':
			tkns[tknIndex] = 5;
			tknIndex++;
			break;	
		case '-':
			tkns[tknIndex] = 6;
			tknIndex++;
			break;
		case '*':
			tkns[tknIndex] = 7;
			tknIndex++;
			break;	
		case '/':
			tkns[tknIndex] = 8;
			tknIndex++;
			break;
		case '%':
			tkns[tknIndex] = 9;
			tknIndex++;
			break;	
		case '.':
			tkns[tknIndex] = 10;
			tknIndex++;
			break;
		case '(':
			tkns[tknIndex] = 11;
			tknIndex++;
			break;	
		case ')':
			tkns[tknIndex] = 12;
			tknIndex++;
			break;
		case ',':
			tkns[tknIndex] = 13;
			tknIndex++;
			break;	
		case '{':
			tkns[tknIndex] = 14;
			tknIndex++;
			break;
		case '}':
			tkns[tknIndex] = 15;
			tknIndex++;
			break;	
		case ';':
			tkns[tknIndex] = 16;
			tknIndex++;
			break;
		case '[':
			tkns[tknIndex] = 17;
			tknIndex++;
			break;	
		case ']':
			tkns[tknIndex] = 18;
			tknIndex++;
			break;
		default:
			tkns[tknIndex] = -1;
			error = 1;
			break;	
	}
}

