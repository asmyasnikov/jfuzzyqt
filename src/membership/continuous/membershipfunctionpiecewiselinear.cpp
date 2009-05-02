/****************************************************************
Copyright (C) 2009 Marco Estanqueiro, Aleksey Myasnikov
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
in file LICENSE along with this program.  If not, see
<http://www.gnu.org/licenses/>
****************************************************************/
/*!
 * \file membershipfunctionpiecewiselinear.cpp
 * \class MembershipFunctionPieceWiseLinear
 * \brief Class implement piece wise linear membership function.
 *        Parameters of this function will be not optimized.
 * \author Marco Estanqueiro <estanqueiro.marco@gmail.com>
 * \author Aleksey Myasnikov <AlekseyMyasnikov@yandex.ru>
 * \author pcingola@users.sourceforge.net from Java jFuzzyLogic project
 * \date 2009/04
 * \version 0.95
 */
#include "membershipfunctionpiecewiselinear.h"
#include <QDebug>
#include <math.h>

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
jfuzzyqt::MembershipFunctionPieceWiseLinear::MembershipFunctionPieceWiseLinear(QObject* parent, const QList<double>& x,const QList<double>& y)
    : MembershipFunctionContinuous(parent, FunctionPieceWiseLinear)
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
    for (int i = 0; i < x.size(); ++i)
    {
        this->x.append( new Value(this,x.at(i)) );
        this->y.append( new Value(this,y.at(i)) );
    }
}

jfuzzyqt::MembershipFunctionPieceWiseLinear::~MembershipFunctionPieceWiseLinear()
{
}
QString jfuzzyqt::MembershipFunctionPieceWiseLinear::toString()const
{
    QString toReturn;
    for (int i = 0; i < x.size(); ++i)
    {
        toReturn.append(QString("(%1, %2) ")
                        .arg(x.at(i)->getValue())
                        .arg(y.at(i)->getValue()));
    }
    return toReturn;
}
QString jfuzzyqt::MembershipFunctionPieceWiseLinear::getName() const
{
    return "PieceWiseLinear";
}

/*!
 * \brief Membership funcion definiton
 *
 * Membership funcion is defined as:
 * 		membership(x) = y[0]											if x <= x[0]
 * 		membership(x) = y[n]											if x >= x[n]  (where n = x.length)
 * 		membership(x) = y[i - 1] + (y[i] - y[i - 1]) / (in - x[i])
 *              if x[i-1] < x <= x[i]
 *
 * \see net.sourceforge.jFuzzyLogic.membership.MembershipFunction#membership(double)
 *
 */
double jfuzzyqt::MembershipFunctionPieceWiseLinear::membership(double index) const
{
    int i, len = x.size();
    double toReturn = 0;

    if( index <= x.at(0)->getValue() )
    {
        toReturn = y.at(0)->getValue();
    }else if( index > x.at(len - 1)->getValue() ){
        toReturn = y.at(len - 1)->getValue();
    }else{
        for( i = 1; i < len; i++ )
        {
            if( index <= x.at(i)->getValue() )
            {
                toReturn = y.at(i - 1)->getValue() + (y.at(i)->getValue() - y.at(i - 1)->getValue()) * ((index - x.at(i - 1)->getValue()) / (x.at(i)->getValue() - x.at(i - 1)->getValue()));
                break;
            }
        }
    }
    return toReturn;
}
bool jfuzzyqt::MembershipFunctionPieceWiseLinear::checkParamters(QString&errors)const
{
    bool toReturn = true;

    if( x.size() > 1 )
    {
        for( int i = 0; i < x.size(); i++ )
        {
            if( (i > 0) && (x.at(i-1)->getValue() > x.at(i)->getValue()) ) {
                toReturn = false;
                errors.append(QString("Array not sorted: x[%1]=%2, x[%3]=%4").arg(i-1).arg(x.at(i-1)->getValue()).arg(i).arg(x.at(i)->getValue()));
            }

            if( (y.at(i)->getValue() < 0) || (y.at(i)->getValue() > 1) ) {
                toReturn = false;
                errors.append(QString("Membership function out of range: y[%1]=%2 (should be in range [0,1])\n").arg(i).arg(y.at(i)->getValue()));
            }
        }
    }
    return toReturn;
}
void jfuzzyqt::MembershipFunctionPieceWiseLinear::estimateUniverse()
{
    if(!universeMax) universeMax = new double;
    if(!universeMin) universeMin = new double;
    *universeMax = -HUGE_VAL;
    *universeMin =  HUGE_VAL;
    for (int i = 0; i < x.size(); ++i)
    {
        *universeMax = qMax(*universeMax, x.at(i)->getValue());
        *universeMin = qMin(*universeMin, x.at(i)->getValue());
    }
}
