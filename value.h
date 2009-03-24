#ifndef VALUE_H
#define VALUE_H

#include "variable.h"
#include <QObject>
#include <QString>

class Value : public QObject
{
	Q_OBJECT
public:
	enum Type {
		REAL, VAR_REFERENCE, UNDEFINED
	};

	Value(QObject* parent=NULL);
	Value(QObject* parent, const double& value);
	~Value();
	void debug(QString tbs)const;
	double getValue()const;
private:
	Type type;
	double valReal;
	Variable* varRef;

};

#endif // VALUE_H
