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
 * \file membershipfunctiongbell.h
 * \class MembershipFunctionGBell
 * \author Aleksey Myasnikov <AlekseyMyasnikov@yandex.ru>
 * \author pcingola@users.sourceforge.net from Java jFuzzyLogic project
 * \date 2009/04
 * \version 0.83
 * \brief Implementation Gaussian membership function
 */
#ifndef MEMBERSHIPFUNCTION_GBELL_H
#define MEMBERSHIPFUNCTION_GBELL_H

#include <QList>
#include "membershipfunctioncontinuous.h"
#include "../value.h"

namespace jfuzzyqt{

class MembershipFunctionGBell : public MembershipFunctionContinuous
{
    Q_OBJECT

public:
    MembershipFunctionGBell(QObject* parent, double a, double b, double mean);
    ~MembershipFunctionGBell();
    void debug(const QString& tbs)const;
    QString getName()const;
    double membership(double index) const;
    bool checkParamters(QString& errors)const;
    void estimateUniverse();

private:
};

};

#endif // MEMBERSHIPFUNCTION_GBELL_H
