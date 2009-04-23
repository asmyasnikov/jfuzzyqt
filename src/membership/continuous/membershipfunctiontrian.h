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
 * \file membershipfunctiontrian.h
 * \class MembershipFunctionTrian
 * \author Aleksey Myasnikov
 * \author pcingola@users.sourceforge.net from Java jFuzzyLogic project
 * \date 2009/04
 * \version 0.2
 * \brief Implementation Triangular membership function
 */
#ifndef MEMBERSHIPFUNCTION_TRIAN_H
#define MEMBERSHIPFUNCTION_TRIAN_H

#include <QList>
#include "membershipfunctioncontinuous.h"
#include "../value.h"

namespace jfuzzyqt{

class MembershipFunctionTrian : public MembershipFunctionContinuous
{
    Q_OBJECT

public:
    MembershipFunctionTrian(QObject* parent, double left, double mid, double right);
    ~MembershipFunctionTrian();
    void debug(const QString& tbs)const;
    QString getName()const;
    double membership(double index) const;
    bool checkParamters(QString& errors)const;
    void estimateUniverse();

private:
};

}using namespace jfuzzyqt;

#endif // MEMBERSHIPFUNCTION_TRIAN_H