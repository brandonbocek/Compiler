
#include "codeGen.h"
using namespace std;

//currentWord = "";
int cgi = 0;
bool printMode = false;
bool assignMode = false;
bool ifMode = false;
bool exprMode = false;
bool modulusMode = false;
string stringToWrite = "";
vector<string> code;
int cei = 0;
int portNum = 0;
vector<string> ports;
vector<int> conditionalDepths;
void gen(Node *root){
	int i;
	
	if(root == NULL) 
		return;
	string name = root->name.c_str();

	//cout << "CodeGen " << name << endl;

	//print out the ports for conditionals if the level is <= the depth where the conditional began	
	if(conditionalDepths.size() > 0){
		while(root->depth <= conditionalDepths[conditionalDepths.size()-1]){
			code.push_back(ports[ports.size()-1]);
			ports.erase(ports.begin()+ports.size()-1);
			conditionalDepths.erase(conditionalDepths.begin()+conditionalDepths.size()-1);		
		}
	}

	if(name == "Out"){
		printMode = true;
		//cout << "WRITE " << varName[cgi++] << endl;
		
		for(i = 0; i<root->words.size() ; i++){
			currentWord = root->words[i].c_str();
			if(currentWord == "PRINT_TKN"){
				//if there an expression and/or modulus for this print, stay on this index for the next step
				if((root->first_Node->words.size() > 0) || (root->first_Node->first_Node->words.size() > 0)){
					stringToWrite =  "WRITE " + varName[cgi--];
				//there is only 1 thing to print either variable or number so print the temp var and move on
				}else{
					if((ports.size() > 0) || (root->first_Node->first_Node->first_Node->words[0].substr(0,3) == "ID_"))
						code.push_back("WRITE " + getVarNameFromIDTkn(root->first_Node->first_Node->first_Node->words[0]));
					else
						code.push_back("WRITE " + varName[cgi++]);
				}
			}
		}	
	}else if(name == "In"){
		for(i = 0; i<root->words.size() ; i++){
			currentWord = root->words[i].c_str();
			if(currentWord == "READ_TKN"){				
				code.push_back("READ " + getVarNameFromIDTkn(root->words[i+1].c_str()));
			}
		}
	}else if(name == "Assign"){
		assignMode = true;
		for(i = 0; i<root->words.size() ; i++){
			currentWord = root->words[i].c_str();
			if(currentWord == "LET_TKN"){	
				if((root->first_Node->words.size() > 0) || (root->first_Node->first_Node->words.size() > 0)){
					//stringToWrite =  "WRITE " + varName[cgi--];
				}else{
					code.push_back("COPY " + getVarNameFromIDTkn(root->words[i+1].c_str()) + " " + varName[++cgi]);
					cgi--;
				}
			}
		}	
	}else if(name == "Iif"){
		ifMode = true;
		//there is either an actual var (D#) or number (T#) on the left side of the if statement
		if((root->first_Node->words.size() == 0) && (root->first_Node->first_Node->words.size() == 0)){
			code.push_back("COPY " + varName[++cgi] + " " + getVarNameFromIDTkn(root->first_Node->first_Node->first_Node->words[0]));
			//the right side of the if statement is also a single variable or number
			if((root->third_Node->words.size() == 0) && (root->third_Node->first_Node->words.size() == 0)){
				if(root->second_Node->words.size() == 1){
					if(root->second_Node->words[0] == "GREATER_THAN_TKN"){
						code.push_back("LOAD " + varName[cgi]);
						code.push_back("SUB " + varName[++cgi]);
						code.push_back("BRZNEG " + addPortToStack(root->depth, true));
					}else if(root->second_Node->words[0] == "LESS_THAN_TKN"){
						code.push_back("LOAD " + varName[++cgi]);
						code.push_back("SUB " + varName[--cgi]);
						code.push_back("BRZNEG " + addPortToStack(root->depth, true));
					}else if(root->second_Node->words[0] == "EQUAL_TKN"){
						code.push_back("LOAD " + varName[cgi]);
						code.push_back("SUB " + varName[++cgi]);
						code.push_back("BRZERO " + addPortToStack(root->depth, true));
					}
				}else if(root->second_Node->words.size() == 2){
					if(root->second_Node->words[0] == "GREATER_THAN_TKN"){
						code.push_back("LOAD " + varName[cgi]);
						code.push_back("SUB " + varName[++cgi]);
						code.push_back("BRNEG " + addPortToStack(root->depth, true));
					}else if(root->second_Node->words[0] == "LESS_THAN_TKN"){
						code.push_back("LOAD " + varName[++cgi]);
						code.push_back("SUB " + varName[--cgi]);
						code.push_back("BRNEG " + addPortToStack(root->depth, true));	
					}else if(root->second_Node->words[0] == "EQUAL_TKN"){
						code.push_back("LOAD " + varName[cgi]);
						code.push_back("SUB " + varName[++cgi]);
						code.push_back("BRPOS " + addPortToStack(root->depth, true));
						code.push_back("BRNEG " + addPortToStack(root->depth, false));
					}
				}
			}
		}else{
			stringToWrite =  "COPY " + getVarNameFromIDTkn(root->words[i+1].c_str()) + " " + varName[++cgi];
			cgi--;
		}
	
	}else if(name == "Loop"){
		if((root->first_Node->words.size() == 0) && (root->first_Node->first_Node->words.size() == 0)){
			code.push_back("COPY " + varName[++cgi] + " " + getVarNameFromIDTkn(root->first_Node->first_Node->first_Node->words[0]));
			//the right side of the iter statement is also a single variable or number
			if((root->third_Node->words.size() == 0) && (root->third_Node->first_Node->words.size() == 0)){
				if(root->second_Node->words.size() == 1){
					if(root->second_Node->words[0] == "GREATER_THAN_TKN"){
						code.push_back(addIterToStack(root->depth, true));
						code.push_back("LOAD " + varName[cgi]);
						code.push_back("SUB " + varName[++cgi]);
						code.push_back("BRZNEG " + getCorrectOut());
					}else if(root->second_Node->words[0] == "LESS_THAN_TKN"){	
						code.push_back(addIterToStack(root->depth, true));
						code.push_back("LOAD " + varName[++cgi]);
						code.push_back("SUB " + varName[--cgi]);
						code.push_back("BRZNEG " + getCorrectOut());
					}else if(root->second_Node->words[0] == "EQUAL_TKN"){	
						code.push_back(addIterToStack(root->depth, true));
						code.push_back("LOAD " + varName[cgi]);
						code.push_back("SUB " + varName[++cgi]);
						code.push_back("BRZERO " + getCorrectOut());
					}
				}else if(root->second_Node->words.size() == 2){
					if(root->second_Node->words[0] == "GREATER_THAN_TKN"){
						code.push_back(addIterToStack(root->depth, true));
						code.push_back("LOAD " + varName[cgi]);
						code.push_back("SUB " + varName[++cgi]);
						code.push_back("BRNEG " + getCorrectOut());
					
					}else if(root->second_Node->words[0] == "LESS_THAN_TKN"){
						code.push_back(addIterToStack(root->depth, true));
						code.push_back("LOAD " + varName[++cgi]);
						code.push_back("SUB " + varName[--cgi]);
						code.push_back("BRNEG " + getCorrectOut());	
					
					}else if(root->second_Node->words[0] == "EQUAL_TKN"){
						code.push_back(addIterToStack(root->depth, true));
						code.push_back("LOAD " + varName[cgi]);
						code.push_back("SUB " + varName[++cgi]);
						string myOut = getCorrectOut();
						code.push_back("BRPOS " + myOut);
						code.push_back("BRNEG " + myOut);	
					}
				}
			}
		}else{
			stringToWrite =  "COPY " + getVarNameFromIDTkn(root->words[i+1].c_str()) + " " + varName[++cgi];
			cgi--;
		}
	
	}else if(name == "R"){	
		for(i = 0; i<root->words.size() ; i++){
			currentWord = root->words[i].c_str();
			if(printMode && currentWord.substr(0,3) == "ID_"){
		//		cout << "cgi:" << cgi << endl;
		//		stringToWrite =  "WRITE " + varName[cgi];cout<< 1 << endl;
		//		string orig = getVarNameFromIDTkn(currentWord);cout << 2 << endl;
		//		code.push_back("COPY "+ varName[cgi]+ " "+orig); cout << 3 << endl;
		//		code.push_back("LOAD " + varName[cgi]);
		//		code.push_back("WRITE " + varName[cgi++]);
				//printMode = false;
				//assignMode = false;
			}else if(printMode && currentWord.substr(0,4) == "NUM_"){
				//stringToWrite =  "WRITE " + varName[cgi--];
				//cout << "IN R block" << endl;
				//cei--;
				//cout << "WRITE " << varName[cgi++] << endl;
				//printMode = false;
				//assignMode = false;
			}
		}
		printMode = false;
		//assignMode = false;
	}else if(name == "Expr"){
	//	cout << "In expr node and size of word vector is " << root->words.size() << endl;
		if((root->words.size() > 0) || (root->first_Node->words.size() > 0)){
			exprMode = true;
	//		cout << "Expr mode is on" << endl;
		}
		if(exprMode && (root->words.size() == 0) && (root->first_Node->words.size() == 0)){
	//		cout << "Using Expr mode" << endl;
			if(stringToWrite == "")
				stringToWrite =  "WRITE " + varName[cgi];
			code.push_back(stringToWrite);
			stringToWrite = "";
			exprMode = false;
		}else if(assignMode){	
			//code.push_back(stringToWrite);
			//stringToWrite = "";
		}

		for(i = 0; i<root->words.size() ; i++){
			currentWord = root->words[0].c_str();
			if(currentWord.substr(0,6) == "MINUS_"){
				cgi++;
				code.insert(code.begin() + cei++, "LOAD " + varName[cgi++]);
				code.insert(code.begin() + cei++, "SUB " + varName[cgi]);
				code.insert(code.begin() + cei++, "STORE " + varName[--cgi]);
				cei = cei - 3;
			}else if(currentWord.substr(0,5) == "STAR_"){
				cgi++;
				code.insert(code.begin() + cei++, "LOAD " + varName[cgi++]);
				code.insert(code.begin() + cei++, "MULT " + varName[cgi]);
				code.insert(code.begin() + cei++, "STORE " + varName[--cgi]);
				cei = cei - 3;
			}else if(currentWord.substr(0,6) == "SLASH_"){
				cgi++;
				code.insert(code.begin() + cei++, "LOAD " + varName[cgi++]);
				code.insert(code.begin() + cei++, "DIV " + varName[cgi]);
				code.insert(code.begin() + cei++, "STORE " + varName[--cgi]);
				cei = cei - 3;
			}	
		}	
	}else if(name == "M"){
		if(root->words.size() > 0){
			modulusMode = true;
		}
		for(i = 0; i<root->words.size() ; i++){
			currentWord = root->words[0].c_str();
			if(currentWord.substr(0,8) == "MODULUS_"){
				cgi++;
				code.insert(code.begin() + cei++, "LOAD " + varName[cgi++]);
				code.insert(code.begin() + cei++, "MULT " + varName[cgi]);
				code.insert(code.begin() + cei++, "STORE " + varName[--cgi]);
				cei = cei - 3;
			}
		}
		if(modulusMode && printMode && root->first_Node->name == "R"){
			code.push_back(stringToWrite);
			modulusMode = false;
		}
	}
	gen(root->first_Node);
	gen(root->second_Node);
	gen(root->third_Node);
	gen(root->fourth_Node);
}


