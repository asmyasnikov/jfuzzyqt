#include "membershipfunction.h"
#include "value.h"
#include <QDebug>

MembershipFunction::MembershipFunction(MembershipType type)
{
	this->type = type;
	this->universeMax = this->universeMin = NULL;
	this->parameters = NULL;
}

MembershipFunction::~MembershipFunction()
{
	/*if (this->universeMax != NULL)
	{
		delete this->universeMax;
		this->universeMax = NULL;
	}
	if (this->universeMin != NULL)
	{
		delete this->universeMin;
		this->universeMin=NULL;
	}
	if (this->parameters!=NULL)
	{
		delete [] this->parameters;
		this->parameters=NULL;
	}*/
}



double MembershipFunction::getUniverseMax()
{
	return *universeMax;
}

double MembershipFunction::getUniverseMin() 
{
	return *universeMin;
}
bool MembershipFunction::checkParamters(QString errors)
{
	return NULL;
}
void MembershipFunction::estimateUniverse(){}

double MembershipFunction::membership(double in) const
{
	return NULL;
}
const bool MembershipFunction::isDiscrete() const
{
	return this->discrete;
}
const QString MembershipFunction::getName() const
{
	/*
	public String getName() {
		String str = this.getClass().getName();
		String mfStr = "MembershipFunction";
		int ind = str.lastIndexOf('.');
		if( ind >= 0 ) {
			str = str.substring(ind + 1);
			if( str.startsWith(mfStr) ) str = str.substring(mfStr.length());
		}
		return str;
	}
	*/
	return "MembershipFunction";
}
void MembershipFunction::debug(QString tbs)const
{
	switch (this->type){
		case FunctionDiscrete:
			qDebug() << tbs <<"[MembershipFunction::debug] virtual method called (FunctionDiscrete)";
			break;
		case FunctionSingleton:
			qDebug() << tbs <<"[MembershipFunction::debug] virtual method called (FunctionSingleton)";
			break;
		case FunctionPieceWiseLinear:
			qDebug() << tbs <<"[MembershipFunction::debug] virtual method called (FunctionPieceWiseLinear)";
			break;
		default:
			qDebug() << tbs <<"[MembershipFunction::debug] virtual method called (default)";
			break;
	}
	
}