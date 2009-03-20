#include "linguisticterm.h"
#include "value.h"
#include "membershipfunction.h"
#include "membershipfunctionpiecewiseLinear.h"
#include "membershipfunctionsingleton.h"
#include <QRegExp>
#include <QList>
#include <QDebug>

LinguisticTerm::LinguisticTerm(QObject* parent)
: QObject (parent)
{
	this->membershipFunction=NULL;
}

LinguisticTerm::LinguisticTerm(QObject* parent, QString& termName, MembershipFunction* membershipFunction)
: QObject (parent)
{
	this->termName = termName;
	this->membershipFunction = membershipFunction;
}

LinguisticTerm::~LinguisticTerm()
{
	/*
	if( this->membershipFunction!=NULL )
	{
		qWarning()<<"LinguisticTerm::~LinguisticTerm";
		//delete this->membershipFunction;
	}*/
}

QString LinguisticTerm::getTermName() const{
	return this->termName;
}

void LinguisticTerm::setTermName(const QString& name)
{
	this->termName = name;
}

MembershipFunction* LinguisticTerm::getMembershipFunction()
{
	return this->membershipFunction;
}
bool LinguisticTerm::loadFrom(QString qString)
{
	bool toReturn = false;
	
	QRegExp rxSingleton("(-?\\d+(.\\d+)*)");
	QRegExp rxPoint("\\s*((-?\\d+(.\\d+)*)\\s*,\\s*(-?\\d+(.\\d+)*))");
	QRegExp rxUnimplemented("(COSINE|DSIGM|GAUSS|TRIAN|GBELL|TRAPE|SIGM|FUNCTION)\\s*\\(((\\d+(.\\d+)*)\\s*,\\s*(\\d+(.\\d+)*))");

	if ( rxUnimplemented.indexIn(qString) > -1)///<Unimplemented
	{
		qCritical("[LinguisticTerm::loadFrom]: Unimplemented") ;
		
	}else if ( rxPoint.indexIn(qString) > -1)///<Point
	{
		QList<Value> x;
		QList<Value> y;
		int pos = 0;
		while ((pos = rxPoint.indexIn(qString, pos)) != -1) {
			x.append( Value(rxPoint.cap(2).toDouble()) );
			y.append( Value(rxPoint.cap(4).toDouble()) );
			pos += rxPoint.matchedLength();
		}
		if( this->membershipFunction!=NULL )
		{
			delete this->membershipFunction;
		}
		this->membershipFunction = new MembershipFunctionPieceWiseLinear(this, x, y);
		toReturn = true;

	}else if (rxSingleton.indexIn(qString) > -1) ///<Singleton
	{
		Value singleTonValueX ( rxSingleton.cap(0).toDouble() );
		if( this->membershipFunction!=NULL )
		{
			delete this->membershipFunction;
		}
		this->membershipFunction = new MembershipFunctionSingleton(this, singleTonValueX);
		toReturn = true;
	}else
	{
		qCritical("LinguisticTerm::loadFrom : unknown linguistic term");
	}
	return toReturn;
}
void LinguisticTerm::debug(QString tbs) const
{
	QString nxtTbs=tbs;
	nxtTbs.append("\t");
	qDebug() << tbs <<"TERM"<<this->termName<<"{";
	if(this->membershipFunction!=NULL)
	{
		this->membershipFunction->debug(nxtTbs);
	}
	qDebug() << tbs <<"}";
}