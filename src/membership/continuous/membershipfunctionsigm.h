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
 * \file membershipfunctionsigm.h
 * \class MembershipFunctionSigm
 * \author Aleksey Myasnikov <AlekseyMyasnikov@yandex.ru>
 * \author pcingola@users.sourceforge.net from Java jFuzzyLogic project
 * \date 2009/04
 * \version 1.08
 * \brief Implementation Sigmoidal membership function
 */
#ifndef MEMBERSHIPFUNCTION_SIGM_H
#define MEMBERSHIPFUNCTION_SIGM_H

#include <QList>
#include "membershipfunctioncontinuous.h"

namespace jfuzzyqt{

class J_FUZZY_QT_EXPORT MembershipFunctionSigm : public MembershipFunctionContinuous
{
    Q_OBJECT

public:
    MembershipFunctionSigm(QObject* parent, double mx, double dx);
    ~MembershipFunctionSigm();
    QString getName()const;
    double membership(double index) const;
    bool checkParameters(QString& errors)const;
    void estimateUniverse();
    QString toString()const;

private:
};

};

#endif // MEMBERSHIPFUNCTION_SIGM_H
