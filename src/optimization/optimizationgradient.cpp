/****************************************************************
Copyright (C) 2009 Aleksey Myasnikov
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser GPL as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser GPL for more details.
You should have received a copy of the GNU Lesser GPL
in file LICENSE along with this program.  If not, see
<http://www.gnu.org/licenses/>
****************************************************************/
/*!
 * \file optimizationgradient.cpp
 * \class OptimizationGradient
 * \author Aleksey Myasnikov <AlekseyMyasnikov@yandex.ru>
 * \date 2009/04
 * \version 1.08
 * \brief Class OptimizationParameters provide access to values
 */
#include "optimizationgradient.h"
#include <QDebug>

jfuzzyqt::OptimizationGradient::OptimizationGradient(   JFuzzyQt* model,
                                                        ErrorFunction* erf,
                                                        QList<Value*> valuesList,
                                                        int maxLineSearchIterations,
                                                        int maxIterations)
    : QObject(model),
      model(model),
      parameterList(valuesList)
{
    this->erf = erf;
    this->maxLineSearchIterations = maxLineSearchIterations;
    this->maxIterations = maxIterations;
}
void jfuzzyqt::OptimizationGradient::optimize(bool verbose)
{
    int k, len = parameterList.size();
    QVector<double> grad(len);
    double alpha, norm = 0., error, error0;
    QVector<double> parameterValues0(len);
    for( int i = 0; i < maxIterations; i++ )
    {
        error0 = erf->evaluate(*model);
        if(verbose)
        {
            qDebug() << "\tCurrent " << i << " error is "  << error0;
        }
        copyFromParameterList(parameterValues0);
        norm = gradient(grad, error0);
        if( norm <= 1.e-10 )
        {
            copyToParameterList(parameterValues0);
            if(verbose)
            {
                qDebug() << "Exit with null norm";
            }
            return;
        }
        alpha = 1.;
        for( k = 0; k < maxLineSearchIterations; k++ )
        {
            for( int j = 0; j < len; j++ )
            {
                parameterList.at(j)->setValue(parameterValues0[j] - alpha * grad[j]);
            }
            error = erf->evaluate(*model);
            if( error < error0 )
            {
                if(verbose)
                {
                    qDebug() << "Error < error0";
                }
                break;
            }
            alpha /= 2.;
        }
        if( k >= maxLineSearchIterations )
        {
            copyToParameterList(parameterValues0);
            if(verbose)
            {
                qDebug() << "k >= maxLineSearchIterations";
            }
            return;
        }
    }
}
double jfuzzyqt::OptimizationGradient::gradient(QVector<double> &gradient, double /*ev0*/)
{
    double norm = 0.;
    double e0 = erf->evaluate(*model);
    for( int i = 0; i < parameterList.size(); i++ )
    {
        Value* param = parameterList.at(i);
        double epsilon = param->getEpsilon();
        double paramValue = param->getValue();
        if( param->setValue(paramValue + epsilon) ) ;
        else if( param->setValue(paramValue - epsilon) ) epsilon *= -1.;
        else epsilon = 0.;
        double e1;
        if( qAbs(epsilon) > 1.e-10 )
        {
            e1 = erf->evaluate(*model);
            param->setValue(paramValue);
        } else e1 = e0;
        gradient[i] = (e0 - e1) / epsilon;
        norm += gradient[i] * gradient[i];
    }
    return norm;
}
void jfuzzyqt::OptimizationGradient::copyFromParameterList(QVector<double> &parameterValues)
{
    for( int j = 0; j < parameterValues.size(); j++ )
    {
        parameterValues[j] = parameterList.at(j)->getValue();
    }
}
void jfuzzyqt::OptimizationGradient::copyToParameterList(QVector<double> &parameterValues)
{
    for( int j = 0; j < parameterValues.size(); j++ )
    {
        parameterList.at(j)->setValue(parameterValues[j]);
    }
}
