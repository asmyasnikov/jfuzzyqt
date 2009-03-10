#include "value.h"
#include <QDebug>

Value::Value()
{
	this->type = UNDEFINED;
	this->valReal = 0;
	
}

Value::Value(double value)
{
	this->type = REAL;
	this->valReal = value;
	this->varRef=NULL;
}

Value::~Value()
{

}
double Value::getValue()const
{
	if( type == UNDEFINED )
	{
		qWarning() << "[Value::getValue]: Value type not defined!";
		return 0;
	}

	switch(type)
	{
		case REAL:
			return this->valReal;
		case VAR_REFERENCE:
			if( varRef == NULL ) {
				qWarning() << "[Value::getValue]: Undefined variable reference!";
				return 0;
			}
			return varRef->getValue();
		default:
			qWarning() << "[Value::getValue]: type '" << type << "' not implemented!";
	}
	qWarning() << "[Value::getValue]: shouldnt not happen";
	return 0;
}

void Value::debug(QString tbs)const
{
	switch (this->type)
	{
	case REAL:
		qDebug() << tbs << "valReal:" << QString::number(this->valReal);
		break;
	case VAR_REFERENCE:
			qDebug() << tbs << "reference:";
			break;
	default:
		qDebug() << tbs << "[Value::debug]:UNDEFINED";
		break;
	}
}
