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
 * \file optimizationdeltajump.cpp
 * \class OptimizationDeltaJump
 * \author Aleksey Myasnikov <AlekseyMyasnikov@yandex.ru>
 * \date 2009/04
 * \version 0.95
 * \brief Class OptimizationParameters provide access to values
 */
#include "optimizationdeltajump.h"
#include <QDebug>

jfuzzyqt::OptimizationDeltaJump::OptimizationDeltaJump( JFuzzyQt* model,
                                                        ErrorFunction* erf,
                                                        QList<Value*> valuesList,
                                                        int maxLineSearchIterations,
                                                        int maxIterations)
    : QObject(model),
      model(model),
      valuesList(valuesList)
{
    this->erf = erf;
    this->maxLineSearchIterations = maxLineSearchIterations;
    this->maxIterations = maxIterations;
}
double jfuzzyqt::OptimizationDeltaJump::jump(int parameterNumber, double error0)
{
    Value* param = valuesList.at(parameterNumber);
    double epsilon = param->getEpsilon();
    double paramValue = param->getValue();
    double error1;
    if( param->setValue(paramValue+epsilon) )
    {
        error1 = erf->evaluate(*model);
        param->setValue(paramValue);
        if( error1 < error0 ) return epsilon;
    }
    if( param->setValue(paramValue-epsilon) )
    {
        error1 = erf->evaluate(*model);
        param->setValue(paramValue);
        if( error1 < error0 ) return -epsilon;
    }
    param->setValue(paramValue);
    return 0;
}
void jfuzzyqt::OptimizationDeltaJump::optimize(bool verbose)
{
    double prevError, error0;
    int countDeadEndIterations = 0;
    for( int iterNum = 0; iterNum < maxIterations; iterNum++ )
    {
        for( int paramNum = 0; paramNum < valuesList.size(); paramNum++ )
        {
            error0 = erf->evaluate(*model);
            if(!paramNum)
            {
                prevError = error0;
            }
            Value* parameter = valuesList.at(paramNum);
            double paramValue = parameter->getValue();
            double jumpVal = jump(paramNum, error0);
            if( qAbs(jumpVal) > 1.e-10 )
            {
                double alpha = 1.;
                double bestAlpha = 0.;
                double bestAlphaError = error0;
                for( int lineIterNum = 0; lineIterNum < maxLineSearchIterations; lineIterNum++ )
                {
                    if( parameter->setValue(paramValue + alpha * jumpVal) )
                    {
                        double error = erf->evaluate(*model);
                        if( error < error0 )
                        {
                            if( error < bestAlphaError )
                            {
                                bestAlphaError = error;
                                bestAlpha = alpha;
                            }
                            alpha *= 2.;
                        } else break;
                    } else break;
                }
                error0 = bestAlphaError;
                parameter->setValue(paramValue + bestAlpha * jumpVal);
            }
        }
        if(verbose)
        {
            qDebug() << " Current error is " << error0;
        }
        if(qAbs(prevError-error0) < 1.e-10)
        {
            countDeadEndIterations++;
        }else{
            countDeadEndIterations = 0;
        }
        if(countDeadEndIterations > 10)
        {
            if(verbose)
            {
                qDebug() << " Found dead-end solution";
            }
            return;
        }
    }
}
