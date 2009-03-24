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
MembershipFunctionPieceWiseLinear::MembershipFunctionPieceWiseLinear(QObject* parent, const QList<double>& x,const QList<double>& y)
	:MembershipFunctionContinuous(parent, FunctionPieceWiseLinear)
{
	if ( x.count()<1 )
	{
		qCritical("QList<double> x, size is 0");
	}
	if ( y.count()<1 )
	{
		qCritical("QList<double> y, size is 0");
	}
	if ( x.count() != y.count() )
	{
		qCritical("Array size differ");
	}
	
	for (int i = 0; i < x.size(); ++i) {

		this->x.append( new Value(this,x.at(i)) );
		this->y.append( new Value(this,y.at(i)) );
	}
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
		str.append ( QString::number( x.at(i)->getValue() ) );
		str.append(" , ");
		str.append ( QString::number( y.at(i)->getValue() ) );
		str.append(")");
	}
	str.append("}");
	qDebug() << tbs << str;
}

/*!
 * \brief Membership funcion definiton
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
	double toReturn = 0;
	
	if( index <= x.at(0)->getValue() )
	{
		toReturn = y.at(0)->getValue();
	}
	else if( index > x.at(len - 1)->getValue() )
	{
		toReturn = y.at(len - 1)->getValue();
	}
	else
	{
		for( i = 1; i < len; i++ )
		{
			if( index <= x.at(i)->getValue() ) 
			{
				toReturn = y.at(i - 1)->getValue() + (y.at(i)->getValue() - y.at(i - 1)->getValue()) * ((index - x.at(i - 1)->getValue()) / (x.at(i)->getValue() - x.at(i - 1)->getValue()));
				break;
			}
		}
	}
	qDebug() << "[MembershipFunctionPieceWiseLinear::membership]:" << toReturn;
	//qCritical("[MembershipFunctionPieceWiseLinear::membership]:Error calculating membership! This should never happen!");
	return toReturn;
}