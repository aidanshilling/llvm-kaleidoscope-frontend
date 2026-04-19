#include <iostream>
#include <Lexer/lexer.h>

static const char* tokName(int tok) {
	switch (tok) {
		case tok_eof:    return "eof";
		case tok_def:    return "def";
		case tok_extern: return "extern";
		case tok_ident:  return "ident";
		case tok_num:    return "num";
		default:         return "op/char";
	}
}

int main() {
	Lexer lexer{""};  // input string unused for now

	while (true) {
		int tok = lexer.getToken();
		std::cout << "token: " << tokName(tok) << " (" << tok << ")\n";
		if (tok == tok_eof) break;
	}
	return 0;
}
