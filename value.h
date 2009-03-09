#ifndef VALUE_H
#define VALUE_H

#include "Variable.h"
#include <QString>

class Value
{
public:
	enum Type {
		REAL, VAR_REFERENCE, UNDEFINED
	};

	Value();
	Value(double value);
	~Value();
	void debug(QString tbs)const;
	double getValue()const;
private:
	Type type;
	double valReal;
	Variable* varRef;

};

#endif // VALUE_H
