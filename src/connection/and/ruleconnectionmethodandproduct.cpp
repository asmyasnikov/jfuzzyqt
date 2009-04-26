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
 * \file ruleconnectionmethodandproduct.cpp
 * \class RuleConnectionMethodAndProduct
 * \author Aleksey Myasnikov <AlekseyMyasnikov@yandex.ru>
 * \author pcingola@users.sourceforge.net from Java jFuzzyLogic project
 * \date 2009/04
 * \version 0.82
 * \brief FIXME
 */
#include "ruleconnectionmethodandproduct.h"
#include <QtGlobal>

RuleConnectionMethodAndProduct::RuleConnectionMethodAndProduct()
    : RuleConnectionMethod("and")
{
}
RuleConnectionMethodAndProduct::~RuleConnectionMethodAndProduct()
{
}
double RuleConnectionMethodAndProduct::connect(double antecedent1, double antecedent2)const
{
    return antecedent1*antecedent2;
}
QString RuleConnectionMethodAndProduct::toQString() const
{
    return "and : prod";
}
