#include "membershipfunctionpiecewiselinear.h"
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

MembershipFunctionPieceWiseLinear::MembershipFunctionPieceWiseLinear(QObject* parent, QList<Value> x, QList<Value> y)
	:MembershipFunctionContinuous(parent, FunctionPieceWiseLinear)
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
double MembershipFunctionPieceWiseLinear::membership(double index) const
{
	int i, len = x.size();
	if( index <= x[0].getValue() )
	{
		return y[0].getValue();
	}
	if( index > x[len - 1].getValue() )
	{
		return y[len - 1].getValue();
	}
	for( i = 1; i < len; i++ )
	{
		if( index <= x[i].getValue() ) 
		{
			return y[i - 1].getValue() + (y[i].getValue() - y[i - 1].getValue()) * ((index - x[i - 1].getValue()) / (x[i].getValue() - x[i - 1].getValue()));
		}
	}
	
	/*if( Double.isNaN(index) ) return Double.NaN;
	throw new RuntimeException("Error calculating membership! This should never happen! (index = " + index + ")");*/

}