string getVarNameFromIDTkn(string name){
	int i = 3, lengthName = 0, lengthValue = 0;

	if(name.substr(0,4) == "NUM_"){
		i = 4;
	}

	while(name[i] != '_'){
		lengthName++;
		i++;
	}
	//cout << name.substr(3,lengthName) << endl;
	
	if(name.substr(0,4) == "NUM_")
		return name.substr(4, lengthName);
	else
		return name.substr(3, lengthName);

}

string addPortToStack(int dep, bool addToStack){

	conditionalDepths.push_back(dep);
	portNum++;
	stringstream ss;
	ss << portNum;
	string s = ss.str();
	if(addToStack)
		ports.push_back("OUT" + s + ":");
	return "OUT" + s;
}

string addIterToStack(int dep, bool addToStack){

	conditionalDepths.push_back(dep);
	conditionalDepths.push_back(dep);
	portNum++;
	stringstream ss;
	ss << portNum;
	string s = ss.str();
	if(addToStack){
		ports.push_back("OUT" + s + ":");
		ports.push_back("BR BEGIN" + s);
	}
	portNum--;
	return "BEGIN" + s + ":";
}

string getCorrectOut(){

	portNum++;
	stringstream ss;
	ss << portNum;
	string s = ss.str();
	return "OUT" + s;
}

/*
string getNumFromIDTkn(string name){
	int i = 3, lengthName = 0, lengthValue = 0;
	while(name[i] != '_'){
		lengthName++;
		i++;
	}
	//cout << name.substr(3,lengthName) << endl;
	
	return name.substr(3, lengthName);

}
*/
