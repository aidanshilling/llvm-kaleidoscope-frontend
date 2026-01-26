#include <Lexer/lexer.h>
#include <cctype>
#include <cstdio>
#include <string>

Lexer::Lexer(const std::string &input) 
	: NumVal(0.0), IdentifierStr("") 
{};

int Lexer::getToken() {
	static int LastChar = ' ';
	while (std::isspace(LastChar)) {
		// TODO: Replace this with something that doesn't just read from stdin
		getchar();
	}

	// handle identifiers
	if (std::isalpha(LastChar)) {
		IdentifierStr += LastChar;

		// read input until whitespace or non alpha character
		while (std::isalnum(LastChar = getchar())) {
			IdentifierStr += LastChar;
		}

		// resolve token types
		if (IdentifierStr == "def") {
			return tok_def;
		}
		if (IdentifierStr == "extern") {
			return tok_extern;
		}
		return tok_ident;
	}

	// handle numbers
	// all numbers are floats so read in digits and '.'
	// TODO: Error handling: Extend this so 123.45.6 is marked as invalid input
	if (std::isdigit(LastChar) || LastChar == '.') {
		std::string NumStr;
		do {
			NumStr += LastChar;
			LastChar = getchar();
		} while (isdigit(LastChar) || LastChar == '.');

		// set class global number value
		NumVal = strtod(NumStr.c_str(), 0);
		return tok_num;
	}

	// handle comments
	if (LastChar == '#') {
		// ignore until eol
		do {
			LastChar = getchar();
		} while(LastChar != EOF && LastChar != '\n' && LastChar != '\r');
	}

	if (LastChar == EOF) {
		return tok_eof;
	}

	// if token is anything else, assume its an operator of some kind
	// and return raw ascii value
	// TODO: Extend this with more token types for operators
	int ThisChar = LastChar;
	LastChar = getchar();
	return ThisChar;
}

int Lexer::getNumVal() {
	return NumVal;
}

std::string Lexer::getIdentifierStr() {
	return IdentifierStr;
}
