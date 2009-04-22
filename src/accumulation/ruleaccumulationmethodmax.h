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
 * \file ruleaccumulationmethodmax.h
 * \class FIXME
 * \author Marco Estanqueiro
 * \author Aleksey Myasnikov
 * \author pcingola@users.sourceforge.net from Java jFuzzyLogic project
 * \date 2009/04
 * \version 0.2
 * \brief FIXME
 */
#ifndef RULEACCUMULATIONMETHODMAX_H
#define RULEACCUMULATIONMETHODMAX_H

#include "ruleaccumulationmethod.h"
#include <QObject>

class RuleAccumulationMethodMax : public RuleAccumulationMethod
{
    Q_OBJECT

public:
    RuleAccumulationMethodMax(QObject *parent=NULL);
    ~RuleAccumulationMethodMax();
    double aggregate(double defuzzifierValue, double valueToAggregate) const;
    QString toQString()const;
private:

};

#endif // RULEACCUMULATIONMETHODMAX_H
