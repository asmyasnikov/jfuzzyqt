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
 * \file membershipfunctiondiscrete.h
 * \class MembershipFunctionDiscrete
 * \author Marco Estanqueiro
 * \author Aleksey Myasnikov
 * \author pcingola@users.sourceforge.net from Java jFuzzyLogic project
 * \date 2009/04
 * \version 0.2
 * \brief FIXME
 */
#ifndef MEMBERSHIPFUNCTIONDISCRETE_H
#define MEMBERSHIPFUNCTIONDISCRETE_H

#include "../membershipfunction.h"

namespace jfuzzyqt{

class MembershipFunctionDiscrete : public MembershipFunction
{
    Q_OBJECT

public:
    MembershipFunctionDiscrete(QObject* parent, MembershipType type);
    ~MembershipFunctionDiscrete();
    virtual int size()const = 0;
    virtual double valueX(int index)const = 0;
private:

};

}using namespace jfuzzyqt;

#endif // MEMBERSHIPFUNCTIONDISCRETE_H
