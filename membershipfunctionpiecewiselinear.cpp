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
/*!
 * \brief Membership funcion definiton
 * 
 * \param index
 * Description of parameter index.
 * 
 * \returns
 * Write description of return value here.
 * 
 * \throws <exception class>
 * Description of criteria for throwing this exception.
 * 
 * Membership funcion is defined as:
 * 		membership(x) = y[0]											if x <= x[0]
 * 		membership(x) = y[n]											if x >= x[n]  (where n = x.length)
 * 		membership(x) = y[i - 1] + (y[i] - y[i - 1]) / (in - x[i])		if x[i-1] < x <= x[i]
 * 	
 * \see net.sourceforge.jFuzzyLogic.membership.MembershipFunction#membership(double)
 * 
 */
double MembershipFunctionPieceWiseLinear::membership(double index) const
{
	int i, len = x.size();
	
	if( index <= x.at(0).getValue() )
	{
		return y.at(0).getValue();
	}
	if( index > x.at(len - 1).getValue() )
	{
		return y.at(len - 1).getValue();
	}
	for( i = 1; i < len; i++ )
	{
		if( index <= x.at(i).getValue() ) 
		{
			return y.at(i - 1).getValue() + (y.at(i).getValue() - y.at(i - 1).getValue()) * ((index - x.at(i - 1).getValue()) / (x.at(i).getValue() - x.at(i - 1).getValue()));
		}
	}
	
	qCritical("[MembershipFunctionPieceWiseLinear::membership]:Error calculating membership! This should never happen!");
	return 0;
}