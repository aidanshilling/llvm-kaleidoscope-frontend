#include <Parser/parser.h>
#include <memory>

/// LogError* - These are little helper functions for error handling.
/// TODO : Make this not return nullptr and handle errors better
std::unique_ptr<ExprAST> LogError(const char *Str) {
	fprintf(stderr, "Error: %s\n", Str);
	return nullptr;
}
std::unique_ptr<PrototypeAST> LogErrorP(const char *Str) {
	LogError(Str);
	return nullptr;
}

Parser::Parser(Lexer &l) : curTok(0), lexer(l) {
	// Install standard binary operators.
	// 1 is lowest precedence.
	BinopPrecedence['<'] = 10;
	BinopPrecedence['+'] = 20;
	BinopPrecedence['-'] = 20;
	BinopPrecedence['*'] = 40; // highest.
};

/// primary
///   ::= identifierexpr
///   ::= numberexpr
///   ::= parenexpr
std::unique_ptr<ExprAST> Parser::ParsePrimary() {
	switch (getCurTok()) {
	default:
		return LogError("unknown token when expecting an expression");
	case Token::tok_ident:
		return ParseIdentifierExpr();
	case Token::tok_num:
		return ParseNumberExpr();
	case '(':
		return ParseParenExpr();
	}
}

int Parser::getCurTok() { return curTok; }

int Parser::getNextTok() { return lexer.getToken(); }

/// numberexpr ::= number
std::unique_ptr<ExprAST> Parser::ParseNumberExpr() {
	auto Result = std::make_unique<NumberExprAST>(lexer.getNumVal());
	getNextTok(); // consume the number
	return std::move(Result);
}

/// parenexpr ::= '(' expression ')'
std::unique_ptr<ExprAST> Parser::ParseParenExpr() {
	getNextTok(); // eat (.
	auto V = ParseExpression();
	if (!V)
		return nullptr;

	if (getCurTok() != ')')
		return LogError("expected ')'");
	getNextTok(); // eat ).
	return V;
}

/// identifierexpr
///   ::= identifier
///   ::= identifier '(' expression* ')'
std::unique_ptr<ExprAST> Parser::ParseIdentifierExpr() {
	std::string IdName = lexer.getIdentifierStr();

	getNextTok(); // eat identifier.

	if (getCurTok() != '(') // Simple variable ref.
		return std::make_unique<VariableExprAST>(IdName);

	// Call.
	getNextTok(); // eat (
	std::vector<std::unique_ptr<ExprAST>> Args;
	if (getCurTok() != ')') {
		while (true) {
			if (auto Arg = ParseExpression())
				Args.push_back(std::move(Arg));
			else
				return nullptr;

			if (getCurTok() == ')')
				break;

			if (getCurTok() != ',')
				return LogError("Expected ')' or ',' in argument list");
			getNextTok();
		}
	}

	// Eat the ')'.
	getNextTok();

	return std::make_unique<CallExprAST>(IdName, std::move(Args));
}

int Parser::GetTokPrecedence() {
	if (!isascii(getCurTok()))
		return -1;

	// Make sure it's a declared binop.
	int TokPrec = BinopPrecedence[getCurTok()];
	if (TokPrec <= 0)
		return -1;
	return TokPrec;
}

std::unique_ptr<ExprAST> Parser::ParseExpression() {
	auto LHS = ParsePrimary();
	if (!LHS)
		return nullptr;

	// TODO: Implement
	return ParseBinOpRHS(0, std::move(LHS));
}
