#ifndef FCLPARSER_H
#define FCLPARSER_H

#include "functblock.h"

class FCLParser
{
public:
	FCLParser(FunctBlock* funcBlock);
	~FCLParser();

private:
	FunctBlock* funcBlock;
};

#endif // FCLPARSER_H
