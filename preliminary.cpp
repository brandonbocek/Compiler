#include "preliminary.h"

using namespace std;

int arraySize = 0;

string removeComments(string totalStr){

	int i=0;	
	bool comment = 0;
	
	while(totalStr[i] != '\0'){
		if(totalStr[i]=='&' && !comment){
			totalStr[i] = ' ';
			comment = 1;
		}else if(totalStr[i] == '&' && comment){
			totalStr[i] = ' ';
			comment = 0;
		}else if(comment){
			totalStr[i] = ' ';
		}
		i++;
	}

	return totalStr;	
}

string* breakIntoArray(string line){
	
	string* arr = new string[MAX];
    	int i = 0;
    	stringstream ssin(line);
    	while (ssin.good() && i < MAX){
        	ssin >> arr[i];
        	++i;
		arraySize++;
    	}
	return arr;
}
