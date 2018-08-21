#ifndef Token_H
#define Token_H

#include <string>
#include <iostream>
using namespace std;

/** Encapsulates a string "token", with corresponding line and column numbers, thus
enhancing error reporting capability.
*/
struct Token
{
	Token(const std::string& nameArg, int lineArg, int columnArg) : name( nameArg ), line( lineArg ),
		column( columnArg ), firstInLine( false ), lastInLine( false ), endOfFile( false )
	{}
	Token() : firstInLine( false ), lastInLine( false ), endOfFile( false ) {}
	~Token() {}
	bool operator==(const Token& rhs) {return name == rhs.name;}
	bool operator!=(const Token& rhs) {return !operator==(rhs);}
	std::string name;
	int line;
	int column;
	bool firstInLine;
	bool lastInLine;
	bool endOfFile;
};
#endif

