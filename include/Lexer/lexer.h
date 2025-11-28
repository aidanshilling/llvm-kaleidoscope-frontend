#include <string>

// Lexer will return tokens between 0-255 for everything
// but what is in this list.
enum Token {
	tok_eof = -1,

	// commands
	tok_def = -2,
	tok_extern = -3,

	// primary
	tok_ident = -4,
	tok_num = -5,
};

class Lexer {
	public:
		Lexer(const std::string &input);

		// returns the next token from stdin
		int getToken();

	private:
		std::string IdentifierStr;
		double NumVal;
};
