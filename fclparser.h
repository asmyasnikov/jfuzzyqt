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
	QString readLine(QTextStream &in);
};

#endif // FCLPARSER_H
