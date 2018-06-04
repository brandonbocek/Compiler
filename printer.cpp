#include "printer.h"
using namespace std;

string printToken(int num){
	switch(num){
		case 1:
			return "EQUAL_TKN";
		case 2:
			return "LESS_THAN_TKN";
		case 3:
			return "GREATER_THAN_TKN";
		case 4:
			return "COLON_TKN";
		case 5:
			return "ADD_TKN";
		case 6:
			return "MINUS_TKN";
		case 7:
			return "STAR_TKN";
		case 8:
			return "SLASH_TKN";
		case 9:
			return "MODULUS_TKN";
		case 10:
			return "PERIOD_TKN";
		case 11:
			return "LEFT_PAREN_TKN";
		case 12:
			return "RIGHT_PAREN_TKN";
		case 13:
			return "COMMA_TKN";
		case 14:
			return "LEFT_CURL_TKN";
		case 15:
			return "RIGHT_CURL_TKN";
		case 16:
			return "SEMI_COL_TKN";
		case 17:
			return "LEFT_SQUARE_TKN";
		case 18:
			return "RIGHT_SQUARE_TKN";
		case 50:
			return "START_TKN";
		case 51:
			return "STOP_TKN";
		case 52:
			return "ITER_TKN";
		case 53:
			return "IFF_TKN";
		case 54:
			return "VOID_TKN";
		case 55:
			return "VAR_TKN";
		case 56:
			return "RETURN_TKN";
		case 57:
			return "READ_TKN";
		case 58:
			return "PRINT_TKN";
		case 59:
			return "PROGRAM_TKN";
		case 60:
			return "THEN_TKN";
		case 61:
			return "LET_TKN";
		case 100:
			return "NUM_TKN";
		case 200:
			return "ID_TKN";
		case 300:
			return "EOF_TKN";
		default:
			return "ERROR FINDING TKN";
	}
}
