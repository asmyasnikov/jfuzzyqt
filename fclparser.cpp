#include "fclparser.h"
#include <QRegExp>
FCLParser::FCLParser(FunctBlock* funcBlock)
{
	this->funcBlock = funcBlock;
}

FCLParser::~FCLParser()
{

}
QString FCLParser::readLine(QTextStream &in)
{
	QString str = in.readLine();
	str = str.toLower();
	str.remove(QRegExp("//.*")); ///< remove comments 
	str.replace(QRegExp("\\s*")," "); ///< convert tabs and multiple spaces to single space
	return str;
}