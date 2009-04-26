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
 * \file membershipfunctiongenericsingleton.h
 * \class MembershipFunctionGenericSingleton
 * \author Aleksey Myasnikov <AlekseyMyasnikov@yandex.ru>
 * \author pcingola@users.sourceforge.net from Java jFuzzyLogic project
 * \date 2009/04
 * \version 0.83
 * \brief FIXME
 */
#ifndef MEMBERSHIPFUNCTION_GENERIC_SINGLETON_H
#define MEMBERSHIPFUNCTION_GENERIC_SINGLETON_H

#include "membershipfunctiondiscrete.h"

namespace jfuzzyqt{

class MembershipFunctionGenericSingleton : public MembershipFunctionDiscrete
{
    Q_OBJECT

public:
    MembershipFunctionGenericSingleton(QObject* parent, const QList<double>& x, const QList<double>& y);
    ~MembershipFunctionGenericSingleton();
    void debug(const QString& tbs)const;
    int size() const;
    double membership(double index) const;
    QString getName()const;
    bool checkParamters(QString& errors)const;
    void estimateUniverse();
    double valueX(int index)const;

private:
    QList<Value*> x;///<Piece wise linear function values x
    QList<Value*> y;///<Piece wise linear function values y
};

}using namespace jfuzzyqt;

#endif // MEMBERSHIPFUNCTION_GENERIC_SINGLETON_H

