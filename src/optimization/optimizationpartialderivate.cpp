/****************************************************************
Copyright (C) 2009 Aleksey Myasnikov
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
 * \file optimizationpartialderivate.cpp
 * \class OptimizationPartialDerivate
 * \author Aleksey Myasnikov <AlekseyMyasnikov@yandex.ru>
 * \date 2009/04
 * \version 0.95
 * \brief Class OptimizationParameters provide access to values
 */
#include "OptimizationPartialDerivate.h"
#include <QDebug>

jfuzzyqt::OptimizationPartialDerivate::OptimizationPartialDerivate( JFuzzyQt* model,
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
void jfuzzyqt::OptimizationPartialDerivate::optimize(bool verbose)
{
    int len = parameterList.size();
    double alpha, error, error0;
    for( int iterNum = 0; iterNum < maxIterations; iterNum++ )
    {
        for( int paramNum = 0; paramNum < len; paramNum++ )
        {
            error0 = erf->evaluate(*model);
            if( verbose )
            {
                qDebug() << "Iteration: " << iterNum << "\tParameter: " << paramNum << "\tError: " << error0;
            }
            double paramValue = parameterList.at(paramNum)->getValue();
            double derivateValue = derivate(paramNum, error0, verbose);
            if( qAbs(derivateValue) < 1.e-10 )
            {
                if( verbose )
                {
                    qDebug() << "Derivate's abs too small (derivate: " << derivateValue << " < " << parameterList.at(paramNum)->getEpsilon() << ")";
                }
            } else {
                alpha = 1.;
                for( int lineIterNum = 0; lineIterNum < maxLineSearchIterations; lineIterNum++ )
                {
                    parameterList.at(paramNum)->setValue(paramValue - alpha * derivateValue);
                    error = erf->evaluate(*model);
                    if( verbose )
                    {
                        qDebug() << "\tLine iteration: " << lineIterNum << "\talpha: " << alpha << "\tDelta_Error: " << (error - error0);
                    }
                    if( error < error0 )
                    {
                        break;
                    }
                    alpha /= 2;
                }
            }
        }
    }
}
double jfuzzyqt::OptimizationPartialDerivate::derivate(int parameterNumber, double error0, bool verbose)
{
    Value* param = parameterList.at(parameterNumber);
    double epsilon = param->getEpsilon();
    double paramValue = param->getValue();
    if( param->setValue(paramValue + epsilon) ) ;
    else if( param->setValue(paramValue - epsilon) ) epsilon *= -1;
    else epsilon = 0.;
    double error1;
    if( qAbs(epsilon) > 1.e-10 ) {
        error1 = erf->evaluate(*model);
        param->setValue(paramValue);
    } else error1 = error0;
    double derivateValue = (error0 - error1) / epsilon;
    if( error1 < error0 )
    {
        if(verbose)
        {
            qDebug() << "CAN DESCENT!!!   error1: " << error1 << "\terror0: " << error0;
        }
    }
    if( verbose )
    {
        qDebug() << "Parameter:" << param->getVarName() << "\tDerivate: " << derivateValue << "\tepsilon: " << epsilon;
    }
    return derivateValue;
}
