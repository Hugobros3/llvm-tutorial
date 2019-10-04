#include "tokens.h"

// static should be useless since we don't include this in other compilation units, right ?
static double number_value;
static std::string identifier_string;

int get_token() {
	int last_char = 'c';
	while (isspace(last_char)) {
		last_char = getchar();
	}

	std::string temp;
	if (isalpha(last_char)) {
		temp = last_char;
		while (isalnum(last_char = getchar())) {
			temp += last_char;
		}

		if (temp == "def")
			return TOKEN_DEF;
		if (temp == "extern")
			return TOKEN_EXTERN;

		identifier_string = temp;
		return TOKEN_IDENTIFIER;
	}

	if (isdigit(last_char) || last_char == '.') {
		do {
			temp += last_char;
			last_char = getchar();
		} while (isdigit(last_char) || last_char == '.');

		number_value = strtod(temp.c_str(), 0);
		return TOKEN_NUMBER;
	}

	if (last_char == '#') {
		do {
			last_char = getchar();
		} while (last_char != EOF && last_char != '\n' && last_char != '\r');

		if (last_char != EOF) {
			return get_token();
		}
	}

	if (last_char == EOF) {
		return TOKEN_EOF;
	}

	// TODO this sucks, LLVM tutorial.
	int this_char = last_char;
	last_char = getchar();
	return (Token)this_char;
}

std::string getIdentifierString() {
	return identifier_string;
}

double getNumberValue() {
	return number_value;
}