#include "MembershipFunctionPieceWiseLinear.h"
#include <QDebug>

/*! \brief Default constructor 
*         Brief description continued.
*
* @param x [] : x points array
* @param y [] : y points array
* A piecewise linear function is defined by 'n' points:
* 		(x_1,y_1) , (x_2,y2) , ... (x_n,y_n)
* ordered by x[] (increasing)
* See also 'membership()' for a precise definition.
*/

MembershipFunctionPieceWiseLinear::MembershipFunctionPieceWiseLinear(QList<Value> x, QList<Value> y)
	:MembershipFunctionContinuous(FunctionPieceWiseLinear)
{
	if ( x.count()<1 )
	{
		qCritical("QList<Value> x, size is 0");
	}
	if ( y.count()<1 )
	{
		qCritical("QList<Value> y, size is 0");
	}
	if ( x.count() != y.count() )
	{
		qCritical("Array size differ");
	}
	this->x=x;
	this->y=y;
}

MembershipFunctionPieceWiseLinear::~MembershipFunctionPieceWiseLinear()
{

}
void MembershipFunctionPieceWiseLinear::debug(QString tbs)const
{
	QString str = "{";
	for (int i = 0; i < x.size(); ++i)
	{
		str.append("(");
		str.append ( QString::number( x.at(i).getValue() ) );
		str.append(" , ");
		str.append ( QString::number( y.at(i).getValue() ) );
		str.append(")");
	}
	str.append("}");
	qDebug() << tbs << str;
}