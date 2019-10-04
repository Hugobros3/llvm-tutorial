#include <string>
enum Token {
	TOKEN_EOF = -1,

	TOKEN_DEF = -2,
	TOKEN_EXTERN = -3,

	TOKEN_IDENTIFIER = -4,
	TOKEN_NUMBER = -5,
};

int get_token();
std::string getIdentifierString();
double getNumberValue();