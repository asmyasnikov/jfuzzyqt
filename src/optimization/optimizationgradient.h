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
 * \file optimizationgradient.h
 * \class OptimizationGradient
 * \author Aleksey Myasnikov <AlekseyMyasnikov@yandex.ru>
 * \date 2009/05
 * \version 1.08
 * \brief Class OptimizationGradient implement delta jump optimization
 */
#ifndef OPTIMIZATION_GRADIENT_H
#define OPTIMIZATION_GRADIENT_H

#include <QObject>
#include "errorfunction.h"
#include "value.h"
#include "../../include/jfuzzyqt.h"

namespace jfuzzyqt{

class J_FUZZY_QT_EXPORT OptimizationGradient : public QObject
{
    Q_OBJECT

    ErrorFunction* erf;
    /** Fuzzy rule set's whose parameters we are optimizing */
    JFuzzyQt* model;
    int maxIterations;
    int maxLineSearchIterations;
    QList<Value*> parameterList;
public :
    OptimizationGradient(JFuzzyQt* model,
                          ErrorFunction* erf,
                          QList<Value*> valuesList,
                          int maxLineSearchIterations = 20,
                          int maxIterations = 20);
    void optimize(bool verbose);
private :
    double gradient(QVector<double> &gradient, double ev0);
    void copyFromParameterList(QVector<double> &parameterValues);
    void copyToParameterList(QVector<double> &parameterValues);
};

}

#endif // OPTIMIZATION_GRADIENT_H
