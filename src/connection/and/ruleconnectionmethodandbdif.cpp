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
 * \file ruleconnectionmethodandbdif.cpp
 * \class RuleConnectionMethodAndBoundedDif
 * \author Aleksey Myasnikov <AlekseyMyasnikov@yandex.ru>
 * \author pcingola@users.sourceforge.net from Java jFuzzyLogic project
 * \date 2009/04
 * \version 1.08
 * \brief FIXME
 */
#include "ruleconnectionmethodandbdif.h"
#include <QtGlobal>

jfuzzyqt::RuleConnectionMethodAndBoundedDif::RuleConnectionMethodAndBoundedDif()
    : RuleConnectionMethod("and")
{
}

jfuzzyqt::RuleConnectionMethodAndBoundedDif::~RuleConnectionMethodAndBoundedDif()
{
}
double jfuzzyqt::RuleConnectionMethodAndBoundedDif::connect(double antecedent1, double antecedent2)const
{
    return qMax(0.,antecedent1+antecedent2-1);
}
QString jfuzzyqt::RuleConnectionMethodAndBoundedDif::toString() const
{
    return "and : bdif";
}
